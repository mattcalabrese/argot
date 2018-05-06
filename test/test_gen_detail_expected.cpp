/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/gen/concept_body/detail/expected.hpp>
#include <argot/gen/concept_body/detail/parenthesized_part.hpp>
#include <argot/gen/concept_body/detail/parse_and.hpp>
#include <argot/gen/concept_body/detail/parse_associated_requirements.hpp>
#include <argot/gen/concept_body/detail/parse_associated_type_or_template.hpp>
#include <argot/gen/concept_body/detail/parse_comma.hpp>
#include <argot/gen/concept_body/detail/parse_concept_body.hpp>
#include <argot/gen/concept_body/detail/parse_concept_definition.hpp>
#include <argot/gen/concept_body/detail/parse_concept_member_specifier.hpp>
#include <argot/gen/concept_body/detail/parse_concept_member_specification.hpp>
#include <argot/gen/concept_body/detail/parse_constrained_parameter_kind.hpp>
#include <argot/gen/concept_body/detail/parse_identifier_like.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_identifier_like.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_template_parameter_list.hpp>
#include <argot/gen/concept_body/detail/parse_parenthesized_type_like.hpp>
#include <argot/gen/concept_body/detail/parse_requirement.hpp>
#include <argot/gen/concept_body/detail/parse_requirement_list.hpp>
#include <argot/gen/concept_body/detail/parse_requires.hpp>
#include <argot/gen/concept_body/detail/parse_requires_clause.hpp>
#include <argot/gen/concept_body/detail/parse_template_parameter.hpp>
#include <argot/gen/concept_body/detail/parse_template_parameter_list.hpp>
#include <argot/gen/concept_body/detail/parse_triple_comma.hpp>
#include <argot/gen/concept_body/detail/parse_type_parameter_key.hpp>
#include <argot/gen/concept_body/detail/parse_type_like.hpp>
#include <argot/gen/concept_body/detail/unparse_node.hpp>

#include "compare_tokens.hpp"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#define ARGOT_DETAIL_TEST_EXP                                                  \
ARGOT_GEN_DETAIL_CONSTRUCT_EXPECTED_VALUE( 1, 2, 3 )

#define ARGOT_DETAIL_TEST_UNEXP                                                \
ARGOT_GEN_DETAIL_CONSTRUCT_UNEXPECTED( 2, 20 )

#define ARGOT_DETAIL_TEST_CALL_SUM( data, a, b, c )                            \
ARGOT_GEN_DETAIL_CONSTRUCT_EXPECTED_VALUE( data( a, b, c ) )
/*
BOOST_AUTO_TEST_CASE( expected_bind_value )
{
  ARGOT_TEST_EXPANSION
  ( "value( sum( 1, 2, 3 ) )"
  , ARGOT_GEN_DETAIL_EXPECTED_BIND
    ( ARGOT_DETAIL_TEST_CALL_SUM, ARGOT_DETAIL_TEST_EXP )( sum, )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( expected_bind_unexpected )
{
  ARGOT_TEST_EXPANSION
  ( "unexpected( 2, 20 )"
  , ARGOT_GEN_DETAIL_EXPECTED_BIND
    ( ARGOT_DETAIL_TEST_CALL_SUM, sum, ARGOT_DETAIL_TEST_UNEXP )
  );

  return 0;
}
*/
BOOST_AUTO_TEST_CASE( parse_comma )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( comma_token ), ( ) )"
  , ARGOT_GEN_DETAIL_PARSE_COMMA( , )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( comma_token ), ( hello ) )"
  , ARGOT_GEN_DETAIL_PARSE_COMMA( , hello )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( comma_token ), ( , ) )"
  , ARGOT_GEN_DETAIL_PARSE_COMMA( ,, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), ( comma_token ), () )"
  , ARGOT_GEN_DETAIL_PARSE_COMMA()
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), ( comma_token ), ( hello, ) )"
  , ARGOT_GEN_DETAIL_PARSE_COMMA( hello, )
  );

  return 0;
}

static_assert( ARGOT_GEN_DETAIL_IS_IDENTIFIER_LIKE( a ) );
static_assert( !ARGOT_GEN_DETAIL_IS_IDENTIFIER_LIKE() );
static_assert( !ARGOT_GEN_DETAIL_IS_IDENTIFIER_LIKE( a, b ) );
static_assert( !ARGOT_GEN_DETAIL_IS_IDENTIFIER_LIKE( () ) );

static_assert( ARGOT_GEN_DETAIL_IS_TYPE_LIKE( a ) );
static_assert( !ARGOT_GEN_DETAIL_IS_TYPE_LIKE() );
static_assert( ARGOT_GEN_DETAIL_IS_TYPE_LIKE( a, b ) );
static_assert( !ARGOT_GEN_DETAIL_IS_TYPE_LIKE( () ) );

