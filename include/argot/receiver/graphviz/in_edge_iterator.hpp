/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_IN_EDGE_ITERATOR_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_IN_EDGE_ITERATOR_HPP_

#include <argot/receiver/graphviz/graph_kind.hpp>
#include <argot/receiver/graphviz/edge_descriptor.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <graphviz/cgraph.h>

namespace argot {
namespace receiver {
namespace graphviz {

template< graph_kind Kind >
class in_edge_iterator_
  : public iterator_facade
    < in_edge_iterator_< Kind >
    , edge_descriptor_< Kind >
    , boost::forward_traversal_tag
    , edge_descriptor_< Kind >&
    , int
    >
{
  static_assert( is_valid_graph_kind_v< Kind >, "Invalid graph_kind value." );
   iterator_core_access;
 public:
  // TODO(mattcalabrese) Possibly make this private.
  explicit in_edge_iterator_( Agedge_t* const edge = nullptr
                            , Agraph_t* const graph = nullptr
                            )
    : edge( edge ), graph( graph ) {}

  Agedge_t* raw() const { return edge; }
 private:
  typename in_edge_iterator_::reference dereference() const { return *edge; }

  bool equal( in_edge_iterator_ const& other ) const
  {
    // TODO(mattcalabrese) Check if this is necessary.
    return ageqedge( edge, other.edge );
  }

  void increment() { edge = agnxtin( graph, edge ); }
  // void decrement() { edge = agprvin( graph, edge ); }

  Agedge_t* edge;
  Agraph_t* graph;
};

using directed_in_edge_iterator
  = in_edge_iterator_< graph_kind::directed >;

using strict_directed_in_edge_iterator
  = in_edge_iterator_< graph_kind::strict_directed >;

using undirected_in_edge_iterator
  = in_edge_iterator_< graph_kind::undirected >;

using strict_undirected_in_edge_iterator
  = in_edge_iterator_< graph_kind::strict_undirected >;

}  // namespace argot::receiver::graphviz
}  // namespace argot::receiver
}  // namespace argot

#endif  // ARGOT_RECEIVER_GRAPHVIZ_IN_EDGE_ITERATOR_HPP_
