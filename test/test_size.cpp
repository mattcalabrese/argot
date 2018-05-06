/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/size.hpp>
#include <argot/detail/type_list.hpp>

using argot::call_detail::size;
using argot::call_detail::type_list;

static_assert( size< type_list<> >::value == 0
             , "Empty list does not have size 0."
             );

static_assert( size< type_list< int > >::value == 1
             , "Single element list does not have size 1."
             );

static_assert( size< type_list< int, float > >::value == 2
             , "Two element list does not have size 2."
             );

static_assert( size< type_list< int, float, double > >::value == 3
             , "Three element list does not have size 3."
             );
