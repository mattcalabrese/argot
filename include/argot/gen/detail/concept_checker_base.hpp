/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_DETAIL_CONCEPT_BASE_HPP_
#define ARGOT_GEN_DETAIL_CONCEPT_BASE_HPP_

#include <argot/gen/requires.hpp>

namespace argot::gen_detail {

struct concept_checker_base
{
  static bool constexpr true_ = true;

  using void_ptr = void*;

  template< class... AndConceptSpecs >
  using and_ = requires_< AndConceptSpecs... >;

  template< class T = void >
  using ARGOT_RESULT_TYPE = T;

  template< class T = void >
  using ARGOT_RESULT_TYPE_ = T;
};

}  // namespace (argot::gen_detail)

#endif  // ARGOT_GEN_DETAIL_CONCEPT_BASE_HPP_
