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
BOOST_PP_CAT( alternative, ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX )

template< class Fun, class... P >
explicit constexpr union_base
( in_place_index_with_result_t< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX >
    const /*in_place_index_with_result*/
, Fun&& fun, P&&... args
) noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
  : ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
    ( call_detail::emplace_holder_with_result
      < ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE >
      ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... )
    ) {}

// TODO(mattcalabrese) handle reference types and const.
// TODO(mattcalabrese) put this in a base constructor for better error messages
template< class... P >
explicit constexpr union_base
( std::in_place_index_t< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX >
    const /*in_place_index*/
, P&&... args
)
noexcept
( std::is_nothrow_constructible_v
  < ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE, P&&... >
) : ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
    ( call_detail::emplace_holder< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE >
      ( ARGOT_FORWARD( P )( args )... )
    ) {}

#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE
#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX
