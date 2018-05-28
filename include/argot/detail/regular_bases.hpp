/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_REGULAR_BASES_HPP_
#define ARGOT_DETAIL_REGULAR_BASES_HPP_

#include <argot/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>

#include <type_traits>

// TODO(mattcalabrese) Add similar utilities for hash support.

namespace argot {
namespace detail_regular_bases {

enum class may_exist { no, yes };
enum class may_be_noexcept { no, yes };
enum class is_noexcept { no, yes };

template< class T, class /*Enabler*/ = void >
inline constexpr bool const& has_proper_equality_operator_v
  = std::false_type::value;

template< class T >
inline constexpr bool const& has_proper_equality_operator_v
< T
, std::void_t
  < decltype
    (   ( ARGOT_DECLVAL( T const& ) == ARGOT_DECLVAL( T const& ) )
      ? true : false
    )
  >
> = std::true_type::value;

template< class T, class /*Enabler*/ = void >
inline constexpr bool const& has_proper_less_than_operator_v
  = std::false_type::value;

template< class T >
inline constexpr bool const& has_proper_less_than_operator_v
< T
, std::void_t
  < decltype
    (   ( ARGOT_DECLVAL( T const& ) < ARGOT_DECLVAL( T const& ) )
      ? true : false
    )
  >
> = std::true_type::value;

// Precondition: `T` is equality-comparable.
template< class T >
inline constexpr bool const& is_nothrow_equality_comparable_v
  = std::bool_constant
    < noexcept
      ( ARGOT_DECLVAL( T const& ) == ARGOT_DECLVAL( T const& ) ? true : false )
    >::value;

// Precondition: `T` is less-than-comparable.
template< class T >
inline constexpr bool const& is_nothrow_less_than_comparable_v
  = std::bool_constant
    < noexcept
      ( ARGOT_DECLVAL( T const& ) < ARGOT_DECLVAL( T const& ) ? true : false )
    >::value;

template< class Child >
struct not_equality_comparable
{
  static constexpr bool const& equality_comparable_v
    = std::false_type::value;

  static constexpr bool const& nothrow_equality_comparable_v
    = std::false_type::value;
};

template< class Child >
struct not_less_than_comparable
{
  static constexpr bool const& less_than_comparable_v
    = std::false_type::value;

  static constexpr bool const& nothrow_less_than_comparable_v
    = std::false_type::value;
};

template< class Child >
struct not_swappable
{
  static constexpr bool const& swappable_v = std::false_type::value;

  static constexpr bool const& nothrow_swappable_v = std::false_type::value;
};

template< class Child, class /*Noexcept*/, class... /*Dependencies*/ >
using not_equality_comparable_ = not_equality_comparable< Child >;

template< class Child, class /*Noexcept*/, class... /*Dependencies*/ >
using not_less_than_comparable_ = not_less_than_comparable< Child >;

template< class Child, class /*Noexcept*/, class... /*Dependencies*/ >
using not_swappable_ = not_swappable< Child >;

template< class... >
using always_false = std::false_type;

template< class... Dependencies >
using all_are_equality_comparable
  = std::bool_constant
    < ( has_proper_equality_operator_v< Dependencies > && ... ) >;

template< class... Dependencies >
using all_are_less_than_comparable
  = std::bool_constant
    < ( has_proper_less_than_operator_v< Dependencies > && ... ) >;

template< class... Dependencies >
using all_are_swappable
  = std::bool_constant< ( std::is_swappable_v< Dependencies > && ... ) >;

template< class... Dependencies >
using all_are_nothrow_equality_comparable
  = std::bool_constant
    < ( is_nothrow_equality_comparable_v< Dependencies > && ... ) >;

template< class... Dependencies >
using all_are_nothrow_less_than_comparable
  = std::bool_constant
    < ( is_nothrow_less_than_comparable_v< Dependencies > && ... ) >;

template< class... Dependencies >
using all_are_nothrow_swappable
  = std::bool_constant
    < ( std::is_nothrow_swappable_v< Dependencies > && ... ) >;

struct regular_core_access
{
  template< class Child, is_noexcept IsNoexcept >
  struct equality_comparable
  {
    static constexpr bool const& equality_comparable_v = std::true_type::value;

    static constexpr bool const& nothrow_equality_comparable_v
      = std::bool_constant< IsNoexcept == is_noexcept::yes >::value;
   private:
    friend constexpr bool operator ==( Child const& lhs, Child const& rhs )
      noexcept( nothrow_equality_comparable_v )
    {
      return lhs.detail_argot_equals( rhs );
    }

