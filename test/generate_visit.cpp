#include <fstream>

char const* extra_spaces( int v )
{
  if( v >= 100 )
    return "";

  if( v >= 10 )
    return " ";

  return "  ";

  return 0;
}

int main()
{
  int const recursion_depth = 16;

  std::ofstream file( "visit_node.hpp" );

  file << R"(#include <argot/gen/concept_body/detail/variadic_empty.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/debug/error.hpp>
#include <boost/preprocessor/detail/auto_rec.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/size.hpp>
)";

  file << R"(
#define ARGOT_GEN_DETAIL_VISIT_NODE                                            \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_VISIT_NODE_                                     \
            , BOOST_PP_AUTO_REC( ARGOT_GEN_DETAIL_VISIT_NODE_P, )"
       << recursion_depth
       << " )          " << extra_spaces( recursion_depth ) << R"(\
            )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE                                     \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_                              \
            , BOOST_PP_AUTO_REC( ARGOT_GEN_DETAIL_VISIT_NODE_P, )"
       << recursion_depth
       << " )   " << extra_spaces( recursion_depth ) << R"(\
            )

#define ARGOT_GEN_DETAIL_IS_CORE_TOKEN_KIND( kind )                            \
BOOST_PP_EQUAL                                                                 \
( 2, BOOST_PP_TUPLE_SIZE( ( ARGOT_GEN_DETAIL_IS_CORE_TOKEN_IMPL ## kind ) ) )

#define ARGOT_GEN_DETAIL_IS_CORE_TOKEN_IMPLnil_token ,
#define ARGOT_GEN_DETAIL_IS_CORE_TOKEN_IMPLcomma_token ,
#define ARGOT_GEN_DETAIL_IS_CORE_TOKEN_IMPLleft_parenthesis_token ,
#define ARGOT_GEN_DETAIL_IS_CORE_TOKEN_IMPLright_parenthesis_token ,

#define ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( kind )                          \
BOOST_PP_IIF( ARGOT_GEN_DETAIL_IS_CORE_TOKEN_KIND( kind )                      \
            , ARGOT_GEN_DETAIL_VARIADIC_EMPTY                                  \
            , ARGOT_GEN_DETAIL_NONCORE_TERSE_TOKEN_CONTENTS                    \
            )( kind )

#define ARGOT_GEN_DETAIL_NONCORE_TERSE_TOKEN_CONTENTS( kind ) ( kind )

)";

  file
    << "#define ARGOT_GEN_DETAIL_VISIT_NODE_P( v )"
       "                                     \\\n"
       "BOOST_PP_CAT( ARGOT_GEN_DETAIL_VISIT_CHECK_"
       "                                    \\\n"
       "            , ARGOT_GEN_DETAIL_VISIT_NODE_ ## v"
       "                                \\\n"
       "              ( BOOST_PP_NIL, ARGOT_GEN_DETAIL_VISIT_NODE_F"
       ", BOOST_PP_NIL )    \\\n"
       "            )\n\n";

  file
    << "#define ARGOT_GEN_DETAIL_VISIT_NODE_F( ... ) BOOST_PP_NIL\n\n";

  file << "#define ARGOT_GEN_DETAIL_VISIT_CHECK_" << ( recursion_depth + 1 )
       << "( n, m, d ) BOOST_PP_ERROR( 0x0001 )\n\n"
       << "#define ARGOT_GEN_DETAIL_VISIT_CHECK_BOOST_PP_NIL 1\n\n";

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_"
      << i << "( n, m, d ) 0\n";
  }

  file << "\n";

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_VISIT_NODE_" << i
      << "( node, macro, data )                   "
      << extra_spaces( i ) << "\\"
      << R"(
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_)" << i << extra_spaces( i )
            << R"(                                \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_)" << i << extra_spaces( i )
            << R"(                             \
            )( node, macro, data )

)";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_" << i
      << "( node, macro, data )" << extra_spaces( i ) << "              \\\n"
         "macro( " << ( i + 1 )
      << ", 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )\n\n";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_VISIT_PARENS_" << i << "( node, mac, data )"
      << "                   " << extra_spaces( i ) << "\\\n"
      << "ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_" << i
      << "                                         " << extra_spaces( i )
      << "\\\n"
      << "( mac, BOOST_PP_TUPLE_ELEM( 0, node )"
         ", BOOST_PP_TUPLE_POP_FRONT( node ), data )\n\n";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_" << i
      << "( mac, kind, contents, data )    " << extra_spaces( i ) << "\\\n"
      << "mac( " << ( i + 1 )
      << ", BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )"
      << "                   " << extra_spaces( i + 1 ) << "\\\n"
      << "   , BOOST_PP_REMOVE_PARENS( kind ), contents, data"
         "                            \\\n"
         "   )\n\n";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_" << i
      << "( node, macro, data )            "
      << extra_spaces( i ) << R"(\
ARGOT_GEN_DETAIL_VISIT_NODE_)" << i <<  extra_spaces( i )
<< R"(                                                \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_)" << i
<< R"(, ( macro, data ) )

)";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_" << i
      << "( v, comp, k, c, d )        "
      << extra_spaces( i ) << "\\"
      << R"(
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

)";
  }

  return 0;
}
