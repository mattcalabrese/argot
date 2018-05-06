/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VALUE_LIST_HPP_
#define ARGOT_VALUE_LIST_HPP_

#define ARGOT_DETAIL_BROKEN_TEMPLATE_AUTO 1

namespace argot {

template< auto... Values >
struct value_list_t {};

template< class... ValueLists >
struct concatenate_value_lists;

template< class... ValueLists >
using concatenate_value_lists_t
  = typename concatenate_value_lists< ValueLists... >::type;

template<>
struct concatenate_value_lists<>
{
  using type = value_list_t<>;
};

template< auto... V >
struct concatenate_value_lists< value_list_t< V... > >
{
  using type = value_list_t< V... >;
};

template< auto... FirstValues, auto...SecondValues, class... TailValueLists >
struct concatenate_value_lists
       < value_list_t< FirstValues... >
       , value_list_t< SecondValues... >
       , TailValueLists...
       >
{
  using type
    = typename concatenate_value_lists
      < value_list_t< FirstValues..., SecondValues... >
      , TailValueLists...
      >::type;
};

}  // namespace argot

#endif // ARGOT_VALUE_LIST_HPP_
