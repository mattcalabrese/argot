/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_PREPROCESS_HPP_
#define ARGOT_DETAIL_PREPROCESS_HPP_

#include <argot/detail/if_.hpp>

#include <cstddef>

namespace argot::detail_argot {

#define ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH() 16

// NOTE: This must match ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH()
#define ARGOT_DETAIL_EXPAND_MAX_UNROLL_DEPTH( macro, data )                    \
macro( 0, data )                                                               \
macro( 1, data )                                                               \
macro( 2, data )                                                               \
macro( 3, data )                                                               \
macro( 4, data )                                                               \
macro( 5, data )                                                               \
macro( 6, data )                                                               \
macro( 7, data )                                                               \
macro( 8, data )                                                               \
macro( 9, data )                                                               \
macro( 10, data )                                                              \
macro( 11, data )                                                              \
macro( 12, data )                                                              \
macro( 13, data )                                                              \
macro( 14, data )                                                              \
macro( 15, data )

// NOTE: This must match ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH()
#define ARGOT_DETAIL_PREPROCESSED_PARAMS_IMPL( i, data )                       \
  class T##i##_0, class T##i##_1, class T##i##_2, class T##i##_3               \
, class T##i##_4, class T##i##_5, class T##i##_6, class T##i##_7               \
, class T##i##_8, class T##i##_9, class T##i##_A, class T##i##_B               \
, class T##i##_C, class T##i##_D, class T##i##_E, class T##i##_F

#define ARGOT_DETAIL_PREPROCESSED_PARAMS( i, data )                            \
ARGOT_DETAIL_PREPROCESSED_PARAMS_IMPL( i, data )

#define ARGOT_DETAIL_TRAILING_PREPROCESSED_PARAMS( i, data )                   \
, ARGOT_DETAIL_PREPROCESSED_PARAMS_IMPL( i, data )

#define ARGOT_DETAIL_PREPROCESSED_ARGS( i, data )                              \
  T##i##_0, T##i##_1, T##i##_2, T##i##_3, T##i##_4, T##i##_5, T##i##_6         \
, T##i##_7, T##i##_8, T##i##_9, T##i##_A, T##i##_B, T##i##_C, T##i##_D         \
, T##i##_E, T##i##_F

constexpr
std::size_t amount_at_depth_table_init( std::size_t const index ) noexcept 
{
  std::size_t result = 1;
  for( std::size_t curr = 0; curr != index; ++curr )
    result *= ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH();
  return result;
}

inline constexpr std::size_t amount_at_depth_table[]
  = { amount_at_depth_table_init( 0 )
    , amount_at_depth_table_init( 1 )
    , amount_at_depth_table_init( 2 )
    , amount_at_depth_table_init( 3 )
    , amount_at_depth_table_init( 4 )
    , amount_at_depth_table_init( 5 )
    , amount_at_depth_table_init( 6 )
    , amount_at_depth_table_init( 7 )
    };

constexpr std::size_t amount_at_depth( std::size_t const depth ) noexcept
{
  return amount_at_depth_table[ depth ];
}

constexpr std::size_t
amount_per_group_at_depth( std::size_t const depth ) noexcept
{
  return amount_at_depth_table[ depth - 1 ];
}

constexpr std::size_t clamp_to_unroll_depth( std::size_t const value ) noexcept
{
  return   ( value <= ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH() )
         ? value
         : ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH();
}

// TODO(calabrese) Make this constant time and/or memoized via variable template
constexpr
std::size_t tree_depth_from_amount( std::size_t const amount ) noexcept
{
  std::size_t result = 1;
  for( std::size_t amount_at_curr_depth = ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH()
     ; amount > amount_at_curr_depth
     ; amount_at_curr_depth *= ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH()
     )
    ++result;

  return result;
}

#define ARGOT_DETAIL_EXPAND_N_TIMES_0( macro, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 0, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_2( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 1, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_3( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 2, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_4( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 3, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_5( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 4, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_6( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 5, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_7( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 6, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_8( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 7, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_9( macro, data )                           \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 8, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_10( macro, data )                          \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 9, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_11( macro, data )                          \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 10, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_12( macro, data )                          \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 11, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_13( macro, data )                          \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 12, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_14( macro, data )                          \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 13, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_15( macro, data )                          \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 14, data )

// TODO(calabrese) Possibly remove this one?
#define ARGOT_DETAIL_EXPAND_N_TIMES_16( macro, data )                          \
ARGOT_DETAIL_EXPAND_N_TIMES_1( macro, data ) macro( 15, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES_IMPL( macro, n, data )                     \
ARGOT_DETAIL_EXPAND_N_TIMES_ ## n( macro, data )

#define ARGOT_DETAIL_EXPAND_N_TIMES( macro, n, data )                          \
  ARGOT_DETAIL_EXPAND_N_TIMES_IMPL( macro, n, data )

struct take_preprocessed_amount_impl_max
{
  template< template< class... > class Result
            ARGOT_DETAIL_TRAILING_PREPROCESSED_PARAMS( 0, ~ )
          , class... /*P*/
          >
  using apply = Result< ARGOT_DETAIL_PREPROCESSED_ARGS( 0, ~ ) >;
};

struct take_preprocessed_amount_impl_not_max
{
  template< template< class... > class Result, class... P >
  using apply = Result< P... >;
};

template< template< class... > class Result, class... P >
using take_preprocessed_amount_into
  = expand_into
    < detail_if_::if_
      < sizeof...( P ) >= ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH() >
      ::then_else::template _
      < take_preprocessed_amount_impl_max
      , take_preprocessed_amount_impl_not_max
      >
      ::template apply
    , Result
    , P...
    >;

template< std::size_t Depth, std::size_t NumGroups >
struct drop_trees_at_depth_impl;

#define ARGOT_DETAIL_DROP_TREES_AT_DEPTH_IMPL( n, data )                       \
  template<>                                                                   \
  struct drop_trees_at_depth_impl< /*Depth =*/ 1, /*NumGroups =*/ n >          \
  {                                                                            \
    template                                                                   \
    < template< std::size_t, class... > class Result                           \
      ARGOT_DETAIL_EXPAND_N_TIMES                                              \
      ( ARGOT_DETAIL_TRAILING_PREPROCESSED_PARAMS, n, ~ )                      \
    , class... P                                                               \
    >                                                                          \
    using apply = Result< 1, P... >;                                           \
  };

ARGOT_DETAIL_EXPAND_MAX_UNROLL_DEPTH( ARGOT_DETAIL_DROP_TREES_AT_DEPTH_IMPL, ~ )

#define ARGOT_DETAIL_PREPROCESSED_TREE_DEPTH_END() 2

#undef ARGOT_DETAIL_DROP_TREES_AT_DEPTH_IMPL

struct drop_trees_at_depth_impl_identity
{
  template< std::size_t Depth, std::size_t /*NumGroups=0*/
          , template< std::size_t, class... > class Result, class... P
          >
  using apply = Result< Depth, P... >;
};

struct drop_trees_at_depth_impl_direct
{
  template< std::size_t Depth, std::size_t NumGroups
          , template< std::size_t, class... > class Result, class... P
          >
  using apply
    = sized_expand_into
      < drop_trees_at_depth_impl< Depth, NumGroups >::template apply
      , Result, P...
      >;
};

struct stop_recursing
{
 template< std::size_t Depth, std::size_t /*AmountOfTimesToApply = 0*/
         , template< std::size_t, class... > class Result, class... P
         >
  using recursion_impl = Result< Depth, P... >;
};

struct drop_trees_at_depth_impl_recursive
{
  template< std::size_t Depth, std::size_t AmountOfTimesToApply
          , template< std::size_t, class... > class Result
            ARGOT_DETAIL_EXPAND_N_TIMES
            ( ARGOT_DETAIL_TRAILING_PREPROCESSED_PARAMS
            , ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH()
            , ~
            )
          , class... P
          >
  using recursion_impl
    = typename detail_if_::if_< ( AmountOfTimesToApply != 1 ) >::then_else
      ::template _< drop_trees_at_depth_impl_recursive, stop_recursing >
      ::template recursion_impl
      < Depth, AmountOfTimesToApply - 1, Result, P... >;

  template< std::size_t Depth, std::size_t NumGroups
          , template< std::size_t, class... > class Result
          , class... P
          >
  using apply
    = recursive_sized_expand
      < recursion_impl, Depth
      ,   amount_at_depth( Depth - ARGOT_DETAIL_PREPROCESSED_TREE_DEPTH_END() )
        * NumGroups
      , Result, P...
      >;
};

struct drop_trees_at_depth_impl_nonzero
{
  template< std::size_t Depth, std::size_t NumGroups
          , template< std::size_t, class... > class Result, class... P
          >
  using apply
    = typename detail_if_::if_
      < ( Depth < ARGOT_DETAIL_PREPROCESSED_TREE_DEPTH_END() ) >::then_else
      ::template _
      < drop_trees_at_depth_impl_direct, drop_trees_at_depth_impl_recursive >
      ::template apply< Depth, NumGroups, Result, P... >;
};

template< std::size_t Depth, std::size_t NumGroups
        , template< std::size_t, class... > class Result, class... P
        >
using drop_tress_at_depth
  = typename detail_if_::if_< NumGroups == 0 >::then_else::template _
    < drop_trees_at_depth_impl_identity, drop_trees_at_depth_impl_nonzero >
    ::template apply< Depth, NumGroups, Result, P... >;

constexpr std::size_t num_groups_from_depth_and_amount
( std::size_t const depth, std::size_t const amount ) noexcept
{
  std::size_t const amount_per_group = amount_per_group_at_depth( depth );
  return clamp_to_unroll_depth(   ( amount + ( amount_per_group - 1 ) )
                                / amount_per_group
                              );
}

// TODO(mattcalabrese)
//   Eliminate this top-level class (use fully parameterized aliases)
template< template< class... > class Template >
struct form_tree_impl
{
  template< std::size_t NumGroups >
  struct of_n_groups;

  template< std::size_t Depth, std::size_t NumParams >
  using of_depth_and_num_params
    = of_n_groups< num_groups_from_depth_and_amount( Depth, NumParams ) >;

  struct terminal_node
  {
    template< std::size_t /*Depth = 1*/, class... P >
    using apply = take_preprocessed_amount_into< Template, P... >;
  };

  struct intermediate_node
  {
    template< std::size_t Depth, class... P >
    using apply
      = typename detail_if_::if_< Depth == 1 >::then_else_apply_values
        ::template _
        < terminal_node
        , of_depth_and_num_params
        , Depth, sizeof...( P )
        >
        ::template apply< Depth, P... >;
  };

  template< std::size_t Depth, class... P >
  using of_depth
    = typename detail_if_::if_< Depth == 1 >
      ::then_else::template _< terminal_node, intermediate_node >
      ::template apply< Depth, P... >;

#define ARGOT_DETAIL_FORM_TREE_OF_N_GROUPS_SPEC_IMPL( n, data )                \
  , drop_tress_at_depth< Depth - 1, n + 1, of_depth, P... >

#define ARGOT_DETAIL_FORM_TREE_OF_N_GROUPS_SPEC( n, data )                     \
  template<>                                                                   \
  struct of_n_groups< /*NumGroups =*/ n + 1 >                                  \
  {                                                                            \
    template< std::size_t Depth, class... P >                                  \
    using apply                                                                \
      = Template                                                               \
        < of_depth< Depth - 1, P... >                                          \
          ARGOT_DETAIL_EXPAND_N_TIMES                                          \
          ( ARGOT_DETAIL_FORM_TREE_OF_N_GROUPS_SPEC_IMPL, n, ~ )               \
        >;                                                                     \
  };

  ARGOT_DETAIL_EXPAND_MAX_UNROLL_DEPTH
  ( ARGOT_DETAIL_FORM_TREE_OF_N_GROUPS_SPEC, ~ )

#undef ARGOT_DETAIL_FORM_TREE_OF_N_GROUPS_SPEC
#undef ARGOT_DETAIL_FORM_TREE_OF_N_GROUPS_SPEC_IMPL

};

template< template< class... > class Template, class... P >
using form_tree
  = typename form_tree_impl< Template >
    ::template of_depth< tree_depth_from_amount( sizeof...( P ) ), P... >;

} // namespace (argot::detail_argot) 

#endif  // ARGOT_DETAIL_PREPROCESS_HPP_
