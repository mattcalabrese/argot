/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_UNION_LIKE_HPP_
#define ARGOT_CONCEPTS_UNION_LIKE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/opt_traits/nil.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/optional.hpp>
#include <boost/variant/variant_fwd.hpp>  // TODO(mattcalabrese) Is fwd enough?
#include <boost/variant/get.hpp>

#include <cstddef>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/union_like.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( UnionLike )
(
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class... T >
struct make_concept_map< UnionLike< boost::variant< T... > > >
{
  using alternative_types = typename boost::variant< T... >::types;

  using index_type = std::size_t;

  // TODO(mattcalabrese) Make sure this works if using old non-variadic variant.
  static index_type constexpr num_alternatives
    = boost::mpl::size< alternative_types >::value;

  template< index_type Index >
  using alternative_type_t
    = typename boost::mpl::at_c< alternative_types, Index >::type;

  template< index_type Index, class Self >
  static constexpr typename call_detail::give_qualifiers_to_t
  < Self&&, alternative_type_t< Index > >
  get( Self&& var )
  {
    using original_type = alternative_type_t< Index >;

    using return_type
      = call_detail::give_qualifiers_to_t< Self&&, original_type >;

    using get_arg
      = std::conditional_t< std::is_reference< original_type >::value
                          , original_type&
                          , std::remove_reference_t< return_type >
                          >;

    BOOST_ASSERT( Index == var.which() );

    // TODO(mattcalabrese) Possibly std::forward
    return static_cast< return_type >( boost::strict_get< get_arg >( var ) );
  }
};

template< class... T >
struct make_concept_map< UnionLike< std::variant< T... > > >
{
  using index_type = std::size_t;

  static index_type constexpr num_alternatives = sizeof...( T );

  template< index_type Index >
  using alternative_type_t
    = std::variant_alternative_t< Index, std::variant< T... > >;

  template< index_type Index, class Self >
  using qualified_alternative_type_t
    = call_detail::give_qualifiers_to_t
      < Self&&, alternative_type_t< Index > >;

  template< index_type Index, class Self >
  static constexpr qualified_alternative_type_t< Index, Self >
  get( Self&& var )
  {
    BOOST_ASSERT( Index == var.index() );
    return static_cast< qualified_alternative_type_t< Index, Self > >
    ( std::get< Index >( var ) );
  }
};

namespace detail_union_like {

// TODO(mattcalabrese) ARGOT_NO_UNIQUE_ADDRESS
template< class T >
inline constexpr opt_traits::nil< T > nil_instance{};

} // namespace argot(::detail_union_like)

// TODO(mattcalabrese) Concept map anything that models OptionalLike

// TODO(mattcalabrese) Make sure this all works in constexpr
template< class Opt >
struct make_concept_map
< UnionLike< Opt >
, ARGOT_REQUIRES( OptionalLike< Opt > )<>
>
{
 private:
  using map = access_raw_concept_map< OptionalLike< Opt > >;
  using element_type_t = typename map::element_type_t;
  using nil_t = opt_traits::nil< element_type_t >;
 public:
  // TOO(mattcalabrese) Change to unsigned char?
  using index_type = std::size_t;

  static index_type constexpr num_alternatives = 2;

  template< index_type Index >
  using alternative_type_t
    = typename argot_detail::conditional< Index == 0 >
      ::template apply< nil_t, element_type_t >;

  template< index_type Index, class Self >
  using qualified_alternative_type_t
    = call_detail::give_qualifiers_to_t< Self&&, alternative_type_t< Index > >;

  template< index_type Index, class Self >
  static constexpr qualified_alternative_type_t< Index, Self >
  get( Self&& opt )
  {
    if constexpr( Index == 0 )
    {
      BOOST_ASSERT( !map::has_value( std::as_const( opt ) ) );
      if constexpr( std::is_lvalue_reference_v< Self&& > )
        if constexpr( std::is_const_v< std::remove_reference_t< Self > > )
          return detail_union_like::nil_instance< element_type_t >;
        else
          return const_cast< nil_t& >
          ( detail_union_like::nil_instance< element_type_t > );
      else
        if constexpr( std::is_const_v< std::remove_reference_t< Self > > )
          return ARGOT_MOVE
          ( detail_union_like::nil_instance< element_type_t > );
        else
          return const_cast< nil_t&& >
          ( ARGOT_MOVE( detail_union_like::nil_instance< element_type_t > ) );
    }
    else
    {
      BOOST_ASSERT( map::has_value( std::as_const( opt ) ) );
      return map::get( ARGOT_FORWARD( Opt )( opt ) );
    }
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_UNION_LIKE_HPP_
