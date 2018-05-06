#include <argot/gen/concept_body/detail/variadic_empty.hpp>

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

#define ARGOT_GEN_DETAIL_VISIT_NODE                                            \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_VISIT_NODE_                                     \
            , BOOST_PP_AUTO_REC( ARGOT_GEN_DETAIL_VISIT_NODE_P, 16 )           \
            )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE                                     \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_                              \
            , BOOST_PP_AUTO_REC( ARGOT_GEN_DETAIL_VISIT_NODE_P, 16 )    \
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

#define ARGOT_GEN_DETAIL_VISIT_NODE_P( v )                                     \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_VISIT_CHECK_                                    \
            , ARGOT_GEN_DETAIL_VISIT_NODE_ ## v                                \
              ( BOOST_PP_NIL, ARGOT_GEN_DETAIL_VISIT_NODE_F, BOOST_PP_NIL )    \
            )

#define ARGOT_GEN_DETAIL_VISIT_NODE_F( ... ) BOOST_PP_NIL

#define ARGOT_GEN_DETAIL_VISIT_CHECK_17( n, m, d ) BOOST_PP_ERROR( 0x0001 )

#define ARGOT_GEN_DETAIL_VISIT_CHECK_BOOST_PP_NIL 1

#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_1( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_2( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_3( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_4( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_5( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_6( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_7( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_8( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_9( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_10( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_11( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_12( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_13( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_14( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_15( n, m, d ) 0
#define ARGOT_GEN_DETAIL_VISIT_CHECK_ARGOT_GEN_DETAIL_VISIT_NODE_16( n, m, d ) 0

#define ARGOT_GEN_DETAIL_VISIT_NODE_1( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_1                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_1                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_2( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_2                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_2                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_3( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_3                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_3                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_4( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_4                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_4                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_5( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_5                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_5                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_6( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_6                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_6                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_7( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_7                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_7                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_8( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_8                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_8                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_9( node, macro, data )                     \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_9                                  \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_9                               \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_10( node, macro, data )                    \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_10                                 \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_10                              \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_11( node, macro, data )                    \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_11                                 \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_11                              \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_12( node, macro, data )                    \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_12                                 \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_12                              \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_13( node, macro, data )                    \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_13                                 \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_13                              \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_14( node, macro, data )                    \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_14                                 \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_14                              \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_15( node, macro, data )                    \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_15                                 \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_15                              \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_NODE_16( node, macro, data )                    \
BOOST_PP_IIF( BOOST_PP_IS_BEGIN_PARENS( node )                                 \
            , ARGOT_GEN_DETAIL_VISIT_PARENS_16                                 \
            , ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_16                              \
            )( node, macro, data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_1( node, macro, data )                \
macro( 2, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_2( node, macro, data )                \
macro( 3, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_3( node, macro, data )                \
macro( 4, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_4( node, macro, data )                \
macro( 5, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_5( node, macro, data )                \
macro( 6, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_6( node, macro, data )                \
macro( 7, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_7( node, macro, data )                \
macro( 8, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_8( node, macro, data )                \
macro( 9, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_9( node, macro, data )                \
macro( 10, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_10( node, macro, data )               \
macro( 11, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_11( node, macro, data )               \
macro( 12, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_12( node, macro, data )               \
macro( 13, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_13( node, macro, data )               \
macro( 14, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_14( node, macro, data )               \
macro( 15, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_15( node, macro, data )               \
macro( 16, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_TERSE_TOK_16( node, macro, data )               \
macro( 17, 0, node, ARGOT_GEN_DETAIL_TERSE_TOKEN_CONTENTS( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_1( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_1                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_2( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_2                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_3( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_3                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_4( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_4                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_5( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_5                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_6( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_6                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_7( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_7                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_8( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_8                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_9( node, mac, data )                     \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_9                                           \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_10( node, mac, data )                    \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_10                                          \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_11( node, mac, data )                    \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_11                                          \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_12( node, mac, data )                    \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_12                                          \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_13( node, mac, data )                    \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_13                                          \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_14( node, mac, data )                    \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_14                                          \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_15( node, mac, data )                    \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_15                                          \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_16( node, mac, data )                    \
ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_16                                          \
( mac, BOOST_PP_TUPLE_ELEM( 0, node ), BOOST_PP_TUPLE_POP_FRONT( node ), data )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_1( mac, kind, contents, data )      \
mac( 2, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_2( mac, kind, contents, data )      \
mac( 3, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_3( mac, kind, contents, data )      \
mac( 4, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_4( mac, kind, contents, data )      \
mac( 5, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_5( mac, kind, contents, data )      \
mac( 6, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_6( mac, kind, contents, data )      \
mac( 7, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_7( mac, kind, contents, data )      \
mac( 8, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_8( mac, kind, contents, data )      \
mac( 9, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                     \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_9( mac, kind, contents, data )      \
mac( 10, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_10( mac, kind, contents, data )     \
mac( 11, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_11( mac, kind, contents, data )     \
mac( 12, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_12( mac, kind, contents, data )     \
mac( 13, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_13( mac, kind, contents, data )     \
mac( 14, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_14( mac, kind, contents, data )     \
mac( 15, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_15( mac, kind, contents, data )     \
mac( 16, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_VISIT_PARENS_IMPL_16( mac, kind, contents, data )     \
mac( 17, BOOST_PP_COMPL( BOOST_PP_IS_BEGIN_PARENS( kind ) )                    \
   , BOOST_PP_REMOVE_PARENS( kind ), contents, data                            \
   )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_1( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_1                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_1, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_2( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_2                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_2, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_3( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_3                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_3, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_4( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_4                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_4, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_5( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_5                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_5, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_6( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_6                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_6, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_7( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_7                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_7, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_8( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_8                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_8, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_9( node, macro, data )              \
ARGOT_GEN_DETAIL_VISIT_NODE_9                                                  \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_9, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_10( node, macro, data )             \
ARGOT_GEN_DETAIL_VISIT_NODE_10                                                 \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_10, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_11( node, macro, data )             \
ARGOT_GEN_DETAIL_VISIT_NODE_11                                                 \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_11, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_12( node, macro, data )             \
ARGOT_GEN_DETAIL_VISIT_NODE_12                                                 \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_12, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_13( node, macro, data )             \
ARGOT_GEN_DETAIL_VISIT_NODE_13                                                 \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_13, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_14( node, macro, data )             \
ARGOT_GEN_DETAIL_VISIT_NODE_14                                                 \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_14, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_15( node, macro, data )             \
ARGOT_GEN_DETAIL_VISIT_NODE_15                                                 \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_15, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_16( node, macro, data )             \
ARGOT_GEN_DETAIL_VISIT_NODE_16                                                 \
( node, ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_16, ( macro, data ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_1( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_2( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_3( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_4( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_5( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_6( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_7( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_8( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_9( v, comp, k, c, d )          \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_10( v, comp, k, c, d )         \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_11( v, comp, k, c, d )         \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_12( v, comp, k, c, d )         \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_13( v, comp, k, c, d )         \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_14( v, comp, k, c, d )         \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_15( v, comp, k, c, d )         \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

#define ARGOT_GEN_DETAIL_ROOTED_VISIT_NODE_IMPL_16( v, comp, k, c, d )         \
BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM( 0, d ), k )                                 \
( v, c, BOOST_PP_TUPLE_ELEM( 1, d ) )

