#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

// Make the includes appear directly so that rebuilds still take place when
// dependencies change.
#if 0
#include <argot/struct_/detail/generation/struct_constructor_generation.hpp>
#include <argot/struct_/detail/generation/struct_equal_to_generation.hpp>
#include <argot/struct_/detail/generation/struct_in_place_constructor_generation.hpp>
#include <argot/struct_/detail/generation/struct_in_place_with_result_constructor_generation.hpp>
#include <argot/struct_/detail/generation/struct_less_than_generation.hpp>
#include <argot/struct_/detail/generation/struct_member_generation.hpp>
#include <argot/struct_/detail/generation/struct_member_typedef_generation.hpp>
#include <argot/struct_/detail/generation/struct_swap_generation.hpp>
#include <argot/struct_/detail/generation/struct_unpack_generation.hpp>
#endif

#define ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS                                  \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX                                    \
BOOST_PP_DEC( BOOST_PP_ITERATION() )

template<>
struct struct_impl_preprocessed< ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX >
{
  // TODO(mattcalabres) Hoist ElementType out of the template
  template< class ElementType, class StructBase >
  static constexpr auto&& get( StructBase&& self ) noexcept
  {
    using qualified_elem
      = call_detail::give_qualifiers_to_t< StructBase&&, ElementType >;

    return static_cast< qualified_elem >
    ( self.BOOST_PP_CAT( member, ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX ) );
  }
};

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, class T ) >
struct struct_base
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, T ) >
{
  static constexpr std::size_t num_members_v
    = ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS;

  template< template< class... > class Result >
  using expand_members_t
    = Result< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, T ) >;

  struct_base() = default;
  ~struct_base() = default;

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_member_typedef_generation.hpp>  \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

// TODO(mattcalabrese) A way to pass the same arguments to each function
template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, class Fun ) >
explicit constexpr struct_base
( in_place_with_result_t
    const /*in_place_with_result*/
  BOOST_PP_ENUM_TRAILING_BINARY_PARAMS
  ( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, Fun, && fun )
) // TODO(mattcalabrese) Noexcept
  :
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_in_place_with_result_constructor_generation.hpp>     \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
{}

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, class P ) >
explicit constexpr struct_base
( std::in_place_t
    const /*in_place*/
  BOOST_PP_ENUM_TRAILING_BINARY_PARAMS
  ( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, P, && arg )
) // TODO(mattcalabrese) Noexcept
  :
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_in_place_constructor_generation.hpp>     \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
{}

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_member_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

  // TODO(mattcalabrese) Checker for unpack constraints in tuple traits

  // TODO(mattcalabrese) Move to the helper template
  template< class Inv, class Self >
  static constexpr decltype( auto ) unpack( Inv&& inv, Self&& self )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Inv )( inv )
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_unpack_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
    );
  }

  // TODO(mattcalabrese) noexcept
  friend
  constexpr bool operator ==( struct_base const& lhs, struct_base const& rhs )
  {
    return true
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_equal_to_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
    ;
  }

  // TODO(mattcalabrese) noexcept
  friend
  constexpr bool operator <( struct_base const& lhs, struct_base const& rhs )
  {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_less_than_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
    return false;
  }

  // TODO(mattcalabrese) noexcept
  constexpr void swap( struct_base& other )
  {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_swap_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
  }
};

#undef ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS
