/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_AUTO_CONCEPT_HPP_
#define ARGOT_GEN_AUTO_CONCEPT_HPP_

#include <argot/gen/detail/is_modeled_impl_base.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot::auto_concept_detail {

// TODO(mattcalabrese) Move to detail header
template< class ConceptSpec, class /*Enabler*/ = void >
struct is_modeled_impl
  : gen_detail::is_modeled_impl_false_base {};

template< class ConceptSpec >
struct is_modeled_impl
< ConceptSpec
, typename call_detail::detached_fast_enable_if
  < is_modeled_v< typename ConceptSpec::requirements > >::_::template apply<>
> : gen_detail::is_modeled_impl_true_base {};

}  // namespace (argot::auto_concept_detail)

#define ARGOT_AUTO_CONCEPT( name )                                             \
struct name                                                                    \
{                                                                              \
  ARGOT_DETAIL_AUTO_CONCEPT_IMPL

#define ARGOT_DETAIL_AUTO_CONCEPT_IMPL( ... )                                  \
  static bool constexpr argot_gen_detail_is_auto_concept_v = true;             \
                                                                               \
  template< class ArgotDetailSelf >                                            \
  using argot_gen_detail_is_modeled_impl                                       \
    = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >;        \
                                                                               \
  using requirements                                                           \
    = typename ::argot::requires_detail::requires_impl< __VA_ARGS__ >::type;   \
                                                                               \
  struct assertion : requirements::assertion {};                               \
}

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/gen/or.hpp>  // Necessary to complete Or from impl_base

#endif

#endif  // ARGOT_GEN_AUTO_CONCEPT_HPP_
