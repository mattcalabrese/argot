/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_COMPARE_TOKENS_HPP_
#define ARGOT_TEST_COMPARE_TOKENS_HPP_

// TODO(mattcalabrese) Use ostringstream.

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <sstream>

#include <boost/wave/cpp_context.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>

namespace argot::test {

struct expansion_analysis_t
{
  bool no_differences() const
  {
    return trailing_seen.empty() && trailing_expected.empty();
  }

  std::string difference_description() const
  {
    std::string result;

    if( no_differences() )
      result = "The expected code and the generated code match.";
    else
    {
      result += "Error: Generated tokens differ from what was expected. \n\n";
      result += "  Expected: ";
      result += match;
      result += trailing_expected;
      result += "\n";
      result += "  But saw:  ";
      result += match;
      result += trailing_seen;
    }

    return result;
  }

  std::string match;
  std::string trailing_seen;
  std::string trailing_expected;
};

class expansion_failure
  : public std::exception
{
 public:
  explicit expansion_failure( std::string differences )
    : differences( std::move( differences ) ) {}

  virtual char const* what() const noexcept override
  {
    return differences.c_str();
  }
 private:
  std::string differences;
};

template< class WaveContext >
std::string context_to_normalized_string( WaveContext& context )
{
  std::string result;
  for( auto&& tok : context )
  {
    auto&& tok_value =  tok.get_value();
    if(    tok_value.begin() != tok_value.end()
        && !std::isspace(*tok_value.begin())
      )
    {
      result.append( tok_value.begin(), tok_value.end() );
      result += ' ';
    }
  }
  return result;

  return 0;
}

expansion_analysis_t expansion_analysis( std::string_view raw_seen
                                       , std::string raw_expected
                                       )
{
  namespace wave = boost::wave;
  namespace lexer = wave::cpplexer;

  raw_expected += '\n';

  std::string_view view_expected = raw_expected;

  // Normalize the inputs by tokenization.
  using lex_it_t = lexer::lex_iterator< lexer::lex_token<> >;
  using context_t = wave::context< char const*, lex_it_t >;

  context_t seen_context( raw_seen.begin(), raw_seen.end(), "seen" );
  context_t expected_context( view_expected.begin(), view_expected.end()
                            , "expected"
                            );

  std::string const seen = (context_to_normalized_string)( seen_context );
  std::string const expected
    = (context_to_normalized_string)( expected_context );

  auto const common_end_its
    = std::mismatch
      ( seen.begin(), seen.end(), expected.begin(), expected.end() );

  return { std::string( seen.begin(), common_end_its.first )
         , std::string( common_end_its.first, seen.end() )
         , std::string( common_end_its.second, expected.end() )
         };

  return 0;
}

void throw_if_failed_expansion( std::string_view raw_seen
                              , std::string raw_expected
                              , char const* file
                              , int line
                              )
{
  expansion_analysis_t const analysis
    = expansion_analysis( raw_seen, raw_expected );

  std::ostringstream os;

  os << "\n\n" << file << ':' << line << ": "
     << analysis.difference_description();

  if( !analysis.no_differences() )
    throw expansion_failure( std::move( os ).str() );

  return 0;
}

}  // namespace (argot::test)

#define ARGOT_TEST_DETAIL_VARIADIC_STRINGIZE_IMPL( ... ) #__VA_ARGS__

#define ARGOT_TEST_VARIADIC_STRINGIZE( ... )                                   \
ARGOT_TEST_DETAIL_VARIADIC_STRINGIZE_IMPL( __VA_ARGS__ )

#define ARGOT_TEST_EXPANSION( expected_string, ... )                           \
( ( void )                                                                     \
  ( ::argot::test::throw_if_failed_expansion                                   \
    ( ARGOT_TEST_VARIADIC_STRINGIZE( __VA_ARGS__ ) "\n"                        \
    , expected_string                                                          \
    , __FILE__, __LINE__                                                       \
    )                                                                          \
  )                                                                            \
)

#endif  // ARGOT_TEST_COMPARE_TOKENS_HPP_
