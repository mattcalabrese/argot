/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_OR_HPP_
#define ARGOT_FUT_OR_HPP_

// TODO(mattcalabrese) Don't use shared_ptr
#include <atomic>
#include <memory>
#include <variant>

namespace argot {
namespace fut {
namespace or_detail {

struct destroy
{
  template< class T >
  constexpr void operator ()( T& arg ) const
  {
    arg.~T();
  }
};

// TODO(mattcalabrese) Analyze atomic operations that are used here.
template< class... ValueTypes >
struct shared_state
{
  ~shared_state()
  {
    std::size_t const index = stored_index.load();

    if( index != sizeof...( ValueTypes ) )
      argot::call( destroy(), prov::access_union( result, index ) );
  }

  template< std::size_t I, class Source >
  constexpr void attempt_set( Source&& source )
  {
    if( bool set_is_initiated_value = false
      ; set_is_initiated.compare_exchange_strong
        ( set_is_initiated_value, true )
      )
    {
      result.template emplace< I >( ARGOT_FORWARD( Source )( source ) );
      stored_index = I;
    }
  }

  destructible_union< ValueTypes... > result;
  std::atomic< std::size_t > stored_index = sizeof...( ValueTypes );
  std::atomic< bool > set_is_initiated = false;
};

template< std::size_t I, class... ValueTypes >
struct continuation
{
  template< class ValueType >
  constexpr void operator()( ValueType&& value ) const
  {
    // TODO(mattcalabrese) Assert that state is not nullptr.
    state->template attempt_set< I >( ARGOT_FORWARD( ValueType )( value ) );
  }

  std::shared_ptr< shared_state< ValueTypes... > > state;
};

} // namespace argot::fut(::or_detail)

struct or_fn
{
  template< class... Futs >
  struct impl;

  template<>
  struct impl
  {
  };

  template< class HeadFut, class... TailFuts >
  struct impl
  {
    ARGOT_ASSERT( Future< HeadFut > );

    HeadFut head;

    impl< TailFuts... > tail;
  };

  template< class... Futs
          , ARGOT_REQUIRES( Future< remove_cvref_t< Futs > > )
                          ( Sinkable< Futs&& > )
                          ()
          >
  constexpr // TODO(mattcalabrese) SFINAE
  operator()( Futs&&... futs )
  {

  }
} inline constexpr or_{};

} // namespace argot(::fut)

template< class... Futs >
struct make_concept_map< Future< fut::or_< Futs... > > >
{
  // TODO(mattcalabrese) Handle references.
  using destructive_value_type_t
    = std::variant< fut_traits::value_type_t< Futs... > >;

  template< class Fun >
  static constexpr auto
  destructive_then( fut::or_< Futs... >&& self, Fun&& fun )
  {
    auto is_set
      = std::allocate_shared< std::atomic< bool > >
  }
};

} // namespace argot

#endif  // ARGOT_FUT_OR_HPP_
