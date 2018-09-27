/*==============================================================================
  Copyright (c) 2016 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_EXT_CALL_EXAMPLE_GRAPHVIZ_HPP_
#define BOOST_EXT_CALL_EXAMPLE_GRAPHVIZ_HPP_

#include <boost_ext/call/prov_traits/provide.hpp>
#include <boost_ext/call/receiver/graphviz.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/program_options/options_description.hpp>

#include <graphviz/cgraph.h>

#include <iostream>
#include <string>

#define BOOST_EXT_CALL_EXAMPLE_GRAPH



#endif  // BOOST_EXT_CALL_EXAMPLE_GRAPHVIZ_HPP_

#ifdef BOOST_EXT_CALL_EXAMPLE_GRAPHVIZ_MAIN
#undef BOOST_EXT_CALL_EXAMPLE_GRAPHVIZ_MAIN

int main( int const num_args, char** const args )
{
  namespace po = boost::program_options;

  std::string format;
  boost::filesystem::path output_file_path;

  po::options_description description( "Usage" );
  description.add_options()
  ("help", "Print command-line options.")
  ("graphviz-version"
  , "The version of the graphviz library that is being used."
  )/*
  ("format", po::value< std::string >( &format )->default_value( "svg" )
  , "Set output format."
  )*/
  ("output-file,o", po::value< boost::filesystem::path >( &output_file_path )
  , "Set the output file."
  );

  po::variables_map parsed_args;
  po::store( po::parse_command_line( num_args, args, description ) );
  po::notify( parsed_args );

  if( parsed_args.count( "help" ) != 0 )
  {
    std::cout << description << '\n';
  }
  else
    if( parsed_args.count( "output-file" ) == 1 )
    {
      // TODO(mattcalabrese) Determine format here.
      boost_ext_call_example_graph
      ( []( char const* root_description, auto&& provider )
        {
          prov_traits::provide( boost_ext::receiver::graphviz( )
                              , std::forward< decltype( provider ) >( provider )
                              );
        }
      );
    }
    else
    {
      std::cout
        << "No output file was specified. Run this executable with the "
           "command-line option \"--help\" for usage information.\n";
    }

  return 0;
}

#endif
