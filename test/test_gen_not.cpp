/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/concept_ensure.hpp>

// TODO(mattcalabrese) Make test more rigorous

namespace {

template< class >
ARGOT_EXPLICIT_CONCEPT( Int )
(
);

}  // namespace

namespace argot {

template<>
struct make_concept_map< Int< int > > {};

}  // namespace argot

namespace {

using argot::Not;

ARGOT_CONCEPT_ENSURE( Int< int > );
ARGOT_CONCEPT_ENSURE( Not< Int< void > > );

}  // namespace
