/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_GRAPH_DETAIL_GRAPH_TRAITS_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_GRAPH_DETAIL_GRAPH_TRAITS_HPP_

#include <argot/receiver/graphviz/graph_kind.hpp>

#include <boost/graph/graph_traits.hpp>

namespace argot {
namespace receiver {
namespace graphviz {

template< graph_kind Kind >
class graph_;

namespace graph_traits_detail {

struct traversal_category
  : public virtual boost::bidirectional_graph_tag
  , public virtual boost::adjacency_graph_tag
  , public virtual boost::vertex_list_graph_tag {};

}  // namespace argot::receiver::graphviz::graph_traits_detail
}  // namespace argot::receiver::graphviz
}  // namespace argot::receiver
}  // namespace argot

#include <argot/receiver/graphviz/edge_descriptor.hpp>
#include <argot/receiver/graphviz/vertex_descriptor.hpp>
#include <argot/receiver/graphviz/edge_iterator.hpp>
#include <argot/receiver/graphviz/in_edge_iterator.hpp>
#include <argot/receiver/graphviz/out_edge_iterator.hpp>
#include <argot/receiver/graphviz/vertex_iterator.hpp>

namespace boost
{

template< argot::receiver::graphviz::graph_kind Kind >
struct graph_traits< argot::receiver::graphviz::graph< Kind > >
{
  static_assert( argot::receiver::graphviz::is_valid_graph_kind_v< Kind >
               , "Invalid graph_kind value."
               );

  using vertex_descriptor
    = argot::receiver::graphviz::vertex_descriptor_< Kind >;

  using edge_descriptor
    = argot::receiver::graphviz::edge_descriptor_< Kind >;

  using directed_category
    = typename argot::receiver::graphviz::graph_kind_detail
      ::graph_kind_traits_impl< Kind >::directed_category;

  using edge_parallel_category
    = typename argot::receiver::graphviz::graph_kind_detail
      ::graph_kind_traits_impl< Kind >::edge_parallel_category;

  using traversal_category
    = argot::receiver::graphviz::graph_traits_detail::traversal_category;

  using vertices_size_type = int;

  using edges_size_type = int;

  using degree_size_type = int;

  using adjacency_iterator
    = argot::receiver::graphviz::adjacency_iterator_< Kind >;

  using out_edge_iterator
    = argot::receiver::graphviz::out_edge_iterator_< Kind >;

  using in_edge_iterator
    = argot::receiver::graphviz::in_edge_iterator_< Kind >;

  using vertex_iterator
    = argot::receiver::graphviz::vertex_iterator_< Kind >;

  using edge_iterator
    = argot::receiver::graphviz::edge_iterator_< Kind >;
};

}  // namespace boost

#endif  // ARGOT_RECEIVER_GRAPHVIZ_GRAPH_DETAIL_GRAPH_TRAITS_HPP_
