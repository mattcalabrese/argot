/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_VARIADIC_CAT_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_VARIADIC_CAT_HPP_

#define ARGOT_GEN_DETAIL_VARIADIC_CAT( left_, ... )                            \
ARGOT_GEN_DETAIL_VARIADIC_CAT_IMPL( left_, __VA_ARGS__ )

#define ARGOT_GEN_DETAIL_VARIADIC_CAT_IMPL( left_, ... )                       \
left_ ## __VA_ARGS__

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_VARIADIC_CAT_HPP_
