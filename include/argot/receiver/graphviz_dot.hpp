/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_GRAPHVIZ_DOT_HPP_
#define ARGOT_RECEIVER_GRAPHVIZ_DOT_HPP_
#if 0
#include <argot/concepts/argument_receiver.hpp>
#include <argot/detail/xml_sanitize.hpp>
#include <argot/prov/argument_provider.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver_traits/provider_types.hpp>

#include <boost/core/demangle.hpp>

#include <cstddef>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace argot {
namespace receiver {

enum class ignore_internal_nodes { no, yes };

namespace graphviz_dot_detail {

template< class... P >
struct output_params;

template<>
struct output_params<>
{
  template< class Os, class TypeOutput >
  static void run( Os&& os, TypeOutput&& /*type_output*/ )
  {
    os << "$ no parameters $";
  }
};

template< class Head >
struct output_params< Head >
{
  template< class Os, class TypeOutput >
  static void run( Os&& os, TypeOutput&& type_output )
  {
    type_output.template output< Head >( os );
  }
};

template< class Head, class Next, class... Tail >
struct output_params< Head, Next, Tail... >
{
  template< class Os, class TypeOutput >
  static void run( Os&& os, TypeOutput&& type_output )
  {
    output_params< Head >::run( os, type_output );
    os << '|';
    output_params< Next, Tail... >::run( os, type_output );
  }
};

template< class Os, class TypeOutput, class ValOutput >
void output_args( Os&& os, TypeOutput&, ValOutput& )
{
  os << "$ no arguments $";
}

template< class Os, class TypeOutput, class ValOutput
        , class Head, class... Tail
        >
void output_args( Os&& os, TypeOutput& type_output, ValOutput& val_output
                , Head&& head, Tail&&... tail
                )
{
  os << '{';

  // TODO(mattcalabrese) Do the sanitization here.
  type_output.template output< Head >( os );
  os << '|';

  // TODO(mattcalabrese) Do the sanitization here.
  val_output.output( os, std::forward< Head >( head ) );
  os << '}';

  // TODO(mattcalabres) if constexpr here
  if constexpr( sizeof...( Tail ) != 0 )
  {
    os << '|';
    ( output_args )
    ( os, type_output, val_output, std::forward< Tail >( tail )... );
  }
}

char const* untaken_edge_attributes()
{
  return "";
}

char const* taken_edge_attributes()
{
  return "[color=yellowgreen,penwidth=4.0]";
}

template< std::size_t BranchIndex >
std::string branch_name( std::string const& parent_name )
{
  std::ostringstream os;
  os << parent_name << ':' << BranchIndex;
  return std::move( os ).str();
}

template< std::size_t LocalBranchIndex, class Os, class TypeOutput >
void untaken_branch_impl
( Os& os, std::string const& parent_name, TypeOutput& type_output )
{
  std::string const name = ( branch_name< LocalBranchIndex > )( parent_name );

  // TODO(mattcalabrese) Put type info into the label instead of just an index.
  os << "  \"" << name << "\"[label=\"Branch" << LocalBranchIndex << "\"]\n"
     << "  \"" << parent_name << "\" -> \"" << name << "\" "
     << untaken_edge_attributes() << '\n';
}

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t IDOffset, class... P, class Os, class TypeOutput
        >
void untaken_receive_impl
( Os& os, std::string const& parent_name, TypeOutput& type_output )
{
  os << "  Leaf" << IDOffset << "[label=\"{" << IDOffset << "|{";

  output_params< P... >::run( os, type_output );

  os << "}}\",fillcolor=wheat]\n"
        "  \""
     << (   ignore_internal_nodes_value == ignore_internal_nodes::no
          ? parent_name
          : "Root"  // TODO(mattcalabrese) Don't hard-code the root name.
        )
     << "\" -> Leaf" << IDOffset << ' '
     << untaken_edge_attributes() << '\n';
}

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t IDOffset
        , class Os, class TypeOutput, class ValOutput, class... P
        >
void receive_impl
( Os& os, std::string const& parent_name
, TypeOutput& type_output, ValOutput& val_output
, P&&... args
)
{
  os << "  Arguments[label=\"{" << IDOffset << "|{";

  ( output_args )( os, type_output, val_output, std::forward< P >( args )... );

  os << "}}\",fillcolor=yellowgreen]\n"
        "  \""
     << (   ignore_internal_nodes_value == ignore_internal_nodes::no
          ? parent_name
          : "Root"  // TODO(mattcalabrese) Don't hard-code the root name.
        )
     << "\" -> Arguments"
     << taken_edge_attributes() << '\n';
}

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t OverallIndex, class... P
        >
struct receive_result
{
  template< class Os, class TypeOutput >
  static std::integral_constant< std::size_t, OverallIndex + 1 >
  write_edges
  ( Os& os, std::string const& parent_name, TypeOutput& type_output )
  {
    ( untaken_receive_impl< ignore_internal_nodes_value, OverallIndex, P... > )
    ( os, parent_name, type_output );

    return {};
  }
};

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t OverallIndex
        >
class graphviz_dot_untaken_t;

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t OverallIndex, std::size_t LocalBranchIndex
        , class... PossibleProviders
        >
struct branch_result;

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t OverallIndex, std::size_t LocalBranchIndex
        >
struct branch_result
< ignore_internal_nodes_value, OverallIndex, LocalBranchIndex >
{
  template< class Os, class TypeOutput >
  static std::integral_constant< std::size_t, OverallIndex > write_edges
  ( Os& os
  , std::string const& /*parent_name*/, TypeOutput& /*type_output*/
  )
  {
    return {};
  }
};

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t OverallIndex, std::size_t LocalBranchIndex
        , class Provider
        >
struct branch_result
< ignore_internal_nodes_value, OverallIndex, LocalBranchIndex, Provider >
{
  template< class Os, class TypeOutput >
  static auto write_edges
  ( Os& os, std::string const& parent_name, TypeOutput& type_output )
  {
    using edge_writer
      = decltype
        ( prov_traits::provide
          ( std::declval< Provider >()
          , std::declval
            < graphviz_dot_untaken_t
              < ignore_internal_nodes_value, OverallIndex >
            >()
          )
        );

    if constexpr( ignore_internal_nodes_value == ignore_internal_nodes::no )
    {
      ( untaken_branch_impl< LocalBranchIndex > )
      ( os, parent_name, type_output );
    }

    return edge_writer::write_edges
    ( os, ( branch_name< LocalBranchIndex > )( parent_name ), type_output );
  }
};

template
< ignore_internal_nodes ignore_internal_nodes_value
, std::size_t OverallIndex, std::size_t LocalBranchIndex, class Provider
, class HeadTrailingPossibleProvider, class... TailTrailingPossibleProviders
>
struct branch_result
< ignore_internal_nodes_value
, OverallIndex, LocalBranchIndex, Provider
, HeadTrailingPossibleProvider, TailTrailingPossibleProviders...
>
{
  template< class Os, class TypeOutput >
  static auto write_edges
  ( Os& os, std::string const& parent_name, TypeOutput& type_output )
  {
    auto const next_overall_index
      = branch_result
        < ignore_internal_nodes_value
        , OverallIndex, LocalBranchIndex, Provider
        >::write_edges( os, parent_name, type_output );

    return branch_result
    < ignore_internal_nodes_value
    , decltype( next_overall_index )::value, LocalBranchIndex + 1
    , HeadTrailingPossibleProvider, TailTrailingPossibleProviders...
    >::write_edges( os, parent_name, type_output );
  }
};

template< ignore_internal_nodes ignore_internal_nodes_value
        , std::size_t OverallIndex
        >
struct graphviz_dot_untaken_t
{
  template< class Self, class... P >
  static receive_result< ignore_internal_nodes_value, OverallIndex, P... >
  receive( Self&& /*self*/, P&&... /*args*/ ) { return {}; }

