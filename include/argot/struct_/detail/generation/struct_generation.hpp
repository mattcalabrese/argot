#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2019, 2020 Matt Calabrese

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
#include <argot/struct_/detail/generation/struct_in_place_constructor_generation_intermediate.hpp>
#include <argot/struct_/detail/generation/struct_in_place_with_result_constructor_generation.hpp>
#include <argot/struct_/detail/generation/struct_in_place_with_result_constructor_generation_intermediate.hpp>
#include <argot/struct_/detail/generation/struct_less_than_generation.hpp>
#include <argot/struct_/detail/generation/struct_member_generation.hpp>
#include <argot/struct_/detail/generation/struct_member_typedef_generation.hpp>
#include <argot/struct_/detail/generation/struct_swap_generation.hpp>
#include <argot/struct_/detail/generation/struct_unpack_generation.hpp>
#endif

#define ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS                                   \
BOOST_PP_ITERATION()

#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0

#define ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX                                    \
BOOST_PP_DEC( BOOST_PP_ITERATION() )

template<>
struct member< ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX >
{
  template< class Tup >
  using apply
    = typename Tup
     ::BOOST_PP_CAT( member_type, ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX );

  template< class Tup >
  static constexpr auto pointer_v
    = &Tup::BOOST_PP_CAT( member, ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX );                       \
};

#undef ARGOT_DETAIL_STRUCT_CURR_IMPL_INDEX
#endif

template<>
struct impl_of_size< ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS >
{
  template< class NextDepth, class... T >
  using num_leaves_impl_depth_n
    = std::integral_constant
      < std::size_t
      , (   0
          + ...
          + T::template num_leaves< NextDepth::value >::value
        )
      >;

#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS == 0
  template< class = void >
#else
  template
  < BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, class T ) >
#endif
  struct impl
  {
    static constexpr std::size_t num_members_v
      = ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS;

    template< std::size_t Depth >
    using num_leaves
      = typename detail_if_::if_< Depth == 1 >::then_else_apply
        ::template _
        < std::integral_constant
          < std::size_t, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS >
        , num_leaves_impl_depth_n
        , std::integral_constant< std::size_t, Depth - 1 >
          BOOST_PP_ENUM_TRAILING_PARAMS
          ( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, T )
        >;

    impl() = default;

#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_member_typedef_generation.hpp>  \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif

  // TODO(mattcalabrese) A way to pass the same arguments to each function

  // TODO(mattcalabrese) Conditional noexcept
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
    template
    < BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, class Fun ) >
#endif
    explicit constexpr impl
    ( in_place_index_with_result_t< 0 > /*next_depth*/
      BOOST_PP_ENUM_TRAILING_BINARY_PARAMS
      ( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, Fun, && fun )
    )
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
      :
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_in_place_with_result_constructor_generation.hpp>     \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
    {}

// TODO(mattcalabrese) Conditional noexcept
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
    template
    < BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, class P ) >
#endif
    explicit constexpr impl
    ( std::in_place_index_t< 0 > /*next_depth*/
      BOOST_PP_ENUM_TRAILING_BINARY_PARAMS
      ( ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS, P, && arg )
    )
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
      :
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_in_place_constructor_generation.hpp>     \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
    {}

    // TODO(mattcalabrese) Conditional noexcept
    template< std::size_t NextDepth, class... Funs >
    explicit constexpr impl
    ( in_place_index_with_result_t< NextDepth > /*next_depth*/
    , Funs&&... funs
    )
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
      :
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_in_place_with_result_constructor_generation_intermediate.hpp> \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
    {}

    // TODO(mattcalabrese) Conditional noexcept
    template< std::size_t NextDepth, class... P >
    explicit constexpr impl
    ( std::in_place_index_t< NextDepth > /*next_depth*/
    , P&&... args
    )
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
      :
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_in_place_constructor_generation_intermediate.hpp> \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
    {}

#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_member_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif

    // TODO(mattcalabrese) Checker for unpack constraints in tuple traits

    template< class Inv, class Self >
    static constexpr decltype( auto )
    unpack_this_level( Inv&& inv, Self&& self )
    {
      return argot_detail::constexpr_invoke
      ( ARGOT_FORWARD( Inv )( inv )
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_unpack_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
      );
    }

    // TODO(mattcalabrese) noexcept
    friend
    constexpr bool operator ==( impl const& lhs, impl const& rhs )
    {
      return true
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_equal_to_generation.hpp>        \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
      ;
    }

    // TODO(mattcalabrese) noexcept
    friend
    constexpr bool operator <( impl const& lhs, impl const& rhs )
    {
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_less_than_generation.hpp>          \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
      return false;
    }

    // TODO(mattcalabrese) noexcept
    constexpr void swap( impl& other )
    {
#if ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS != 0
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS - 1                             \
     , <argot/struct_/detail/generation/struct_swap_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
#endif
    }
  };
};

#undef ARGOT_DETAIL_STRUCT_CURR_NUM_MEMBERS
