/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONVERT_FUTURE_HPP_
#define ARGOT_CONVERT_FUTURE_HPP_

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace detail_convert_future {

template< class FutParam >
using persistent_future_concept_impl
  = PersistentFuture
    < std::remove_const_t< std::remove_reference_t< FutParam > > >;

template< class FutParam >
using persistent_future_concept
  = argot_detail::conditional< std::is_lvalue_reference_v< Fut > >
    ::template half_meta_apply
    < persistent_future_concept_impl, Future< Fut >
    , Fut
    >;

}  // namespace argot(::detail_convert_future)

template< class FPackager >
struct convert_future_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

  template
  < class Fut, class Fun
  , ARGOT_REQUIRES
    ( detail_convert_future::persistent_future_concept< Fut > )
    ( DecaySinkable< Fun&& > )
    ( InvocableWith
      < std::decay_t< Fun&& >, value_type_t< remove_cvref_t< Fut > >&& >
    )
    ( InvocableWith
      < std::decay_t< Fun&& >, value_type_t< remove_cvref_t< Fut > > const& >
    )
    ()
  >
  constexpr void operator ()( Fut&& self, Exec&& exec, Fun&& fun ) const
  {
    using fut_concept = detail_convert_future::persistent_future_concept< Fut >;

    return fut_traits::then< FPackager >
    ( ARGOT_FORWARD( Fut )( self )
    , executor::immediate
    , []( auto&& value ) -> fut_traits::value_type_t< remove_cvref_t< Fut > >
      {
        return ARGOT_FORWARD( decltype( value ) )( value );
      }
    );
  }
} inline constexpr convert_future{};

} // namespace argot

#endif  // ARGOT_CONVERT_FUTURE_HPP_