  template
  < class Self
  , class Provider
  , class... TrailingPossibleProviders
  >
  static branch_result
  < ignore_internal_nodes_value
  , OverallIndex, 0, Provider, TrailingPossibleProviders...
  >
  branch
  ( Self&& self
  , receiver_traits::provider_types_t<>
  , Provider&& provider
  , receiver_traits::provider_types_t< TrailingPossibleProviders... >
  )
  {
    return {};
  }

  template
  < class Self
  , class HeadLeadingPossibleProvider, class... TailLeadingPossibleProviders
  , class Provider
  , class... TrailingPossibleProviders
  >
  static branch_result
  < ignore_internal_nodes_value
  , OverallIndex, 0, HeadLeadingPossibleProvider
  , TailLeadingPossibleProviders..., Provider, TrailingPossibleProviders...
  >
  branch
  ( Self&& self
  , receiver_traits::provider_types_t
    < HeadLeadingPossibleProvider, TailLeadingPossibleProviders... >
  , Provider&& provider
  , receiver_traits::provider_types_t< TrailingPossibleProviders... >
  )
  {
    return {};
  }
};

template< ignore_internal_nodes ignore_internal_nodes_value
        , class Os
        , std::size_t OverallIndex
        , class TypeOutput, class ValOutput
        >
class graphviz_dot_edges_t
{
  Os&& os;  // TODO(mattcalabrese) Use contained here
  std::string parent_name;
  TypeOutput type_output;
  ValOutput val_output;
 public:
  graphviz_dot_edges_t
  ( Os&& os, std::string parent_name
  , TypeOutput type_output, ValOutput val_output
  )
    : os( std::forward< Os >( os ) )
    , parent_name( std::move( parent_name ) )
    , type_output( std::move( type_output ) )
    , val_output( std::move( val_output ) ) {}

