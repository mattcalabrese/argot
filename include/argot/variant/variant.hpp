/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_VARIANT_HPP_
#define ARGOT_VARIANT_VARIANT_HPP_

#include <argot/union/destructible_union.hpp>

#include <argot/impossible.hpp>
#include <argot/no_unique_address.hpp>

namespace argot {

template< class... T >
class variant;

template< class T0, class... Tn >
class variant< T0, Tn... >
{
 public:
  // TODO(mattcalabrese)
  //   Default construct to first trivial default-constructible, or first
  //   noexcept alt or first default constructible.

  template< class
 private:
  ARGOT_NO_UNIQUE_ADDRESS destructible_union< T0, Tn... > alternatives;
  std::size_t which; // TODO(mattcalabrese) More sophisticated size type picking
};

template<>
class variant<>
{
  ARGOT_NO_UNIQUE_ADDRESS impossible no_alternatives;
};

}  // namespace argot

#endif  // ARGOT_VARIANT_VARIANT_HPP_
