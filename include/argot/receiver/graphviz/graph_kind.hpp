/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_GRAPH_KIND_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_GRAPH_KIND_HPP_

#include <boost/graph/graph_traits.hpp>

#include <type_traits>

namespace argot {
namespace receiver {
namespace graphviz {

enum class graph_kind
{ directed, strict_directed, undirected, strict_undirected };

namespace graph_kind_detail {

template< graph_kind kind >
struct graph_kind_traits_impl
{
  using is_valid = std::false_type;
};

template< graph_kind kind >
struct graph_kind_traits_impl< graph_kind::directed >
{
  using is_valid = std::true_type;

  using directed_category = boost::directed_tag;

  using edge_parallel_category = allow_parallel_edge_tag;

  // TODO(mattcalabrese) construct instead of returning the constant.
  static Agdesc_t description()
  {
    return Agdirected;
  }
};

template< graph_kind kind >
struct graph_kind_traits_impl< graph_kind::strict_directed >
{
  using is_valid = std::true_type;

  using directed_category = boost::directed_tag;

  using edge_parallel_category = disallow_parallel_edge_tag;

  // TODO(mattcalabrese) construct instead of returning the constant.
  static Agdesc_t description()
  {
    return Agstrictdirected;
  }
};

template< graph_kind kind >
struct graph_kind_traits_impl< graph_kind::undirected >
{
  using is_valid = std::true_type;

  using directed_category = boost::undirected_tag;

  using edge_parallel_category = allow_parallel_edge_tag;

  // TODO(mattcalabrese) construct instead of returning the constant.
  static Agdesc_t description()
  {
    return Agundirected;
  }
};

template< graph_kind kind >
struct graph_kind_traits_impl< graph_kind::strict_undirected >
{
  using is_valid = std::true_type;

  using directed_category = boost::undirected_tag;

  using edge_parallel_category = disallow_parallel_edge_tag;

  // TODO(mattcalabrese) construct instead of returning the constant.
  static Agdesc_t description()
  {
    return Agstrictundirected;
  }
};

}  // namespace argot::receiver::graphviz::graph_kind_detail

template< graph_kind kind >
struct is_valid_graph_kind : graph_kind_detail< kind >::is_valid{};

template< graph_kind kind >
inline
bool constexpr is_valid_graph_kind_v = is_valid_graph_kind< kind >::value;

}  // namespace argot::receiver::graphviz
}  // namespace argot::receiver
}  // namespace argot

#endif  // ARGOT_RECEIVER_GRAPHVIZ_GRAPH_KIND_HPP_