BOOST_AUTO_TEST_CASE( parse_triple_comma )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( (triple_comma, comma_token, comma_token, comma_token ) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA( ,,, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( (triple_comma, comma_token, comma_token, comma_token ) )"
         ", ( hello )"
         ")"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA( ,,, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( (triple_comma, comma_token, comma_token, comma_token ) ), ( , ) )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA( ,,,, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(triple_comma), comma_token, () )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA()
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft((triple_comma, comma_token)), comma_token, () )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA(,)
  );

  ARGOT_TEST_EXPANSION
  ( R"( unexpected
        ( soft( (triple_comma, comma_token, comma_token))
        , comma_token
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA(,,)
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(triple_comma), comma_token, (hello,,,) )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA(hello,,,)
  );

  ARGOT_TEST_EXPANSION
  ( R"( unexpected
        ( soft( (triple_comma, comma_token))
        , comma_token
        , (hello,,)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA(,hello,,)
  );

  ARGOT_TEST_EXPANSION
  ( R"( unexpected
        ( soft( (triple_comma, comma_token, comma_token))
        , comma_token
        , (hello,)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TRIPLE_COMMA(,,hello,)
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_requires )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( requires ), ( ) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES( requires )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ), ( hello ) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES( requires hello )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ), ( , ) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES( requires, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ), ( hello, ) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES( requires hello, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ), ( hello, world, ) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES( requires hello, world, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (requires), ())"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES()
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (requires), (,))"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES(,)
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (requires), (()))"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES(())
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (requires), ( () requires ) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES( () requires )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (requires), ( , requires ))"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES( , requires )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_and )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( and ), ( ) )"
  , ARGOT_GEN_DETAIL_PARSE_AND( and )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( and ), ( hello ) )"
  , ARGOT_GEN_DETAIL_PARSE_AND( and hello )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( and ), ( , ) )"
  , ARGOT_GEN_DETAIL_PARSE_AND( and, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( and ), ( hello, ) )"
  , ARGOT_GEN_DETAIL_PARSE_AND( and hello, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( and ), ( hello, world, ) )"
  , ARGOT_GEN_DETAIL_PARSE_AND( and hello, world, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (and), ())"
  , ARGOT_GEN_DETAIL_PARSE_AND()
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (and), (,))"
  , ARGOT_GEN_DETAIL_PARSE_AND(,)
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (and), (()))"
  , ARGOT_GEN_DETAIL_PARSE_AND(())
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (and), (() and ))"
  , ARGOT_GEN_DETAIL_PARSE_AND( () and )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (and), (, and))"
  , ARGOT_GEN_DETAIL_PARSE_AND( , and )
  );

  return 0;
}


BOOST_AUTO_TEST_CASE( parenthesized_part )
{
  ARGOT_TEST_EXPANSION
  ( "()"
  , ARGOT_GEN_DETAIL_PARENTHESIZED_PART( () )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_identifier_like )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( ((thing), hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( ((thing), hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, hello, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( ((thing), hello) ), ( , world ) )"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE
    ( thing, hello, world )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), ( (thing) ), (( hello, world ) hi))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE
    ( thing, ( hello, world ) hi )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((hello, world), hi))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE
    ( thing, ( hello, world ), hi )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ())"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), (()))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, () )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), (,))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, , )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((),))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, (), )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((,)))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, (,) )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((hello)))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, (hello) )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((hello) world))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, (hello) world)
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((hello),))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, (hello),)
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((hello), world))"
  , ARGOT_GEN_DETAIL_PARSE_IDENTIFIER_LIKE( thing, (hello), world)
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_parenthesized_identifier_like )
{
  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((thing), hello)
          , right_parenthesis_token
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE( thing, ( hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((thing), hello)
          , right_parenthesis_token
          )
        , (world)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE
    ( thing, ( hello ) world )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((thing), hello)
          , right_parenthesis_token
          )
        , (, world)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE
    ( thing, ( hello ), world )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((hello, world)) )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE
    ( thing, ( hello, world ) )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), (( hello, world ) hi))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE
    ( thing, ( hello, world ) hi )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((hello, world), hi))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE
    ( thing, ( hello, world ), hi )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (left_parenthesis_token), ())"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE( thing, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), (()))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE( thing, () )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (left_parenthesis_token), (,))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE( thing, , )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((),))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE( thing, (), )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (thing), ((,)))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_IDENTIFIER_LIKE( thing, (,) )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_type_like )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( ((blah), hello ) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE
    ( blah, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( ((blah), hello, world ) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE
    ( blah, hello, world )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), ())"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE
    ( blah, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), (,))"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE
    ( blah,, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), (()))"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE
    ( blah, () )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), ((), ))"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE
    ( blah, (), )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), ((,)))"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_LIKE
    ( blah, (,) )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_parenthesized_type_like )
{
  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((blah), hello)
          , right_parenthesis_token
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, ( hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((blah), hello, world)
          , right_parenthesis_token
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, ( hello, world ) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((blah), hello)
          , right_parenthesis_token
          )
        , ( world )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, ( hello ) world )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((blah), hello, world)
          , right_parenthesis_token
          )
        , ( hi )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, ( hello, world ) hi )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ((blah), hello, world)
          , right_parenthesis_token
          )
        , (,hi)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, ( hello, world ), hi )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (left_parenthesis_token), ())"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (left_parenthesis_token), (hello))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), (()))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, () )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), ((), ))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, (), )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), (blah), ((,)))"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TYPE_LIKE
    ( blah, (,) )
  );

  return 0;
}

