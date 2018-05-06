/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_WHEN_ANY_HPP_
#define ARGOT_CONC_WHEN_ANY_HPP_

#include <argot/conc/when_ready.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/ready_future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/destructive_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/as.hpp>
#include <argot/remove_cvref.hpp>

// TODO(mattcalabrese) Don't use shared_ptr
#include <atomic>
#include <cstddef>
#include <memory>

namespace argot {
namespace conc {
namespace detail_when_any {

enum class multithreaded { no, yes };

template< class LeadingValueTypes, class TrailingValueTypes, class ValueType >
struct provider;

template< class... LeadingValueTypes, class... TrailingValueTypes
        , class ValueType
        >
struct provider
{
  ARGOT_NO_UNIQUE_ADDRESS ValueType value;
};

// TODO(mattcalabrese) Template based on whether or not it is multithreaded.
template< multithreaded Multithreaded, class Fun, class... ValueTypes >
struct state;

template< class Fun, class... ValueTypes >
struct state< Multithreaded::yes, Fun, ValueTypes... >
{
  // TODO(mattcalabrese) Concept asserts on callability.

  std::atomic< std::size_t > futures_left;
  std::atomic_flag result_is_ready = ATOMIC_FLAG_INIT;
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;

  template< std::size_t I, class ValueTypeP >
  void set( ValueTypeP&& arg )
  {
    // If we didn't already receive a result...
    if( !result_is_ready.test_and_set() )
      ARGOT_MOVE( fun )( /*TODO(mattcalabrese) Form provider*/ );
  }

  // TODO(mattcalabrese) Handle exceptions
};

}  // namespace argot::conc(::detail_when_any)

struct when_any_fn
{
 private:
  template< class Alloc >
  struct with_allocator
  {
    // TODO(mattcalabrese) Assert Alloc is an allocator.

    template< class Fut
            , ARGOT_REQUIRES( Future< remove_cvref_t< Fut > >... )
                            ( Sinkable< Fut&& > )
                            ()
            >
    [[nodiscard]] constexpr auto operator()( Fut&& fut ) const;

    ARGOT_NO_UNIQUE_ADDRESS Alloc alloc;
  };

  template< Alloc, class... Futs >
  struct impl;

  template< class Alloc, class HeadFut >
  struct impl< Alloc, HeadFut >
  {
    ARGOT_CONCEPT_ASSERT( Future< HeadFut > );

    template< detail_when_any::multithreaded Multithreaded, class Fun >
    using state_t
      = detail_when_any::state
        < Multithreaded, Fun, fut_traits::value_type_t< HeadFut > >;

    ARGOT_NO_UNIQUE_ADDRESS Alloc alloc;
    ARGOT_NO_UNIQUE_ADDRESS HeadFut head;
  };

  template< class Alloc, class HeadFut, class NextFut, class... TailFuts >
  struct impl< Alloc, HeadFut, NextFut, TailFuts... >
  {
    ARGOT_CONCEPT_ASSERT( Future< HeadFut > );

    template< detail_when_any::multithreaded Multithreaded, class Fun >
    using state_t
      = detail_when_any::state
        < Multithreaded, Fun
        , fut_traits::value_type_t< HeadFut >
        , fut_traits::value_type_t< NextFut >
        , fut_traits::value_type_t< TailFuts >...
        >;

    ARGOT_NO_UNIQUE_ADDRESS HeadFut head;
    ARGOT_NO_UNIQUE_ADDRESS impl< NextFut, TailFuts... > tail;
  };

  template< class Fut >
  static constexpr auto exceptional_impl( Fut&& fut );

  template< class Fut >
  static constexpr auto basic_impl( Fut&& fut )
  {
    return conc::when_ready( ARGOT_FORWARD( Fut )( fut ) );
  }

  // TODO(mattcalabrese) Expand out argument lists to some length N
  template< class HeadFut, class... TailFuts >
  static constexpr
  auto always_ready_value_impl( HeadFut&& head_fut, TailFuts&&... tail_futs )
  {
    if constexpr
    ( ARGOT_IS_MODELED_V( ReadyValueFuture< remove_cvref_t< HeadFut > > ) )
      return conc::when_ready( ARGOT_FORWARD( HeadFut )( head_fut ) );
    else
      return always_ready_impl( ARGOT_FORWARD( TailFuts )( tail_futs )... );
  }
 public:
  // TODO(mattcalabrese)
  //   Handle the ReadyFuture case where they may be exceptional at runtime.
  //   Make the implementation branch when all futures are statically ready.
  //   Make the implementation branch when all but one future is statically
  //     ready.
  template< class HeadFut, class... TailFuts
          , ARGOT_REQUIRES( Future< remove_cvref_t< HeadFut > >... )
                          ( Future< remove_cvref_t< TailFuts > >... )
                          ( Sinkable< HeadFut&& > )
                          ( Sinkable< TailFuts&& >... )
                          ()
          >
  [[nodiscard]]
  constexpr auto operator()( HeadFut&& head_fut, TailFuts&&... tail_futs ) const
  {
    // If any of the futures is an "always ready", non-exceptional future...
    if constexpr
    (    ARGOT_IS_MODELED_V( ReadyValueFuture< remove_cvref_t< HeadFut > > )
      || (    ARGOT_IS_MODELED_V
              ( ReadyValueFuture< remove_cvref_t< TailFuts > > )
           || ...
         )
    )
      return always_ready_impl
      ( ARGOT_FORWARD_AND_SINK( HeadFut )( head_fut )
      , ARGOT_FORWARD_AND_SINK( TailFuts )( tail_futs )...
      );
    else if constexpr  // Else, if all are "always ready" exceptional futures...
    (    ARGOT_IS_MODELED_V
         ( ReadyExceptionalFuture< remove_cvref_t< HeadFut > > )
      && (    ARGOT_IS_MODELED_V
              ( ReadyExceptionalFuture< remove_cvref_t< TailFuts > > )
           && ...
         )
    )
      return exceptional_impl( ARGOT_FORWARD_AND_SINK( HeadFut )( head_fut ) );
    else if constexpr( sizeof...( TailFuts ) == 0 )
      return conc::when_ready( ARGOT_FORWARD_AND_SINK( HeadFut )( head_fut ) );
    else
      return basic_impl
      ( ARGOT_FORWARD_AND_SINK( HeadFut )( head_fut )
      , ARGOT_FORWARD_AND_SINK( TailFuts )( tail_futs )...
      );
  }
} inline constexpr when_any{};

} // namespace argot(::conc)

template< class LeadingValueTypes, class TrailingValueTypes, class ValueType >
struct make_concept_map
< ArgumentProvider
  < conc::detail_when_any::provider
    < LeadingValueType, TrailingValueTypes, ValueType >
  >
>
{
  template< class Receiver >
  static constexpr decltype( auto )
  provide( conc::detail_when_any::provider
           < LeadingValueType, TrailingValueTypes, ValueType >&& self
         , Receiver&& rec
         )
  {
    return receiver_traits::receive_branch
    ( ARGOT_FORWARD( Receiver )( rec )
    , LeadingValueTypes(), TrailingValueTypes()
    , ARGOT_FORWARD( ValueType )( self.value )
    );
  }
};

} // namespace argot

#endif  // ARGOT_CONC_WHEN_ANY_HPP_
