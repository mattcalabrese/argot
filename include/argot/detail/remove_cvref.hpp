/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_REMOVE_CVREF_HPP_
#define ARGOT_DETAIL_REMOVE_CVREF_HPP_

namespace argot::detail_argot {

template< class T >
struct remove_cvref
{
  using type = T;
};

template< class T >
struct remove_cvref< T const >
{
  using type = T;
};

template< class T >
struct remove_cvref< T volatile >
{
  using type = T;
};

template< class T >
struct remove_cvref< T volatile const >
{
  using type = T;
};

template< class T >
struct remove_cvref< T& >
{
  using type = T;
};

template< class T >
struct remove_cvref< T const& >
{
  using type = T;
};

template< class T >
struct remove_cvref< T volatile& >
{
  using type = T;
};

template< class T >
struct remove_cvref< T volatile const& >
{
  using type = T;
};

template< class T >
struct remove_cvref< T&& >
{
  using type = T;
};

template< class T >
struct remove_cvref< T const&& >
{
  using type = T;
};

template< class T >
struct remove_cvref< T volatile&& >
{
  using type = T;
};

template< class T >
struct remove_cvref< T volatile const&& >
{
  using type = T;
};

template< class T >
using remove_cvref_t = typename remove_cvref< T >::type;

}  // namespace (argot::detail_argot)

#endif  // ARGOT_DETAIL_REMOVE_CVREF_HPP_
