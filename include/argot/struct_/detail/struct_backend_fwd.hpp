/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_
#define ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_

#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/in_place_with_result.hpp>

#include <cstddef>
#include <type_traits>

namespace argot {

namespace detail_struct {

template< class... >
struct struct_base;

template<>
struct struct_base<>
{
  struct_base() = default;
  explicit constexpr struct_base( in_place_with_result_t ) noexcept {}
};

template< std::size_t Index >
struct struct_impl_preprocessed;

template< std::size_t Index >
struct struct_impl_variadic;

template< std::size_t NumAlternatives, std::size_t Index >
using struct_impl
  = typename argot_detail::conditional
    < NumAlternatives <= ARGOT_MAX_PREPROCESSED_STRUCT_ELEMENTS >
    ::template apply
    < struct_impl_preprocessed< Index >
    , struct_impl_variadic< Index >
    >;

}  // namespace argot(::detail_struct)
}  // namespace argot

#endif  // ARGOT_STRUCT_DETAIL_STRUCT_BACKEND_FWD_HPP_
