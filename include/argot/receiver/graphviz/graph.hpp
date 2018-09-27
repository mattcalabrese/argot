/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_GRAPH_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_GRAPH_HPP_

#include <argot/receiver/graphviz/graph_kind.hpp>
#include <argot/receiver/graphviz/graph/detail/graph_traits.hpp>

#include <boost/graph/copy.hpp>
#include <boost/optional/optional.hpp>
#include <boost/none.hpp>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>

namespace argot {
namespace receiver {
namespace graphviz {

// TODO(mattcalabrese) Possibly make not bidirectional
//                     (check if each end iterator is decrementable)
template< graph_kind Kind >
class graph_
{
  static_assert( is_valid_graph_kind_v< Kind >, "Invalid graph_kind value." );
 public:
  using kind = std::integral_constant< graph_kind, Kind >;
  static graph_kind constexpr kind_v = kind::value;

  graph_() = delete;  // TODO(mattcalabrese) Define to default construct.
  graph_( graph_&& ) = default;
  graph_& operator =( graph_&& ) = default;

  graph_( graph_ const& other )
    : graph_()
  {
    boost::copy_graph( other, *this );
    // TODO(mattcalabrese) Check for errors.
  }

  graph_& operator =( graph_ const& other )
  {
    if( this != &other )
      *this = graph_( other );

    return *this;
  }

  // TODO(mattcalabrese) Change this to return expected
  static boost::optional< graph_ >
  construct( std::string name, kind const graph_kind /*, options*/ )
  {
    boost::optional< Agdesc_t > const graph_descriptor
      = kind_to_descriptor( graph_kind );

    // If we got a valid descriptor.
    if( graph_descriptor )
    {
      // NOTE: graphviz is not const-correct
      unique_ptr_type underlying_graph_init
      ( ::agopen( const_cast< char* >( name.c_str() ), *graph_descriptor
                , nullptr /*TODO(mattcalabrese) use*/
                )
      );

      // TODO(mattcalabrese) Check for errors if possible.
      return graph_( std::move( underlying_graph_init ) );
    }
    else
    {
      return boost::none;
    }
  }

  Agraph_t* raw() { return underlying_graph.get(); }
  Agraph_t const* raw() const { return underlying_graph.get(); }
 private:
  struct deleter
  {
    void operator ()( Agraph_t* const graph_to_close ) const
    {
      ::agclose( graph_to_close );
    }
  };

  using unique_ptr_type = std::unique_ptr< Agraph_t, deleter >;

  explicit graph_( unique_ptr_type underlying_graph )
    : underlying_graph( std::move( underlying_graph ) ) {}

  unique_ptr_type underlying_graph;
};

using directed_graph = graph_< graph_kind::directed >;
using strict_directed_graph = graph_< graph_kind::strict_directed >;
using undirected_graph = graph_< graph_kind::undirected >;
using strict_undirected_graph = graph_< graph_kind::strict_undirected >;

template< graph_kind Kind >
std::pair
< typename boost::graph_traits< graph_< Kind > >::out_edge_iterator
, typename boost::graph_traits< graph_< Kind > >::out_edge_iterator
>
out_edges
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind > const& graph
)
{
  using iterator
    = typename boost::graph_traits< graph_< Kind > >::out_edge_iterator;

  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return std::make_pair
  ( iterator( ::agfstout( raw_graph, vertex.raw() ), raw_graph )
  , iterator( nullptr, raw_graph )
  );
}

template< graph_kind Kind >
typename boost::graph_traits< graph_< Kind > >::vertex_descriptor
source( typename boost::graph_traits< graph_< Kind > >::edge_descriptor edge
      , graph_< Kind > const& graph
      )
{
  // NOTE: Not qualified because it's a macro
  return agtail( edge.raw() );
}

template< graph_kind Kind >
typename boost::graph_traits< graph_< Kind > >::vertex_descriptor
target( typename boost::graph_traits< graph_< Kind > >::edge_descriptor edge
      , graph_< Kind > const& graph
      )
{
  // NOTE: Not qualified because it's a macro
  return aghead( edge.raw() );
}

template< graph_kind Kind >
typename boost::graph_traits< graph_< Kind > >::degree_size_type
out_degree
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind > const& graph
)
{
  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return ::agdegree( raw_graph, vertex.raw(), FALSE, TRUE );
}

template< graph_kind Kind >
std::pair
< typename boost::graph_traits< graph_< Kind > >::in_edge_iterator
, typename boost::graph_traits< graph_< Kind > >::in_edge_iterator
>
in_edges
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind > const& graph
)
{
  using iterator
    = typename boost::graph_traits< graph_< Kind > >::in_edge_iterator;

  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return std::make_pair
  ( iterator( ::agfstout( raw_graph, vertex.raw() ), raw_graph )
  , iterator( nullptr, raw_graph )
  );
}

