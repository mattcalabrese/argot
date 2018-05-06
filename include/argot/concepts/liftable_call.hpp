/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_LIFTABLE_CALL_HPP_
#define ARGOT_CONCEPTS_LIFTABLE_CALL_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/invocable_object_with_kinds.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov/group.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace liftable_call_detail {

template< class Invocable, class... Providers >
struct liftable_call_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < InvocableObjectWithKinds
        < Invocable
        , prov_traits::argument_list_kinds_of_destructive_t
          < prov::result_of_group_t< Providers&&... > >
        >
      >;
};

}  // namespace argot(::liftable_call_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/liftable_call.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Don't deal with references to providers here.
template< class Invocable, class... Providers >
ARGOT_AUTO_CONCEPT( LiftableCall )
(
  ArgumentProvider< Providers >...
, TransparentRequirement
  < liftable_call_detail::liftable_call_requirements
    < Invocable, Providers... >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_LIFTABLE_CALL_HPP_
