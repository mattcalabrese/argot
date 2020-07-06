/*==============================================================================
  Copyright (c) 2019, 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_EXPAND_HPP_
#define ARGOT_DETAIL_EXPAND_HPP_

#include <argot/detail/conditional.hpp>

#include <cstddef>

namespace argot::detail_argot {

template< template< class... > class Template, class... P >
using expand
  = typename argot_detail::conditional
    < ( sizeof...( P ) != ~static_cast<std::size_t>( 0 ) ) >
    ::template half_meta_apply< Template, void, P... >;


template< template< template< class... > class, class... > class Template
        , template< class... > class Result, class... P >
using expand_into
  = typename argot_detail::conditional
    < ( sizeof...( P ) != ~static_cast<std::size_t>( 0 ) ) >
    ::template continue_< Template, Result, P... >;

template< template< std::size_t, template< class... > class, class... >
          class Template
        , std::size_t I, template< class... > class Result, class... P >
using expand_into_with_index
  = typename argot_detail::conditional
    < ( sizeof...( P ) != ~static_cast<std::size_t>( 0 ) ) >
    ::template continue_with_index< Template, I, Result, P... >;

template< template< template< std::size_t, class... > class, class... >
          class Template
        , template< std::size_t, class... > class Result
        , class... P
        >
using sized_expand_into
  = typename argot_detail::conditional
    < ( sizeof...( P ) != ~static_cast<std::size_t>( 0 ) ) >
    ::template sized_continue< Template, Result, P... >;

  template< template< std::size_t, std::size_t
                    , template< std::size_t, class... > class
                    , class...
                    >
            class Template
          , std::size_t D, std::size_t N
          , template< std::size_t, class... > class Result
          , class... P
          >
using recursive_sized_expand
  = typename argot_detail::conditional
    < ( sizeof...( P ) != ~static_cast<std::size_t>( 0 ) ) >
    ::template recursive_sized_continue< Template, D, N, Result, P... >;

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_EXPAND_HPP_
