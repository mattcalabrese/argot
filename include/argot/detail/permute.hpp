/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_PERMUTE_HPP_
#define ARGOT_DETAIL_PERMUTE_HPP_

#include <argot/detail/concatenate.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

namespace argot {
namespace call_detail {

// Precondition: Each of TypeListLists is a type list of type lists.
template< class... TypeListLists >
struct permute;

template< class... TypeListLists >
using permute_t = typename permute< TypeListLists... >::type;

template<>
struct permute<>
{
  using type
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t<> >;
};

template< class OnlyHeadTypeList
        , class... HeadTailTypeLists
        >
struct permute
< receiver_traits::argument_list_kinds_t< OnlyHeadTypeList >
, receiver_traits::argument_list_kinds_t< HeadTailTypeLists... >
>
{
  using type
    = receiver_traits::argument_list_kinds_t
      < typename receiver_traits::combine_argument_types
        < OnlyHeadTypeList, HeadTailTypeLists >::type...
      >;
};

template< class... HeadTypeLists
        , class... TailTypeListLists
        >
struct permute< receiver_traits::argument_list_kinds_t< HeadTypeLists... >
              , TailTypeListLists...
              >
{
  using type
    = typename concatenate
      < typename permute
        < receiver_traits::argument_list_kinds_t< HeadTypeLists >
        , typename permute< TailTypeListLists... >::type
        >::type...
      >::type;
};

} // namespace argot::call_detail
} // namespace argot

#endif  // ARGOT_DETAIL_PERMUTE_HPP_
