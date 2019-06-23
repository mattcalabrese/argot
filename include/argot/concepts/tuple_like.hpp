/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_TUPLE_LIKE_HPP_
#define ARGOT_CONCEPTS_TUPLE_LIKE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/concepts/valid.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/forward.hpp>

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/tuple_like.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( TupleLike )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

// TODO(mattcalabrese) Do this from a namespace not nested in argot.
namespace tuple_like_detail {

using std::get;

template< class T, std::size_t I, class /*Enabler*/ = void >
using result_of_get_t = decltype( get< I >( ARGOT_DECLVAL( T ) ) );

template< class Tup >
using tuple_size_sfinae = decltype( std::tuple_size< Tup >::value );

}  // namespace argot(::tuple_like_detail)

template< class Tup >
struct make_concept_map
< TupleLike< Tup >
, ARGOT_REQUIRES( UnqualifiedObject< Tup > )
                ( Valid< tuple_like_detail::tuple_size_sfinae, Tup > )
                <>
>
{
  using index_type = std::size_t;

  static index_type constexpr num_elements = std::tuple_size_v< Tup >;

  template< index_type Index >
  using element_type_t = std::tuple_element_t< Index, Tup >;

  template< index_type Index, class Self >
  static constexpr tuple_like_detail::result_of_get_t< Self, Index >
  get( Self&& self )
  {
    using std::get;
    return get< Index >( ARGOT_FORWARD( Self )( self ) );
  }
};

}  // namespace argot

#endif  // ARGOT_TUPLE_LIKE_HPP_
