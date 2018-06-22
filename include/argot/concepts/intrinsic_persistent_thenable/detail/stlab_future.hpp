/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_INTRINSIC_PERSISTENT_THENABLE_STLAB_FUTURE_HPP_
#define ARGOT_CONCEPTS_INTRINSIC_PERSISTENT_THENABLE_STLAB_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_STLAB_FUTURE
#error Included stlab::future concept map header without continuations enabled.
#else

#include <argot/concepts/future.hpp>
#include <argot/concepts/intrinsic_thenable/detail/stlab_future.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/move.hpp>
#include <argot/void_.hpp>

#include <stlab/concurrency/future.hpp>

#include <type_traits>

namespace argot {

// TODO(mattcalabrese) Require copyability of the T, or T is a void type
// TODO(mattcalabrese) Constrain "Fun" ?
template< class T, class Exec >
struct make_concept_map
< IntrinsicPersistentThenable< stlab::future< T >, packager::stlab, Exec >
, ARGOT_REQUIRES( Executor< Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class ExecP, class Fun >
  static constexpr auto
  then( stlab::future< T > const& self, ExecP&& exec, Fun&& fun )
  {
    return self.then
    ( detail_thenable_stlab_future::to_stlab_executor
      ( call_detail::forward_and_sink< ExecP >( exec ) )
    , detail_thenable_stlab_future::continuation
      < Fun, fut_traits::value_type_t< stlab::future< T > > >
      { ARGOT_MOVE( fun ) }
    );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_STLAB_FUTURE

#endif  // ARGOT_CONCEPTS_INTRINSIC_PERSISTENT_THENABLE_STLAB_FUTURE_HPP_
