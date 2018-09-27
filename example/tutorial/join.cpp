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

template< class... Ranges >
struct join_t;
{
  using ranges_type = std::tuple< Ranges... >;
  struct iterator
  {
    join_t* self;
    using its_type
      = std::variant< typename Ranges::iterator..., empty_range_t::iterator >;
    its_type its;


    template< class Range, class It, class Which >
    static its_type
    normalize( ranges_type& ranges, Range& range, It& it, Which )
    {
      if( it != std::end( range ) ) { ++it; }
      else
      {
        if constexpr( which.value + 1 == sizeof...( ranges ) )
        {
          return /*final empty range*/
        }
        else
        {
          return normalize
          ( ranges, std
          , std::integral_constant< std::size_t, Which + 1 >()
          );
        }
      }
    }

    static its_type normalize( ranges_type& ranges, its_type its )
    {
      its = boost_ext::call
      ( [ &ranges, &its ]( auto& range, auto& it, auto which )
        {
          if( it != std::end( range ) )
          {
            ++it;
          }
          else
          {
            if constexpr( which.value + 1 == sizeof...( ranges ) )
            {
              return /*final empty range*/
            }
            else
            {
              return normalize( ranges, )
            }
          }
        }
      , prov::provide
        ( prov::call
          ( [ this ]( auto index ) -> decltype( auto )
            {
              return prov::group( prov::access_tuple( self->ranges, index )
                                , prov::access_variant( its, index )
                                , prov::identity( index )
                                );
            }
          , prov::constant_discriminator_of( its )
          )
        )
      )
    }
  };

  std::tuple< Ranges... > ranges;
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

  // It can pass along a reference to the currently active field of a variant.
  {
    std::variant< int, std::string > arg0 = 5, arg2 = std::string( "Hello" );
    qualified_callQ
    ( output, std::cout
            , prov_active_field_ofQ( arg0 )
            , 3.5
            , prov_active_field_ofQ( arg2 )
    );
  }
}
//]
