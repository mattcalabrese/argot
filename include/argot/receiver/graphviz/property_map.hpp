/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_PROPERTY_MAP_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_PROPERTY_MAP_HPP_

#include <argot/receiver/graphviz/graph_kind.hpp>
#include <argot/receiver/graphviz/graph.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

#include <graphviz/cgraph.h>

#include <string>

namespace argot {
namespace receiver {
namespace graphviz {

namespace property_map_detail {

template< graph_kind GraphKind, class TagKind >
struct key_type_impl;

template< graph_kind GraphKind >
struct key_type_impl< GraphKind, boost::edge_property_tag >
{
  using type
    = typename boost::graph_traits< graph_< GraphKind > >::edge_descriptor;
};

template< graph_kind GraphKind >
struct key_type_impl< GraphKind, boost::vertex_property_tag >
{
  using type
    = typename boost::graph_traits< graph_< GraphKind > >::vertex_descriptor;
};

template< graph_kind GraphKind, class GraphvizPropertyTag >
using key_type_t
  = typename key_type_impl
    < GraphKind, typename GraphvizPropertyTag::kind >::type;

}  // namespace argot::receiver::graphviz::property_map_detail

// TODO(mattcalabrese) Verify that the tag is one of the graphviz tags.
template< graph_kind GraphKind, class GraphvizPropertyTag >
class property_map
{
  using property_tag = GraphvizPropertyTag;
};

template< graph_kind GraphKind, class GraphvizPropertyTag >
std::string
get( property_map< GraphKind, GraphvizPropertyTag > const& graph
   , property_map_detail::key_type_t< GraphKind, GraphvizPropertyTag > key
   )
{
  // TODO(mattcalabrese) Behave properly with respect to default values.
  char const* value = ::agget( key.raw(), GraphvizPropertyTag::name() );
  return value ? std::string( value ) : std::string( "" );
}

template< graph_kind GraphKind, class GraphvizPropertyTag >
void
put( property_map< GraphKind, GraphvizPropertyTag > const& graph
   , property_map_detail::key_type_t< GraphKind, GraphvizPropertyTag > key
   , char const* value
   )
{
  // TODO(mattcalabrese) Likely init all attributes in the graph constructor.
  //                     Change the default to what is documented.
  ::agsafeset( key.raw(), GraphvizPropertyTag::name(), value, "" );
}

}  // namespace argot::receiver::graphviz
}  // namespace argot::receiver
}  // namespace argot

#endif  // ARGOT_RECEIVER_GRAPHVIZ_PROPERTY_MAP_HPP_