template< graph_kind Kind >
typename boost::graph_traits< graph_< Kind > >::degree_size_type
in_degree
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind > const& graph
)
{
  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return ::agdegree( raw_graph, vertex.raw(), TRUE, FALSE );
}

template< graph_kind Kind >
typename boost::graph_traits< graph_< Kind > >::degree_size_type
degree( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
      , graph_< Kind > const& graph
      )
{
  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return ::agdegree( raw_graph, vertex.raw(), TRUE, TRUE );
}

template< graph_kind Kind >
std::pair
< typename boost::graph_traits< graph_< Kind > >::adjacency_iterator
, typename boost::graph_traits< graph_< Kind > >::adjacency_iterator
>
adjacent_vertices
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind > const& graph
)
{
  using iterator
    = typename boost::graph_traits< graph_< Kind > >::adjacency_iterator;
  auto out_edges_range = out_edges( vertex, graph );

  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return std::make_pair
  ( iterator( std::move( out_edges_range.first ), raw_graph )
  , iterator( std::move( out_edges_range.second ), raw_graph )
  );
}

template< graph_kind Kind >
std::pair
< typename boost::graph_traits< graph_< Kind > >::vertex_iterator
, typename boost::graph_traits< graph_< Kind > >::vertex_iterator
>
vertices( graph_< Kind > const& graph )
{
  using iterator
    = typename boost::graph_traits< graph_< Kind > >::vertex_iterator;

  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return std::make_pair
  ( iterator( ::agfstnode( raw_graph ), raw_graph )
  , iterator( nullptr, raw_graph )
  );
}

template< graph_kind Kind >
typename boost::graph_traits< graph_< Kind > >::vertex_size_type
num_vertices
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind > const& graph
)
{
  // The graphviz cgraph library is not const-correct.
  Agraph_t* const raw_graph = const_cast< Agraph_t* >( graph.raw() );

  return ::agnnodes( raw_graph );
}

template< graph_kind Kind >
typename boost::graph_traits< graph_< Kind > >::vertex_descriptor
add_vertex( graph_< Kind >& graph )
{
  return ::agnode( graph.raw(), nullptr, TRUE );
}

namespace graph_detail {

struct clear_vertex_undirected
{
  template< graph_kind Kind >
  static void run
  ( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
  , graph_< Kind >& graph
  )
  {
    auto const remove_edge_fun
      = [ &graph ]( auto& edge )
        {
          ::agdeledge( graph.raw(), edge.raw() );
        };

    auto const vertex_out_edges = out_edges( vertex, graph );
    std::for_each( vertex_out_edges.first, vertex_out_edges.second
                 , remove_edge_fun
                 );
  }
};

struct clear_vertex_directed
{
  template< graph_kind Kind >
  static void run
  ( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
  , graph_< Kind >& graph
  )
  {
    clear_vertex_undirected::run( vertex, graph );

    auto const remove_edge_fun
      = [ &graph ]( auto& edge )
        {
          ::agdeledge( graph.raw(), edge.raw() );
        };

    auto const vertex_in_edges = in_edges( vertex, graph );
    std::for_each( vertex_in_edges.first, vertex_in_edges.second
                 , remove_edge_fun
                 );
  }
};

} // namespace argot::receiver::graphviz::graph_detail

template< graph_kind Kind >
void clear_vertex
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind >& graph
)
{
  std::conditional_t
  < Kind == graph_kind::undirected || Kind == graph_kind::strict_undirected
  , graph_detail::clear_vertex_undirected
  , graph_detail::clear_vertex_directed
  >::run( vertex, graph );
}

template< graph_kind Kind >
void remove_vertex
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor vertex
, graph_< Kind >& graph
)
{
  ::agdelnode( graph.raw(), vertex );
}

