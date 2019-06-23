/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_TRAITS_PERSISTENT_FORGETFUL_THEN_HPP_
#define ARGOT_FUT_TRAITS_PERSISTENT_FORGETFUL_THEN_HPP_

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/fut_traits/destructive_forgetful_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::fut_traits {

// TODO(mattcalabrese) Require syncability of value_type_t?
struct persistent_forgetful_then_fn
{
 public:
  template
  < class Fut, class Exec, class Fun
  , ARGOT_REQUIRES
    ( PersistentFuture< Fut > )
    ( Executor< detail_argot::remove_cvref_t< Exec > > )
    ( PersistentForgetfulThenable< Fut, detail_argot::remove_cvref_t< Exec > > )
    ( InvocableWith< std::decay_t< Fun&& >, value_type_t< Fut >&& > )
    ( InvocableWith< std::decay_t< Fun&& >, value_type_t< Fut > const& > )
    ( Sinkable< Exec&& > )
    ( DecaySinkable< Fun&& > )
    ()
  >
  constexpr void operator ()( Fut const& self, Exec&& exec, Fun&& fun ) const
  {
    access_raw_concept_map
    < PersistentForgetfulThenable< Fut, detail_argot::remove_cvref_t< Exec > > >
    ::forgetful_then
    ( self
    , call_detail::forward_and_sink< Exec >( exec )
    , call_detail::forward_and_decay_sink< Fun >( fun )
    );
  }
} inline constexpr persistent_forgetful_then{};

template< class Fut, class Exec, class Fun >
using result_of_persistent_forgetful_then_t
  = basic_result_of_t< persistent_forgetful_then_fn const&, Fut, Exec, Fun >;

template< class Fut, class Exec, class Fun >
using result_of_persistent_forgetful_then
  = basic_result_of< persistent_forgetful_then_fn const&, Fut, Exec, Fun >;

} // namespace (argot::fut_traits)

#endif  // ARGOT_FUT_TRAITS_PERSISTENT_FORGETFUL_THEN_HPP_
