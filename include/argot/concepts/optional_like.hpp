/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_OPTIONAL_LIKE_HPP_
#define ARGOT_CONCEPTS_OPTIONAL_LIKE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/detail/forward.hpp>

#include <boost/assert.hpp>
#include <boost/optional.hpp>

#include <cstddef>
#include <optional>
#include <type_traits>
#include <variant>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/optional_like.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( OptionalLike )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T >
struct make_concept_map< OptionalLike< boost::optional< T > > >
{
  using element_type_t = T;

  static constexpr bool has_value( boost::optional< T > const& opt )
  {
    return static_cast< bool >( opt );
  }

  template< class Self >
  static constexpr
  typename call_detail::give_qualifiers_to_t < Self&&, element_type_t >
  get( Self&& opt )
  {
    BOOST_ASSERT( static_cast< bool >( opt ) );
    return *ARGOT_FORWARD( Self )( opt );
  }
};

template< class T >
struct make_concept_map< OptionalLike< std::optional< T > > >
{
  using element_type_t = T;

  static constexpr bool has_value( std::optional< T > const& opt )
  {
    return opt.has_value();
  }

  template< class Self >
  static constexpr
  typename call_detail::give_qualifiers_to_t< Self&&, element_type_t >
  get( Self&& opt )
  {
    BOOST_ASSERT( opt.has_value() );
    return *ARGOT_FORWARD( Self )( opt );
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_OPTIONAL_LIKE_HPP_
