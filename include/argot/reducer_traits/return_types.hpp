/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TRAITS_RETURN_TYPES_HPP_
#define ARGOT_REDUCER_TRAITS_RETURN_TYPES_HPP_

namespace argot {
namespace reducer_traits {

template< class... ReturnTypes >
struct return_types_t{};

template< class... ReturnTypes >
return_types_t< ReturnTypes... > constexpr return_types{};

}  // namespace argot::reducer_traits
}  // namespace argot

#endif  // ARGOT_REDUCER_TRAITS_POSSIBLE_RETURN_TYPES_HPP_
