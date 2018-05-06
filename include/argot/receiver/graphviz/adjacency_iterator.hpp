/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_ADJACENCY_ITERATOR_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_ADJACENCY_ITERATOR_HPP_

#include <argot/receiver/graphviz/graph.hpp>
#include <argot/receiver/graphviz/graph_kind.hpp>
#include <argot/receiver/graphviz/out_edge_iterator.hpp>
#include <argot/receiver/graphviz/vertex_descriptor.hpp>

#include <boost/graph/adjacency_iterator.hpp>

namespace argot {
namespace receiver {
namespace graphviz {

// TODO(mattcalabrese) Possibly rewrite this in a way that makes it a type that
//                     is able to be deduced.
template< graph_kind Kind >
using adjacency_iterator_
  = typename boost::adjacency_iterator_generator
    < graph_< Kind >
    , vertex_descriptor_< Kind >
    , out_edge_iterator_< Kind >
    >::type;

using directed_adjacency_iterator
  = adjacency_iterator_< graph_kind::directed >;

using strict_directed_adjacency_iterator
  = adjacency_iterator_< graph_kind::strict_directed >;

using undirected_adjacency_iterator
  = adjacency_iterator_< graph_kind::undirected >;

using strict_undirected_adjacency_iterator
  = adjacency_iterator_< graph_kind::strict_undirected >;

}  // namespace argot::receiver::graphviz
}  // namespace argot::receiver
}  // namespace argot

#endif  // ARGOT_RECEIVER_GRAPHVIZ_ADJACENCY_ITERATOR_HPP_
