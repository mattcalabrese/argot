/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_RETURN_GRAPHVIZ_DOT_HPP_
#define ARGOT_RECEIVER_RETURN_GRAPHVIZ_DOT_HPP_

#if 0

#include <argot/concepts/argument_receiver.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/detail/type_list.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver_traits/provider_types.hpp>

#include <type_traits>
#include <utility>

// TODO(mattcalabrese) Escape the quotes in the dot language.

namespace argot {
namespace receiver {
namespace return_graphviz_dot_detail {

template< class... P >
struct output_params;

template<>
struct output_params<>
{
  template< class Os >
  static void run( Os&& /*os*/ ) {}
};

template< class Head >
struct output_params< Head >
{
  template< class Os >
  static void run( Os&& os )
  {
    os << typeid( Head ).name();
  }
};

template< class Head, class Next, class... Tail >
struct output_params< Head, Next, Tail... >
{
  template< class Os >
  static void run( Os&& os )
  {
    output_params< Head >::run( os );
    os << ", ";
    output_params< Next, Tail... >::run( os );
  }
};

class return_graphviz_dot_untaken_branch_impl_t
{
  static char const* color()
  {
    return "[color=red,penwidth=3.0]";
  }

  template< class... P >
  struct receive_result
  {
    template< std::size_t ID, class Os >
    void generate_edge( Os&& os, std::string const& parent )
    {
      os
        << "  \"" << parent << "\" -> \""
        << '[' << ID << "]( ";

      output_params< P... >::run( os );

      os << " )\"" << color() << '\n';
    }
  };

  template< class... P >
  static call_detail::type_list< receive_result< P... > >
  receive( return_graphviz_dot_untaken_branch_impl_t /*self*/
        , P&&... /*args*/
        ) { return {}; }

  template< class... PossibleProviders >
  using branch_result_impl
    = typename call_detail::concatenate
      < decltype
        ( prov_traits::provide
          ( std::declval< PossibleProviders >()
          , std::declval
            < argument_receiver
              < return_graphviz_dot_untaken_branch_impl_t >
            >()
          )
        )...
      >::type;

  template< class QualifiedThis, class... PossibleProviders >
  using branch_result = branch_result_impl< PossibleProviders... >;

  template< class... LeadingPossibleProviders
          , class Provider
          , class... TrailingPossibleProviders
          >
  static constexpr branch_result_impl
  < LeadingPossibleProviders..., Provider, TrailingPossibleProviders... >
  branch
  ( return_graphviz_dot_untaken_branch_impl_t self
  , receiver_traits::provider_types_t< LeadingPossibleProviders... >
  , Provider&& provider
  , receiver_traits::provider_types_t< TrailingPossibleProviders... >
  )
  {
    return {};
  }
};

template< std::size_t IDOffset, class Os >
void generate_dot_impl( Os&& os, std::string const& parent
                      , call_detail::type_list<>
                      )
{
}

template< std::size_t IDOffset
        , class Os, class HeadBranch, class... TailBranches
        >
void generate_dot_impl( Os&& os, std::string const& parent
                      , call_detail::type_list< HeadBranch, TailBranches... >
                      )
{
  // TODO(mattcalabrese) Rewrite with fold expressions
  HeadBranch::template generate_edge< IDOffset >( os, parent );
  ( generate_dot_impl< IDOffset + 1 > )
  ( os, parent, call_detail::type_list< TailBranches... >() );
}

template< class LeadingUntakenBranches
        , class TakenBranch
        , class TrailingUntakenBranches
        >
struct generate_dot;

template< class... LeadingUntakenBranches
        , class TakenBranch
        , class... TrailingUntakenBranches
        >
struct generate_dot
< call_detail::type_list< LeadingUntakenBranches... >
, TakenBranch
, call_detail::type_list< TrailingUntakenBranches... >
>
{
  template< class Os >
  Os&& operator ()( Os&& os, std::string const& parent ) const
  {
    ( generate_dot_impl< 0 > )
    ( os, parent, call_detail::type_list< LeadingUntakenBranches... >() );

    taken_branch.template generate_edge< sizeof...( LeadingUntakenBranches ) >
    ( os, parent );

    ( generate_dot_impl< sizeof...( LeadingUntakenBranches ) + 1 > )
    ( os, parent, call_detail::type_list< TrailingUntakenBranches... >() );

    return std::forward< Os >( os );
  }

  TakenBranch taken_branch;
};

template< class LeadingUntakenBranches
        , class TakenBranch
        , class TrailingUntakenBranches
        >
struct make_generate_dot;

template< class... LeadingUntakenBranches
        , class... InternalLeadingUntakenBranches
        , class TakenBranch
        , class... InternalTrailingUntakenBranches
        , class... TrailingUntakenBranches
        >
struct make_generate_dot
< call_detail::type_list< LeadingUntakenBranches... >
, generate_dot
  < call_detail::type_list< InternalLeadingUntakenBranches... >
  , TakenBranch
  , call_detail::type_list< InternalTrailingUntakenBranches... >
  >
, call_detail::type_list< TrailingUntakenBranches... >
>
{
  using type
    = generate_dot
      < call_detail::type_list
        < LeadingUntakenBranches..., InternalLeadingUntakenBranches... >
      , TakenBranch
      , call_detail::type_list
        < InternalTrailingUntakenBranches..., TrailingUntakenBranches... >
      >;
};

class return_graphviz_dot_taken_branch_impl
{
  static char const* color()
  {
    return "[color=green,penwidth=3.0]";
  }

