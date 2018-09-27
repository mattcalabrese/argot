/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_POTENTIALLY_INVOCABLE_HPP_
#define ARGOT_CONCEPTS_POTENTIALLY_INVOCABLE_HPP_

//[description
/*`
PotentiallyInvocable is an [argot_gen_concept] that is satisfied by types that
have the potential to have an overloaded `operator()`.
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace potentially_invocable_detail {

template< class T, class /*Enabler*/ = void >
struct can_add_ref_impl : std::false_type {};

template< class T >
struct can_add_ref_impl< T, std::void_t< T& > > : std::true_type {};

template< class T >
struct can_add_ref : can_add_ref_impl< T >::type {};

} // namespace argot(::potentially_invocable_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/potentially_invocable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( PotentiallyInvocable )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

// TODO(mattcalabrese)[
//   Figure out better way to short-circuit without disjunction.
template< class T >
struct make_concept_map
< PotentiallyInvocable< T >
, typename call_detail::detached_fast_enable_if
  < std::disjunction_v
    < std::is_class< std::remove_reference_t< T > >
    , std::is_union< std::remove_reference_t< T > >
    , std::conjunction
      < std::is_function
        < std::remove_pointer_t< std::remove_reference_t< T > > >
      , potentially_invocable_detail::can_add_ref< T >
      >
    , std::is_member_pointer< std::remove_reference_t< T > >
    >
  >
  ::_::template apply<>
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_POTENTIALLY_INVOCABLE_HPP_
