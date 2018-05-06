/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_VERTEX_DESCRIPTOR_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_VERTEX_DESCRIPTOR_HPP_

#include <argot/receiver/graphviz/graph_kind.hpp>

#include <graphviz/cgraph.h>

namespace argot {
namespace receiver {
namespace graphviz {

template< graph_kind Kind >
class vertex_descriptor_
{
  static_assert( is_valid_graph_kind_v< Kind >, "Invalid graph_kind value." );
 public:
  vertex_desciptor() = default;

  explicit vertex_descriptor_( Agnode_t* const node ) : node( node ) {}

  Agnode_t* raw() const { return node; }
 private:
  Agnode_t* node;
};

using directed_vertex_descriptor
  = vertex_descriptor_< graph_kind::directed >;

using strict_directed_vertex_descriptor
  = vertex_descriptor_< graph_kind::strict_directed >;

using undirected_vertex_descriptor
  = vertex_descriptor_< graph_kind::undirected >;

using strict_undirected_vertex_descriptor
  = vertex_descriptor_< graph_kind::strict_undirected >;

}  // namespace argot::receiver::graphviz
}  // namespace argot::receiver
}  // namespace argot

#endif  // ARGOT_RECEIVER_GRAPHVIZ_VERTEX_DESCRIPTOR_HPP_
