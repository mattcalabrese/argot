/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/union_.hpp>

#include <argot/concepts/constructible.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include <cstddef>

namespace {

namespace union_traits = argot::union_traits;

using argot::Constructible;
using argot::Not;

using argot::union_;

using union_t = union_<>;

template< std::size_t >
inline constexpr bool always_true_c = true;

// This will fail to compile if union_t is an incomplete type.
// TODO(mattcalabrese) Create a better check to be sure the type is complete.
static_assert( always_true_c< sizeof( union_t ) > );

ARGOT_CONCEPT_ENSURE( Not< Constructible< union_t > > );

}  // namespace