    friend constexpr bool operator !=( Child const& lhs, Child const& rhs )
      noexcept( nothrow_equality_comparable_v )
    {
      return !lhs.detail_argot_equals( rhs );
    }
  };

  template< class Child, is_noexcept IsNoexcept >
  struct less_than_comparable
  {
    static constexpr bool const& less_than_comparable_v = std::true_type::value;

    static constexpr bool const& nothrow_less_than_comparable_v
      = std::bool_constant< IsNoexcept == is_noexcept::yes >::value;
   private:
    friend constexpr bool operator <( Child const& lhs, Child const& rhs )
      noexcept( nothrow_less_than_comparable_v )
    {
      return lhs.detail_argot_less( rhs );
    }

    friend constexpr bool operator <=( Child const& lhs, Child const& rhs )
      noexcept( nothrow_less_than_comparable_v )
    {
      return !rhs.detail_argot_less( lhs );
    }

    friend constexpr bool operator >=( Child const& lhs, Child const& rhs )
      noexcept( nothrow_less_than_comparable_v )
    {
      return !lhs.detail_argot_less( rhs );
    }

    friend constexpr bool operator >( Child const& lhs, Child const& rhs )
      noexcept( nothrow_less_than_comparable_v )
    {
      return rhs.detail_argot_less( lhs );
    }
  };

  template< class Child, is_noexcept IsNoexcept >
  struct swappable
  {
    static constexpr bool const& swappable_v = std::true_type::value;

    static constexpr bool const& nothrow_swappable_v
      = std::bool_constant< IsNoexcept == is_noexcept::yes >::value;
   private:
    friend constexpr void swap( Child& lhs, Child& rhs )
      noexcept( nothrow_swappable_v )
    {
      lhs.detail_argot_swap( rhs );
    }
  };

  template< class Child, class Noexcept, class... Dependencies >
  using equality_comparable_
    = equality_comparable
      < Child
      , argot_detail::conditional< Noexcept::value >::template meta_apply
        < all_are_nothrow_equality_comparable, always_false, Dependencies... >
        ::value ? is_noexcept::yes : is_noexcept::no
      >;

  template< class Child, class Noexcept, class... Dependencies >
  using less_than_comparable_
    = less_than_comparable
      < Child
      , argot_detail::conditional< Noexcept::value >::template meta_apply
        < all_are_nothrow_less_than_comparable, always_false, Dependencies... >
        ::value ? is_noexcept::yes : is_noexcept::no
      >;

  template< class Child, class Noexcept, class... Dependencies >
  using swappable_
    = swappable
      < Child
      , argot_detail::conditional< Noexcept::value >::template meta_apply
        < all_are_nothrow_swappable, always_false, Dependencies... >
        ::value ? is_noexcept::yes : is_noexcept::no
      >;
};

template< class Child, may_be_noexcept Noexcept
        , may_exist Condition = may_exist::yes
        , class... Dependencies
        >
using equality_comparable
  = typename argot_detail::conditional
    < argot_detail::conditional< Condition == may_exist::yes >
      ::template meta_apply
      < all_are_equality_comparable, always_false, Dependencies... >::value
    >::template meta_apply
    < regular_core_access::equality_comparable_, not_equality_comparable_
    , Child
    , std::bool_constant< Noexcept == may_be_noexcept::yes ? true : false >
    , Dependencies...
    >;

template< class Child, may_be_noexcept Noexcept
        , may_exist Condition = may_exist::yes
        , class... Dependencies
        >
using less_than_comparable
  = typename argot_detail::conditional
    < argot_detail::conditional< Condition == may_exist::yes >
      ::template meta_apply
      < all_are_less_than_comparable, always_false, Dependencies... >::value
    >::template meta_apply
    < regular_core_access::less_than_comparable_, not_less_than_comparable_
    , Child
    , std::bool_constant< Noexcept == may_be_noexcept::yes ? true : false >
    , Dependencies...
    >;

template< class Child, may_be_noexcept Noexcept
        , may_exist Condition = may_exist::yes
        , class... Dependencies
        >
using swappable
  = typename argot_detail::conditional
    < argot_detail::conditional< Condition == may_exist::yes >
      ::template meta_apply< all_are_swappable, always_false, Dependencies... >
      ::value
    >::template meta_apply
    < regular_core_access::swappable_, not_swappable_
    , Child
    , std::bool_constant< Noexcept == may_be_noexcept::yes ? true : false >
    , Dependencies...
    >;

}  // namespace detail_regular_bases
}  // namespace argot

#endif  // ARGOT_DETAIL_REGULAR_BASES_HPP_
