/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_UNHANDLED_SWITCHABLE_VALUE_HPP_
#define ARGOT_CONCEPTS_UNHANDLED_SWITCHABLE_VALUE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/concepts/switchable.hpp>
#include <argot/concepts/true.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/sink.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/switch_traits/provider_of_isolated.hpp>

#include <type_traits>
#include <utility>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace unhandled_switchable_value_detail {

struct unhandled_with_no_explicit_default_t {};

// TODO(mattcalabrese) Move to another file
template< auto Value, class Def >
constexpr auto nary_provider_of_isolated( Def&& def )
{
  return ARGOT_FORWARD( Def )( def );
}

template< auto Value, class Def, class HeadBody, class... TailBodies >
constexpr auto
nary_provider_of_isolated( Def&& def, HeadBody&& head, TailBodies&&... tail )
{
  if constexpr
  ( is_modeled_v< SwitchBodyCase< detail_argot::remove_cvref_t< HeadBody >, Value > > )
    return switch_traits::provider_of_isolated< Value >
    ( ARGOT_FORWARD( HeadBody )( head ) );
  else
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< detail_argot::remove_cvref_t< HeadBody > > > )
      return (nary_provider_of_isolated< Value >)
      ( ARGOT_FORWARD( HeadBody )( head )
      , ARGOT_FORWARD( TailBodies )( tail )...
      );
    else
      return (nary_provider_of_isolated< Value >)
      ( ARGOT_FORWARD( Def )( def ), ARGOT_FORWARD( TailBodies )( tail )... );
}

template< auto Value, class... Bodies >
struct unhandled_switchable_value_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < True
        < std::is_same_v
          < decltype
            ( (nary_provider_of_isolated< Value >)
              ( unhandled_with_no_explicit_default_t()
              , ARGOT_DECLVAL( Bodies )...
              )
            )
          , unhandled_with_no_explicit_default_t
          >
        >
      >;
};

}  // namespace argot(::unhandled_switchable_value_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/unhandled_switchable_value.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Make sure the bodies can be combined
// TODO(mattcalabrese) Check for no duplicates
template< auto Value, class... Bodies >
ARGOT_AUTO_CONCEPT( UnhandledSwitchableValue )
(
  Switchable< decltype( Value ), Bodies... >
, TransparentRequirement
  < unhandled_switchable_value_detail
    ::unhandled_switchable_value_requirements< Value, Bodies... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_UNHANDLED_SWITCHABLE_VALUE_HPP_
