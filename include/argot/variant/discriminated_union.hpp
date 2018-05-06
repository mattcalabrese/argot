/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_DISCRIMINATED_UNION_HPP_
#define ARGOT_VARIANT_DISCRIMINATED_UNION_HPP_

#include <argot/union/destructible_union.hpp>

#include <argot/no_unique_address.hpp>

namespace argot {

template< class... T >
class discriminated_union
{
 public:
 private:
  ARGOT_NO_UNIQUE_ADDRESS destructible_union< T... > alternatives;
  std::size_t which; // TODO(mattcalabrese) More sophisticated size type picking
};

}  // namespace argot

#endif  // ARGOT_VARIANT_DISCRIMINATED_UNION_HPP_
