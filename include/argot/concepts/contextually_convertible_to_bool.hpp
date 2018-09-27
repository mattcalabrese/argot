/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_CONTEXTUALLY_CONVERTIBLE_TO_BOOL_HPP_
#define ARGOT_CONCEPTS_CONTEXTUALLY_CONVERTIBLE_TO_BOOL_HPP_

//[description
/*`
ContextuallyConvertibleToBool is the [argot_gen_concept] for types that are
[contextually_convertible_to_bool].
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/valid.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>

namespace argot {
namespace contextually_convertible_to_bool_detail {

template< class T >
using contextually_convertible_to_bool_requirement_impl
  = decltype( ARGOT_DECLVAL( T ) ? true : false );

} // namespace argot(::contextually_convertible_to_bool_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/contextually_convertible_to_bool.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( ContextuallyConvertibleToBool )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< ContextuallyConvertibleToBool< T >
, ARGOT_REQUIRES
  ( Valid
    < contextually_convertible_to_bool_detail
      ::contextually_convertible_to_bool_requirement_impl
    , T
    >
  )
  <>
>
{
  // TODO(mattcalabrese) conditional noexcept?
  static constexpr bool convert( T&& arg )
  {
    return ARGOT_FORWARD( T )( arg ) ? true : false;
  }
};

} // namespace argot

#endif  // ARGOT_CONCEPTS_CONTEXTUALLY_CONVERTIBLE_TO_BOOL_HPP_
