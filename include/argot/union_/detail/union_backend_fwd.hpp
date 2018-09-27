/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_DETAIL_UNION_BACKEND_FWD_HPP_
#define ARGOT_UNION_DETAIL_UNION_BACKEND_FWD_HPP_

#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>

#include <cstddef>
#include <type_traits>

namespace argot {

template< class... T >
class union_;

// TODO(mattcalabrese) Move in_place_index_with_result_t to separate file.
template< std::size_t I >
struct in_place_index_with_result_t
{
  explicit in_place_index_with_result_t() = default;
};

template< std::size_t I >
constexpr in_place_index_with_result_t< I > in_place_index_with_result{};

namespace detail_union {

template< std::size_t Index >
struct union_impl_preprocessed;

template< std::size_t Index >
struct union_impl_variadic;

template< class... T >
struct raw_struct;

template<>
struct raw_struct<> {};

namespace no_default_no_destructor {

template< class... T >
struct union_base;

}  // argot::detail_union(::no_default_no_destructor)

namespace no_default_has_destructor {

template< class... T >
struct union_base;

}  // argot::detail_union(::no_default_has_destructor)

namespace has_default_no_destructor {

template< class... T >
struct union_base;

}  // argot::detail_union(::has_default_no_destructor)

namespace has_default_has_destructor {

template< class... T >
struct union_base;

template<>
struct union_base<> {};

}  // argot::detail_union(::has_default_has_destructor)

template< class... T >
using destructor_check_when_has_default
  = typename argot_detail::conditional
    < std::is_trivially_destructible_v< raw_struct< T... > > >
    ::template meta_apply
    < has_default_has_destructor::union_base
    , has_default_no_destructor::union_base
    , T...
    >;

template< class... T >
using destructor_check_when_no_default
  = typename argot_detail::conditional
    < std::is_trivially_destructible_v< raw_struct< T... > > >
    ::template meta_apply
    < no_default_has_destructor::union_base
    , no_default_no_destructor::union_base
    , T...
    >;

template< class... T >
using union_base
  = typename argot_detail::conditional
    < std::is_trivially_default_constructible_v< raw_struct< T... > > >
    ::template meta_apply
    < destructor_check_when_has_default
    , destructor_check_when_no_default
    , T...
    >;

template< std::size_t NumAlternatives, std::size_t Index >
using union_impl
  = typename argot_detail::conditional
    < NumAlternatives <= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES >
    ::template apply
    < union_impl_preprocessed< Index >
    , union_impl_variadic< Index >
    >;

} // namespace argot(::detail_union)
} // namespace argot

#endif  // ARGOT_UNION_DETAIL_UNION_BACKEND_FWD_HPP_
