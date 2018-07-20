/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

// Special-member-function concepts (non-mutating)
#include "test_concepts_default_constructible.cpp"
#include "test_concepts_nothrow_default_constructible.cpp"
#include "test_concepts_trivially_default_constructible.cpp"
#include "test_concepts_move_constructible.cpp"
#include "test_concepts_nothrow_move_constructible.cpp"
#include "test_concepts_trivially_move_constructible.cpp"
#include "test_concepts_copy_constructible.cpp"
#include "test_concepts_nothrow_copy_constructible.cpp"
#include "test_concepts_trivially_copy_constructible.cpp"
#include "test_concepts_destructible.cpp"
#include "test_concepts_nothrow_destructible.cpp"
#include "test_concepts_trivially_destructible.cpp"

// Special-member-function concepts (mutating)
#include "test_concepts_move_assignable.cpp"
#include "test_concepts_nothrow_move_assignable.cpp"
#include "test_concepts_trivially_move_assignable.cpp"
#include "test_concepts_copy_assignable.cpp"
#include "test_concepts_nothrow_copy_assignable.cpp"
#include "test_concepts_trivially_copy_assignable.cpp"

// Comparisons (equality)
#include "test_concepts_equality_comparable.cpp"
#include "test_concepts_nothrow_equality_comparable.cpp"
#include "test_concepts_inequality_comparable.cpp"
#include "test_concepts_nothrow_inequality_comparable.cpp"

// Comparisons (ordering)
#include "test_concepts_less_than_comparable.cpp"
#include "test_concepts_nothrow_less_than_comparable.cpp"
#include "test_concepts_less_equal_comparable.cpp"
#include "test_concepts_nothrow_less_equal_comparable.cpp"
#include "test_concepts_greater_equal_comparable.cpp"
#include "test_concepts_nothrow_greater_equal_comparable.cpp"
#include "test_concepts_greater_than_comparable.cpp"
#include "test_concepts_nothrow_greater_than_comparable.cpp"

// Swap
#include "test_concepts_swappable.cpp"
#include "test_concepts_nothrow_swappable.cpp"

// Hash
#include "test_concepts_hashable.cpp"
#include "test_concepts_nothrow_hashable.cpp"
