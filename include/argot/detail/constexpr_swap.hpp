/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONSTEXPR_SWAP_HPP_
#define ARGOT_DETAIL_CONSTEXPR_SWAP_HPP_

#include <argot/detail/detection.hpp>
#include <argot/move.hpp>

#include <type_traits>

// NOTE: Intentionally not nested in argot namespace for name lookup.
namespace detail_argot_swap {

template< class T
        , argot::call_detail::fast_enable_if_t< std::is_swappable_v< T >, int >
            = 0
        >
constexpr void constexpr_swap( T& lhs, T& rhs )
  noexcept( std::is_nothrow_swappable_v< T > )
{
  if constexpr( std::is_array_v< T > )
    for( std::decay_t< T > lhs_it = lhs, rhs_it = rhs
       ; lhs_it != lhs + sizeof( T ) / sizeof( lhs[ 0 ] )
       ; ++lhs_it, ++rhs_it
       )
      ( constexpr_swap )( *lhs_it, *rhs_it );
  else
    if constexpr( std::is_scalar_v< T > )
    {
      T const temp = lhs;
      lhs = rhs;
      rhs = temp;
    }
    else
    {
      using std::swap;
      swap( lhs, rhs );
    }
}

} // namespace detail_argot_swap

#endif  // ARGOT_DETAIL_CONSTEXPR_SWAP_HPP_
