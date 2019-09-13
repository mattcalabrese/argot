/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_VARIADIC_GROUP_HPP_
#define ARGOT_DETAIL_VARIADIC_GROUP_HPP_

#include <argot/detail/variadic_range.hpp>
#include <argot/detail/variadic_take.hpp>

#include <cstddef>

namespace argot::detail_argot {

#define ARGOT_DETAIL_MAX_PREPROCESSED_DROP 10

template< std::size_t NumGroups >
struct variadic_group_impl;

// Intentionally undefined.
template<>
struct variadic_group_impl< 0 >;

template<>
struct variadic_group_impl< 1 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply = Result< variadic_take< AmountPerGroup, Group, P... > >;
};

template<>
struct variadic_group_impl< 2 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      >;
};

template<>
struct variadic_group_impl< 3 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      >;
};

template<>
struct variadic_group_impl< 4 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
      >;
};

template<>
struct variadic_group_impl< 5 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 4, AmountPerGroup, Group, P... >
      >;
};

template<>
struct variadic_group_impl< 6 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 4, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 5, AmountPerGroup, Group, P... >
      >;
};

template<>
struct variadic_group_impl< 7 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 4, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 5, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 6, AmountPerGroup, Group, P... >
      >;
};

template<>
struct variadic_group_impl< 8 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 4, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 5, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 6, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 7, AmountPerGroup, Group, P... >
      >;
};

template<>
struct variadic_group_impl< 9 >
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 4, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 5, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 6, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 7, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 8, AmountPerGroup, Group, P... >
      >;
};

template< template< class... > class Result, class... T >
struct variadic_bind_front
{
  template< class... P >
  using apply = Result< T..., P... >;
};

template<>
struct variadic_group_impl< 10 >
{
  static_assert( 10 == ARGOT_DETAIL_MAX_PREPROCESSED_GROUP );

  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = Result
      < variadic_take< AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 4, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 5, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 6, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 7, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 8, AmountPerGroup, Group, P... >
      , variadic_sized_range< AmountPerGroup * 9, AmountPerGroup, Group, P... >
      >;

  template< std::size_t AmountToGroup
          , template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply_recursive
    = typename variadic_group_impl
      < ARGOT_DETAIL_MAX_PREPROCESSED_GROUP - AmountToGroup >::template apply
      < variadic_bind_front
        < Result
        , variadic_take< AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 2, AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 3, AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 4, AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 5, AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 6, AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 7, AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 8, AmountPerGroup, Group, P... >
        , variadic_sized_range< AmountPerGroup * 9, AmountPerGroup, Group, P... >
        >::template apply
      , P...
      >;
};

template< std::size_t NumGroups >
struct variadic_group_impl
{
  template< template< class... > class Result
          , template< class... > class Group
          , std::size_t AmountPerGroup
          , class... P
          >
  using apply
    = variadic_group_impl< ARGOT_DETAIL_MAX_PREPROCESSED_DROP >
      ::template apply_recursive
      < I - ARGOT_DETAIL_MAX_PREPROCESSED_DROP, Result, P... >;
};

#undef ARGOT_DETAIL_MAX_PREPROCESSED_GROUP

template< template< class... > class Group
        , std::size_t AmountPerGroup
        , template< class... > class Result
        , class... P
        >
using variadic_group
  = typename variadic_group_impl< sizeof...( P ) / AmountPerGroup >
    ::template apply< Result, Group, AmountPerGroup, P... >;

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_VARIADIC_GROUP_HPP_
