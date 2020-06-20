/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_INTRINSIC_UNPACKABLE_HPP_
#define ARGOT_CONCEPTS_INTRINSIC_UNPACKABLE_HPP_

//[description
/*`
IntrinsicUnpackable is an [argot_gen_concept] for TupleLike types that have a
more efficient way to expand out all members and element types than O(n)
applications of tuple_traits::get and tuple_traits::element_type_t.]
*/
//]

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <array>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/intrinsic_unpackable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( IntrinsicUnpackable )
(
  TupleLike< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

// TODO(mattcalabrese) Do this from a namespace not nested in argot.
namespace detail_intrinsic_unpackable {

template< class T, auto /*I*/ >
using always_with_index = T;

// TODO(calabrese) Do this without type templates
template< class IndexList >
struct intrinsic_unpackable_impl;

template< class T, auto... Indices >
struct intrinsic_unpackable_impl< std::integer_sequence< T, Indices... > >
{
  template< class Tup >
  using map_of = access_raw_concept_map< TupleLike< Tup > >;

  template< class Tup, template< class... > class Result >
  using expand_elements_t
    = Result< typename map_of< Tup >::template element_type_t< Indices >... >;

  template< template< class... > class Result, class IndexType >
  using t_size_times_t = Result< always_with_index< IndexType, Indices >... >;

  template< class Fun, class Tup >
  static constexpr decltype( auto ) apply( Fun&& fun, Tup&& tup )
  {
    using map = map_of< detail_argot::remove_cvref_t< Tup > >;

    // TODO(calabrese) Possibly don't invoke at this level (just function call)?
    // NOTE: This intentionally differs from how std::apply works (this does not
    //       call "get" multiple times with rvalues and instead forwards the
    //       results of the calls to get).
    if constexpr( std::is_rvalue_reference_v< Tup&& > )
      return argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , ARGOT_FORWARD( typename map::template element_type_t< Indices > )
        ( map::template get< Indices >( tup ) )...
      );
    else
      return argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , map::template get< Indices >( tup )...
      );
  }

  template< class Fun, class A >
  static constexpr decltype( auto ) apply_array( Fun&& fun, A&& tup )
  {
    // TODO(calabrese) Possibly don't invoke at this level (just function call)?
    // NOTE: This intentionally differs from how std::apply works (this does not
    //       call "get" multiple times with rvalues and instead forwards the
    //       results of the calls to get).
    if constexpr( std::is_rvalue_reference_v< A&& > )
      return argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , ARGOT_MOVE( tup[ Indices ] )...
      );
    else
      return argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Fun )( fun )
      , tup[ Indices ]...
      );
  }
};

} // namespace argot(::detail_intrinsic_unpackable)

template< class... T >
struct make_concept_map< IntrinsicUnpackable< std::tuple< T... > > >
{
  template< template< class... > class Result >
  using expand_element_types_t = Result< T... >;

  template< class Fun, class Self >
  static constexpr decltype( auto ) apply( Fun&& fun, Self&& self )
  {
    return std::apply( ARGOT_FORWARD( Fun )( fun )
                     , ARGOT_FORWARD( Self )( self )
                     );
  }
};

template< class T, std::size_t Size >
struct make_concept_map< IntrinsicUnpackable< std::array< T, Size > > >
{
  template< template< class... > class Result >
  using expand_element_types_t
    = typename detail_intrinsic_unpackable::intrinsic_unpackable_impl
      < std::make_index_sequence< Size > >
      ::template t_size_times_t< Result, T >;

  template< class Fun, class Self >
  static constexpr decltype( auto ) apply( Fun&& fun, Self&& self )
  {
    return detail_intrinsic_unpackable::intrinsic_unpackable_impl
    < std::make_index_sequence< Size > >
    ::apply_array( ARGOT_FORWARD( Fun )( fun )
                 , ARGOT_FORWARD( Self )( self )
                 );
  }
};

template< class First, class Second >
struct make_concept_map< IntrinsicUnpackable< std::pair< First, Second > > >
{
  template< template< class... > class Result >
  using expand_element_types_t = Result< First, Second >;

  template< class Fun, class Self >
  static constexpr decltype( auto ) apply( Fun&& fun, Self&& self )
  {
    // TODO(calabrese) Make sure this works for rvalue reference members.
    // TODO(calabrese) Possibly don't invoke at this level (just function call)?
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun )
    , ARGOT_FORWARD( Self )( self ).first, ARGOT_FORWARD( Self )( self ).second
    );
  }
};

} // namespace argot

#endif  // ARGOT_CONCEPTS_INTRINSIC_UNPACKABLE_HPP_
