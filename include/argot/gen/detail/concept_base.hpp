/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_DETAIL_CONCEPT_BASE_HPP_
#define ARGOT_GEN_DETAIL_CONCEPT_BASE_HPP_

namespace argot::gen_detail {

template< class... ConceptSpecs >
struct requires_impl;

struct concept_base
{
  using requirements = requires_impl<>;

  using assertion = requirements::assertion;
};

}  // namespace (argot::gen_detail)

#endif  // ARGOT_GEN_DETAIL_CONCEPT_BASE_HPP_
