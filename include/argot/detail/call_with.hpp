/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CALL_WITH_HPP_
#define ARGOT_DETAIL_CALL_WITH_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>

namespace argot {
namespace call_detail {

template< class Fun, class ArgTypes >
struct result_of_call_with {};

// TODO(mattcalabrese) Use result of constexpr invoke
template< class Fun, class... P >
struct result_of_call_with< Fun, receiver_traits::argument_types_t< P... > >
  : std::invoke_result< Fun&&, P&&... >{};

template< class Fun, class ArgTypes >
using result_of_call_with_t
  = typename result_of_call_with< Fun, ArgTypes >::type;

template< class Fun, class ArgTypes >
struct basic_result_of_call_with {};

template< class Fun, class... P >
struct basic_result_of_call_with
< Fun, receiver_traits::argument_types_t< P... > >
  : basic_result_of< Fun, P&&... >{};

template< class Fun, class ArgTypes >
using basic_result_of_call_with_t
  = typename basic_result_of_call_with< Fun, ArgTypes >::type;

}  // namespace argot::call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_CALL_WITH_HPP_
