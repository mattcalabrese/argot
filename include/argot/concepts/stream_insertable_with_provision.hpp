/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_PROVISION_HPP_
#define ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_PROVISION_HPP_

//[description
/*`
StreamInsertableWithProvision is an [argot_gen_concept] that is satisfied if
each of the arguments of an ArgumentProvider's provision is StreamInsertable
with the specified type.
*/
//]

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/stream_insertable_with_kinds.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/prov_traits/argument_list_kinds_of.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detail_stream_insertable_with_provision {

template< class Stream, class Provider >
struct stream_insertable_with_provision_requirements
{
  template< template< class... > class Reqs >
  using expand_requirements
    = Reqs
      < StreamInsertableWithKinds
        < Stream
        , prov_traits::argument_list_kinds_of_t< Provider >
        >
      >;
};

} // namespace argot(::detail_stream_insertable_with_provision)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/stream_insertable_with_provision.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Stream, class Provider >
ARGOT_AUTO_CONCEPT( StreamInsertableWithProvision )
(
  ArgumentProvider< detail_argot::remove_cvref_t< Provider > >
, TransparentRequirement
  < detail_stream_insertable_with_provision
    ::stream_insertable_with_provision_requirements
    < Stream, Provider >
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_PROVISION_HPP_
