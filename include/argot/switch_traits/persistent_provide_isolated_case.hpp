/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_ISOLATED_CASE_HPP_
#define ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_ISOLATED_CASE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/switch_traits/argument_list_kinds_of_case_persistent.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot::switch_traits {

template< auto Value >
struct persistent_provide_isolated_case_t
{
  template
  < class Case, class Receiver
  , ARGOT_REQUIRES
    ( PersistentSwitchBodyCase< Case, Value > )
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_case_persistent_t< Case, Value >
      >
    )
    ()
  >
  constexpr decltype( auto )
  operator ()( Case const& case_, Receiver&& rec ) const
  {
    return access_raw_concept_map< PersistentSwitchBodyCase< Case, Value > >
    ::provide_isolated_case( case_, ARGOT_FORWARD( Receiver )( rec ) );
  }
};

template< auto Value >
persistent_provide_isolated_case_t< Value > constexpr
persistent_provide_isolated_case{};

// TODO(mattcalabrese) Make result type calculators

/*

template< auto Value, class Case, class Receiver >
using result_of_destructive_provide_t
  = basic_result_of_t
    < destructive_provide_t const&, Case&&, ValueType&&, Receiver&& >;

template< auto Value, class Case, class Receiver >
using result_of_destructive_provide
  = basic_result_of
    < destructive_provide_t const&, Case&&, ValueType&&, Receiver&& >;;
*/
}  // namespace (argot::switch_traits)

#endif  // ARGOT_SWITCH_TRAITS_PERSISTENT_PROVIDE_ISOLATED_CASE_HPP_
