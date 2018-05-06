/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FUTURE_LIKE_FUTURE_LIKE_BOOST_FUTURE_HPP_
#define ARGOT_CONCEPTS_FUTURE_LIKE_FUTURE_LIKE_BOOST_FUTURE_HPP_

#include <argot/fut_traits/config.hpp>

#ifndef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#error Included boost::future concept map header without continuations enabled.
#else

#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/future_like/immediate_boost_executor.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/void_.hpp>

#include <boost/thread/future.hpp>

#include <type_traits>

namespace argot {

template< class T >
struct make_concept_map< Future< boost::future< T > > >
{
  using value_type_t
    = typename argot_detail::conditional< std::is_void_v< T > >
      ::template half_meta_apply< void_to_regular_void_t, T, T >;

  // TODO(mattcalabrese) Constrain
  // TODO(mattcalabrese) Rewrite this to use an immediate executor.
  template< class Fun >
  static constexpr decltype( auto )
  then( boost::future< T >&& self, Fun&& fun )
  {
    // TODO(mattcalabrese) Perform the decay_sink as a cast to avoid moves
    return ARGOT_MOVE( self ).then
    ( boost::launch::sync
    , [ fun = call_detail::decay_sink( ARGOT_FORWARD( Fun )( fun ) ) ]
      ( boost::future< T >&& self_arg ) mutable -> decltype( auto )
      {
        if constexpr( std::is_void_v< T > )
        {
          ARGOT_MOVE( self_arg ).get();
          return argot_detail::constexpr_invoke( ARGOT_MOVE( fun ), void_() );  // TODO(mattcalabrese) Fix qualifiers
        }
        else
          return argot_detail::constexpr_invoke
          ( ARGOT_MOVE( fun ), ARGOT_MOVE( self_arg ).get() );
      }
    );
  }
};

} // namespace argot

#endif  // ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION

#endif  // ARGOT_CONCEPTS_FUTURE_LIKE_FUTURE_LIKE_BOOST_FUTURE_HPP_
