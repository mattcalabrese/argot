/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_INTEGER_SEQUENCE_HPP_
#define ARGOT_PROV_INTEGER_SEQUENCE_HPP_

#include <argot/prov/unpack_integer_sequence.hpp>

#include <type_traits>
#include <utility>

namespace argot::prov {

// TODO(mattcalabrese) Test the remove_const
// TODO(mattcalabrese) Require integral type (std requires it)
template< auto Size >
using integer_sequence_t
  = result_of_unpack_integer_sequence_t
    < std::make_integer_sequence
      < std::remove_const_t< decltype( Size ) >, Size >
    >;

template< auto Size >
integer_sequence_t< Size > constexpr integer_sequence{};

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_INTEGER_SEQUENCE_HPP_
