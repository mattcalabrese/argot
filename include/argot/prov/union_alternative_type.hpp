/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TO_UNION_ALTERNATIVE_TYPE_HPP_
#define ARGOT_PROV_TO_UNION_ALTERNATIVE_TYPE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/prov/access_variant.hpp>
#include <argot/prov/bind_call.hpp>
#include <argot/prov/constant_variant_index_of.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/tag.hpp>

#include <type_traits>
#include <utility>

namespace argot::prov {

// TODO(mattcalabrese) Constrain to be UnionLike
template< class UnionLike >
struct to_union_alternative_type_fn
{
  template< class IndexType, IndexType Index >
  [[nodiscard]]
  constexpr result_of_value_of_t
  < tag< union_traits::alternative_type_t< UnionLike, Index > > >
  operator ()( std::integral_constant< IndexType, Index > ) const
  {
    return prov::value_of
    ( argot::tag< union_traits::alternative_type_t< UnionLike, Index > >() );
  }

  template< class LazyThisT = to_union_alternative_type_fn >
  [[nodiscard]]
  constexpr result_of_transform_t
  < LazyThisT const&

  >
  operator ()
  ( union_traits::index_type_t< remove_cvref_t< UnionLike > > const index ) const
  {
    return prov::transform
    ( prov::union_index< UnionLike >
    , ( *this )
    );
  }
} inline constexpr to_union_alternative_type{};

template< class UnionLike, class Index >
using result_of_to_union_alternative_type
  = basic_result_of< to_union_alternative_type_fn const&, Index >;

template< class UnionLike, class Index >
using result_of_to_union_alternative_type_t
  = basic_result_of_t< to_union_alternative_type_fn const&, Index >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_TO_UNION_ALTERNATIVE_TYPE_HPP_