// TODO(mattcalabrese) Test nested visitation

#define ARGOT_TEST_VISIT( v, is_composite, kind, contents, data )              \
v, is_composite, kind, contents, data

BOOST_AUTO_TEST_CASE( visit_node )
{
  ARGOT_TEST_EXPANSION
  ( "2, 0, nil_token, , hello"
  , ARGOT_GEN_DETAIL_VISIT_NODE
    ( nil_token, ARGOT_TEST_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "2, 0, comma_token, , hello"
  , ARGOT_GEN_DETAIL_VISIT_NODE
    ( comma_token, ARGOT_TEST_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "2, 0, left_parenthesis_token, , hello"
  , ARGOT_GEN_DETAIL_VISIT_NODE
    ( left_parenthesis_token, ARGOT_TEST_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "2, 0, right_parenthesis_token, , hello"
  , ARGOT_GEN_DETAIL_VISIT_NODE
    ( right_parenthesis_token, ARGOT_TEST_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "2, 1, user_token, (comma_token, comma_token), hello"
  , ARGOT_GEN_DETAIL_VISIT_NODE
    ( (user_token, comma_token, comma_token), ARGOT_TEST_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "2, 0, user_token, (a, b), hello"
  , ARGOT_GEN_DETAIL_VISIT_NODE
    ( ((user_token), a, b), ARGOT_TEST_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "2, 1, user_token, ((other_token, a), comma_token), hello"
  , ARGOT_GEN_DETAIL_VISIT_NODE
    ( (user_token, (other_token, a), comma_token), ARGOT_TEST_VISIT, hello )
  );

  return 0;
}

#define ARGOT_TEST_ROOTED_VISITnil_token( v, contents, data )                  \
saw_nil_token, v, contents, data

#define ARGOT_TEST_ROOTED_VISITcomma_token( v, contents, data )                \
saw_comma_token, v, contents, data

#define ARGOT_TEST_ROOTED_VISITleft_parenthesis_token( v, contents, data )     \
saw_left_parenthesis_token, v, contents, data

#define ARGOT_TEST_ROOTED_VISITright_parenthesis_token( v, contents, data )    \
saw_right_parenthesis_token, v, contents, data

#define ARGOT_TEST_ROOTED_VISITuser_token( v, contents, data )                 \
saw_user_token, v, contents, data

BOOST_AUTO_TEST_CASE( rooted_visit_node )
{
  ARGOT_TEST_EXPANSION
  ( "saw_nil_token, 2, , hello"
  , ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE
    ( nil_token, ARGOT_TEST_ROOTED_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "saw_comma_token, 2, , hello"
  , ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE
    ( comma_token, ARGOT_TEST_ROOTED_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "saw_left_parenthesis_token, 2, , hello"
  , ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE
    ( left_parenthesis_token, ARGOT_TEST_ROOTED_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "saw_right_parenthesis_token, 2, , hello"
  , ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE
    ( right_parenthesis_token, ARGOT_TEST_ROOTED_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "saw_user_token, 2, (comma_token, comma_token), hello"
  , ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE
    ( (user_token, comma_token, comma_token), ARGOT_TEST_ROOTED_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "saw_user_token, 2, (a, b), hello"
  , ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE
    ( ((user_token), a, b), ARGOT_TEST_ROOTED_VISIT, hello )
  );

  ARGOT_TEST_EXPANSION
  ( "saw_user_token, 2, ((other_token, a), comma_token), hello"
  , ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE
    ( (user_token, (other_token, a), comma_token)
    , ARGOT_TEST_ROOTED_VISIT, hello
    )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( unparse_node )
{
  ARGOT_TEST_EXPANSION
  ( ""
  , ARGOT_GEN_DETAIL_UNPARSE_NODE
    ( nil_token )
  );

  ARGOT_TEST_EXPANSION
  ( ","
  , ARGOT_GEN_DETAIL_UNPARSE_NODE
    ( comma_token )
  );

  ARGOT_TEST_EXPANSION
  ( "()"
  , ARGOT_GEN_DETAIL_UNPARSE_NODE
    ( ( user_token, left_parenthesis_token, right_parenthesis_token ) )
  );

  ARGOT_TEST_EXPANSION
  ( "requires"
  , ARGOT_GEN_DETAIL_UNPARSE_NODE
    ( requires )
  );

  ARGOT_TEST_EXPANSION
  ( "( hello, world )"
  , ARGOT_GEN_DETAIL_UNPARSE_NODE
    ( ( test_node
      , left_parenthesis_token
      , ((blah), hello, world)
      , right_parenthesis_token
      )
    )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_requirement )
{
  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ( ( requirement ), hello )
          , right_parenthesis_token
          )
        , ( )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( ( hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ( ( requirement ), hello, world )
          , right_parenthesis_token
          )
        , ( )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( ( hello, world ) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ( ( requirement ), hello )
          , right_parenthesis_token
          )
        , ( world )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( ( hello ) world )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ( ( requirement ), hello, world )
          , right_parenthesis_token
          )
        , ( hi )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( ( hello, world ) hi )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( left_parenthesis_token
          , ( ( requirement ), hello, world )
          , right_parenthesis_token
          )
        , ( , hi )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( ( hello, world ), hi )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), ( left_parenthesis_token ), ())"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT()
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), ( requirement ), (()))"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( () )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), ( requirement ), ((), ))"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( (), )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected( soft(), ( requirement ), ((,)))"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT( (,) )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_requirement_list )
{
  ARGOT_TEST_EXPANSION
  ( "value( requirement_list( (hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST
    ( ( hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( requirement_list( (hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST
    ( ( hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( requirement_list( (hello), (world) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST
    ( ( hello ) and ( world ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( requirement_list( (hello), (world) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST
    ( ( hello ) and ( world ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( requirement_list( (hello, world), (world, hello) )"
         ", ()"
         ")"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST
    ( ( hello, world ) and ( world, hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( requirement_list( (hello, world), (world, hello) )"
          ", (,)"
          ")"
  , ARGOT_GEN_DETAIL_PARSE_REQUIREMENT_LIST
    ( ( hello, world ) and ( world, hello ), )
  );

  // TODO(mattcalabrese) Test failures
}

#if 0

BOOST_AUTO_TEST_CASE( parse_requires_clause )
{
  ARGOT_TEST_EXPANSION
  ( "value( (requires (hello)), requires_clause( (hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( requires ( hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (requires (hello)), requires_clause( (hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( requires ( hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (requires (hello) and (world))"
         ", requires_clause( (hello), (world) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( requires ( hello ) and ( world ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (requires (hello) and (world))"
         ", requires_clause( (hello), (world) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( requires ( hello ) and ( world ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (requires (hello, world) and (world, hello))"
         ", requires_clause( (hello, world), (world, hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( requires ( hello, world ) and ( world, hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (requires (hello, world) and (world, hello))"
         ", requires_clause( (hello, world), (world, hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( requires ( hello, world ) and ( world, hello ), )
  );

/*
  ARGOT_TEST_EXPANSION
  ( "value( , requires_clause( (hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( ( hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( , requires_clause( (hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( ( hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( , requires_clause( (hello), (world) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( ( hello ) and ( world ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( , requires_clause( (hello), (world) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( ( hello ) and ( world ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( , requires_clause( (hello, world), (world, hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( ( hello, world ) and ( world, hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( "value( , requires_clause( (hello, world), (world, hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_REQUIRES_CLAUSE
    ( ( hello, world ) and ( world, hello ), )
  );*/
}

BOOST_AUTO_TEST_CASE( parse_associated_requirements )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( requires (hello), ), associated_requirements( (hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires (hello), ), associated_requirements( (hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ),, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires (hello) and (world), )"
    "     , associated_requirements( (hello), (world) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ) and ( world ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires (hello) and (world), )"
    "       , associated_requirements( (hello), (world) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ) and ( world ),, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello, world ) and ( world, hello ), )"
    "     , associated_requirements( (hello, world), (world, hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello, world ) and ( world, hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello, world ) and ( world, hello ), )"
    "     , associated_requirements( (hello, world), (world, hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello, world ) and ( world, hello ),, )
  );

  // TODO(mattcalabrese) Test more errors

  ARGOT_TEST_EXPANSION
  ( "unexpected"
    "( hard( \"Expected a comma at the end of associated-requirements: \" )"
    ", associated_requirements, ( requires ( hello ) )"
    ")"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ) )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected"
    "( hard( \"Expected a comma at the end of associated-requirements: \" )"
    ", associated_requirements, ( requires ( hello ) and ( world ) )"
    ")"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ) and ( world ) )
  );

  ARGOT_TEST_EXPANSION
  ( "unexpected"
    "( hard( \"Expected a comma at the end of associated-requirements: \" )"
    ", associated_requirements"
    ", ( requires ( hello, world ) and ( world, hello ) )"
    ")"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello, world ) and ( world, hello ) )
  );

  return 0;
}

BOOST_AUTO_TEST_CASE( parse_type_parameter_key )
{
  ARGOT_TEST_EXPANSION
  ( "  value( ( class ), type_parameter_key( class ), () )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( class )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename ), type_parameter_key( typename ), () )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( typename )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class ), type_parameter_key( class ), ( hello) )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( class hello )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename ), type_parameter_key( typename ), ( hello ) )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( typename hello )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class ), type_parameter_key( class ), ( hello, world ) )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( class hello, world )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename ), type_parameter_key( typename ), ( hello, world ) )"
  , ARGOT_GEN_DETAIL_PARSE_TYPE_PARAMETER_KEY( typename hello, world )
  );

  // TODO(mattcalabrese) Test failures
}

BOOST_AUTO_TEST_CASE( parse_associated_type_or_template )
{
  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", associated_type( type_parameter_key( class ), name( foo ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE( class foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename foo, )"
    ", associated_type( type_parameter_key( typename ), name( foo ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE( typename foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", associated_type( type_parameter_key( class ), name( foo ) )"
    ", (a) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE( class foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename foo, )"
    ", associated_type( type_parameter_key( typename ), name( foo ) )"
    ", (a) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE( typename foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", associated_type( type_parameter_key( class ), name( foo ) )"
    ", (a, b) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE( class foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename foo, )"
    ", associated_type( type_parameter_key( typename ), name( foo ) )"
    ", (a, b) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE( typename foo, a, b )
  );

  // TODO(mattcalabrese) Test failures
/*



  ARGOT_TEST_EXPANSION
  ( "unexpected"
    "( hard( \"Expected a comma at the end of associated-requirements: \" )"
    ", associated_requirements"
    ", ( requires ( hello, world ) and ( world, hello ) )"
    ")"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE
    ( requires ( hello, world ) and ( world, hello ) )
  );*/
}

BOOST_AUTO_TEST_CASE( parse_constrained_parameter_kind )
{
  ARGOT_TEST_EXPANSION
  ( "  value( ( ((foo)) )"
    ", constrained_parameter_kind( foo )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND( ((foo)) )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( ((foo)) )"
    ", constrained_parameter_kind( foo )"
    ", (bar) )"
  , ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND( ((foo)) bar )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( ((foo)) )"
    ", constrained_parameter_kind( foo )"
    ", (,) )"
  , ARGOT_GEN_DETAIL_PARSE_CONSTRAINED_PARAMETER_KIND( ((foo)), )
  );

  // TODO(mattcalabrese) Test failures
/*



  ARGOT_TEST_EXPANSION
  ( "unexpected"
    "( hard( \"Expected a comma at the end of associated-requirements: \" )"
    ", associated_requirements"
    ", ( requires ( hello, world ) and ( world, hello ) )"
    ")"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_TYPE_OR_TEMPLATE
    ( requires ( hello, world ) and ( world, hello ) )
  );*/
}

BOOST_AUTO_TEST_CASE( parse_concept_member_specifier )
{
  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello ), ), associated_requirements( (hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello ), ), associated_requirements( (hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ),, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello ) and ( world ), )"
    "     , associated_requirements( (hello), (world) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ) and ( world ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello ) and ( world ), )"
    "     , associated_requirements( (hello), (world) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello ) and ( world ),, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello, world ) and ( world, hello ), )"
    "     , associated_requirements( (hello, world), (world, hello) ), () )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello, world ) and ( world, hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello, world ) and ( world, hello ), )"
    "     , associated_requirements( (hello, world), (world, hello) ), (,) )"
  , ARGOT_GEN_DETAIL_PARSE_ASSOCIATED_REQUIREMENTS
    ( requires ( hello, world ) and ( world, hello ),, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", associated_type( type_parameter_key( class ), name( foo ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( class foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename foo, )"
    ", associated_type( type_parameter_key( typename ), name( foo ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( typename foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", associated_type( type_parameter_key( class ), name( foo ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( class foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename foo, )"
    ", associated_type( type_parameter_key( typename ), name( foo ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( typename foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", associated_type( type_parameter_key( class ), name( foo ) )"
    ", (a, b) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( class foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename foo, )"
    ", associated_type( type_parameter_key( typename ), name( foo ) )"
    ", (a, b) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFIER( typename foo, a, b )
  );

  // TODO(mattcalabrese) Test failures
}

BOOST_AUTO_TEST_CASE( parse_concept_member_specification )
{
  ARGOT_TEST_EXPANSION
  ( "value"
    "( ( requires ( hello ), )"
    ", concept_member_specification( associated_requirements( (hello) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( requires ( hello ), )
  );

  ARGOT_TEST_EXPANSION
  ( "value"
    "( ( requires ( hello ), )"
    ", concept_member_specification( associated_requirements( (hello) ) )"
    ", (,) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( requires ( hello ),, )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello ) and ( world ), )"
    ", concept_member_specification( associated_requirements"
    "( (hello), (world) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( requires ( hello ) and ( world ), )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", concept_member_specification("
    "   associated_type( type_parameter_key( class ), name( foo ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION( class foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( typename foo, )"
    ", concept_member_specification"
    "( associated_type( type_parameter_key( typename ), name( foo ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION( typename foo, )
  );

  ARGOT_TEST_EXPANSION
  ( "  value( ( class foo, )"
    ", concept_member_specification("
    " associated_type( type_parameter_key( class ), name( foo ) ) )"
    ", (a, b) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION( class foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( requires ( hello ) and ( world ),"
             "requires ( world ) and ( hello ),)"
    ", concept_member_specification"
    "( associated_requirements"
    "  ( (hello), (world) )"
    ", associated_requirements"
    "  ( (world), (hello) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( requires ( hello ) and ( world ),
      requires ( world ) and ( hello ),
    )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (requires ( hello ) and ( world ), typename foo,)"
    ", concept_member_specification"
    "( associated_requirements"
    "  ( (hello), (world) )"
    ", associated_type"
    "  ( type_parameter_key( typename ), name( foo ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( requires ( hello ) and ( world ),
      typename foo,
    )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (typename foo, requires ( hello ) and ( world ),)"
    ", concept_member_specification"
    "( associated_type"
    "  ( type_parameter_key( typename ), name( foo ) )"
    ", associated_requirements"
    "  ( (hello), (world) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( typename foo,
      requires ( hello ) and ( world ),
    )
  );

  ARGOT_TEST_EXPANSION
  ( "value( (typename foo, requires ( hello ) and ( world ), class bar,)"
    ", concept_member_specification"
    "( associated_type"
    "  ( type_parameter_key( typename ), name( foo ) )"
    ", associated_requirements"
    "  ( (hello), (world) )"
    ", associated_type"
    "  ( type_parameter_key( class ), name( bar ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( typename foo,
      requires ( hello ) and ( world ),
      class bar,
    )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ( typename foo,
            requires ( hello ) and ( world ),
            class bar,
          )
        , concept_member_specification
          ( associated_type( type_parameter_key( typename ), name( foo ) )
          , associated_requirements( ( hello ), ( world ) )
          , associated_type( type_parameter_key( class ), name( bar ) )
          )
        , ( a b c, d )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_MEMBER_SPECIFICATION
    ( typename foo,
      requires ( hello ) and ( world ),
      class bar,
      a b c, d
    )
  );

  // TODO(mattcalabrese) Test failures
}

BOOST_AUTO_TEST_CASE( parse_concept_body )
{
  ARGOT_TEST_EXPANSION
  ( "value"
    "( ()"
    ", concept_body()"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY(())
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , concept_body()
        , ( hello, world )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY(() hello, world )
  );

  ARGOT_TEST_EXPANSION
  ( "value"
    "( (( requires ( hello ),) )"
    ", concept_body"
    "  ( concept_member_specification( associated_requirements( (hello) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    (( requires ( hello ), ))
  );

  ARGOT_TEST_EXPANSION
  ( "value"
    "( ( (requires ( hello ),) )"
    ", concept_body"
    "  ( concept_member_specification( associated_requirements( (hello) ) ) )"
    ", (,) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    ( (requires ( hello ),), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( (requires ( hello ) and ( world ),) )"
    ", concept_body"
    "  ( concept_member_specification( associated_requirements"
    "( (hello), (world) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    (( requires ( hello ) and ( world ), ))
  );

  ARGOT_TEST_EXPANSION
  ( "  value( (( class foo, ))"
    ", concept_body"
    "  ( concept_member_specification("
    "   associated_type( type_parameter_key( class ), name( foo ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY(( class foo, ))
  );

  ARGOT_TEST_EXPANSION
  ( "  value( (( typename foo, ))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_type( type_parameter_key( typename ), name( foo ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY(( typename foo, ))
  );

  ARGOT_TEST_EXPANSION
  ( "  value( (( class foo, ))"
    ", concept_body"
    "  ( concept_member_specification("
    " associated_type( type_parameter_key( class ), name( foo ) ) ) )"
    ", (a, b) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY( (class foo,) a, b )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( (requires ( hello ) and ( world ),"
             "requires ( world ) and ( hello ),))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_requirements"
    "  ( (hello), (world) )"
    ", associated_requirements"
    "  ( (world), (hello) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    (( requires ( hello ) and ( world ),
       requires ( world ) and ( hello ),
    ))
  );

  ARGOT_TEST_EXPANSION
  ( "value( ((requires ( hello ) and ( world ), typename foo,))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_requirements"
    "  ( (hello), (world) )"
    ", associated_type"
    "  ( type_parameter_key( typename ), name( foo ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    (( requires ( hello ) and ( world ),
       typename foo,
    ))
  );

  ARGOT_TEST_EXPANSION
  ( "value( ((typename foo, requires ( hello ) and ( world ),))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_type"
    "  ( type_parameter_key( typename ), name( foo ) )"
    ", associated_requirements"
    "  ( (hello), (world) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    (( typename foo,
       requires ( hello ) and ( world ),
    ))
  );

  ARGOT_TEST_EXPANSION
  ( "value( ((typename foo, requires ( hello ) and ( world ), class bar,))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_type"
    "  ( type_parameter_key( typename ), name( foo ) )"
    ", associated_requirements"
    "  ( (hello), (world) )"
    ", associated_type"
    "  ( type_parameter_key( class ), name( bar ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    (( typename foo,
       requires ( hello ) and ( world ),
       class bar,
    ))
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( (( typename foo,
            requires ( hello ) and ( world ),
            class bar,
          ))
        , concept_body
          ( concept_member_specification
            ( associated_type( type_parameter_key( typename ), name( foo ) )
            , associated_requirements( ( hello ), ( world ) )
            , associated_type( type_parameter_key( class ), name( bar ) )
            )
          )
        , ( a b c, d )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    ( (  typename foo,
         requires ( hello ) and ( world ),
         class bar,
      )
      a b c, d
    )
  );

  // TODO(mattcalabrese) Test failures
}

BOOST_AUTO_TEST_CASE( parse_template_parameter )
{
  // TODO(mattcalabrese) Test parsing of parenthesized parameter kinds.

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( class foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( typename foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( class foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( typename foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( class foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( typename foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( class,,, foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( typename,,, foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( class,,, foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( typename,,, foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( class,,, foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter
          ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER( typename,,, foo, a, b )
  );
  // TODO(mattcalabrese) Test failures
}

BOOST_AUTO_TEST_CASE( parse_template_parameter_list )
{
  // TODO(mattcalabrese) Test parsing of parenthesized parameter kinds.

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( class foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( typename foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( class foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( typename foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( class foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( typename foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( class,,, foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( typename,,, foo )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( class,,, foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( typename,,, foo, a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( class,,, foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST( typename,,, foo, a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( bar ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( baz ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST
    ( typename,,, foo, class bar, class,,, baz )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( bar ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( baz ) )
          )
        , (, blip,)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_TEMPLATE_PARAMETER_LIST
    ( typename,,, foo, class bar, class,,, baz, blip, )
  );

  // TODO(mattcalabrese) Test failures
}

BOOST_AUTO_TEST_CASE( parse_parenthesized_template_parameter_list )
{
  // TODO(mattcalabrese) Test parsing of parenthesized parameter kinds.

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST(( class foo ))
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    (( typename foo ))
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (class foo), a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (typename foo), a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (class foo), a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 0 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (typename foo), a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (class,,, foo) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (typename,,, foo) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (class,,, foo), a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          )
        , (, a)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (typename,,, foo), a )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (class,,, foo), a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          )
        , (, a, b)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (typename,,, foo), a, b )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( bar ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( baz ) )
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (typename,,, foo, class bar, class,,, baz) )
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , parenthesized_template_parameter_list
          ( template_parameter
            ( type_parameter_key( typename ), variadic( 1 ), name( foo ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 0 ), name( bar ) )
          , template_parameter
            ( type_parameter_key( class ), variadic( 1 ), name( baz ) )
          )
        , (, blip,)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_PARENTHESIZED_TEMPLATE_PARAMETER_LIST
    ( (typename,,, foo, class bar, class,,, baz), blip, )
  );

  // TODO(mattcalabrese) Test failures
}

BOOST_AUTO_TEST_CASE( parse_concept_definition )
{
  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , concept_definition
          ( auto( 0 ), name( foo )
          , parenthesized_template_parameter_list
            ( template_parameter
              ( type_parameter_key( class ), variadic( 0 ), name( A ) )
            , template_parameter
              ( type_parameter_key( typename ), variadic( 1 ), name( b ) )
            )
          , concept_body()
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b)())
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , concept_definition
          ( auto( 0 ), name( foo )
          , parenthesized_template_parameter_list
            ( template_parameter
              ( type_parameter_key( class ), variadic( 0 ), name( A ) )
            , template_parameter
              ( type_parameter_key( typename ), variadic( 1 ), name( b ) )
            )
          , concept_body()
          )
        , (blah)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b)() blah)
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , concept_definition
          ( auto( 0 ), name( foo )
          , parenthesized_template_parameter_list
            ( template_parameter
              ( type_parameter_key( class ), variadic( 0 ), name( A ) )
            , template_parameter
              ( type_parameter_key( typename ), variadic( 1 ), name( b ) )
            )
          , concept_body(), comma()
          )
        , ()
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b)(),)
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , concept_definition
          ( auto( 0 ), name( foo )
          , parenthesized_template_parameter_list
            ( template_parameter
              ( type_parameter_key( class ), variadic( 0 ), name( A ) )
            , template_parameter
              ( type_parameter_key( typename ), variadic( 1 ), name( b ) )
            )
          , concept_body(), comma()
          )
        , (blah)
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b)(), blah)
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( ()
        , concept_body()
        , ( hello, world )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b)() hello, world )
  );

  ARGOT_TEST_EXPANSION
  ( "value"
    "( (( requires ( hello ),) )"
    ", concept_body"
    "  ( concept_member_specification( associated_requirements( (hello) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_BODY
    (( requires ( hello ), ))
  );

  ARGOT_TEST_EXPANSION
  ( "value"
    "( ( (requires ( hello ),) )"
    ", concept_body"
    "  ( concept_member_specification( associated_requirements( (hello) ) ) )"
    ", (,) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    ( concept (foo)(class A, typename,,, b) (requires ( hello ),), )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( (requires ( hello ) and ( world ),) )"
    ", concept_body"
    "  ( concept_member_specification( associated_requirements"
    "( (hello), (world) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    ( concept (foo)(class A, typename,,, b)( requires ( hello ) and ( world ), ))
  );

  ARGOT_TEST_EXPANSION
  ( "  value( (( class foo, ))"
    ", concept_body"
    "  ( concept_member_specification("
    "   associated_type( type_parameter_key( class ), name( foo ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b)( class foo, ))
  );

  ARGOT_TEST_EXPANSION
  ( "  value( (( typename foo, ))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_type( type_parameter_key( typename ), name( foo ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b)( typename foo, ))
  );

  ARGOT_TEST_EXPANSION
  ( "  value( (( class foo, ))"
    ", concept_body"
    "  ( concept_member_specification("
    " associated_type( type_parameter_key( class ), name( foo ) ) ) )"
    ", (a, b) )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    (concept (foo)(class A, typename,,, b) (class foo,) a, b )
  );

  ARGOT_TEST_EXPANSION
  ( "value( ( (requires ( hello ) and ( world ),"
             "requires ( world ) and ( hello ),))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_requirements"
    "  ( (hello), (world) )"
    ", associated_requirements"
    "  ( (world), (hello) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    ( concept (foo)(class A, typename,,, b)( requires ( hello ) and ( world ),
       requires ( world ) and ( hello ),
    ))
  );

  ARGOT_TEST_EXPANSION
  ( "value( ((requires ( hello ) and ( world ), typename foo,))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_requirements"
    "  ( (hello), (world) )"
    ", associated_type"
    "  ( type_parameter_key( typename ), name( foo ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    ( concept (foo)(class A, typename,,, b)( requires ( hello ) and ( world ),
       typename foo,
    ))
  );

  ARGOT_TEST_EXPANSION
  ( "value( ((typename foo, requires ( hello ) and ( world ),))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_type"
    "  ( type_parameter_key( typename ), name( foo ) )"
    ", associated_requirements"
    "  ( (hello), (world) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    ( concept (foo)(class A, typename,,, b)( typename foo,
       requires ( hello ) and ( world ),
    ))
  );

  ARGOT_TEST_EXPANSION
  ( "value( ((typename foo, requires ( hello ) and ( world ), class bar,))"
    ", concept_body"
    "  ( concept_member_specification"
    "( associated_type"
    "  ( type_parameter_key( typename ), name( foo ) )"
    ", associated_requirements"
    "  ( (hello), (world) )"
    ", associated_type"
    "  ( type_parameter_key( class ), name( bar ) ) ) )"
    ", () )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    ( concept (foo)(class A, typename,,, b)( typename foo,
       requires ( hello ) and ( world ),
       class bar,
    ))
  );

  ARGOT_TEST_EXPANSION
  ( R"( value
        ( (( typename foo,
            requires ( hello ) and ( world ),
            class bar,
          ))
        , concept_body
          ( concept_member_specification
            ( associated_type( type_parameter_key( typename ), name( foo ) )
            , associated_requirements( ( hello ), ( world ) )
            , associated_type( type_parameter_key( class ), name( bar ) )
            )
          )
        , ( a b c, d )
        )
      )"
  , ARGOT_GEN_DETAIL_PARSE_CONCEPT_DEFINITION
    ( concept (foo)(class A, typename,,, b) (  typename foo,
         requires ( hello ) and ( world ),
         class bar,
      )
      a b c, d
    )
  );

  // TODO(mattcalabrese) Test failures
}
#endif
