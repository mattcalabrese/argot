/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_STLAB_FUTURE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_STLAB_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_STLAB_FUTURE
#error Included stlab::future concept map header without continuations enabled.
#else

#include <argot/concepts/forgetful_thenable/stlab_future.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/move.hpp>

#include <stlab/concurrency/future.hpp>
#include <stlab/concurrency/immediate_executor.hpp>

namespace argot {

template< class T >
struct make_concept_map
< PersistentForgetfulThenable< stlab::future< T >, executor::immediate_t > >
{
  // TODO(mattcalabrese) Constrain
  template< class Fun >
  static constexpr void forgetful_then
  ( stlab::future< T > const& self, executor::immediate_t, Fun&& fun )
  {
    (void)ARGOT_MOVE( self ).then
    ( stlab::immediate_executor
    , detail_future_stlab_future::continuation
      < Fun, fut_traits::value_type_t< stlab::future< T > > >
      { ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_STLAB_FUTURE

#endif  // ARGOT_CONCEPTS_PERSISTENT_FORGETFUL_THENABLE_STLAB_FUTURE_HPP_
