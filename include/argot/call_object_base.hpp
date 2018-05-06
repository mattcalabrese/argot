/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CALL_OBJECT_BASE_HPP_
#define ARGOT_CALL_OBJECT_BASE_HPP_

#include <argot/call.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/declval.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/reducer_traits/is_argument_reducer.hpp>
#include <argot/remove_cvref.hpp>

#include <memory>
#include <type_traits>
#include <utility>

namespace argot {
namespace call_object_base_detail {

template< class Fun, class... P >
using result_of_run_t
  = decltype
    ( remove_cvref_t< Fun >::run
      ( ARGOT_DECLVAL( Fun ), ARGOT_DECLVAL( P )... )
    );

template< class Fun >
struct call_fun_t
{
  ARGOT_CONCEPT_ASSERT( Reference< Fun > );

  using cv_fun = std::remove_reference_t< Fun >;

  template< class... P >
  constexpr result_of_run_t operator ()( P&&... args ) &&
  {
    return cv_fun::run
    ( ARGOT_FORWARD( Fun )( *fun ), ARGOT_FORWARD( P )( args )... );
  }

  cv_fun* fun;
};

template< class Fun >
constexpr call_fun_t< Fun&& > make_call_fun( Fun&& fun ) noexcept
{
  return { std::addressof( fun ) };
}

}  // namespace argot::call_object_base_detail

template< class Fun >
struct call_object_base
{
  // TODO(mattcalabrese) class type
  ARGOT_CONCEPT_ASSERT( UnqualifiedObject< Fun > );

  template< class Reducer >
  struct with_reducer_t
  {
    using bound_call_t = call_t::with_reducer< Reducer >;

    // TODO(mattcalabrese) Check callability
    template< class... P >
    constexpr
    std::invoke_result_t
    < bound_call_t const&, call_fun_t< Fun const& >&&, P&&... >
    operator ()( P&&... args ) const&
    {
      return bound_call
      ( call_object_base_detail::make_call_fun( fun )
      , ARGOT_FORWARD( P )( args )...
      );
    }

    // TODO(mattcalabrese) Check callability
    template< class... P >
    constexpr
    std::invoke_result_t
    < bound_call_t&&, call_fun_t< Fun&& >&&, P&&... >
    operator ()( P&&... args ) &&
    {
      return ARGOT_MOVE( bound_call )
      ( call_object_base_detail::make_call_fun( ARGOT_MOVE( fun ) )
      , ARGOT_FORWARD( P )( args )...
      );
    }

    bound_call_t bound_call;
    Fun fun;
  };

  // TODO(mattcalabrese) Check callability
  template< class... P >
  constexpr result_of_call_t< Fun const&, P... >
  operator ()( P&&... args ) const&
  {
    return call( call_object_base_detail::make_call_fun( fun )
               , ARGOT_FORWARD( P )( args )...
               );
  }

  // TODO(mattcalabrese) Check callability
  template< class... P >
  constexpr result_of_call_t< Fun, P... > operator ()( P&&... args ) &&
  {
    return call( call_object_base_detail::make_call_fun( ARGOT_MOVE( fun ) )
               , ARGOT_FORWARD( P )( args )...
               );
  }

  // TODO(mattcalabrese) Check that Fun is a child type here.
  template< class Reducer >
  constexpr
  ARGOT_REQUIRES( ReturnValueReducer< remove_cvref_t< Reducer > > )
                ( Sinkable< Reducer&& > )
                ( Sinkable< Fun const& > )
  < with_reducer_t< remove_cvref_t< Reducer > > >
  operator []( Reducer&& reducer ) const&
  {
    return { call[ ARGOT_FORWARD( Reducer )( reducer ) ]
           , static_cast< Fun const& >( *this )
           };
  }

  // TODO(mattcalabrese) Check that Fun is a child type here.
  template< class Reducer >
  constexpr
  ARGOT_REQUIRES( ReturnValueReducer< remove_cvref_t< Reducer > > )
                ( Sinkable< Reducer&& > )
                ( Sinkable< Fun&& > )
  < with_reducer_t< remove_cvref_t< Reducer > > >
  operator []( Reducer&& reducer ) &&
  {
    return { call[ ARGOT_FORWARD( Reducer )( reducer ) ]
           , ARGOT_FORWARD( Fun )( *this )
           };
  }
};

}  // namespace argot

#endif  // ARGOT_CALL_OBJECT_BASE_HPP_
