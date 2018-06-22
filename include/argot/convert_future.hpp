/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONVERT_FUTURE_HPP_
#define ARGOT_CONVERT_FUTURE_HPP_

#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/thenable.hpp>
#include <argot/concepts/persistent_thenable.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/forward.hpp>
#include <argot/fut_traits/then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace detail_convert_future {

template< class FutParam, class FPackager >
using persistent_thenable_concept_impl
  = PersistentThenable
    < std::remove_const_t< FutParam >
    , FPackager
    , executor::immediate_t
    >;

template< class FutParam, class FPackager >
using thenable_concept
  = typename argot_detail::conditional< std::is_lvalue_reference_v< FutParam > >
    ::template meta_apply
    < persistent_thenable_concept_impl
    , Thenable
    , std::remove_reference_t< FutParam >, FPackager, executor::immediate_t
    >;

}  // namespace argot(::detail_convert_future)

template< class FPackager >
struct convert_future_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

  template
  < class Fut
  , ARGOT_REQUIRES
    ( detail_convert_future::thenable_concept< Fut, FPackager > )()
  >
  constexpr void operator ()( Fut&& self ) const
  {
    return fut_traits::then< FPackager >
    ( ARGOT_FORWARD( Fut )( self )
    , executor::immediate
    , []( auto&& value ) -> fut_traits::value_type_t< remove_cvref_t< Fut > >
      {
        return ARGOT_FORWARD( decltype( value ) )( value );
      }
    );
  }
};

template< class FPackager >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< convert_future_fn< FPackager > >
constexpr convert_future{};


} // namespace argot

#endif  // ARGOT_CONVERT_FUTURE_HPP_
