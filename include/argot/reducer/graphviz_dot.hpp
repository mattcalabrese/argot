/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_GRAPHVIZ_DOT_HPP_
#define ARGOT_REDUCER_GRAPHVIZ_DOT_HPP_

#include <argot/detail/xml_sanitize.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/remove_cvref.hpp>

#include <boost/core/demangle.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <string>
#include <sstream>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

// TODO(mattcalabrese) Escape the quotes in the dot language.

namespace argot {
namespace reducer {
namespace graphviz_dot_detail {

template< class... P >
struct output_params;

template<>
struct output_params< std::tuple<> >
{
  template< class Os, class TypeOutput >
  static void run( Os&& /*os*/, TypeOutput&& /*type_output*/ ) {}
};

template< class Head >
struct output_params< std::tuple< Head > >
{
  template< class Os, class TypeOutput >
  static void run( Os&& os, TypeOutput&& type_output )
  {
    type_output.template output< Head >( os );
  }
};

template< class Head, class Next, class... Tail >
struct output_params< std::tuple< Head, Next, Tail... > >
{
  template< class Os, class TypeOutput >
  static void run( Os&& os, TypeOutput&& type_output )
  {
    output_params< std::tuple< Head > >::run( os, type_output );
    os << '|';
    output_params< std::tuple< Next, Tail... > >::run( os, type_output );
  }
};

template< class Tuple, std::size_t I = std::tuple_size< Tuple >::value >
struct output_args;

template<>
struct output_args< std::tuple<>, 0 >
{
  template< class Os, class TypeOutput, class ValOutput >
  static void run( Os&& os, std::tuple<> const&, TypeOutput&, ValOutput& )
  {
    os << "$ no arguments $";
  }
};

template< class Head, class... Tail, std::size_t I >
struct output_args< std::tuple< Head, Tail... >, I >
{
  template< class Os, class TypeOutput, class ValOutput >
  static void run( Os&& os, std::tuple< Head, Tail... > const& tup
                 , TypeOutput& type_output, ValOutput& val_output
                 )
  {
    os << '{';
    type_output.template output
    < typename std::tuple_element
      < sizeof...( Tail ) + 1 - I, std::tuple< Head, Tail... > >::type
    >
    ( os );
    os << '|';
    val_output.output
    ( os, std::get< sizeof...( Tail ) + 1 - I >( tup ) );
    os << "}|";

    output_args< std::tuple< Head, Tail... >, I - 1 >::run
    ( os, tup, type_output, val_output );
  }
};

template< class Head, class... Tail >
struct output_args< std::tuple< Head, Tail... >, 1 >
{
  template< class Os, class TypeOutput, class ValOutput >
  static void run( Os&& os, std::tuple< Head, Tail... > const& tup
                 , TypeOutput& type_output, ValOutput& val_output
                 )
  {
    os << '{';
    type_output.template output
    < typename std::tuple_element
      < sizeof...( Tail ), std::tuple< Head, Tail... > >::type
    >( os );
    os << '|';
    val_output.output( os, std::get< sizeof...( Tail ) >( tup ) );
    os << '}';
  }
};

template< std::size_t IDOffset, class TypeOutput, class Os >
void generate_dot_impl_untaken
( Os&& os, std::string const& edge_attributes
, TypeOutput&& type_output, reducer_traits::return_types_t<>
)
{
}

template< std::size_t IDOffset
        , class Os, class TypeOutput, class HeadBranch, class... TailBranches
        >
void generate_dot_impl_untaken
( Os&& os, std::string const& edge_attributes
, TypeOutput&& type_output
, reducer_traits::return_types_t< HeadBranch, TailBranches... >
)
{
  os
    << "  Branch" << IDOffset << "[label=\"{" << IDOffset
    << "|{";

  output_params< remove_cvref_t< HeadBranch > >
  ::run( os, type_output );

  os
    << "}}\"]\n"
       "  Root -> Branch" << IDOffset << ' ' << edge_attributes << '\n';

  ( generate_dot_impl_untaken< IDOffset + 1 > )
  ( os, edge_attributes, type_output
  , reducer_traits::return_types< TailBranches... >
  );
}

template< std::size_t IDOffset
        , class Os, class TypeOutput, class ValOutput, class... Elements
        >
void generate_dot_impl_taken
( Os&& os, std::string const& edge_attributes
, TypeOutput& type_output, ValOutput&& val_output
, std::tuple< Elements... > const& tup
)
{
  // TODO(mattcalabrese) Rewrite with fold expressions
  os
    << "  Branch" << IDOffset << "[label=\"{" << IDOffset
    << "|{";

  output_args< std::tuple< Elements... > >::run
  ( os, tup, type_output, val_output );

  os
    << "}}\", fillcolor=green]\n"
       "  Root -> Branch" << IDOffset << ' ' << edge_attributes << '\n';
}

template< class TypeOutput, class ValOutput >
class graphviz_dot_t
{
  std::string graph_name;
  std::string prov_form;
  TypeOutput type_output;
  ValOutput val_output;
 public:
  graphviz_dot_t
  ( std::string graph_name, std::string prov_form
  , TypeOutput type_output, ValOutput val_output
  )
    : graph_name( std::move( graph_name ) )
    , prov_form( std::move( prov_form ) )
    , type_output( std::move( type_output ) )
    , val_output( std::move( val_output ) ) {}

