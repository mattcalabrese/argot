
/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_CONVERTIBLE_TO_TYPE_OR_CONSTANT_HPP_
#define ARGOT_CONCEPTS_CONVERTIBLE_TO_TYPE_OR_CONSTANT_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

namespace convertible_to_type_or_constant_detail {

template< class T >
struct is_std_integral_constant : std::false_type {};

template< class T, T Value >
struct is_std_integral_constant< std::integral_constant< T, Value > >
  : std::true_type {};

} // namespace argot(::convertible_to_type_or_constant_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/convertible_to_type_or_constant.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Type, class ExpectedValueType >
ARGOT_EXPLICIT_CONCEPT( ConvertibleToTypeOrConstant )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class Type, class ExpectedValueType >
struct make_concept_map
< ConvertibleToTypeOrConstant< Type, ExpectedValueType >
, typename call_detail::detached_fast_enable_if
  < !convertible_to_type_or_constant_detail
    ::is_std_integral_constant< detail_argot::remove_cvref_t< Type > >::value
  >
  ::_::template and_< std::is_convertible_v< Type, ExpectedValueType > >
  ::_::template apply<>
> {};

template< class Type, class ExpectedValueType >
struct make_concept_map
< ConvertibleToTypeOrConstant< Type, ExpectedValueType >
, typename call_detail::detached_fast_enable_if
  < convertible_to_type_or_constant_detail
    ::is_std_integral_constant< detail_argot::remove_cvref_t< Type > >::value
  >
  ::_::template and_
    < std::is_convertible_v
      < typename detail_argot::remove_cvref_t< Type >::value_type
      , ExpectedValueType
      >
    >
  ::_::template apply<>
> {};

} // namespace argot

#endif  // ARGOT_CONCEPTS_CONVERTIBLE_TO_TYPE_OR_CONSTANT_HPP_
