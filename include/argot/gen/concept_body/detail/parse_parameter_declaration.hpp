/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_PARAMETER_DECLARATION_HPP_
#define ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_PARAMETER_DECLARATION_HPP_

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_requires_clause.hpp>

////////////////////////////////////////////////////////////////////////////////
// parameter-declaration:                                                     //
//   (~~token-soup~~ ?,,,) ?identifier-like                                   //
//   (~~token-soup~~) default(identifier-like, type-like)                     //
////////////////////////////////////////////////////////////////////////////////

#define ARGOT_GEN_DETAIL_PARSE_PARAMETER_DECLARATION( ... )                    \

#endif  // ARGOT_GEN_CONCEPT_BODY_DETAIL_PARSE_PARAMETER_DECLARATION_HPP_
