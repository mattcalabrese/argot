/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_REGULARITY_ARCHETYPES_HPP_
#define ARGOT_TEST_REGULARITY_ARCHETYPES_HPP_

#include <argot/concepts/copy_assignable.hpp>
#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/default_constructible.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/equality_comparable.hpp>
#include <argot/concepts/inequality_comparable.hpp>
#include <argot/concepts/greater_equal_comparable.hpp>
#include <argot/concepts/greater_than_comparable.hpp>
#include <argot/concepts/hashable.hpp>
#include <argot/concepts/less_equal_comparable.hpp>
#include <argot/concepts/less_than_comparable.hpp>
#include <argot/concepts/move_assignable.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/nothrow_copy_assignable.hpp>
#include <argot/concepts/nothrow_copy_constructible.hpp>
#include <argot/concepts/nothrow_default_constructible.hpp>
#include <argot/concepts/nothrow_destructible.hpp>
#include <argot/concepts/nothrow_equality_comparable.hpp>
#include <argot/concepts/nothrow_inequality_comparable.hpp>
#include <argot/concepts/nothrow_greater_equal_comparable.hpp>
#include <argot/concepts/nothrow_greater_than_comparable.hpp>
#include <argot/concepts/nothrow_hashable.hpp>
#include <argot/concepts/nothrow_less_equal_comparable.hpp>
#include <argot/concepts/nothrow_less_than_comparable.hpp>
#include <argot/concepts/nothrow_move_assignable.hpp>
#include <argot/concepts/nothrow_move_constructible.hpp>
#include <argot/concepts/nothrow_swappable.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/swappable.hpp>
#include <argot/concepts/trivially_copy_assignable.hpp>
#include <argot/concepts/trivially_copy_constructible.hpp>
#include <argot/concepts/trivially_default_constructible.hpp>
#include <argot/concepts/trivially_destructible.hpp>
#include <argot/concepts/trivially_move_assignable.hpp>
#include <argot/concepts/trivially_move_constructible.hpp>
#include <argot/detail/constexpr_test_utilities.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include <boost/preprocessor/arithmetic/div.hpp>
#include <boost/preprocessor/arithmetic/mod.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <cstddef>
#include <functional>
#include <utility>

#include "regularity_facilities.hpp"

namespace argot_test {

struct int_member { int member; };
struct default_initializer { int member = 5; };

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
>
struct regularity_archetype_base;

template< class RegularityProfile >
struct regularity_archetype;

template< class... RegProfiles >
using combined_regularity_archetype_t
  = regularity_archetype< combine_regularity_profiles_t< RegProfiles... > >;

#define ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( kind )                          \
using kind = regularity_archetype< kind ## _profile >

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_default_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( trivial_default_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_default_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_default_constructor );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_move_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( trivial_move_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_move_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_move_constructor );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_copy_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( trivial_copy_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_copy_constructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_copy_constructor );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_move_assign );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( trivial_move_assign );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_move_assign );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_move_assign );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_copy_assign );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( trivial_copy_assign );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_copy_assign );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_copy_assign );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_destructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( trivial_destructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_destructor );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_destructor );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_equality );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_equality );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_equality );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_inequality );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_inequality );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_inequality );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_less_than );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_less_than );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_less_than );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_less_equal );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_less_equal );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_less_equal );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_greater_equal );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_greater_equal );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_greater_equal );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_greater_than );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_greater_than );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_greater_than );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_swap );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_swap );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_swap );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( no_hash );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( nothrow_hash );
ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( exceptional_hash );

ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF( trivially_complete );

#undef ARGOT_TEST_DETAIL_DEFINE_ARCHETYPE_OF

struct nothrow_bool
{
  explicit nothrow_bool() = delete;
  ~nothrow_bool() = default;
  nothrow_bool( nothrow_bool const& ) = delete;
  nothrow_bool& operator =( nothrow_bool const& ) = delete;

  explicit constexpr operator bool() const noexcept { return value; }

  static constexpr nothrow_bool make( bool const value ) noexcept
  {
    return nothrow_bool( value );
  }
 private:
  explicit constexpr nothrow_bool( bool const value ) noexcept
    : value( value ) {}

  bool value;
};

struct exceptional_bool
{
  explicit exceptional_bool() = delete;
  ~exceptional_bool() = default;
  exceptional_bool( nothrow_bool const& ) = delete;
  exceptional_bool& operator =( exceptional_bool const& ) = delete;

  explicit constexpr operator bool() const { return value; }

  static constexpr exceptional_bool make( bool const value ) noexcept
  {
    return exceptional_bool( value );
  }
 private:
  explicit constexpr exceptional_bool( bool const value ) noexcept
    : value( value ) {}

