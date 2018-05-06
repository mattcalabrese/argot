/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_TRAITS_DESTRUCTIVE_GET_HPP_
#define ARGOT_FUT_TRAITS_DESTRUCTIVE_GET_HPP_

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor_traits/execute.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot::fut_traits {
namespace detail_destructive_get {

template< class Fun, class ValueType >
struct bound_function
{
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType&& > );

  Fun fun;
  ValueType arg;  // TODO(mattcalabrese) Use holder to account for references

  constexpr void operator ()() &&
  {
    (void)argot_detail::constexpr_invoke
    ( ARGOT_MOVE( fun ), ARGOT_FORWARD( ValueType )( arg ) );
  }
};

template< class Exec, class Fun, class ValueType >
struct continuation
{
  ARGOT_CONCEPT_ASSERT( Executor< Exec > );
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType&& > );
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType const& > );

  // TODO(mattcalabrese) Require argument syncability
  constexpr void operator ()( ValueType&& arg ) &&
  {
    (void)executor_traits::execute
    ( ARGOT_MOVE( exec )
    , bound_function< Fun, ValueType >{ ARGOT_MOVE( fun ), ARGOT_MOVE( arg ) }
    );
  }

  // TODO(mattcalabrese) Require argument syncability
  constexpr void operator ()( ValueType const& arg ) &&
  {
    (void)executor_traits::execute
    ( ARGOT_MOVE( exec )
    , bound_function< Fun, ValueType >{ ARGOT_MOVE( fun ), arg }
    );
  }

  Exec exec;
  Fun fun;
};

template< class Exec, class Fun, class ValueType >
struct continuation< Exec, Fun, ValueType& >
{
  ARGOT_CONCEPT_ASSERT( Executor< Exec > );
  ARGOT_CONCEPT_ASSERT( InvocableObjectWith< Fun, ValueType& > );

  constexpr void operator ()( ValueType& arg ) &&
  {
    (void)executor_traits::execute
    ( ARGOT_MOVE( exec )
    , bound_function< Fun, ValueType >{ ARGOT_MOVE( fun ), arg }
    );
  }

  Exec exec;
  Fun fun;
};

}  // namespace detail_destructive_get

// TODO(mattcalabrese) Require syncability of value_type_t?
struct destructive_get_fn
{
 private:
  struct dummy_t {};

  template< class ValueType >
  union result_holder_trivial_destructor_t
  {
    constexpr result_holder_t() : dummy() {}
    dummy_t dummy;
    call_detail::holder< ValueType > result;
  };


  template< class ValueType >
  union result_holder_nontrivial_destructor_t
  {
    constexpr result_holder_t() : dummy() {}
    dummy_t dummy;
    call_detail::holder< ValueType > result;
  };

  template< class ValueType >
  using result_holder_t
    = typename argot_detail::conditional
      < std::is_trivially_destructible_v< holder< ValueType > > >
      ::template meta_apply
      < result_holder_trivial_destructor_t
      , result_holder_nontrivial_destructor_t
      , ValueType
      >;
 public:
  template
  < class Fut
  , ARGOT_REQUIRES( Future< Fut > )
                  ( Semaphore< Fut > )
                  ()
  >
  constexpr decltype( auto ) operator ()( Fut&& self ) const
  {
    using value_type = fut_traits::value_type_t< Fut >;

    result_holder_t result;

    access_raw_concept_map< Future< Fut > >::get
    ( ARGOT_MOVE( self )
    , detail_destructive_get::continuation
      < remove_cvref_t< Exec >, std::decay_t< Fun >, value_type_t< Fut > >
      { call_detail::forward_and_sink< Exec >( exec )
      , call_detail::forward_and_decay_sink< Fun >( fun )
      }
    );

    if constexpr( std::is_rvalue_reference_v< value_type > )
      return ARGOT_MOVE( result );
    else
      return result;
  }
} inline constexpr destructive_get{};

template< class Fut, class Fun >
using result_of_destructive_get_t
  = basic_result_of_t< destructive_get_fn const&, Fut, Fun >;

template< class Fut, class Fun >
using result_of_destructive_get
  = basic_result_of< destructive_get_fn const&, Fut, Fun >;

} // namespace (argot::fut_traits)

#endif  // ARGOT_FUT_TRAITS_DESTRUCTIVE_GET_HPP_
