/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TRAITS_RETURN_TYPES_OF_CALL_HPP_
#define ARGOT_REDUCER_TRAITS_RETURN_TYPES_OF_CALL_HPP_

#include <argot/concepts/argot_invocable_before_reduction.hpp>
#include <argot/detail/call_with.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/reducer_traits/return_types.hpp>

namespace argot::reducer_traits {
namespace detail_return_types_of_call {

template< class Fun, class InvocationArgumentLists >
struct return_types_of_call_impl {};

template< class Fun, class... InvocationArgumentLists >
struct return_types_of_call_impl
       < Fun
       , receiver_traits::argument_list_kinds_t< InvocationArgumentLists... >
       >
{
  using type
    = reducer_traits::return_types_t
      < call_detail::result_of_call_with_t< Fun, InvocationArgumentLists >... >;
};

}  // namespace argot::reducer_traits(::detail_return_types_of_call)

template< class Fun, class... P >
using return_types_of_call_t
  = ARGOT_REQUIRES( ArgotInvocableBeforeReduction< Fun, P... > )
    < typename detail_return_types_of_call::return_types_of_call_impl
      < Fun
      , prov_traits::argument_list_kinds_of_destructive_t
        < prov::result_of_default_to_reference_to_t< P... > >
      >::type
    >;

template< class Fun, class... P >
using return_types_of_call
  = call_detail::lazy_expand< return_types_of_call_t, Fun, P... >;

} // namespace (argot::reducer_traits)

#endif  // ARGOT_REDUCER_TRAITS_RETURN_TYPES_OF_CALL_HPP_
