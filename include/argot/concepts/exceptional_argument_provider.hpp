/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EXCEPTIONAL_ARGUMENT_PROVIDER_HPP_
#define ARGOT_CONCEPTS_EXCEPTIONAL_ARGUMENT_PROVIDER_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace exceptional_argument_provider_detail {

template< class T >
struct exceptional_argument_provider_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < SameType
        < prov_traits::argument_list_kinds_of_destructive_t< T >
        , receiver_traits::argument_list_kinds_t<>
        >
      >;
};

}  // namespace argot(::exceptional_argument_provider_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/exceptional_argument_provider.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_AUTO_CONCEPT( ExceptionalArgumentProvider )
(
  ArgumentProvider< T >
, TransparentRequirement
  < exceptional_argument_provider_detail
    ::exceptional_argument_provider_requirements< T >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_EXCEPTIONAL_ARGUMENT_PROVIDER_HPP_