  template< class Self, class... P >
  static std::integral_constant< std::size_t, OverallIndex + 1 >
  receive( Self&& self, P&&... args )
  {
    ( receive_impl< ignore_internal_nodes_value, OverallIndex > )
    ( self.os, self.parent_name, self.type_output, self.val_output
    , std::forward< P >( args )...
    );

    return {};
  }

  template
  < class Self
  , class... LeadingPossibleProviders
  , class Provider
  , class... TrailingPossibleProviders
  >
  static auto branch
  ( Self&& self
  , receiver_traits::provider_types_t< LeadingPossibleProviders... >
  , Provider&& provider
  , receiver_traits::provider_types_t< TrailingPossibleProviders... >
  )
  {
    auto const overall_taken_index
      = branch_result
        < ignore_internal_nodes_value
        , OverallIndex, 0
        , LeadingPossibleProviders...
        >::write_edges( self.os, self.parent_name, self.type_output );

    std::size_t constexpr local_taken_branch_index
      = sizeof...( LeadingPossibleProviders );

    std::string const name
      = ( branch_name< local_taken_branch_index > )( self.parent_name );

    if constexpr( ignore_internal_nodes_value == ignore_internal_nodes::no )
    {
      // TODO(mattcalabrese) Put value into the label instead of just an index.
      self.os
        << "  \"" << name << "\"[label=\"Branch"
                          << local_taken_branch_index
                          << "\",fillcolor=yellowgreen]\n"
        << "  \"" << self.parent_name << "\" -> \"" << name << "\" "
        << taken_edge_attributes() << '\n';
    }

    auto const next_index
      = prov_traits::provide
        ( std::forward< Provider >( provider )
        , graphviz_dot_edges_t
          < ignore_internal_nodes_value
          , Os&, decltype( overall_taken_index )::value
          , TypeOutput, ValOutput
          >( self.os
           , ( branch_name< sizeof...( LeadingPossibleProviders ) > )
             ( self.parent_name )
           , self.type_output, self.val_output
           )
        );

    return branch_result
    < ignore_internal_nodes_value
    , decltype( next_index )::value, sizeof...( LeadingPossibleProviders ) + 1
    , TrailingPossibleProviders...
    >::write_edges( self.os, self.parent_name, self.type_output );
  }
};


template< ignore_internal_nodes ignore_internal_nodes_value
        , class TypeOutput, class ValOutput
        >
class graphviz_dot_t
{
 public:
  graphviz_dot_t
  ( std::string graph_name, std::string prov_form
  , TypeOutput type_output, ValOutput val_output
  )
    : graph_name( std::move( graph_name ) )
    , prov_form( std::move( prov_form ) )
    , type_output( std::move( type_output ) )
    , val_output( std::move( val_output ) ) {}

  template< class Self, class... P >
  static std::string receive( Self&& self, P&&... args )
  {
    std::ostringstream os;

    begin_impl( self, os );

    using underlying_receiver_type
      = graphviz_dot_edges_t
        < ignore_internal_nodes_value
        , std::ostringstream&, 0, TypeOutput, ValOutput
        >;

    os
      << underlying_receiver_type::receive
         ( underlying_receiver_type
           ( os, root_name(), std::forward< Self >( self ).type_output
           , std::forward< Self >( self ).val_output
           )
         , std::forward< P >( args )...
         );

    end_impl( os );

    return std::move( os ).str();
  }

  template
  < class Self
  , class... LeadingPossibleProviders
  , class Provider
  , class... TrailingPossibleProviders
  >
  static std::string branch
  ( Self&& self
  , receiver_traits::provider_types_t< LeadingPossibleProviders... >
  , Provider&& provider
  , receiver_traits::provider_types_t< TrailingPossibleProviders... >
  )
  {
    std::ostringstream os;

    begin_impl( self, os );

    using underlying_receiver_type
      = graphviz_dot_edges_t
        < ignore_internal_nodes_value
        , std::ostringstream&, 0, TypeOutput, ValOutput
        >;

    underlying_receiver_type::branch
    ( underlying_receiver_type
      ( os, root_name(), std::forward< Self >( self ).type_output
      , std::forward< Self >( self ).val_output
      )
    , receiver_traits::provider_types< LeadingPossibleProviders... >
    , std::forward< Provider >( provider )
    , receiver_traits::provider_types< TrailingPossibleProviders... >
    );

    end_impl( os );

    return std::move( os ).str();
  }
 private:
  static char const* root_name() { return "Root"; }

