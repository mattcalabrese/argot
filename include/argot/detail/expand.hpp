/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

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
  = typename argot_detail::conditional< ( sizeof...( P ) < 3000000000 ) >
    ::template half_meta_apply< Template, void, P... >;


template< template< template< class... > class, class... > class Template
        , template< class... > class Result, class... P >
using expand_into
  = typename argot_detail::conditional< ( sizeof...( P ) < 3000000000 ) >
    ::template continue_< Template, Result, P... >;

template< template< std::size_t, template< class... > class, class... >
          class Template
        , std::size_t I, template< class... > class Result, class... P >
using expand_into_with_index
  = typename argot_detail::conditional< ( sizeof...( P ) < 3000000000 ) >
    ::template continue_with_index< Template, I, Result, P... >;

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_EXPAND_HPP_
