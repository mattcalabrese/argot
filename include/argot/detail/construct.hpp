/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONSTRUCT_HPP_
#define ARGOT_DETAIL_CONSTRUCT_HPP_

#include <argot/concepts/constructible.hpp>
#include <argot/concepts/object.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/forward.hpp>

#include <type_traits>

namespace argot {
namespace detail_argot {

template< class T >
struct construct_fn
{
  template< class... P
          , ARGOT_REQUIRES( Constructible< T, P&&... > )()
          >
  constexpr T operator ()( P&&... args ) const
  noexcept( std::is_nothrow_constructible_v< T, P&&... > )
  {
    return T( ARGOT_FORWARD( P )( args )... );
  }
};

template< class T >
ARGOT_REQUIRES( Object< T > )
< construct_fn< std::remove_cv_t< T > > > constexpr construct{};

}  // namespace argot(::detail_argot)
}  // namespace argot

#endif  // ARGOT_DETAIL_CONSTRUCT_HPP_
