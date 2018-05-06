#include <argot/gen/concept_body/detail/visit_node.hpp>

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

#define ARGOT_GEN_DETAIL_UNPARSE_NODE                                          \
BOOST_PP_CAT( ARGOT_GEN_DETAIL_UNPARSE_NODE_                                   \
            , BOOST_PP_AUTO_REC( ARGOT_GEN_DETAIL_VISIT_NODE_P, 16 )         \
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

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_1( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_1, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_2( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_2, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_3( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_3, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_4( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_4, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_5( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_5, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_6( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_6, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_7( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_7, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_8( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_8, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_9( node )                                \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_9, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_10( node )                               \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_10, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_11( node )                               \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_11, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_12( node )                               \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_12, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_13( node )                               \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_13, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_14( node )                               \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_14, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_15( node )                               \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_15, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_16( node )                               \
ARGOT_GEN_DETAIL_VISIT_NODE( node, ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_16, ~ )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_1( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_1                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_2( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_2                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_3( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_3                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_4( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_4                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_5( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_5                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_6( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_6                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_7( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_7                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_8( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_8                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_9( v, is_comp, kind, contents, d )  \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_9                        \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_10( v, is_comp, kind, contents, d ) \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_10                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_11( v, is_comp, kind, contents, d ) \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_11                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_12( v, is_comp, kind, contents, d ) \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_12                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_13( v, is_comp, kind, contents, d ) \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_13                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_14( v, is_comp, kind, contents, d ) \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_14                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_15( v, is_comp, kind, contents, d ) \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_15                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_IMPL_16( v, is_comp, kind, contents, d ) \
BOOST_PP_IIF( is_comp                                                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_16                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_TERMINAL                           \
            )( kind, contents )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_1( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_1                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_2( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_2                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_3( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_3                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_4( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_4                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_5( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_5                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_6( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_6                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_7( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_7                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_8( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_8                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_9( kind, contents )            \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_9                   \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_10( kind, contents )           \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_10                  \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_11( kind, contents )           \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_11                  \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_12( kind, contents )           \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_12                  \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_13( kind, contents )           \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_13                  \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_14( kind, contents )           \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_14                  \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_15( kind, contents )           \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_15                  \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_16( kind, contents )           \
BOOST_PP_FOR( BOOST_PP_TUPLE_PUSH_BACK( contents, ~ )                          \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_PRED                     \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_OP                       \
            , ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_16                  \
            )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_1( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_2( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_3( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_4( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_5( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_6( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_7( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_8( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_9( r, contents )          \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_10( r, contents )         \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_11( r, contents )         \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_12( r, contents )         \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_13( r, contents )         \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_14( r, contents )         \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_15( r, contents )         \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

#define ARGOT_GEN_DETAIL_UNPARSE_NODE_COMPOSITE_BODY_16( r, contents )         \
ARGOT_GEN_DETAIL_UNPARSE_NODE( BOOST_PP_TUPLE_ELEM( 0, contents ) )

