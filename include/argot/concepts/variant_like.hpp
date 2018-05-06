/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_VARIANT_LIKE_HPP_
#define ARGOT_CONCEPTS_VARIANT_LIKE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/union_traits/index_type.hpp>

#include <boost/optional.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <optional>
#include <variant>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/variant_like.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( VariantLike )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class... T >
struct make_concept_map< VariantLike< boost::variant< T... > > >
{
  using index_type = union_traits::index_type_t< boost::variant< T... > >;

  [[nodiscard]] static
  constexpr index_type index_of( boost::variant< T... > const& self ) noexcept
  {
    return static_cast< index_type >( self.which() );
  }
};

template< class... T >
struct make_concept_map< VariantLike< std::variant< T... > > >
{
  using index_type = union_traits::index_type_t< std::variant< T... > >;

  [[nodiscard]] static
  constexpr index_type index_of( std::variant< T... > const& self ) noexcept
  {
    return static_cast< index_type >( self.index() );
  }
};

// TODO(mattcalabrese) Make sure this all works in constexpr
template< class Opt >
struct make_concept_map
< VariantLike< Opt >
, ARGOT_REQUIRES( OptionalLike< Opt > )<>
>
{
  using index_type = union_traits::index_type_t< OptionalLike< Opt > >;

  [[nodiscard]] static
  constexpr index_type index_of( Opt const& self ) noexcept
  {
    return access_raw_concept_map< Opt >::has_value( self ) ? index_type{ 1 }
                                                            : index_type{ 0 };
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_VARIANT_LIKE_HPP_
