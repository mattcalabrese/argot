/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_SQUASH_HPP_
#define ARGOT_FUT_SQUASH_HPP_

#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/higher_order_future.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/forward.hpp>
#include <argot/fut_traits/forgetful_then.hpp>
#include <argot/fut_traits/then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot {
namespace fut {
namespace squash_detail {

template< class Exec, class Fun >
struct forgetful_continuation
{
  // TODO(mattcalabrese) Concept assert

  template< class Fut >
  constexpr void operator ()( Fut&& fut ) &&
  {
    fut_traits::forgetful_then
    ( ARGOT_FORWARD( Fut )( fut )
    , ARGOT_MOVE( exec )
    , ARGOT_MOVE( fun )
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Exec exec;
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
};

template< class Exec, class Fun >
struct continuation
{
  // TODO(mattcalabrese) Concept assert

  template< class Fut >
  constexpr decltype( auto ) operator ()( Fut&& fut ) &&
  {
    return fut_traits::forgetful_then
    ( ARGOT_FORWARD( Fut )( fut )
    , ARGOT_MOVE( exec )
    , ARGOT_MOVE( fun )
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Exec exec;
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
};

}  // namespace argot(::fut::squash_detail)

struct squash_t
{
  template< class FutFut >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( HigherOrderFuture< FutFut > );

    ARGOT_NO_UNIQUE_ADDRESS FutFut futfut;
  };

  template< class FutFut
          , ARGOT_REQUIRES( HigherOrderFuture< FutFut > )
                          ( Sinkable< FutFut&& > )
                          ()
          >
  [[nodiscard]]
  constexpr auto operator()( FutFut&& futfut ) const
  {
    return impl< detail_argot::remove_cvref_t< FutFut > >
    { call_detail::forward_and_sink< FutFut >( futfut ) };
  }
} inline constexpr squash{};

// TODO(mattcalabrese) result calculators

}  // namespace argot(::fut)

template< class FutFut >
struct make_concept_map< Future< fut::squash_t::impl< FutFut > > >
{
  using value_type_t
    = fut_traits::value_type_t< fut_traits::value_type_t< FutFut > >;
};

template< class FutFut, class Exec >
struct make_concept_map
< ForgetfulThenable< fut::squash_t::impl< FutFut >, Exec >
, ARGOT_REQUIRES
  ( Executor< Exec > )
  ( ForgetfulThenable< FutFut, executor::immediate_t > )
  ( ForgetfulThenable // TODO(mattcalabrese) Handle reference value types
    < fut_traits::value_type_t< FutFut >
    , Exec
    >
  )
  <>
>
{
  template< class ExecP, class Fun >
  static constexpr void forgetful_then
  ( fut::squash_t::impl< FutFut >&& self, ExecP&& exec, Fun&& fun )
  {
    access_raw_concept_map
    < ForgetfulThenable< FutFut, executor::immediate_t > >::forgetful_then
    ( ARGOT_MOVE( self.futfut )
    , executor::immediate
    , fut::squash_detail::forgetful_continuation< Exec, detail_argot::remove_cvref_t< Fun > >
      { ARGOT_FORWARD( ExecP )( exec ), ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

template< class FutFut >
struct make_concept_map
< PersistentFuture< fut::squash_t::impl< FutFut > >
, ARGOT_REQUIRES( PersistentFuture< FutFut > )<>
>
{
};


template< class FutFut, class Exec >
struct make_concept_map
< PersistentForgetfulThenable
  < fut::squash_t::impl< FutFut >, Exec >
, ARGOT_REQUIRES
  ( PersistentFuture< FutFut > )
  ( Executor< Exec > )
  ( PersistentForgetfulThenable< FutFut, executor::immediate_t > )
  ( ForgetfulThenable  // TODO(mattcalabrese) Handle reference value types
    < fut_traits::value_type_t< FutFut >
    , Exec
    >
  )
  <>
>
{
  template< class ExecP, class Fun >
  static constexpr void forgetful_then
  ( fut::squash_t::impl< FutFut > const& self, ExecP&& exec, Fun&& fun )
  {
    access_raw_concept_map
    < PersistentForgetfulThenable< FutFut, executor::immediate_t > >
    ::forgetful_then
    ( self.futfut
    , executor::immediate
    , fut::squash_detail::forgetful_continuation< Exec, detail_argot::remove_cvref_t< Fun > >
      { ARGOT_FORWARD( ExecP )( exec ), ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

// TODO(mattcalabrese) Support intrinsic thenable

#if 0

template< class FutFut, class Fpackager, class Exec >
struct make_concept_map
< IntrinsicThenable< fut::squash_t::impl< FutFut >, FPackager, Exec >
, ARGOT_REQUIRES
  ( IntrinsicThenable< fut_traits::value_type_t< FutFut >, FPackager, Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class ExecP, class Fun >
  static constexpr void
  then( fut::squash_t::impl< FutFut >&& self, ExecP&& exec, Fun&& fun )
  {
    return fut::squash
    ( fut_traits::then
      ( ARGOT_MOVE( self.futfut )
      , fut::squash_detail::continuation< detail_argot::remove_cvref_t< Fun > >
        { ARGOT_FORWARD( Fun )( fun ) }
      )
    );
  }
};

#endif

}  // namespace argot

#endif  // ARGOT_FUT_SQUASH_HPP_
