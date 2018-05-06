/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REMOVE_CVREF_HPP_
#define ARGOT_REMOVE_CVREF_HPP_

#include <type_traits>

namespace argot {

template< class T >
struct remove_cvref
{
  using type = std::remove_cv_t< std::remove_reference_t< T > >;
};

template< class T >
using remove_cvref_t = typename remove_cvref< T >::type;

template< class T >
struct is_unqualified
  : std::is_same< remove_cvref_t< T >, T >::type{};

// TODO(mattcalabrese) Use is_same_v form
template< class T >
bool constexpr is_unqualified_v
  = std::is_same< remove_cvref_t< T >, T >::value;

}  // namespace argot

#endif  // ARGOT_REMOVE_CVREF_HPP_
