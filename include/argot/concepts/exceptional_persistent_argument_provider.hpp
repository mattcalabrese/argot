/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EXCEPTIONAL_PERSISTENT_ARGUMENT_PROVIDER_HPP_
#define ARGOT_CONCEPTS_EXCEPTIONAL_PERSISTENT_ARGUMENT_PROVIDER_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/exceptional_argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace exceptional_persistent_argument_provider_detail {

template< class T >
struct exceptional_persistent_argument_provider_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < SameType
        < prov_traits::argument_list_kinds_of_persistent_t< T >
        , receiver_traits::argument_list_kinds_t<>
        >
      >;
};

}  // namespace argot(::exceptional_persistent_argument_provider_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/exceptional_persistent_argument_provider.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Remove the need for the transparent check
//                     (require that persistent providers must at most differ
//                     by qualifiers of arguments)
template< class T >
ARGOT_AUTO_CONCEPT( ExceptionalPersistentArgumentProvider )
(
  PersistentArgumentProvider< T >
, ExceptionalArgumentProvider< T >
, TransparentRequirement
  < exceptional_persistent_argument_provider_detail
    ::exceptional_persistent_argument_provider_requirements< T >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

}  // namespace argot

#endif  // ARGOT_CONCEPTS_EXCEPTIONAL_PERSISTENT_ARGUMENT_PROVIDER_HPP_
