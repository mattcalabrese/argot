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
#include <argot/struct_/detail/generation/struct_in_place_constructor_generation.hpp>
#include <argot/struct_/detail/generation/struct_in_place_with_result_constructor_generation.hpp>
#include <argot/struct_/detail/generation/struct_member_generation.hpp>
#include <argot/struct_/detail/generation/struct_member_typedef_generation.hpp>
#include <argot/struct_/detail/generation/struct_unpack_generation.hpp>
#include <argot/struct_/detail/generation/struct_zipped_unpack_generation.hpp>
#endif

#define ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS                                  \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX                                    \
BOOST_PP_DEC( BOOST_PP_ITERATION() )

template<>
struct struct_impl_preprocessed< ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX >
{
  template< class... T >
  using member_type_t
    = typename struct_base< T... >
      ::BOOST_PP_CAT( member_type, ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX );

  template< class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    using qualified_alt
      = call_detail::give_qualifiers_to_t
        < Self&&
        , typename access_raw_concept_map
          < TupleLike< detail_argot::remove_cvref_t< Self > > >
          ::template element_type_t< ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX >
        >;

    return static_cast< qualified_alt >
    ( self.elements
      .BOOST_PP_CAT( member, ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX )
    );
  }
};

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, class T ) >
struct struct_base
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, T ) >
{
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

  template< class Inv, class... Selves >
  static constexpr decltype( auto )
  zipped_unpack( Inv&& inv, Selves&&... selves )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Inv )( inv )
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_zipped_unpack_generation.hpp>   \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
    );
  }
};

#undef ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS
