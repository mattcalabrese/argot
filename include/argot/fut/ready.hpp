/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_READY_HPP_
#define ARGOT_FUT_READY_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/remove_cvref.hpp>

namespace argot {
namespace fut {
  /*
namespace ready_detail {

template< class Fun, class... P >
constexpr impl< basic_result_of_t< Fun&&, P&&... > >
make_from_result( Fun&& fun, P&&... args )
{
  return { ARGOT_MOVE( fun )( ARGOT_FORWARD( P )( args )... ) };
}

template< class Fun, class T >
struct immediate_function
{
  // TODO(mattcalabrese) Concept assert that fun and arg are references.

  constexpr basic_result_of_t< Fun&&, P&&... > operator ()() &&
  {
    return ARGOT_FORWARD( Fun )( fun )( ARGOT_FORWARD( T )( arg ) );
  }

  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  ARGOT_NO_UNIQUE_ADDRESS T arg;
};

} // namespace argot::fut(::ready_detail)
*/

struct ready_fn
{
  template< class T >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( UnqualifiedObject< T > );

    ARGOT_NO_UNIQUE_ADDRESS T value;
  };

  template< class T
          , ARGOT_REQUIRES( Sinkable< T&& > )()
          >
  [[nodiscard]] constexpr auto operator ()( T&& source ) const
  {
    // TODO(mattcalabrese) Don't use forward and sink, allow conversions.
    return impl< remove_cvref_t< T > >
    { call_detail::forward_and_sink< T >( source ) };
  }

} inline constexpr ready{};

template< class T >
using result_of_ready_t = basic_result_of_t< ready_fn const&, T >;

template< class T >
using result_of_ready = basic_result_of< ready_fn const&, T >;

} // namespace argot(::fut)

template< class T >
struct make_concept_map< Future< fut::ready_fn::impl< T > > >
{
  using value_type_t = T;
};

template< class T >
struct make_concept_map
< ForgetfulThenable< fut::ready_fn::impl< T >, executor::immediate_t > >
{
  template< class Fun >
  static constexpr void forgetful_then
  ( fut::ready_fn::impl< T >&& self, executor::immediate_t, Fun&& fun )
  {
    (void)ARGOT_FORWARD( Fun )( fun )( ARGOT_MOVE( self.value ) );
  }
};

// TODO(mattcalabrese) Possibly require copyable
template< class T >
struct make_concept_map< PersistentFuture< fut::ready_fn::impl< T > > >
{
};

template< class T >
struct make_concept_map
< PersistentForgetfulThenable
  < fut::ready_fn::impl< T >, executor::immediate_t >
>
{
  template< class Fun >
  static constexpr void forgetful_then
  ( fut::ready_fn::impl< T > const& self, executor::immediate_t, Fun&& fun )
  {
    (void)ARGOT_FORWARD( Fun )( fun )( self.value );
  }
};

// TODO(mattcalabrese) Uncomment once the ready_as version is done.
#if 0

template< class T, class FutPackager, class Exec >
struct make_concept_map
< Thenable< fut::ready_fn::impl< T >, packager::ready, Exec >
, ARGOT_REQUIRES( ImmediateExecutor< Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class ExecP, class Fun >
  static constexpr auto
  then( fut::ready_detail::impl< T >&& self, ExecP&& exec, Fun&& fun )
  {
    return fut::ready_detail::impl< basic_result_of_t< Fun&&, T&& > >
    { executor_traits::execute_immediately
      ( ARGOT_FORWARD( ExecP )( exec )
      , fut::ready_detail::immediate_function< Fun&&, T&& >
        { ARGOT_FORWARD( Fun )
        , ARGOT_MOVE( self.value )
        }
      )
    };
  }
};

// TODO(mattcalabrese) Possibly require copyable
template< class T, class FutPackager, class Exec >
struct make_concept_map
< PersistentThenable< fut::ready_fn::impl< T >, packager::ready, Exec >
, ARGOT_REQUIRES( ImmediateExecutor< Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class ExecP, class Fun >
  static constexpr auto
  then( fut::ready_detail::impl< T > const& self, ExecP&& exec, Fun&& fun )
  {
    return fut::ready_detail::impl< basic_result_of_t< Fun&&, T&& > >
    { executor_traits::execute_immediately
      ( ARGOT_FORWARD( ExecP )( exec )
      , fut::ready_detail::immediate_function< Fun&&, T&& >
        { ARGOT_FORWARD( Fun )
        , self.value
        }
      )
    };
  }
};

#endif

} // namespace argot

#endif  // ARGOT_FUT_READY_HPP_
