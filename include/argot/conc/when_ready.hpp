/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_WHEN_READY_HPP_
#define ARGOT_CONC_WHEN_READY_HPP_

#include <argot/conc/bless_result.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/persistent_concurrent_argument_provider.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/fut/augment.hpp>
#include <argot/fut_traits/destructive_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/as.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot {
namespace conc {

struct when_ready_fn
{
 public:
  template< class Fut >
  struct to_argument_provider
  {
    ARGOT_CONCEPT_ASSERT( Future< Fut > );

    template< class ValueType >
    constexpr auto operator()( ValueType&& value ) &&
    {
      return prov::as< fut_traits::value_type_t< detail_argot::remove_cvref_t< Fut > > >
      ( ARGOT_FORWARD( ValueType )( value ) );
    }
  };

  template< class Fut >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Future< Fut > );

    ARGOT_NO_UNIQUE_ADDRESS Fut fut;
  };
 public:
  template< class Fut
          , ARGOT_REQUIRES( Future< detail_argot::remove_cvref_t< Fut > > )
                          ( Sinkable< Fut&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator()( Fut&& fut ) const
  {
    // TODO(mattcalabrese) bless in place
    return conc::bless_result
    ( fut::augment
    , ARGOT_FORWARD( Fut )( fut )
    , to_argument_provider< detail_argot::remove_cvref_t< Fut > >()
    );
  }
} inline constexpr when_ready{};

template< class Fut >
using result_of_when_ready_t = basic_result_of_t< when_ready_fn const&, Fut >;

template< class Fut >
using result_of_when_ready = basic_result_of< when_ready_fn const&, Fut >;

} // namespace argot(::conc)

template< class Fut >
struct make_concept_map
< ConcurrentArgumentProvider< conc::when_ready_fn::impl< Fut > > >
{
  template< class Rec >
  static constexpr auto
  then_provide( conc::when_ready_fn::impl< Fut >&& self, Rec&& rec )
  {
    return fut::augment
    ( ARGOT_MOVE( self.fut )
    , [ rec = ARGOT_MOVE( rec ) ]( auto&& arg ) mutable
      {
        return receiver_traits::receive
        ( ARGOT_FORWARD( Rec )( rec )
        , prov::as< fut_traits::value_type_t< Fut > >
          ( ARGOT_FORWARD( decltype( arg ) )( arg ) )
        );
      }
    );
  }
};

template< class Fut >
struct make_concept_map
< PersistentConcurrentArgumentProvider< conc::when_ready_fn::impl< Fut > >
, ARGOT_REQUIRES( PersistentFuture< Fut > )<>
>
{
  template< class Rec >
  static constexpr auto
  then_provide( conc::when_ready_fn::impl< Fut > const& self, Rec&& rec )
  {
    return fut::augment
    ( self.fut
    , [ rec = ARGOT_MOVE( rec ) ]( auto&& arg ) mutable
      {
        return receiver_traits::receive
        ( ARGOT_FORWARD( Rec )( rec )
        , prov::as< fut_traits::value_type_t< Fut > >
          ( ARGOT_FORWARD( decltype( arg ) )( arg ) )
        );
      }
    );
  }
};

} // namespace argot

#endif  // ARGOT_CONC_WHEN_READY_HPP_
