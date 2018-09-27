/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_DETAIL_CONCEPT_ASSERTION
#define ARGOT_GEN_DETAIL_CONCEPT_ASSERTION

#include <argot/gen/requires.hpp>

namespace argot {

template< class ConceptSpec >
struct deduced_concept_assertion
{
  static bool constexpr value = true;

  // NOTE:
  //   If you get a failure here that means a call to ARGOT_CONCEPT_ASSERT
  //   determined a concept was not modeled. To see which concept was not
  //   modeled and where the requirement for it to be modeled came from, read
  //   your compiler error's "required from" notes, which will trace through the
  //   concept hierarchy back to the call to ARGOT_CONCEPT_ASSERT.
  using check
    = typename ::argot::FAILED_BECAUSE_THE_FOLLOWING_CONCEPT_IS_NOT_MODELED
      < ConceptSpec >::CONCEPT_ASSERTION_FAILURE;
};

} // namespace argot

#endif  // ARGOT_GEN_DETAIL_CONCEPT_ASSERTION