  template< class Self, class Os >
  static void begin_impl( Self&& self, Os& os )
  {
    os
      << "digraph " << call_detail::xml_sanitize( self.graph_name ) << "\n"
         "{\n"
         "  edge[headport=w,tailport=e]\n"
         "  rankdir=LR\n"
         "  node[shape=Mrecord,style=filled]\n"
         "  Root[label=\""<< call_detail::xml_sanitize( self.prov_form )
                          << "\",shape=box3d,fillcolor=yellowgreen]\n";
  }

  template< class Os >
  static  void end_impl( Os& os )
  {
    os << '}';
  }

  std::string graph_name;
  std::string prov_form;
  TypeOutput type_output;
  ValOutput val_output;
};

} // namespace argot::receiver::graphviz_dot_detail

struct demangled_type_output
{
  template< class T >
  struct impl
  {
    template< class Os >
    static void run( Os&& os )
    {
      os
        << call_detail::xml_sanitize
           ( boost::core::demangle( typeid( T ).name() ) )
        << ( std::is_volatile< T >::value ? " volatile" : "" )
        << ( std::is_const< T >::value ? " const" : "" );
    }
  };

  template< class T >
  struct impl< T& >
  {
    template< class Os >
    static void run( Os&& os )
    {
      impl< T >::run( os );
      os << "&amp;";
    }
  };

  template< class T >
  struct impl< T&& >
  {
    template< class Os >
    static void run( Os&& os )
    {
      impl< T >::run( os );
    }
  };

  template< class T, class Os >
  Os&& output( Os&& os ) const
  {
    impl< T >::run( os );
    return std::forward< Os >( os );
  }
};

template< class Os, class T >
void value_output_impl( Os& os, const T& arg )
{
  os << arg;
}

template< class Os, class ValueType, ValueType Value >
Os& value_output_impl( Os& os, std::integral_constant< ValueType, Value > )
{
  os << "{}";
  return os;
}

struct value_output
{
 private:
  template< class Os, class T, class /*Enabler*/ = void >
  struct can_describe : std::false_type{};

  template< class Os, class T >
  struct can_describe
  < Os, T
  , std::void_t
    < decltype( std::declval< T const& >().describe( std::declval< Os >() ) ) >
  > : std::true_type{};

 public:
  template< class Os, class T >
  void output( Os&& os, T const& arg ) const
  {
    // TODO(mattcalabrese) Check for error
    std::ostringstream unsanitized;
    value_output_impl( unsanitized, arg );
    os << call_detail::xml_sanitize( unsanitized.str() );
  }

  template
  < class Os, class Impl
  , std::enable_if_t
    < !can_describe< std::ostringstream&, Impl >::value, int > = 0
  >
  void output( Os&& os, prov::argument_provider< Impl > const& arg ) const
  {
    // TODO(mattcalabrese) Check for error
    os << call_detail::xml_sanitize( "?" );
  }

  template
  < class Os, class Impl
  , std::enable_if_t
    < can_describe< std::ostringstream&, Impl >::value, int > = 0
  >
  void output( Os&& os, prov::argument_provider< Impl > const& arg ) const
  {
    // TODO(mattcalabrese) Check for error
    std::ostringstream unsanitized;
    arg.state().describe( unsanitized );
    os << call_detail::xml_sanitize( unsanitized.str() );
  }
};

// TODO(mattcalabrese) Make this a function object.
template< ignore_internal_nodes ignore_internal_nodes_value
            = ignore_internal_nodes::no
        , class TypeOutput = demangled_type_output
        , class ValOutput = value_output
        >
argument_receiver
< graphviz_dot_detail::graphviz_dot_t
  < ignore_internal_nodes_value, TypeOutput, ValOutput >
>
graphviz_dot
( std::string graph_name, std::string prov_form
, TypeOutput type_output = TypeOutput()
, ValOutput val_output = ValOutput()
)
{
  return graphviz_dot_detail::graphviz_dot_t
  < ignore_internal_nodes_value, TypeOutput, ValOutput >
  ( std::move( graph_name ), std::move( prov_form )
  , std::move( type_output ), std::move( val_output )
  );
}

} // namespace argot::receiver
} // namespace argot

#endif

#endif  // ARGOT_RECEIVER_GRAPHVIZ_DOT_HPP_