  // TODO(mattcalabrese) Replace the output with fold expressions.

  template< class Os >
  static void output_args( Os&& /*os*/ ) {}

  template< class Os, class Head >
  static void output_args( Os&& os, Head&& head )
  {
    os
      << typeid( Head&& ).name()
      << "( " << std::forward< Head >( head ) << " )";
  }

  template< class Os, class Head, class Next, class... Tail >
  static void output_args( Os&& os, Head&& head, Next&& next, Tail&&... tail )
  {
    output_args( os, std::forward< Head >( head ) );
    os << ", ";
    output_args
    ( os, std::forward< Next >( next ), std::forward< Tail >( tail )... );
  }

  struct generate_edge_t
  {
    template< std::size_t ID >
    void generate_edge( Os& os, std::string const& parent ) const
    {
      os
        << "  \"" << node_name << "\" -> \""
        << '[' << ID << "]( " << args_text << " )" << color() << "\n";
    }

    std::string args_text;
  };

  template< class... P >
  static generate_dot
  < call_detail::type_list<>
  , generate_edge_t
  , call_detail::type_list<>
  >
  receive( return_graphviz_dot_taken_branch_impl /*self*/, P&&... args )
  {
    std::ostringstream args_text;
    output_args( args_text, std::forward< P >( args )... );
    return { std::move( args_text ).str() };
  }

  template< class... LeadingPossibleProviders
          , class Provider
          , class... TrailingPossibleProviders
          >
  static constexpr
  typename make_generate_dot
  < typename call_detail::concatenate
    < decltype
      ( prov_traits::provide
        ( std::declval< LeadingPossibleProviders >()
        , std::declval
          < argument_receiver
            < return_graphviz_dot_untaken_branch_impl_t >
          >()
        )
      )...
    >::type
  , decltype
    ( prov_traits::provide
      ( std::declval< Provider >()
      , std::declval
        < argument_receiver
          < return_graphviz_dot_taken_branch_impl >
        >()
      )
    )
  , typename call_detail::concatenate
    < decltype
      ( prov_traits::provide
        ( std::declval< TrailingPossibleProviders >()
        , std::declval
          < argument_receiver
            < return_graphviz_dot_untaken_branch_impl_t >
          >()
        )
      )...
    >::type
  >::type
  branch
  ( return_graphviz_dot_taken_branch_impl /*self*/
  , receiver_traits::provider_types_t< LeadingPossibleProviders... >
  , Provider&& provider
  , receiver_traits::provider_types_t< TrailingPossibleProviders... >
  )
  {
    return
    { prov_traits::provide
      ( std::forward< Provider >( provider )
      , return_graphviz_dot_taken_branch_impl()
      ).taken_branch
    };
  }
};

struct graphviz_dot_string_impl
{
  std::string graph_name;
  std::string root_node;

  template< class EdgeGenerator >
  std::string generate_dot( EdgeGenerator&& edge_generator ) const
  {
    std::ostringstream text;
    text
      << "digraph " << graph_name << "\n "
         "{\n";

    edge_generator( text, root_node );

    text << '}';

    return std::move( text ).str();
  }

  template< class Self, class... P >
  static std::string receive( Self&& self, P&&... args )
  {
    return generate_dot
    ( argument_receiver< return_graphviz_dot_taken_branch_impl >{} );
  }
};

} // namespace argot::receiver::return_graphviz_dot_detail

} // namespace argot::receiver
} // namespace argot

#endif

#endif  // ARGOT_RECEIVER_RETURN_GRAPHVIZ_DOT_HPP_