namespace graph_detail {

struct add_edge_impl
{
  template< graph_kind Kind >
  std::pair
  < typename boost::graph_traits< graph_< Kind > >::edge_descriptor
  , bool
  >
  static run
  ( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor source
  , typename boost::graph_traits< graph_< Kind > >::vertex_descriptor target
  , graph_< Kind >& graph
  )
  {
    return ::agedge( graph.raw(), source.raw(), target.raw(), nullptr, TRUE );
  }
};

struct add_edge_strict_impl
{
  template< graph_kind Kind >
  std::pair
  < typename boost::graph_traits< graph_< Kind > >::edge_descriptor
  , bool
  >
  static run
  ( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor source
  , typename boost::graph_traits< graph_< Kind > >::vertex_descriptor target
  , graph_< Kind >& graph
  )
  {
    Agedge_t* const possibly_existing_edge
      = ::agedge( graph.raw(), source.raw(), target.raw(), nullptr, FALSE );

    return possibly_existing_edge != nullptr
    ? std::make_pair( possibly_existing_edge, false )
    : std::make_pair
      ( ::agedge( graph.raw(), source.raw(), target.raw(), nullptr, TRUE )
      , true
      );
  }
};

} // namespace argot::receiver::graphviz::graph_detail

// Note:
//   For graphs that do not allow parallel edges this violates complexity
//   requirements of Boost.Graph (further, Boost.Graph should not require
//   returning true if the edge exists -- it should be a precondition violation,
//   with a separate function that does what it specifies if necessary, and
//   whose complexity is worse).
template< graph_kind Kind >
std::pair
< typename boost::graph_traits< graph_< Kind > >::edge_descriptor
, bool
>
add_edge
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor source
, typename boost::graph_traits< graph_< Kind > >::vertex_descriptor target
, graph_< Kind >& graph
)
{
  return std::conditional_t
  < Kind == graph_kind::directed || Kind == graph_kind::undirected
  , graph_detail::add_edge_impl
  , graph_detail::add_edge_strict_impl
  >::run( source, target, graph );
}

template< graph_kind Kind >
void remove_edge
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor source
, typename boost::graph_traits< graph_< Kind > >::vertex_descriptor target
, graph_< Kind >& graph
)
{
  Agedge_t* const possibly_existing_edge
    = ::agedge( graph.raw(), source.raw(), target.raw(), nullptr, FALSE );

  if( possibly_existing_edge != nullptr )
    ::agdeledge( graph.raw(), possibly_existing_edge );
}

template< graph_kind Kind >
void remove_edge
( typename boost::graph_traits< graph_< Kind > >::edge_iterator edge_it
, graph_< Kind >& graph
)
{
  ::agdeledge( graph.raw(), edge_it.raw() );
}

template< graph_kind Kind >
void remove_edge
( typename boost::graph_traits< graph_< Kind > >::edge_descriptor edge
, graph_< Kind >& graph
)
{
  ::agdeledge( graph.raw(), edge.raw() );
}

template< class Predicate, graph_kind Kind >
void remove_out_edge_if
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor source
, Predicate predicate  // TODO(mattcalabrese) Possibly forward
, graph_< Kind >& graph
)
{
  auto const out_edge_range = out_edges( source, graph );
  std::for_each
  ( out_edge_range.first, out_edge_range.second
  , [ &graph, &predicate ]( auto& edge )
    {
      if( predicate( edge ) )
        remove_edge( edge, graph );
    }
  );
}

template< class Predicate, graph_kind Kind >
void remove_in_edge_if
( typename boost::graph_traits< graph_< Kind > >::vertex_descriptor source
, Predicate predicate  // TODO(mattcalabrese) Possibly forward
, graph_< Kind >& graph
)
{
  auto const in_edge_range = in_edges( source, graph );
  std::for_each
  ( in_edge_range.first, in_edge_range.second
  , [ &graph, &predicate ]( auto& edge )
    {
      if( predicate( edge ) )
        remove_edge( edge, graph );
    }
  );
}

// TODO(mattcalabrese) Implement remove_edge_if

} // namespace argot::receiver::graphviz
} // namespace argot::receiver
} // namespace argot

#endif  // ARGOT_RECEIVER_GRAPHVIZ_GRAPH_HPP_