  static char const* untaken_edge_attributes()
  {
    return "";
  }

  static char const* taken_edge_attributes()
  {
    return "[color=green,penwidth=4.0]";
  }

  // In actuality should fail substitution for types that wouldn't be valid.
  // i.e. void (unless the Regular Void paper is accepted by EWG...)
  template< class... ReturnTypes >
  using return_type = std::string;

  struct reduction_function_specifier
  {
    template
    < class Self
    , class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun
    >
    static std::string reduce
    ( Self&& self
    , reducer_traits::return_types_t< LeadingReturnTypes... >
    , reducer_traits::return_types_t< TrailingReturnTypes... >
    , Fun&& fun
    )
    {
      std::ostringstream text;
      text
        << "digraph " << self.graph_name << "\n"
           "{\n"
           "  edge[headport=w,tailport=e]\n"
           "  rankdir=LR\n"
           "  Root[label=\""<< self.prov_form << "\", shape=box3d]\n"
           "  node[shape=Mrecord,style=filled]\n";

      ( generate_dot_impl_untaken< 0 > )
      ( text, untaken_edge_attributes(), self.type_output
      , reducer_traits::return_types< LeadingReturnTypes... >
      );

      ( generate_dot_impl_taken< sizeof...( LeadingReturnTypes ) > )
      ( text, taken_edge_attributes(), self.type_output, self.val_output
      , std::forward< Fun >( fun )()
      );

      ( generate_dot_impl_untaken< sizeof...( LeadingReturnTypes ) + 1 > )
      ( text, untaken_edge_attributes(), self.type_output
      , reducer_traits::return_types< TrailingReturnTypes... >
      );

      text << '}';

      return std::move( text ).str();
    }
  };
};

}  // namespace argot::reducer::graphviz_dot_detail

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
  template< class Os, class T >
  void output( Os&& os, T&& arg ) const
  {
    // TODO(mattcalabrese) Check for error
    std::ostringstream unsanitized;
    value_output_impl( unsanitized, std::forward< T >( arg ) );
    os << call_detail::xml_sanitize( unsanitized.str() );
  }
};

template< class TypeOutput = demangled_type_output
        , class ValOutput = value_output
        >
graphviz_dot_detail::graphviz_dot_t< TypeOutput, ValOutput >
graphviz_dot
( std::string graph_name, std::string root_name
, TypeOutput type_output = TypeOutput()
, ValOutput val_output = ValOutput()
)
{
  return graphviz_dot_detail::graphviz_dot_t< TypeOutput, ValOutput >
  ( std::move( graph_name ), std::move( root_name )
  , std::move( type_output ), std::move( val_output )
  );
}

}  // namespace argot::reducer
}  // namespace argot

#endif  // ARGOT_REDUCER_GRAPHVIZ_DOT_HPP_
