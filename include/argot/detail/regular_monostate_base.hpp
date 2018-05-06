/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_REGULAR_MONOSTATE_BASE_HPP_
#define ARGOT_DETAIL_REGULAR_MONOSTATE_BASE_HPP_

namespace argot {
namespace detail_monostate_base {

template< class Child >
struct regular_monostate_base
{
  friend constexpr bool operator ==( Child const&, Child const& )
  {
    return true;
  }

  friend constexpr bool operator !=( Child const&, Child const& )
  {
    return false;
  }

  friend constexpr bool operator <( Child const&, Child const& )
  {
    return false;
  }

  friend constexpr bool operator <=( Child const&, Child const& )
  {
    return true;
  }

  friend constexpr bool operator >=( Child const&, Child const& )
  {
    return true;
  }

  friend constexpr bool operator >( Child const&, Child const& )
  {
    return false;
  }

  friend constexpr void swap( Child&, Child& ) noexcept {}

  // TODO(mattcalabrese) Hash
};

}  // namespace argot(::detail_monostate_base)

namespace argot_detail {

using detail_monostate_base::regular_monostate_base;

}  // namespace argot_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_REGULAR_MONOSTATE_BASE_HPP_
