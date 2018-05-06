/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_VERTEX_ITERATOR_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_VERTEX_ITERATOR_HPP_

#include <argot/receiver/graphviz/graph_kind.hpp>
#include <argot/receiver/graphviz/vertex_descriptor.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <graphviz/cgraph.h>

namespace argot {
namespace receiver {
namespace graphviz {

template< graph_kind Kind >
class vertex_iterator_
  : public iterator_facade
    < vertex_iterator_< Kind >
    , vertex_descriptor_< Kind >
    , boost::forward_traversal_tag
    , vertex_descriptor_< Kind >&
    , int
    >
{
  static_assert( is_valid_graph_kind_v< Kind >, "Invalid graph_kind value." );
   iterator_core_access;
 public:
  // TODO(mattcalabrese) Possibly make this private.
  explicit vertex_iterator_( Agnode_t* const node = nullptr
                           , Agraph_t* const graph = nullptr
                           )
    : node( node ), graph( graph ) {}

  Agnode_t* raw() const { return node; }
 private:
  typename vertex_iterator_::reference dereference() const { return *node; }

  bool equal( vertex_iterator_ const& other ) const
  {
    return node == other.node;
  }

  void increment() { node = agnxtnode( graph, node ); }
  // void decrement() { node = agprvnode( graph, node ); }

  Agnode_t* node;
  Agraph_t* graph;
};

using directed_vertex_iterator
  = vertex_iterator_< graph_kind::directed >;

using strict_directed_vertex_iterator
  = vertex_iterator_< graph_kind::strict_directed >;

using undirected_vertex_iterator
  = vertex_iterator_< graph_kind::undirected >;

using strict_undirected_vertex_iterator
  = vertex_iterator_< graph_kind::strict_undirected >;

}  // namespace argot::receiver::graphviz
}  // namespace argot::receiver
}  // namespace argot

#endif  // ARGOT_RECEIVER_GRAPHVIZ_VERTEX_ITERATOR_HPP_
