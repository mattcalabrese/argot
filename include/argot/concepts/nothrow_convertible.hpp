/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_NOTHROW_CONVERTIBLE_HPP_
#define ARGOT_CONCEPTS_NOTHROW_CONVERTIBLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/is_modeled.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/concepts/convertible.hpp>
#include <argot/concepts/nothrow_explicitly_convertible.hpp>
#include <argot/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/if_.hpp>

#include <type_traits>

namespace argot::detail_nothrow_convertible {

struct convert_nonvoid
{
  template< class T, class U >
  static void test( U = ARGOT_DECLVAL( T ) ) noexcept;
};

struct convert_void
{
  template< class T, class U
          , call_detail::fast_enable_if_t< std::is_void_v< U > >* = nullptr
          >
  static void test() noexcept;
};

} // namespace (argot::detail_nothrow_convertible)

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/nothrow_convertible.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T, class U >
ARGOT_EXPLICIT_CONCEPT( NothrowConvertible )
(
  NothrowExplicitlyConvertible< T, U >
, Convertible< T, U >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

template< class T, class U >
struct make_concept_map
< NothrowConvertible< T, U >
, typename call_detail::detached_fast_enable_if
  < is_modeled_v< Convertible< T, U > > >::_::template and_
  < noexcept
    ( detail_if_::if_< std::is_void_v< T > >::then_else::template _
      < detail_nothrow_convertible::convert_void
      , detail_nothrow_convertible::convert_nonvoid
      >
      ::template test< T, U >()
    )
  >::void_
> {};


}  // namespace argot

#endif  // ARGOT_CONCEPTS_NOTHROW_CONVERTIBLE_HPP_
