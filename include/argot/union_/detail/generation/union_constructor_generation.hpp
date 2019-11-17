#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

#define ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX                              \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE                               \
BOOST_PP_CAT( T, ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX )

#define ARGOT_DETAIL_UNION_CURR_ALTERNATIVE                                    \
BOOST_PP_CAT( member, ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX )

template< class... P >
explicit constexpr union_base
( std::in_place_index_t< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX >
    const /*in_place_index*/
, P&&... args
) noexcept
  ( ARGOT_IS_MODELED
    ( NothrowEmplaceableWhenContained
      < ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE, P&&... >
    )
  )
  : ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
    ( ARGOT_FORWARD( P )( args )... ) {}

template< class Fun, class... P >
explicit constexpr union_base
( in_place_index_with_result_t< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX >
    const /*in_place_index_with_result*/
, Fun&& fun, P&&... args
) noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  : ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
    ( argot::void_to_regular_void_invoke
      ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... )
    ) {}

#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE
#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX
