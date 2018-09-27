/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_VARIADIC_AT_HPP_
#define ARGOT_DETAIL_VARIADIC_AT_HPP_

#include <cstddef>

namespace argot::argot_detail {

template< bool ElementIsFound >
struct variadic_at_impl;

template<>
struct variadic_at_impl< /*ElementIsFound =*/ false >
{
  template< std::size_t I, class H, class... T >
  using apply
    = typename variadic_at_impl< I == 1 >::template apply< I - 1, T... >;
};

template<>
struct variadic_at_impl< /*ElementIsFound =*/ true >
{
  template< std::size_t I, class H, class... T >
  using apply = H;
};

template< std::size_t I, class... T >
using variadic_at_t
  = typename variadic_at_impl< I == 0 >::template apply< I, T... >;

} // namespace (argot::argot_detail)

#endif  // ARGOT_DETAIL_VARIADIC_AT_HPP_
