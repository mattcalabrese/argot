/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_IMPOSSIBLE_HPP_
#define ARGOT_IMPOSSIBLE_HPP_

#include <argot/detail/unreachable.hpp>

#include <boost/config.hpp>

#include <cstddef>

//[description
/*`
argot::impossible is an uninhabitable object type for which all operations are
undefined behavior. Its primary use is as the return type of functions that do
not return (that is they either always either cause the program to halt,
propagate an exception, or have control flow that would lead to undefined
behavior). An instance meets the syntactic requirements for copying, comparison,
swapping, and hashing.

[note_for_ub]
*/
//]

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

struct impossible
{
  explicit impossible() = delete;
  //<-
  [[noreturn]]
  BOOST_FORCEINLINE
  friend bool operator ==( impossible, impossible ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  [[noreturn]]
  BOOST_FORCEINLINE
  friend bool operator !=( impossible, impossible ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  [[noreturn]]
  BOOST_FORCEINLINE
  friend bool operator <( impossible, impossible ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  [[noreturn]]
  BOOST_FORCEINLINE
  friend bool operator <=( impossible, impossible ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  [[noreturn]]
  BOOST_FORCEINLINE
  friend bool operator >=( impossible, impossible ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  [[noreturn]]
  BOOST_FORCEINLINE
  friend bool operator >( impossible, impossible ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  [[noreturn]]
  BOOST_FORCEINLINE
  friend void swap( impossible& lhs, impossible& rhs ) noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  } //->
};

} // namespace argot

//<-

namespace std {

template< class >
struct hash;

template<>
struct hash< ::argot::impossible >
{
  [[noreturn]]
  BOOST_FORCEINLINE
  size_t operator ()( ::argot::impossible ) const noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

}

//->

//]

#endif  // ARGOT_IMPOSSIBLE_HPP_
