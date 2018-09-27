/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_EXPLICIT_CONCEPT_HPP_
#define ARGOT_GEN_EXPLICIT_CONCEPT_HPP_

#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/detail/concept_assertion.hpp>
#include <argot/gen/detail/is_modeled_impl_base.hpp>
#include <argot/gen/requires.hpp>

namespace argot::concept_detail {

// TODO(mattcalabrese) Move to detail header
template< class ConceptSpec, class /*Enabler*/ = void >
struct is_modeled_impl : gen_detail::is_modeled_impl_true_base {
  // If you get an error here then a concept map was created but the associated
  // requirements were not met.
  using type
    = typename FAILED_BECAUSE_THE_FOLLOWING_CONCEPT_IS_NOT_MODELED
      < typename ConceptSpec::requirements >::_::template result<>;
};

template< class ConceptSpec >
struct is_modeled_impl
< ConceptSpec
, typename access_raw_concept_map< ConceptSpec >
  ::argot_detail_concept_is_not_mapped
> : gen_detail::is_modeled_impl_false_base {};

} // namespace (argot::concept_detail)

#define ARGOT_EXPLICIT_CONCEPT( name )                                         \
struct name                                                                    \
{                                                                              \
  using ArgotDetailConceptSpec = name;                                         \
                                                                               \
  ARGOT_DETAIL_EXPLICIT_CONCEPT_IMPL

#define ARGOT_DETAIL_EXPLICIT_CONCEPT_IMPL( ... )                              \
  static bool constexpr argot_gen_detail_is_auto_concept_v = false;            \
                                                                               \
  template< class ArgotDetailSelf >                                            \
  using argot_gen_detail_is_modeled_impl                                       \
    = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >;             \
                                                                               \
  using requirements                                                           \
    = typename ::argot::requires_detail::requires_impl< __VA_ARGS__ >::type;   \
                                                                               \
  struct assertion                                                             \
    : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {};         \
}

#include <argot/gen/or.hpp>  // Necessary to complete Or from impl_base

#endif  // ARGOT_GEN_EXPLICIT_CONCEPT_HPP_
