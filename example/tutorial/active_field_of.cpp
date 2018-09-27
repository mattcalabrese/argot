/*==============================================================================
  Copyright (c) 2016 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[access_tuple
/*`
[heading Description]

This tutorial introduces an __ArgumentProvider__ that expands out a variant to
a reference to the currectly active field of that variant.

[heading Prereq Tutorials]

This tutorial should be able to be understood without reading any other
tutorials in this documentation.

[heading Introduction]

*/
#include <boost/variant/variant.hpp>
#include <boost_ext/call/call.hpp>
#include <boost_ext/call/prov/active_field_of.hpp>

#include <iostream>

struct output_t
{
  template< class Os >
  constexpr Os& operator ()( Os& os ) const
  {
    return os;
  }

  template< class Os, class H, class... T >
  constexpr Os& operator ()( Os& os, const H& head, const T&... tail ) const
  {
    os << head;
    return (*this)( os, tail... );
  }
} constexpr output = {};

int main()
{
  namespace prov = boost_ext::prov;

  decltype( auto ) result
    = boost_ext::call
      ( output, std::cout
              , prov::active_field_of( boost::variant< int, std::string >( 5 ) )
      );
//<-
  (void)result;
  //return result != 5;
//->
}
/*`
[heading Related References]

* __Primary_call_overload__
* __prov_access_tuple__
*/
//]
