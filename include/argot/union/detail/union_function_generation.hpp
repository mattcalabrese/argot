#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif

#include <boost/preprocessor/cat.hpp>

#define ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX                              \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE                               \
BOOST_PP_CAT( T, ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX )

#define ARGOT_DETAIL_UNION_CURR_ALTERNATIVE                                    \
BOOST_PP_CAT( alternative, ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX )

  // TODO(mattcalabrese) handle refernce types and const.
template
< class... P
, ARGOT_REQUIRES
  ( Constructible< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE, P&&... > )()
>
explicit constexpr union_
( std::in_place_index_t< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX >
    const /*in_place_index*/
, P&&... args
)
noexcept
( std::is_nothrow_constructible_v
  < ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE, P&&... >
) : ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
    ( call_detail::make_holder< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE >
      ( ARGOT_FORWARD( P )( args ) )
    ) {}

// TODO(mattcalabrese) handle refernce types and const.
template
< class U, class... P
, ARGOT_REQUIRES
  ( Constructible< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE
                 , std::initializer_list< U >&, P&&...
                 >
  )()
>
explicit constexpr union_
( std::in_place_index_t< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX >
    const /*in_place_index*/
, std::initializer_list< U > ilist, P&&... args
)
noexcept
( std::is_nothrow_constructible_v
  < ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE
  , std::initializer_list< U >&, P&&...
  >
) : ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
    ( call_detail::make_holder< ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE >
      ( ilist, ARGOT_FORWARD( P )( args ) )
    ) {}

// TODO(mattcalabrese) Create emplacement and accessors.

#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE
#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_TYPE
#undef ARGOT_DETAIL_UNION_CURR_ALTERNATIVE_INDEX

#endif  // ARGOT_PREPROCESSING_MODE
