/*==============================================================================
  Copyright (c) 2016 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define header_allQ <boost_ext/call.hpp>
#define qualified_callQ boost_ext::call

//[preface_example
/*`
[heading Example]

The simplest way to describe the features of this library is with a set of
examples that should be relatively self-explanatory.
*/
#include header_allQ

#include <iostream>
#include <string>
#include <tuple>
#include <variant>

// This is just a Callable we will use for all of the following examples.
// It takes a stream and a series of arguments, outputting each.
constexpr auto output = []( auto& os, const auto&... args ) -> decltype( auto )
{
  return ( os << ... << args );
};

// In the following function, every time std::call is used, output is ultimately
// invoked with equivalent values.
int main()
{
  namespace prov = namespaceQ::prov;

  // In its simplest usage, std::call does what std::invoke does.
  // It just invokes the Callable with the specified arguments.
  {
    qualified_callQ
    ( output, std::cout
            , 5
            , 3.5
            , std::string( "Hello" )
    );
  }

  // It can also be used with a provider that unpacks tuples.
  // Note that std::cout is not a member of the tuple, so it is
  // simply forwarded to the Callable as-is.
  {
    auto args = std::make_tuple( 5, 3.5, std::string( "Hello" ) );
    qualified_callQ
    ( output, std::cout
            , prov_unpackQ( args )
    );
  }

  // It can also unpack a tuple, followed by additional arguments.
  // Note that neither std::cout nor the string are members of the tuple.
  {
    auto args = std::make_tuple( 5, 3.5 );
    qualified_callQ
    ( output, std::cout
            , prov_unpackQ( args )
            , std::string( "Hello" )
    );
  }

  // It can pass along a reference to the currently active alternative of a variant.
  {
    std::variant< int, std::string > arg0 = 5, arg2 = std::string( "Hello" );
    qualified_callQ
    ( output, std::cout
            , prov_active_alternative_ofQ( arg0 )
            , 3.5
            , prov_active_alternative_ofQ( arg2 )
    );
  }
}
//]
