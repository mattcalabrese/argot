/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_FUTURE_STLAB_FUTURE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_FUTURE_STLAB_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_STLAB_FUTURE
#error Included stlab::future concept map header without continuations enabled.
#else

#include <argot/concepts/future/stlab_future.hpp>
#include <argot/gen/make_concept_map.hpp>

#include <stlab/concurrency/future.hpp>

namespace argot {

template< class T >
struct make_concept_map< PersistentFuture< stlab::future< T > > >
{
};

} // namespace argot

#endif  // ARGOT_HAS_STLAB_FUTURE

#endif  // ARGOT_CONCEPTS_PERSISTENT_FUTURE_STLAB_FUTURE_HPP_
