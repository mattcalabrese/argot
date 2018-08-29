/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_PROVIDE_RESULT_TO_HPP_
#define ARGOT_REDUCER_PROVIDE_RESULT_TO_HPP_

#include <argot/concepts/return_value_reducer.hpp>
#include <argot/contained.hpp>
#include <argot/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/reducer_traits/return_types.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace reducer {

struct provide_result_to_t
{
  template< class Receiver >
  struct impl
  {
    // TODO(mattcalabrese) Use receiver_reference
    contained< Receiver&& > receiver;
  };

  // TODO(mattcalabrese) Include enabler
  template< class Receiver >
  constexpr impl< Receiver > operator ()( Receiver&& rec ) const
  {
    return
    { argot::make_contained< Receiver&& >
      ( ARGOT_FORWARD( Receiver )( rec ) )
    };
  }
} inline constexpr provide_result_to{};

// TODO(mattcalabrese) Include enabler
template< class Receiver >
using result_of_provide_result_to_t
  = provide_result_to_t::impl< Receiver >;

template< class Receiver >
struct result_of_provide_result_to
{
  using type
    = result_of_provide_result_to_t< Receiver >;
};

}  // namespace argot::reducer

template< class Receiver >
struct make_concept_map
< ReturnValueReducer< reducer::provide_result_to_t::impl< Receiver > > >
{
  using is_homogeneous = std::false_type;

  template
  < class Self
  , class... LeadingReturnTypes, class Fun, class... TrailingReturnTypes
  >
  static constexpr receiver_traits::result_of_receive_branch_t
  < call_detail::give_qualifiers_to_t< Self&&, Receiver >
  , receiver_traits::argument_list_kinds_t
    < receiver_traits::argument_types_t< LeadingReturnTypes&& >... >
  , receiver_traits::argument_list_kinds_t
    < receiver_traits::argument_types_t< TrailingReturnTypes&& >... >
  , std::invoke_result_t< Fun&& >
  >
  reduce
  ( Self&& self
  , reducer_traits::return_types_t< LeadingReturnTypes... >
  , Fun&& fun
  , reducer_traits::return_types_t< TrailingReturnTypes... >
  )
  {
    return receiver_traits::receive_branch
    ( argot::access_contained( ARGOT_FORWARD( Self )( self ).receiver )
    , receiver_traits::argument_list_kinds
      ( receiver_traits::argument_types< LeadingReturnTypes&& >... )
    , receiver_traits::argument_list_kinds
      ( receiver_traits::argument_types< TrailingReturnTypes&& >... )
    , ARGOT_FORWARD( Fun )( fun )()
    );
  }
};

}  // namespace argot

#endif  // ARGOT_REDUCER_PROVIDE_RESULT_TO_HPP_
