/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_REGULARITY_FACILITIES_HPP_
#define ARGOT_TEST_REGULARITY_FACILITIES_HPP_

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
#include <argot/gen/and.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>

#include <algorithm>
#include <type_traits>
#include <utility>

namespace argot_test {

enum class default_constructible { no, exceptional, noexcept_, trivial };
enum class move_constructible    { no, exceptional, noexcept_, trivial };
enum class copy_constructible    { no, exceptional, noexcept_, trivial };
enum class move_assignable       { no, exceptional, noexcept_, trivial };
enum class copy_assignable       { no, exceptional, noexcept_, trivial };
enum class destructible          { no, exceptional, noexcept_, trivial };

enum class equality_comparable      { no, exceptional, noexcept_ };
enum class inequality_comparable    { no, exceptional, noexcept_ };
enum class less_comparable          { no, exceptional, noexcept_ };
enum class less_equal_comparable    { no, exceptional, noexcept_ };
enum class greater_equal_comparable { no, exceptional, noexcept_ };
enum class greater_comparable       { no, exceptional, noexcept_ };

enum class swappable { no, exceptional, noexcept_ };
enum class hashable  { no, exceptional, noexcept_ };

template
< default_constructible DefaultConstructibleValue = default_constructible::no
, move_constructible MoveConstructibleValue = move_constructible::no
, copy_constructible CopyConstructibleValue = copy_constructible::no
, move_assignable MoveAssignableValue = move_assignable::no
, copy_assignable CopyAssignableValue = copy_assignable::no
, destructible DestructibleValue = destructible::no
, equality_comparable EqualityComparableValue = equality_comparable::no
, inequality_comparable InequalityComparableValue = inequality_comparable::no
, less_comparable LessComparableValue = less_comparable::no
, less_equal_comparable LessEqualComparableValue = less_equal_comparable::no
, greater_equal_comparable GreaterEqualComparableValue
    = greater_equal_comparable::no
, greater_comparable GreaterComparableValue = greater_comparable::no
, swappable SwappableValue = swappable::no
, hashable HashableValue = hashable::no
>
struct regularity_profile
{
  static constexpr default_constructible default_constructible_kind
    = DefaultConstructibleValue;

  static constexpr move_constructible move_constructible_kind
    = MoveConstructibleValue;

  static constexpr copy_constructible copy_constructible_kind
    = CopyConstructibleValue;

  static constexpr move_assignable move_assignable_kind
    = MoveAssignableValue;

  static constexpr copy_assignable copy_assignable_kind
    = CopyAssignableValue;

  static constexpr destructible destructible_kind
    = DestructibleValue;

  static constexpr equality_comparable equality_comparable_kind
    = EqualityComparableValue;

  static constexpr inequality_comparable inequality_comparable_kind
    = InequalityComparableValue;

  static constexpr less_comparable less_comparable_kind
    = LessComparableValue;

  static constexpr less_equal_comparable less_equal_comparable_kind
    = LessEqualComparableValue;

  static constexpr greater_equal_comparable greater_equal_comparable_kind
    = GreaterEqualComparableValue;

  static constexpr greater_comparable greater_comparable_kind
    = GreaterComparableValue;

  static constexpr swappable swappable_kind
    = SwappableValue;

