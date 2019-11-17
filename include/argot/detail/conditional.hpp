/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONDITIONAL_HPP_
#define ARGOT_DETAIL_CONDITIONAL_HPP_

#include <cstddef>

namespace argot::argot_detail {

template< bool Condition >
struct conditional
{
  template< class T, class U >
  using apply = T;

  template< template< class... > class T, template< class... > class /*U*/
          , class... P
          >
  using meta_apply = T< P... >;

  template< template< auto... > class T, template< auto... > class /*U*/
          , auto... P
          >
  using meta_apply_values = T< P... >;

  template< template< class... > class T, class /*U*/, class... P >
  using half_meta_apply = T< P... >;

  template< template< auto... > class T, class /*U*/, auto... P >
  using half_meta_apply_values = T< P... >;

  template< template< template< class... > class, class... > class T
          , template< class... > class R, class... P
          >
  using continue_ = T< R, P... >;

  template< template< std::size_t, template< class... > class, class... >
            class T
          , std::size_t I, template< class... > class R, class... P
          >
  using continue_with_index = T< I, R, P... >;
};

template<>
struct conditional< false >
{
  template< class T, class U >
  using apply = U;

  template< template< class... > class /*T*/, template< class... > class U
          , class... P
          >
  using meta_apply = U< P... >;

  template< template< auto... > class /*T*/, template< auto... > class U
          , auto... P
          >
  using meta_apply_values = U< P... >;

  template< template< class... > class /*T*/, class U, class... /*P*/ >
  using half_meta_apply = U;

  template< template< auto... > class /*T*/, class U, auto... /*P*/ >
  using half_meta_apply_values = U;
};

} // namespace (argot::argot_detail)

#endif  // ARGOT_DETAIL_CONDITIONAL_HPP_
