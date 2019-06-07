/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_REGULAR_MONOSTATE_BASE_HPP_
#define ARGOT_DETAIL_REGULAR_MONOSTATE_BASE_HPP_

#include <argot/forward.hpp>

#include <cstddef>
#include <functional>
#include <type_traits>

namespace argot {
namespace detail_monostate_base {

template< class Child >
struct regular_monostate_base
{
  friend constexpr bool operator ==( Child const&, Child const& ) noexcept
  {
    return true;
  }

  friend constexpr bool operator !=( Child const&, Child const& ) noexcept
  {
    return false;
  }

  friend constexpr bool operator <( Child const&, Child const& ) noexcept
  {
    return false;
  }

  friend constexpr bool operator <=( Child const&, Child const& ) noexcept
  {
    return true;
  }

  friend constexpr bool operator >=( Child const&, Child const& ) noexcept
  {
    return true;
  }

  friend constexpr bool operator >( Child const&, Child const& ) noexcept
  {
    return false;
  }

  friend constexpr void swap( Child&, Child& ) noexcept {}
};

}  // namespace argot(::detail_monostate_base)

namespace argot_detail {

using detail_monostate_base::regular_monostate_base;

}  // namespace argot_detail
}  // namespace argot

// TODO(mattcalabrese) Use traits to pass by value when feasible.
#define ARGOT_DETAIL_MONOSTATE_HASH_DEFINITION( ... )                          \
struct hash< __VA_ARGS__ >                                                     \
{                                                                              \
  static_assert( ::std::is_same_v< hash, ::std::hash< __VA_ARGS__ > > );       \
                                                                               \
  constexpr ::std::size_t operator()                                           \
  ( ::argot::forward_detail::direct_identity_t< __VA_ARGS__ > const& )         \
  const noexcept                                                               \
  {                                                                            \
    return 0;                                                                  \
  }                                                                            \
}

#endif  // ARGOT_DETAIL_REGULAR_MONOSTATE_BASE_HPP_