  static constexpr hashable hashable_kind
    = HashableValue;
};


struct underlying_value_less
{
  template< class Enum, std::enable_if_t< std::is_enum_v< Enum >, int > = 0 >
  constexpr bool operator()( Enum const lhs, Enum const rhs ) const
  {
    using underlying_type = std::underlying_type_t< Enum >;

    return   static_cast< underlying_type >( lhs )
           < static_cast< underlying_type >( rhs );
  }
};

template< class... RegProfs >
struct combine_regularity_profiles
{
  using type
    = regularity_profile
      < std::max
        ( { RegProfs::default_constructible_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::move_constructible_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::copy_constructible_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::move_assignable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::copy_assignable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::destructible_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::equality_comparable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::inequality_comparable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::less_comparable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::less_equal_comparable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::greater_equal_comparable_kind... }
        , underlying_value_less()
        )
      , std::max
        ( { RegProfs::greater_comparable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::swappable_kind... }, underlying_value_less() )
      , std::max
        ( { RegProfs::hashable_kind... }, underlying_value_less() )
      >;
};

template<>
struct combine_regularity_profiles<>
{
  using type = regularity_profile<>;
};

template< class... RegProfs >
using combine_regularity_profiles_t
  = typename combine_regularity_profiles< RegProfs... >::type;

// TODO(mattcalabrese) Perform nested checks lazily
#define ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER( trait_root, concept_ )      \
argot::argot_detail::conditional                                               \
< ARGOT_IS_MODELED( argot::Nothrow ## trait_root< T > ) >::template apply      \
< typename argot::argot_detail::conditional                                    \
  < ARGOT_IS_MODELED( argot::Trivially ## trait_root< T > ) >::template apply  \
  < std::integral_constant< concept_, concept_::trivial >                      \
  , std::integral_constant< concept_, concept_::noexcept_ >                    \
  >                                                                            \
, typename argot::argot_detail::conditional                                    \
  < ARGOT_IS_MODELED( argot::trait_root< T > ) >::template apply               \
  < std::integral_constant< concept_, concept_::exceptional >                  \
  , std::integral_constant< concept_, concept_::no >                           \
  >                                                                            \
>::value

// TODO(mattcalabrese) Perform nested checks lazily
#define ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN( trait_root, concept_ )          \
argot::argot_detail::conditional                                               \
< ARGOT_IS_MODELED( argot::trait_root< T > ) >::template apply                 \
< typename argot::argot_detail::conditional                                    \
  < ARGOT_IS_MODELED( argot::Nothrow ## trait_root< T > ) >::template apply    \
  < std::integral_constant< concept_, concept_::noexcept_ >                    \
  , std::integral_constant< concept_, concept_::exceptional >                  \
  >                                                                            \
, std::integral_constant< concept_, concept_::no >                             \
>::value

template< class T >
using syntactic_regularity_profile_of_t
  = regularity_profile
    < ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER
      ( DefaultConstructible, default_constructible )
    , ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER
      ( MoveConstructible, move_constructible )
    , ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER
      ( CopyConstructible, copy_constructible )
    , ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER
      ( MoveAssignable, move_assignable )
    , ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER
      ( CopyAssignable, copy_assignable )
    , ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER
      ( Destructible, destructible )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( EqualityComparable, equality_comparable )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( InequalityComparable, inequality_comparable )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( LessThanComparable, less_comparable )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( LessEqualComparable, less_equal_comparable )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( GreaterEqualComparable, greater_equal_comparable )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( GreaterThanComparable, greater_comparable )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( Swappable, swappable )
    , ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
      ( Hashable, hashable )
    >;

#undef ARGOT_TEST_DETAIL_CLASSIFY_COMMON_FUN
#undef ARGOT_TEST_DETAIL_CLASSIFY_SPECIAL_MEMBER

using no_default_constructor_profile
  = regularity_profile<>;

using trivial_default_constructor_profile
  = regularity_profile< default_constructible::trivial >;

using nothrow_default_constructor_profile
  = regularity_profile< default_constructible::noexcept_ >;

using exceptional_default_constructor_profile
  = regularity_profile< default_constructible::exceptional >;

using no_move_constructor_profile
  = regularity_profile<>;

using trivial_move_constructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::trivial
    >;

using nothrow_move_constructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::noexcept_
    >;

using exceptional_move_constructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::exceptional
    >;

using no_copy_constructor_profile
  = regularity_profile<>;

using trivial_copy_constructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::trivial
    >;

using nothrow_copy_constructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::noexcept_
    >;

using exceptional_copy_constructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::exceptional
    >;

using no_move_assign_profile
  = regularity_profile<>;

using trivial_move_assign_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::trivial
    >;

using nothrow_move_assign_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::noexcept_
    >;

using exceptional_move_assign_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::exceptional
    >;

using no_copy_assign_profile
  = regularity_profile<>;

using trivial_copy_assign_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::trivial
    >;

using nothrow_copy_assign_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::noexcept_
    >;

using exceptional_copy_assign_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::exceptional
    >;

using no_destructor_profile
  = regularity_profile<>;

using trivial_destructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::trivial
    >;

using nothrow_destructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::noexcept_
    >;

using exceptional_destructor_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::exceptional
    >;

using no_equality_profile
  = regularity_profile<>;

using nothrow_equality_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::noexcept_
    >;

using exceptional_equality_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::exceptional
    >;

using no_inequality_profile
  = regularity_profile<>;

using nothrow_inequality_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::noexcept_
    >;

using exceptional_inequality_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::exceptional
    >;

using no_less_than_profile
  = regularity_profile<>;

using nothrow_less_than_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::noexcept_
    >;

using exceptional_less_than_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::exceptional
    >;

using no_less_equal_profile
  = regularity_profile<>;

using nothrow_less_equal_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::noexcept_
    >;

using exceptional_less_equal_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::exceptional
    >;

using no_greater_equal_profile
  = regularity_profile<>;

using nothrow_greater_equal_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::noexcept_
    >;

using exceptional_greater_equal_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::exceptional
    >;

using no_greater_than_profile
  = regularity_profile<>;

using nothrow_greater_than_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::no
    , greater_comparable::noexcept_
    >;

using exceptional_greater_than_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::no
    , greater_comparable::exceptional
    >;

using no_swap_profile
  = regularity_profile<>;

using nothrow_swap_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::no
    , greater_comparable::no
    , swappable::noexcept_
    >;

using exceptional_swap_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::no
    , greater_comparable::no
    , swappable::exceptional
    >;

using no_hash_profile
  = regularity_profile<>;

using nothrow_hash_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::no
    , greater_comparable::no
    , swappable::no
    , hashable::noexcept_
    >;

using exceptional_hash_profile
  = regularity_profile
    < default_constructible::no
    , move_constructible::no
    , copy_constructible::no
    , move_assignable::no
    , copy_assignable::no
    , destructible::no
    , equality_comparable::no
    , inequality_comparable::no
    , less_comparable::no
    , less_equal_comparable::no
    , greater_equal_comparable::no
    , greater_comparable::no
    , swappable::no
    , hashable::exceptional
    >;

using trivially_complete_profile
  = regularity_profile
    < default_constructible::trivial
    , move_constructible::trivial
    , copy_constructible::trivial
    , move_assignable::trivial
    , copy_assignable::trivial
    , destructible::trivial
    , equality_comparable::noexcept_
    , inequality_comparable::noexcept_
    , less_comparable::noexcept_
    , less_equal_comparable::noexcept_
    , greater_equal_comparable::noexcept_
    , greater_comparable::noexcept_
    , swappable::noexcept_
    , hashable::noexcept_
    >;

#define ARGOT_TEST_COMMON_DECL_CONCEPT_DECL( trait_root, concept_ )            \
template< trait_root concept_ ## Value >                                       \
struct concept_for_ ## trait_root;                                             \
                                                                               \
template< class T, trait_root concept_ ## Value >                              \
using ConceptFor ## concept_                                                   \
  = typename concept_for_ ## trait_root< concept_ ## Value >                   \
    ::template apply< T >;                                                     \
                                                                               \
template<>                                                                     \
struct concept_for_ ## trait_root< trait_root::no >                            \
{                                                                              \
  template< class T >                                                          \
  using apply = argot::Not< argot::concept_< T > >;                            \
};                                                                             \
                                                                               \
template<>                                                                     \
struct concept_for_ ## trait_root< trait_root::noexcept_ >                     \
{                                                                              \
  template< class T >                                                          \
  using apply                                                                  \
    = argot::Nothrow ## concept_< T >;                                         \
};                                                                             \
                                                                               \
template<>                                                                     \
struct concept_for_ ## trait_root< trait_root::exceptional >                   \
{                                                                              \
  template< class T >                                                          \
  using apply                                                                  \
    = argot::And< argot::concept_< T >                                         \
                , argot::Not< argot::Nothrow ## concept_< T > >                \
                >;                                                             \
}

#define ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL( trait_root, concept_ )\
template< trait_root concept_ ## Value >                                       \
struct concept_for_ ## trait_root;                                             \
                                                                               \
template< class T, trait_root concept_ ## Value >                              \
using ConceptFor ## concept_                                                   \
  = typename concept_for_ ## trait_root< concept_ ## Value >                   \
    ::template apply< T >;                                                     \
                                                                               \
template<>                                                                     \
struct concept_for_ ## trait_root< trait_root::no >                            \
{                                                                              \
  template< class T >                                                          \
  using apply = argot::Not< argot::concept_< T > >;                            \
};                                                                             \
                                                                               \
template<>                                                                     \
struct concept_for_ ## trait_root< trait_root::noexcept_ >                     \
{                                                                              \
  template< class T >                                                          \
  using apply                                                                  \
    = argot::And< argot::Nothrow ## concept_< T >                              \
                , argot::Not< argot::Trivially ## concept_< T > >              \
                >;                                                             \
};                                                                             \
                                                                               \
template<>                                                                     \
struct concept_for_ ## trait_root< trait_root::exceptional >                   \
{                                                                              \
  template< class T >                                                          \
  using apply                                                                  \
    = argot::And< argot::concept_< T >                                         \
                , argot::Not< argot::Nothrow ## concept_< T > >                \
                >;                                                             \
};                                                                             \
                                                                               \
template<>                                                                     \
struct concept_for_ ## trait_root< trait_root::trivial >                       \
{                                                                              \
  template< class T >                                                          \
  using apply = argot::Trivially ## concept_< T >;                             \
}

ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL
( default_constructible, DefaultConstructible );

ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL
( move_constructible, MoveConstructible );

ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL
( copy_constructible, CopyConstructible );

ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL
( move_assignable, MoveAssignable );

ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL
( copy_assignable, CopyAssignable );

ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL
( destructible, Destructible );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL( equality_comparable, EqualityComparable );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL
( inequality_comparable, InequalityComparable );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL( less_comparable, LessThanComparable );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL
( less_equal_comparable, LessEqualComparable );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL
( greater_equal_comparable, GreaterEqualComparable );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL
( greater_comparable, GreaterThanComparable );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL( swappable, Swappable );

ARGOT_TEST_COMMON_DECL_CONCEPT_DECL( hashable, Hashable );

#undef ARGOT_TEST_SPECIAL_MEMBER_FUNCTION_CONCEPT_DECL
#undef ARGOT_TEST_COMMON_DECL_CONCEPT_DECL

template< class T
        , class RegularityProfile = syntactic_regularity_profile_of_t< T >
        >
using RegularityConcept
  = argot::And
    < ConceptForDefaultConstructible
      < T, RegularityProfile::default_constructible_kind >
    , ConceptForMoveConstructible
      < T, RegularityProfile::move_constructible_kind >
    , ConceptForCopyConstructible
      < T, RegularityProfile::copy_constructible_kind >
    , ConceptForMoveAssignable
      < T, RegularityProfile::move_assignable_kind >
    , ConceptForCopyAssignable
      < T, RegularityProfile::copy_assignable_kind >
    , ConceptForDestructible
      < T, RegularityProfile::destructible_kind >
    , ConceptForEqualityComparable
      < T, RegularityProfile::equality_comparable_kind >
    , ConceptForInequalityComparable
      < T, RegularityProfile::inequality_comparable_kind >
    , ConceptForLessThanComparable
      < T, RegularityProfile::less_comparable_kind >
    , ConceptForLessEqualComparable
      < T, RegularityProfile::less_equal_comparable_kind >
    , ConceptForGreaterEqualComparable
      < T, RegularityProfile::greater_equal_comparable_kind >
    , ConceptForGreaterThanComparable
      < T, RegularityProfile::greater_comparable_kind >
    , ConceptForSwappable
      < T, RegularityProfile::swappable_kind >
    , ConceptForHashable
      < T, RegularityProfile::hashable_kind >
    >;

} // namespace argot_test

#endif // ARGOT_TEST_REGULARITY_FACILITIES_HPP_
