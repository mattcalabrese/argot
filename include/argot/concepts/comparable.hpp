/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_COMPARABLE_HPP_
#define ARGOT_CONCEPTS_COMPARABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/equatable.hpp>
#include <argot/concepts/object.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/concepts/equatable.hpp>
#include <argot/concepts/equality_comparable.hpp>
#include <argot/concepts/greater_equal_comparable.hpp>
#include <argot/concepts/greater_than_comparable.hpp>
#include <argot/concepts/inequality_comparable.hpp>
#include <argot/concepts/less_equal_comparable.hpp>
#include <argot/concepts/less_than_comparable.hpp>
#include <argot/concepts/nothrow_equality_comparable.hpp>
#include <argot/concepts/nothrow_greater_equal_comparable.hpp>
#include <argot/concepts/nothrow_greater_than_comparable.hpp>
#include <argot/concepts/nothrow_inequality_comparable.hpp>
#include <argot/concepts/nothrow_less_equal_comparable.hpp>
#include <argot/concepts/nothrow_less_than_comparable.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/comparable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( Comparable )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

// TODO(mattcalabrese) Don't do conditional noexcept in these?
template< class T >
struct make_concept_map
< Comparable< T >
, ARGOT_REQUIRES( Equatable< T > )
                ( LessThanComparable< T > )
                <>
>
{
  static constexpr bool equal_to( T const& lhs, T const& rhs )
  noexcept
  ( noexcept
    ( access_raw_concept_map< Equatable< T > >
      ::equal_to( ARGOT_DECLVAL( T const& ), ARGOT_DECLVAL( T const& ) )
    )
  )
  {
    return   access_raw_concept_map< Equatable< T > >::equal_to( lhs, rhs )
           ? true : false;
  }

  static constexpr bool not_equal_to( T const& lhs, T const& rhs )
  noexcept
  ( noexcept
    ( access_raw_concept_map< Equatable< T > >
      ::not_equal_to( ARGOT_DECLVAL( T const& ), ARGOT_DECLVAL( T const& ) )
    )
  )
  {
    return   access_raw_concept_map< Equatable< T > >::not_equal_to( lhs, rhs )
           ? true : false;
  }

  static constexpr bool less_than( T const& lhs, T const& rhs )
  noexcept( ARGOT_IS_MODELED( NothrowLessThanComparable< T > ) )
  {
    return ( lhs < rhs ) ? true : false;
  }

  static constexpr bool less_equal( T const& lhs, T const& rhs )
  noexcept
  ( ARGOT_IS_MODELED
    ( typename argot_detail::conditional
      < ARGOT_IS_MODELED( LessEqualComparable< T > ) >::template meta_apply
      < NothrowLessEqualComparable
      , NothrowLessThanComparable
      , T
      >
    )
  )
  {
    if constexpr( ARGOT_IS_MODELED( LessEqualComparable< T > ) )
      return ( lhs <= rhs ) ? true : false;
    else
      return ( rhs < lhs ) ? false : true;
  }

  static constexpr bool greater_equal( T const& lhs, T const& rhs )
  noexcept
  ( ARGOT_IS_MODELED
    ( typename argot_detail::conditional
      < ARGOT_IS_MODELED( GreaterEqualComparable< T > ) >::template meta_apply
      < NothrowGreaterEqualComparable
      , NothrowLessThanComparable
      , T
      >
    )
  )
  {
    if constexpr( ARGOT_IS_MODELED( GreaterEqualComparable< T > ) )
      return ( lhs >= rhs ) ? true : false;
    else
      return ( lhs < rhs ) ? false : true;
  }

  static constexpr bool greater_than( T const& lhs, T const& rhs )
  noexcept
  ( ARGOT_IS_MODELED
    ( typename argot_detail::conditional
      < ARGOT_IS_MODELED( GreaterThanComparable< T > ) >::template meta_apply
      < NothrowGreaterThanComparable
      , NothrowLessThanComparable
      , T
      >
    )
  )
  {
    if constexpr( ARGOT_IS_MODELED( GreaterThanComparable< T > ) )
      return ( lhs > rhs ) ? true : false;
    else
      return ( rhs < lhs ) ? true : false;
  }
};

template< class T >
struct make_concept_map< Comparable< T& > >
{
  static constexpr bool equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) == std::addressof( rhs );
  }

  static constexpr bool not_equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) != std::addressof( rhs );
  }

  static constexpr bool less_than( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) < std::addressof( rhs );
  }

  static constexpr bool less_equal( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) <= std::addressof( rhs );
  }

  static constexpr bool greater_equal( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) >= std::addressof( rhs );
  }

  static constexpr bool greater_than( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) > std::addressof( rhs );
  }
};

template< class T >
struct make_concept_map< Comparable< T&& > >
{
  static constexpr bool equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) == std::addressof( rhs );
  }

  static constexpr bool not_equal_to( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) != std::addressof( rhs );
  }

  static constexpr bool less_than( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) < std::addressof( rhs );
  }

  static constexpr bool less_equal( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) <= std::addressof( rhs );
  }

  static constexpr bool greater_equal( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) >= std::addressof( rhs );
  }

  static constexpr bool greater_than( T const& lhs, T const& rhs ) noexcept
  {
    return std::addressof( lhs ) > std::addressof( rhs );
  }
};

} // namespace argot

#endif  // ARGOT_CONCEPTS_COMPARABLE_HPP_
