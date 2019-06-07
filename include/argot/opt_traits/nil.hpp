/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPT_TRAITS_NIL_HPP_
#define ARGOT_OPT_TRAITS_NIL_HPP_

#include <argot/detail/regular_monostate_base.hpp>

#include <cstddef>
#include <functional>

namespace argot::opt_traits {

template< class T >
struct nil
  : private argot_detail::regular_monostate_base< nil< T > > {};

} // namespace (argot::opt_traits)

namespace std {

template< class T >
ARGOT_DETAIL_MONOSTATE_HASH_DEFINITION( ::argot::opt_traits::nil< T > );

} // namespace std

#endif  // ARGOT_OPT_TRAITS_NIL_HPP_
