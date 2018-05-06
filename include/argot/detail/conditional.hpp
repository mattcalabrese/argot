/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONDITIONAL_HPP_
#define ARGOT_DETAIL_CONDITIONAL_HPP_

namespace argot::argot_detail {

template< bool Condition >
struct conditional
{
  template< class T, class U >
  using apply = T;

  template< template< class... > class T, template< class... > class U
          , class... P
          >
  using meta_apply = T< P... >;

  template< template< class... > class T, class U, class... P >
  using half_meta_apply = T< P... >;
};

template<>
struct conditional< false >
{
  template< class T, class U >
  using apply = U;

  template< template< class... > class T, template< class... > class U
          , class... P
          >
  using meta_apply = U< P... >;

  template< template< class... > class T, class U, class... P >
  using half_meta_apply = U;
};

}  // namespace (argot::argot_detail)

#endif  // ARGOT_DETAIL_CONDITIONAL_HPP_
