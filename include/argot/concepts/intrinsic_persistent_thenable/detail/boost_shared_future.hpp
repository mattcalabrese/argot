/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_INTRINSIC_PERSISTENT_THENABLE_BOOST_SHARED_FUTURE_HPP_
#define ARGOT_CONCEPTS_INTRINSIC_PERSISTENT_THENABLE_BOOST_SHARED_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#error Included boost::shared_future concept map header without continuations enabled.
#else

#include <argot/concepts/future.hpp>
#include <argot/concepts/intrinsic_thenable/detail/boost_shared_future.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/move.hpp>
#include <argot/packager/boost_shared_future.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/void_.hpp>

#include <boost/thread/future.hpp>

#include <type_traits>

namespace argot {

template< class T, class Exec >
struct make_concept_map
< IntrinsicPersistentThenable
  < boost::shared_future< T >, packager::boost_shared_future, Exec >
, ARGOT_REQUIRES( Executor< Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class Fun >
  static constexpr auto
  then( boost::shared_future< T > const& self, Exec const& exec, Fun&& fun )
  {
    return self.then
    ( boost::launch::sync
    , detail_future_boost_shared_future::continuation
      < remove_cvref_t< Fun >
      , fut_traits::value_type_t< boost::shared_future< T > >
      >{ ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION

#endif  // ARGOT_CONCEPTS_INTRINSIC_PERSISTENT_THENABLE_BOOST_SHARED_FUTURE_HPP_
