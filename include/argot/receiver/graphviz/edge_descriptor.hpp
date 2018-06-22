/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_EDGE_DESCRIPTOR_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_EDGE_DESCRIPTOR_HPP_

#include <argot/receiver/graphviz/graph_kind.hpp>

#include <graphviz/cgraph.h>

namespace argot::receiver::graphviz {

template< graph_kind Kind >
class edge_descriptor_
{
  static_assert( is_valid_graph_kind_v< Kind >, "Invalid graph_kind value." );
 public:
  edge_descriptor_() = default;

  explicit edge_descriptor_( Agedge_t* const edge ) : edge( edge ) {}

  Agedge_t* raw() const { return edge; }
 private:
  Agedge_t* edge;
};

using directed_edge_descriptor
  = edge_descriptor_< graph_kind::directed >;

using strict_directed_edge_descriptor
  = edge_descriptor_< graph_kind::strict_directed >;

using undirected_edge_descriptor
  = edge_descriptor_< graph_kind::undirected >;

using strict_undirected_edge_descriptor
  = edge_descriptor_< graph_kind::strict_undirected >;

}  // namespace (argot::receiver::graphviz)

#endif  // ARGOT_RECEIVER_GRAPHVIZ_EDGE_DESCRIPTOR_HPP_
