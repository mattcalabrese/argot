/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_FUTURE_DETAIL_BOOST_SHARED_FUTURE_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_FUTURE_DETAIL_BOOST_SHARED_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#error Included boost::shared_future concept map header without continuations enabled.
#else

#include <argot/concepts/persistent_future.hpp>
#include <argot/gen/make_concept_map.hpp>

#include <boost/thread/future.hpp>

namespace argot {

template< class T >
struct make_concept_map< PersistentFuture< boost::shared_future< T > > >
{
};

} // namespace argot

#endif  // ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION

#endif  // ARGOT_CONCEPTS_PERSISTENT_FUTURE_DETAIL_BOOST_SHARED_FUTURE_HPP_
