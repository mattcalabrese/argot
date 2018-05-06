/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_ENSURE_HPP_
#define ARGOT_GEN_CONCEPT_ENSURE_HPP_

#include <argot/gen/requires.hpp>

// Always enabled, regardless of configuration.
#define ARGOT_CONCEPT_ENSURE( ... )                                            \
static_assert                                                                  \
( ::argot::requires_detail::requires_impl< __VA_ARGS__ >::type::assertion      \
  ::value                                                                      \
)

#endif  // ARGOT_GEN_CONCEPT_ENSURE_HPP_
