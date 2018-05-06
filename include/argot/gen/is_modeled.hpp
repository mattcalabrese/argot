/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_IS_MODELED_HPP_
#define ARGOT_GEN_IS_MODELED_HPP_

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

// TODO(mattcalabrese)
//   static_assert that the concept map is valid whenever it is specialized.

namespace argot {

template< class ConceptSpec >
bool constexpr is_modeled_v
  = ConceptSpec::template argot_gen_detail_is_modeled_impl< ConceptSpec >
    ::value;

template< class ConceptSpec >
struct is_modeled : std::bool_constant< is_modeled_v< ConceptSpec > > {};

}  // namespace argot

#define ARGOT_IS_MODELED( ... ) ::argot::is_modeled_v< __VA_ARGS__ >

#endif  // ARGOT_GEN_IS_MODELED_HPP_
