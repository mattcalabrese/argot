/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_CONCATENATE_HPP_
#define ARGOT_DETAIL_CONCATENATE_HPP_

#include <argot/receiver_traits/argument_list_kinds.hpp>

namespace argot {
namespace call_detail {

template< class... TypeLists >
struct concatenate;

template< class... TypeLists >
using concatenate_t = typename concatenate< TypeLists... >::type;

template<>
struct concatenate<>
{
  using type = receiver_traits::argument_list_kinds_t<>;
};

template< class... T >
struct concatenate< receiver_traits::argument_list_kinds_t< T... > >
{
  using type = receiver_traits::argument_list_kinds_t< T... >;
};

template< class... FirstTypes, class...SecondTypes
        , class... TailTypeLists
        >
struct concatenate
       < receiver_traits::argument_list_kinds_t< FirstTypes... >
       , receiver_traits::argument_list_kinds_t< SecondTypes... >
       , TailTypeLists...
       >
{
  using type
    = typename concatenate
      < receiver_traits::argument_list_kinds_t
        < FirstTypes..., SecondTypes... >
      , TailTypeLists...
      >::type;
};

}  // namespace argot::call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_CONCATENATE_HPP_
