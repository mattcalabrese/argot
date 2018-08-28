/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EQUATABLE_HPP_
#define ARGOT_CONCEPTS_EQUATABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/declval.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/concepts/equality_comparable.hpp>
#include <argot/concepts/inequality_comparable.hpp>
#include <argot/concepts/nothrow_equality_comparable.hpp>
#include <argot/concepts/nothrow_inequality_comparable.hpp>
#include <argot/gen/requires.hpp>

#include <memory>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/equatable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( Equatable )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map
< Equatable< T >
, ARGOT_REQUIRES( EqualityComparable< T > )<>
>
{
  // TODO(mattcalabrese) Don't do noexcept?
  static constexpr bool equal_to( T const& lhs, T const& rhs )
  noexcept( noexcept( ( lhs == rhs ) ? true : false ) )
  {
    return ( lhs == rhs ) ? true : false;
  }

  // TODO(mattcalabrese) Don't do noexcept?
  static constexpr bool not_equal_to( T const& lhs, T const& rhs )
  noexcept
  ( ARGOT_IS_MODELED
    ( typename argot_detail::conditional
      < ARGOT_IS_MODELED( InequalityComparable< T > ) >
      ::template meta_apply
      < NothrowInequalityComparable, NothrowEqualityComparable, T >
    )
  )
  {
    if constexpr( ARGOT_IS_MODELED( InequalityComparable< T > ) )
      return ( lhs != rhs ) ? true : false;
    else
      return ( lhs == rhs ) ? false : true;
  }
};

template< class T >
struct make_concept_map< Equatable< T& > >
{
  // TODO(mattcalabrese) Don't do noexcept?
  static constexpr bool equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) == std::addressof( rhs );
  }

  // TODO(mattcalabrese) Don't do noexcept?
  static constexpr bool not_equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) != std::addressof( rhs );
  }
};

template< class T >
struct make_concept_map< Equatable< T&& > >
{
  // TODO(mattcalabrese) Don't do noexcept?
  static constexpr bool equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) == std::addressof( rhs );
  }

  // TODO(mattcalabrese) Don't do noexcept?
  static constexpr bool not_equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) != std::addressof( rhs );
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_EQUATABLE_HPP_
