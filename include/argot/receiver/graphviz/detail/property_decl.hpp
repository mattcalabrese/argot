/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_DETAIL_PROPERTY_DECL_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_DETAIL_PROPERTY_DECL_HPP_

#include <boost/graph/properties.hpp>

#define ARGOT_RECEIVER_GRAPHVIZ_DETAIL_PROPERTY_DECL( kind_, name_ )           \
struct name_                                                                   \
{                                                                              \
  using kind = ::boost::kind+ ## _property_tag;                                \
  static char const* name() { return #name_; }                                 \
}

#endif  // ARGOT_RECEIVER_GRAPHVIZ_DETAIL_PROPERTY_DECL_HPP_
