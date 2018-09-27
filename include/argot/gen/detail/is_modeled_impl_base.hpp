/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_DETAIL_IS_MODELED_IMPL_BASE_HPP_
#define ARGOT_GEN_DETAIL_IS_MODELED_IMPL_BASE_HPP_

#include <argot/gen/is_modeled.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

template< class... ConceptSpecs >
struct Or;

namespace gen_detail {

struct is_modeled_impl_true_base
  : std::true_type
{
  template< class... ConceptSpecs >
  using or_ = std::true_type;
};

struct is_modeled_impl_false_base
  : std::false_type
{
  template< class... ConceptSpecs >
  using or_ = std::bool_constant< is_modeled_v< Or< ConceptSpecs... > > >;
};

} // namespace argot(::gen_detail)
} // namespace argot

#endif  // ARGOT_GEN_DETAIL_IS_MODELED_IMPL_BASE_HPP_
