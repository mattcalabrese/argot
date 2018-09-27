/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_XML_SANITIZE_HPP_
#define ARGOT_DETAIL_XML_SANITIZE_HPP_

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

namespace argot {
namespace call_detail {

inline std::string xml_sanitize( std::string const& source )
{
  std::vector< char > result;
  result.reserve( source.size() + 1 );

  auto const end = source.end();
  auto const pred = []( char a )
  {
    return
      a == '"' || a == '<' || a == '>' || a == '{' || a == '}' || a == '\'';
  };

  auto curr_begin = source.begin();

  for
  ( auto curr_end = std::find_if( source.begin(), end, pred )
  ; curr_end != end
  ;   (void)( curr_begin = std::next( curr_end ) )
    , (void)( curr_end = std::find_if( curr_begin, end, pred ) )
  )
  {
    std::copy( curr_begin, curr_end, std::back_inserter( result ) );
    switch( *curr_end )
    {
     case '"':
      result.push_back( '&' );
      result.push_back( 'q' );
      result.push_back( 'u' );
      result.push_back( 'o' );
      result.push_back( 't' );
      result.push_back( ';' );
      break;
     case '<':
      result.push_back( '&' );
      result.push_back( 'l' );
      result.push_back( 't' );
      result.push_back( ';' );
      break;
     case '>':
      result.push_back( '&' );
      result.push_back( 'g' );
      result.push_back( 't' );
      result.push_back( ';' );
      break;
     case '{':
      result.push_back( '\\' );
      result.push_back( '{' );
      break;
     case '}':
      result.push_back( '\\' );
      result.push_back( '}' );
      break;
     case '\'':
      result.push_back( '&' );
      result.push_back( 'a' );
      result.push_back( 'p' );
      result.push_back( 'o' );
      result.push_back( 's' );
      result.push_back( ';' );
      break;
     default: // TODO(mattcalabrese) Unreachable
      break;
    }
  }

  std::copy( curr_begin, end, std::back_inserter( result ) );
  result.push_back( '\0' );

  return std::string( result.data() );
}

} // namespace argot::call_detail
} // namespace argot

#endif  // ARGOT_DETAIL_XML_SANITIZE_HPP_
