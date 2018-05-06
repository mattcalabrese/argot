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

  std::ofstream file( "unparse_node.hpp" );

  file << R"(#include <argot/gen/concept_body/detail/visit_node.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/auto_rec.hpp>
#include <boost/preprocessor/repetition/for.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/push_back.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/vmd/is_empty.hpp>
)";

  file << R"(
#define ARGOT_GEN_DETAIL_UNPARSE_NODE                                          \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_UNPARSE_NODE_                                   \
            , BOOST_PP_AUTO_REC( ARGOT_GEN_DETAIL_VISIT_NODE_P, )"
       << recursion_depth
       << " )        " << extra_spaces( recursion_depth ) << R"(\
            )


#define ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL( kind, contents )               \
BOOST_PP_IIF( ARGOT_GEN_DETAIL_IS_CORE_TOKEN_KIND( kind )                      \
            , ARGOT_GEN_DETAIL_UNPARSE_CORE_TOKEN                              \
            , ARGOT_GEN_DETAIL_UNPARSE_NONCORE_TERMINAL                        \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_CORE_TOKEN( kind, contents )                  \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_UNPARSE_CORE_TOKEN_, kind )

#define ARGOT_GEN_DETAIL_UNPARSE_CORE_TOKEN_nil_token
#define ARGOT_GEN_DETAIL_UNPARSE_CORE_TOKEN_comma_token ,
#define ARGOT_GEN_DETAIL_UNPARSE_CORE_TOKEN_left_parenthesis_token (
#define ARGOT_GEN_DETAIL_UNPARSE_CORE_TOKEN_right_parenthesis_token )

#define ARGOT_GEN_DETAIL_UNPARSE_NONCORE_TERMINAL( kind, contents )            \
BOOST_PP_IIF( BOOST_VMD_IS_EMPTY( contents )                                   \
            , ARGOT_GEN_DETAIL_UNPARSE_NONCORE_TERMINAL_TERSE                  \
            , ARGOT_GEN_DETAIL_UNPARSE_NONCORE_TERMINAL_VERBOSE                \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NONCORE_TERMINAL_TERSE( kind, contents ) kind

#define ARGOT_GEN_DETAIL_UNPARSE_NONCORE_TERMINAL_VERBOSE( kind, contents )    \
BOOST_PP_TUPLE_ENUM( contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED( r, contents )            \
BOOST_PP_NOT_EQUAL( 1, BOOST_PP_TUPLE_SIZE( contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP( r, contents )              \
BOOST_PP_TUPLE_POP_FRONT( contents )

)";

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_UNPARSE_NODE_" << i << "( node )"
      << "                              " << extra_spaces( i ) << "\\\n"
      << "ARGOT_GEN_DETAIL_VISIT_NODE"
         "( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_" << i << ", ~ )\n\n";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_" << i
      << "( v, is_comp, kind, contents, d )" << extra_spaces( i ) << "\\\n"
         "BOOST_PP_IIF( is_comp"
         "                                                          \\\n"
         "            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_" << i
      << extra_spaces( i )
      << "                      \\\n"
         "            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL"
         "                           \\\n"
         "            )( kind, contents )\n\n";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_" << i
      << "( kind, contents )" << extra_spaces( i ) << "          \\\n"
      << "BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )"
         "                          \\\n"
         "            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED"
         "                     \\\n"
         "            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP"
         "                       \\\n"
         "            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_"
      << i << extra_spaces( i )
      << "                 \\\n"
         "            )\n\n";
  }

  for( int i = 1; i != recursion_depth + 1; ++i )
  {
    file
      << "#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_"
      << i << "( r, contents )" << extra_spaces( i ) << "        \\\n"
      << "ARGOT_GEN_DETAIL_UNPARSE_NODE"
      << "( BOOST_PP_TUPLE_ELEM( 0, contents ) )\n\n";
  }

  return 0;
}
