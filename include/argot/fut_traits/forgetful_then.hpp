/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUTURE_TRAITS_FORGETFUL_THEN_HPP_
#define ARGOT_FUTURE_TRAITS_FORGETFUL_THEN_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut_traits/destructive_then.hpp>
#include <argot/fut_traits/persistent_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::fut_traits {

struct forgetful_then_fn
{
  // TODO(mattcalabrese)
  //   Possibly check if we can even sinklike_cast.
  template
  < class Fut, class Exec, class Fun
  , ARGOT_REQUIRES
    ( typename argot_detail::conditional
      < std::is_rvalue_reference_v
        < call_detail::result_of_sinklike_cast_t< Fut&& > >
      >::template meta_apply
      < Future, PersistentFuture
      , detail_argot::remove_cvref_t< Fut >
      >
    )
    ( Executor< detail_argot::remove_cvref_t< Exec > > )
    ( typename argot_detail::conditional
      < std::is_rvalue_reference_v
        < call_detail::result_of_sinklike_cast_t< Fut&& > >
      >::template meta_apply
      < ForgetfulThenable, PersistentForgetfulThenable
      , detail_argot::remove_cvref_t< Fut >, detail_argot::remove_cvref_t< Exec >
      >
    )
    ( Sinkable< Exec&& > )
    ( DecaySinkable< Fun&& > )
    ( InvocableWith
      < std::decay_t< Fun&& >
      , value_type_t< std::remove_reference_t< Fut > >
      >
    )
    ()
  >
  constexpr void operator ()( Fut&& provider, Exec&& exec, Fun&& fun ) const
  {
    using RawFut = detail_argot::remove_cvref_t< Fut >;

    using QualifiedFut
      = call_detail::result_of_sinklike_cast_t< Fut&& >;

    // TODO(mattcalabrese) Perform the decay_sink as a cast to avoid moves
    if constexpr( std::is_rvalue_reference_v< QualifiedFut > )
      return access_raw_concept_map
      < ForgetfulThenable< RawFut, detail_argot::remove_cvref_t< Exec > > >
      ::forgetful_then( static_cast< QualifiedFut >( provider )
                      , call_detail::forward_and_sink< Exec >( exec )
                      , call_detail::forward_and_decay_sink< Fun >( fun )
                      );
    else
      return access_raw_concept_map
      < PersistentForgetfulThenable< RawFut, detail_argot::remove_cvref_t< Exec > > >
      ::forgetful_then( static_cast< QualifiedFut >( provider )
                      , call_detail::forward_and_sink< Exec >( exec )
                      , call_detail::forward_and_decay_sink< Fun >( fun )
                      );
  }
} inline constexpr forgetful_then{};

template< class Fut, class Exec, class Fun >
using result_of_forgetful_then_t
  = basic_result_of_t< forgetful_then_fn const&, Fut, Exec, Fun >;

template< class Fut, class Exec, class Fun >
using result_of_forgetful_then
  = basic_result_of< forgetful_then_fn const&, Fut, Exec, Fun >;

} // namespace (argot::fut_traits)

#endif  // ARGOT_FUTURE_TRAITS_FORGETFUL_THEN_HPP_
