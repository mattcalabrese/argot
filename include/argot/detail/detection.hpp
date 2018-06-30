/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_DETECTION_HPP_
#define ARGOT_DETAIL_DETECTION_HPP_

#include <type_traits>
#include <utility>

namespace argot::call_detail {

template< class /*Enabler*/
        , template< class... /*P*/ > class Temp, class... P
        >
struct lazy_expand_impl {};

template< template< class... /*P*/ > class Temp, class... P >
struct lazy_expand_impl< std::void_t< Temp< P... > >, Temp, P... >
{
  using type = Temp< P... >;
};

template< template< class... /*P*/ > class Temp, class... P >
struct lazy_expand : lazy_expand_impl< void, Temp, P... > {};

template< class /*Enabler*/
        , template< class... /*P*/ > class Temp, class... P
        >
struct lazy_inherit_impl {};

template< template< class... /*P*/ > class Temp, class... P >
struct lazy_inherit_impl< std::void_t< Temp< P... > >, Temp, P... >
  : Temp< P... > {};

template< template< class... /*P*/ > class Temp, class... P >
struct lazy_inherit : lazy_inherit_impl< void, Temp, P... > {};

template< class Enabler, template< class... /*P*/ > class Temp, class... P >
struct is_detected_impl : std::false_type {};

template< template< class... /*P*/ > class Temp, class... P >
struct is_detected_impl< std::void_t< Temp< P... > >, Temp, P... >
  : std::true_type {};

template< template< class... /*P*/ > class Temp, class... P >
struct is_detected : is_detected_impl< void, Temp, P... >::type {};

template< template< class... /*P*/ > class Temp, class... P >
bool constexpr is_detected_v = is_detected_impl< void, Temp, P... >::value;

template< bool T >
struct detached_fast_enable_if
{
  using _ = detached_fast_enable_if;

  template< bool V >
  using and_ = detached_fast_enable_if< V >;

  template< class Result = void >
  using apply = Result;

  using void_ = void;
};

template<>
struct detached_fast_enable_if< false > {};

template< bool T, class Result = void >
using fast_enable_if_t
  = typename detached_fast_enable_if< T >::_::template apply< Result >;

template< template< auto /*I*/, class /*T*/ > class Temp, auto I, class T
        , class /*Enabler*/ = void
        >
struct lazy_expand_get_impl {};

template< template< auto /*I*/, class /*T*/ > class Temp, auto I, class T >
struct lazy_expand_get_impl< Temp, I, T, std::void_t< Temp< I, T > > >
{
  using type = Temp< I, T >;
};

template< template< auto /*I*/, class /*T*/ > class Temp, auto I, class T >
struct lazy_expand_get : lazy_expand_get_impl< Temp, I, T > {};

template< template< class /*T*/, auto /*I*/ > class Temp, class T, auto I
        , class /*Enabler*/ = void
        >
struct lazy_expand_access_impl {};

template< template< class /*T*/, auto /*I*/ > class Temp, class T, auto I >
struct lazy_expand_access_impl< Temp, T, I, std::void_t< Temp< T, I > > >
{
  using type = Temp< T, I >;
};

template< template< class /*T*/, auto /*I*/ > class Temp, class T, auto I >
struct lazy_expand_access : lazy_expand_access_impl< Temp, T, I > {};

}  // namespace (argot::call_detail)

#endif  // ARGOT_DETAIL_DETECTION_HPP_
