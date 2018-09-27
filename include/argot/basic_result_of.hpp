/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_BASIC_RESULT_OF_HPP_
#define ARGOT_BASIC_RESULT_OF_HPP_

#include <argot/detail/declval.hpp>
#include <argot/detail/exact_declval.hpp>
#include <argot/lazy_expand.hpp>

namespace argot {

template< class Fun, class... P >
using basic_result_of_t
  = decltype
    ( ARGOT_DECLVAL( Fun&& )
      ( argot_detail::exact_declval< P&& >()... )  // TODO(mattcalabrese) Eliminate the &&
    );

template< class Fun, class... P >
using basic_result_of = lazy_expand< basic_result_of_t, Fun, P... >;

template< class Fun, class... P >
bool constexpr is_nothrow_basic_callable_v
  = noexcept
    ( ARGOT_DECLVAL( Fun&& )
      ( argot_detail::exact_declval< P&& >()... )  // TODO(mattcalabrese) Eliminate the &&
    );

} // namespace argot

#endif  // ARGOT_BASIC_RESULT_OF_HPP_
