/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

template<>
struct regularity_archetype_base
< default_constructible::ARGOT_TEST_REGULARITY_KIND_OF( default_constructor )
, move_constructible::ARGOT_TEST_REGULARITY_KIND_OF( move_constructor )
, copy_constructible::ARGOT_TEST_REGULARITY_KIND_OF( copy_constructor )
> : detail_archetype_operations::adl_base
{
  ARGOT_TEST_SPECIFY_SPECIAL_MEMBER( default_constructor )
  ARGOT_TEST_SPECIFY_SPECIAL_MEMBER( move_constructor )
  ARGOT_TEST_SPECIFY_SPECIAL_MEMBER( copy_constructor )

  regularity_archetype_base& operator =( regularity_archetype_base&& )
    = default;

  regularity_archetype_base& operator =( regularity_archetype_base const& )
    = default;

  ~regularity_archetype_base() = default;

  std::size_t member;

 private:
  template< class >
  friend struct regularity_archetype;

  explicit regularity_archetype_base( std::size_t value ) : member( value ) {}
};

template
< default_constructible DefaultConstructibleValue
, move_constructible MoveConstructibleValue
, copy_constructible CopyConstructibleValue
, equality_comparable EqualityComparableValue
, inequality_comparable InequalityComparableValue
, less_comparable LessComparableValue
, less_equal_comparable LessEqualComparableValue
, greater_equal_comparable GreaterEqualComparableValue
, greater_comparable GreaterComparableValue
, swappable SwappableValue
, hashable HashableValue
>
struct regularity_archetype
< regularity_profile
  < DefaultConstructibleValue
  , MoveConstructibleValue
  , CopyConstructibleValue
  , move_assignable::ARGOT_TEST_REGULARITY_KIND_OF( move_assign )
  , copy_assignable::ARGOT_TEST_REGULARITY_KIND_OF( copy_assign )
  , destructible::ARGOT_TEST_REGULARITY_KIND_OF( destructor )
  , EqualityComparableValue
  , InequalityComparableValue
  , LessComparableValue
  , LessEqualComparableValue
  , GreaterEqualComparableValue
  , GreaterComparableValue
  , SwappableValue
  , HashableValue
  >
> : private regularity_archetype_base
    < DefaultConstructibleValue
    , MoveConstructibleValue
    , CopyConstructibleValue
    >
{
  regularity_archetype() = default;
  regularity_archetype( regularity_archetype&& ) = default;
  regularity_archetype( regularity_archetype const& ) = default;

  ARGOT_TEST_SPECIFY_SPECIAL_MEMBER( move_assign )
  ARGOT_TEST_SPECIFY_SPECIAL_MEMBER( copy_assign )
  ARGOT_TEST_SPECIFY_SPECIAL_MEMBER( destructor )

  struct make_fn
  {
    constexpr
    regularity_archetype operator ()( std::size_t value ) const noexcept
    {
      return regularity_archetype( detail_regularity_archetype::make(), value );
    }
  };

  static constexpr make_fn make{};

  using regularity_archetype_base
        < DefaultConstructibleValue
        , MoveConstructibleValue
        , CopyConstructibleValue
        >::member;

 private:
  constexpr regularity_archetype
  ( detail_regularity_archetype::make, std::size_t value ) noexcept
    : regularity_archetype_base
      < DefaultConstructibleValue
      , MoveConstructibleValue
      , CopyConstructibleValue
      >( value ) {}
};