  bool value;
};

namespace detail_archetype_operations {

struct adl_base {};

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
bool operator ==
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , equality_comparable::no
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , equality_comparable::no
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) = delete;

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr nothrow_bool operator ==
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , equality_comparable::noexcept_
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , equality_comparable::noexcept_
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return nothrow_bool::make( lhs.member == rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr exceptional_bool operator ==
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , equality_comparable::exceptional
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , equality_comparable::exceptional
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return exceptional_bool::make( lhs.member == rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
bool operator !=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , inequality_comparable::no
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , inequality_comparable::no
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) = delete;

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr nothrow_bool operator !=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , inequality_comparable::noexcept_
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , inequality_comparable::noexcept_
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return nothrow_bool::make( lhs.member != rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr exceptional_bool operator !=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , inequality_comparable::exceptional
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , inequality_comparable::exceptional
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return exceptional_bool::make( lhs.member != rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
bool operator <
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , less_comparable::no
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , less_comparable::no
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) = delete;

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr nothrow_bool operator <
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , less_comparable::noexcept_
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , less_comparable::noexcept_
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return nothrow_bool::make( lhs.member < rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr exceptional_bool operator <
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , less_comparable::exceptional
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , less_comparable::exceptional
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return exceptional_bool::make( lhs.member < rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
bool operator <=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , less_equal_comparable::no
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , less_equal_comparable::no
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) = delete;

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr nothrow_bool operator <=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , less_equal_comparable::noexcept_
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , less_equal_comparable::noexcept_
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return nothrow_bool::make( lhs.member <= rhs.member );;
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr exceptional_bool operator <=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , less_equal_comparable::exceptional
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , less_equal_comparable::exceptional
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return exceptional_bool::make( lhs.member <= rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
bool operator >=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , greater_equal_comparable::no
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , greater_equal_comparable::no
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) = delete;

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr nothrow_bool operator >=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , greater_equal_comparable::noexcept_
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , greater_equal_comparable::noexcept_
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return nothrow_bool::make( lhs.member >= rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr exceptional_bool operator >=
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , greater_equal_comparable::exceptional
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , greater_equal_comparable::exceptional
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return exceptional_bool::make( lhs.member >= rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, swappable SwappableValue
, hashable HashableValue
>
bool operator >
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , greater_comparable::no
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , greater_comparable::no
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) = delete;

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr nothrow_bool operator >
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , greater_comparable::noexcept_
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , greater_comparable::noexcept_
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return nothrow_bool::make( lhs.member > rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, swappable SwappableValue
, hashable HashableValue
>
constexpr exceptional_bool operator >
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , greater_comparable::exceptional
    , SwappableValue
    , HashableValue
    >
  > const& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , greater_comparable::exceptional
    , SwappableValue
    , HashableValue
    >
  > const& rhs
) noexcept
{
  return exceptional_bool::make( lhs.member > rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
void swap
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  >&
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , HashableValue
    >
  >&
) = delete;

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, hashable HashableValue
>
constexpr void swap
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , swappable::noexcept_
    , HashableValue
    >
  >& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
  , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , swappable::noexcept_
    , HashableValue
    >
  >& rhs
) noexcept
{
  std::swap( lhs.member, rhs.member );
}

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, move_assignable MoveAssignableValue
, copy_assignable CopyAssignableValue
, destructible DestructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, hashable HashableValue
>
constexpr void swap
( regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , swappable::exceptional
    , HashableValue
    >
  >& lhs
, regularity_archetype
  < regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , swappable::exceptional
    , HashableValue
    >
  >& rhs
)
{
  std::swap( lhs.member, rhs.member );
}

} // namespace argot_test(::detail_archetype_operations)
} // namespace argot_test

namespace std {

template
< ::argot_test::default_constructible DefaultConstructibleValue
, ::argot_test::move_constructible MoveConstructibleValue
, ::argot_test::copy_constructible CopyConstructibleValue
, ::argot_test::move_assignable MoveAssignableValue
, ::argot_test::copy_assignable CopyAssignableValue
, ::argot_test::destructible DestructibleValue
, ::argot_test::equality_comparable EqualityComparableValue
, ::argot_test::inequality_comparable InequalityComparableValue
, ::argot_test::less_comparable LessComparableValue
, ::argot_test::less_equal_comparable LessEqualComparableValue
, ::argot_test::greater_equal_comparable GreaterEqualComparableValue
, ::argot_test::greater_comparable GreaterComparableValue
, ::argot_test::swappable SwappableValue
>
struct hash
< ::argot_test::regularity_archetype
  < ::argot_test::regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , ::argot_test::hashable::noexcept_
    >
  >
>
{
  using argument_type
    = ::argot_test::regularity_archetype
      < ::argot_test::regularity_profile
        < DefaultConstructibleValue
        , MoveConstructibleValue
        , CopyConstructibleValue
        , MoveAssignableValue
        , CopyAssignableValue
        , DestructibleValue
        , EqualityComparableValue
        , InequalityComparableValue
        , LessComparableValue
        , LessEqualComparableValue
        , GreaterEqualComparableValue
        , GreaterComparableValue
        , SwappableValue
        , ::argot_test::hashable::noexcept_
        >
      >;

  using result_type = std::size_t;

  constexpr std::size_t operator ()( argument_type const& self ) const noexcept
  {
    return self.member;
  }
};

template
< ::argot_test::default_constructible DefaultConstructibleValue
, ::argot_test::move_constructible MoveConstructibleValue
, ::argot_test::copy_constructible CopyConstructibleValue
, ::argot_test::move_assignable MoveAssignableValue
, ::argot_test::copy_assignable CopyAssignableValue
, ::argot_test::destructible DestructibleValue
, ::argot_test::equality_comparable EqualityComparableValue
, ::argot_test::inequality_comparable InequalityComparableValue
, ::argot_test::less_comparable LessComparableValue
, ::argot_test::less_equal_comparable LessEqualComparableValue
, ::argot_test::greater_equal_comparable GreaterEqualComparableValue
, ::argot_test::greater_comparable GreaterComparableValue
, ::argot_test::swappable SwappableValue
>
struct hash
< ::argot_test::regularity_archetype
  < ::argot_test::regularity_profile
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    , MoveAssignableValue
    , CopyAssignableValue
    , DestructibleValue
    , EqualityComparableValue
    , InequalityComparableValue
    , LessComparableValue
    , LessEqualComparableValue
    , GreaterEqualComparableValue
    , GreaterComparableValue
    , SwappableValue
    , ::argot_test::hashable::exceptional
    >
  >
>
{
  using argument_type
    = ::argot_test::regularity_archetype
      < ::argot_test::regularity_profile
        < DefaultConstructibleValue
        , MoveConstructibleValue
        , CopyConstructibleValue
        , MoveAssignableValue
        , CopyAssignableValue
        , DestructibleValue
        , EqualityComparableValue
        , InequalityComparableValue
        , LessComparableValue
        , LessEqualComparableValue
        , GreaterEqualComparableValue
        , GreaterComparableValue
        , SwappableValue
        , ::argot_test::hashable::exceptional
        >
      >;

  using result_type = std::size_t;

  constexpr std::size_t operator ()( argument_type const& self ) const
  {
    return self.member;
  }
};

} // namespace std

namespace argot_test {
namespace detail_regularity_archetype {

struct make {};

} // namespace argot_test(::detail_regularity_archetype)

////////////////////////////////////////////////////////////////////////////////
// Begin generation of regularity_archetype specializations                   //
////////////////////////////////////////////////////////////////////////////////

#define ARGOT_TEST_REGULARITY_PROFILE_default_constructor_0 no
#define ARGOT_TEST_REGULARITY_PROFILE_default_constructor_1 trivial
#define ARGOT_TEST_REGULARITY_PROFILE_default_constructor_2 noexcept_
#define ARGOT_TEST_REGULARITY_PROFILE_default_constructor_3 exceptional

#define ARGOT_TEST_REGULARITY_PROFILE_move_constructor_0 no
#define ARGOT_TEST_REGULARITY_PROFILE_move_constructor_1 trivial
#define ARGOT_TEST_REGULARITY_PROFILE_move_constructor_2 noexcept_
#define ARGOT_TEST_REGULARITY_PROFILE_move_constructor_3 exceptional

#define ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_0 no
#define ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_1 trivial
#define ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_2 noexcept_
#define ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_3 exceptional

#define ARGOT_TEST_REGULARITY_PROFILE_move_assign_0 no
#define ARGOT_TEST_REGULARITY_PROFILE_move_assign_1 trivial
#define ARGOT_TEST_REGULARITY_PROFILE_move_assign_2 noexcept_
#define ARGOT_TEST_REGULARITY_PROFILE_move_assign_3 exceptional

#define ARGOT_TEST_REGULARITY_PROFILE_copy_assign_0 no
#define ARGOT_TEST_REGULARITY_PROFILE_copy_assign_1 trivial
#define ARGOT_TEST_REGULARITY_PROFILE_copy_assign_2 noexcept_
#define ARGOT_TEST_REGULARITY_PROFILE_copy_assign_3 exceptional

#define ARGOT_TEST_REGULARITY_PROFILE_destructor_0 no
#define ARGOT_TEST_REGULARITY_PROFILE_destructor_1 trivial
#define ARGOT_TEST_REGULARITY_PROFILE_destructor_2 noexcept_
#define ARGOT_TEST_REGULARITY_PROFILE_destructor_3 exceptional

#define ARGOT_TEST_REGULARITY_PROFILE_default_constructor()                    \
BOOST_PP_CAT                                                                   \
( ARGOT_TEST_REGULARITY_PROFILE_default_constructor_                           \
, BOOST_PP_MOD                                                                 \
  ( BOOST_PP_DIV( BOOST_PP_ITERATION(), 16 /*num trailing kinds*/ )            \
  , 4 /*num default-constructor kinds*/                                        \
  )                                                                            \
)

#define ARGOT_TEST_REGULARITY_PROFILE_move_constructor()                       \
BOOST_PP_CAT                                                                   \
( ARGOT_TEST_REGULARITY_PROFILE_move_constructor_                              \
, BOOST_PP_MOD                                                                 \
  ( BOOST_PP_DIV( BOOST_PP_ITERATION(), 4 /*num trailing kinds*/ )             \
  , 4 /*num move-constructor kinds*/                                           \
  )                                                                            \
)

#define ARGOT_TEST_REGULARITY_PROFILE_copy_constructor()                       \
BOOST_PP_CAT                                                                   \
( ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_                              \
, BOOST_PP_MOD                                                                 \
  ( BOOST_PP_ITERATION(), 4 /*num copy-constructor kinds*/ )                       \
)

#define ARGOT_TEST_REGULARITY_PROFILE_move_assign()                            \
BOOST_PP_CAT                                                                   \
( ARGOT_TEST_REGULARITY_PROFILE_move_assign_                                   \
, BOOST_PP_MOD                                                                 \
  ( BOOST_PP_DIV( BOOST_PP_ITERATION(), 16 /*num trailing kinds*/ )            \
  , 4 /*num move-assign kinds*/                                                \
  )                                                                            \
)

#define ARGOT_TEST_REGULARITY_PROFILE_copy_assign()                            \
BOOST_PP_CAT                                                                   \
( ARGOT_TEST_REGULARITY_PROFILE_copy_assign_                                   \
, BOOST_PP_MOD                                                                 \
  ( BOOST_PP_DIV( BOOST_PP_ITERATION(), 4 /*num trailing kinds*/ )             \
  , 4 /*num copy-assign kinds*/                                                \
  )                                                                            \
)

#define ARGOT_TEST_REGULARITY_PROFILE_destructor()                             \
BOOST_PP_CAT                                                                   \
( ARGOT_TEST_REGULARITY_PROFILE_destructor_                                    \
, BOOST_PP_MOD( BOOST_PP_ITERATION(), 4 /*num destructor kinds*/ )             \
)

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_no               \
explicit regularity_archetype_base() = delete;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_trivial          \
regularity_archetype_base() = default;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_exceptional      \
constexpr regularity_archetype_base() : member() {}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_noexcept_        \
constexpr regularity_archetype_base() noexcept : member() {}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructor_no                  \
regularity_archetype_base( regularity_archetype_base&& ) = delete;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructor_trivial             \
regularity_archetype_base( regularity_archetype_base&& ) = default;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructor_exceptional         \
constexpr regularity_archetype_base( regularity_archetype_base&& other )       \
  : member( std::move( other.member ) ) {}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructor_noexcept_           \
constexpr                                                                      \
regularity_archetype_base( regularity_archetype_base&& other ) noexcept        \
  : member( std::move( other.member ) ) {}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructor_no                  \
regularity_archetype_base( regularity_archetype_base const& ) = delete;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructor_trivial             \
regularity_archetype_base( regularity_archetype_base const& ) = default;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructor_exceptional         \
constexpr regularity_archetype_base( regularity_archetype_base const& other )  \
  : member( other.member ) {}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructor_noexcept_           \
constexpr                                                                      \
regularity_archetype_base( regularity_archetype_base const& other ) noexcept   \
  : member( other.member ) {}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_no                       \
regularity_archetype& operator =( regularity_archetype&& ) = delete;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_trivial                  \
regularity_archetype& operator =( regularity_archetype&& ) = default;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_exceptional              \
constexpr regularity_archetype& operator =( regularity_archetype&& other )     \
{                                                                              \
  member = std::move( other.member );                                          \
  return *this;                                                                \
}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_noexcept_                \
constexpr                                                                      \
regularity_archetype& operator =( regularity_archetype&& other ) noexcept      \
{                                                                              \
  member = std::move( other.member );                                          \
  return *this;                                                                \
}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_no                       \
regularity_archetype& operator =( regularity_archetype const& ) = delete;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_trivial                  \
regularity_archetype& operator =( regularity_archetype const& ) = default;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_exceptional              \
constexpr                                                                      \
regularity_archetype& operator =( regularity_archetype const& other )          \
{                                                                              \
  member = other.member;                                                       \
  return *this;                                                                \
}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_noexcept_                \
constexpr                                                                      \
regularity_archetype& operator =( regularity_archetype const& other ) noexcept \
{                                                                              \
  member = other.member;                                                       \
  return *this;                                                                \
}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_no                        \
~regularity_archetype() = delete;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_trivial                   \
~regularity_archetype() = default;

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_exceptional               \
~regularity_archetype() noexcept( false ) {}

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_noexcept_                 \
~regularity_archetype() {}

#define ARGOT_TEST_REGULARITY_KIND_OF( member )                                \
BOOST_PP_CAT( ARGOT_TEST_REGULARITY_PROFILE_, member )()

#define ARGOT_TEST_SPECIFY_SPECIAL_MEMBER( member )                            \
BOOST_PP_CAT                                                                   \
( BOOST_PP_CAT( ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_, member )                   \
, BOOST_PP_CAT( _, BOOST_PP_CAT( ARGOT_TEST_REGULARITY_PROFILE_, member )() )  \
)

// NOTE: This include appears in a #if 0 block just so that rebuilds take place
//       whenever the <argot_test/regularity_archetype_maker.hpp> file changes.
#if 0
#include <argot_test/regularity_archetype_maker.hpp>
#endif

#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( 0,   4 /*number of destructor kinds*/                                   \
          * 4 /*number of copy assign kinds*/                                  \
          * 4 /*number of move assign kinds*/ - 1                              \
     , <argot_test/regularity_archetype_maker.hpp>                             \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER
#undef ARGOT_TEST_REGULARITY_KIND_OF
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_noexcept_
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_exceptional
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_trivial
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_destructor_no
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_noexcept_
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_exceptional
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_trivial
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_assign_no
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_noexcept_
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_exceptional
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_trivial
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_assign_no
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructible_noexcept_
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructible_exceptional
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructible_trivial
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_copy_constructible_no
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructible_noexcept_
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructible_exceptional
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructible_trivial
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_move_constructible_no
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_noexcept_
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_exceptional
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_trivial
#undef ARGOT_TEST_SPECIFY_SPECIAL_MEMBER_default_constructor_no
#undef ARGOT_TEST_REGULARITY_PROFILE_destructor
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_assign
#undef ARGOT_TEST_REGULARITY_PROFILE_move_assign
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_constructor
#undef ARGOT_TEST_REGULARITY_PROFILE_move_constructor
#undef ARGOT_TEST_REGULARITY_PROFILE_default_constructor
#undef ARGOT_TEST_REGULARITY_PROFILE_destructor_3
#undef ARGOT_TEST_REGULARITY_PROFILE_destructor_2
#undef ARGOT_TEST_REGULARITY_PROFILE_destructor_1
#undef ARGOT_TEST_REGULARITY_PROFILE_destructor_0
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_assign_3
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_assign_2
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_assign_1
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_assign_0
#undef ARGOT_TEST_REGULARITY_PROFILE_move_assign_3
#undef ARGOT_TEST_REGULARITY_PROFILE_move_assign_2
#undef ARGOT_TEST_REGULARITY_PROFILE_move_assign_1
#undef ARGOT_TEST_REGULARITY_PROFILE_move_assign_0
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_3
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_2
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_1
#undef ARGOT_TEST_REGULARITY_PROFILE_copy_constructor_0
#undef ARGOT_TEST_REGULARITY_PROFILE_move_constructor_3
#undef ARGOT_TEST_REGULARITY_PROFILE_move_constructor_2
#undef ARGOT_TEST_REGULARITY_PROFILE_move_constructor_1
#undef ARGOT_TEST_REGULARITY_PROFILE_move_constructor_0

////////////////////////////////////////////////////////////////////////////////
// End generation of regularity_archetype specializations                     //
////////////////////////////////////////////////////////////////////////////////

} // namespace argot_test

#endif // ARGOT_TEST_REGULARITY_ARCHETYPES_HPP_
