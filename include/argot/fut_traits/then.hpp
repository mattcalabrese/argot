/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUTURE_TRAITS_THEN_HPP_
#define ARGOT_FUTURE_TRAITS_THEN_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut_traits/destructive_then.hpp>
#include <argot/fut_traits/persistent_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::fut_traits {

template< class FPackager >
struct then_fn
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );

  // TODO(mattcalabrese)
  //   Possibly check if we can even sinklike_cast.
  template
  < class Fut, class Exec, class Fun
  , ARGOT_REQUIRES
    ( typename argot_detail::conditional
      < std::is_rvalue_reference_v
        < call_detail::result_of_sinklike_cast_t< Fut&& > >
      >::template meta_apply
      < Future, PersistentFuture
      , detail_argot::remove_cvref_t< Fut >
      >
    )
    ( Executor< detail_argot::remove_cvref_t< Exec > > )
    ( InvocableWith  // TODO(mattcalabrese) Fix constraint
      < std::decay_t< Fun&& >
      , value_type_t< std::remove_reference_t< Fut > >
      >
    )
    ( Sinkable< Exec&& > )
    ( DecaySinkable< Fun&& > )
    ()
  >
  constexpr decltype( auto )
  operator ()( Fut&& self, Exec&& exec, Fun&& fun ) const
  {
    // TODO(mattcalabrese) Remove
    // using RawFut = detail_argot::remove_cvref_t< Fut >;

    using QualifiedFut
      = call_detail::result_of_sinklike_cast_t< Fut&& >;

    // TODO(mattcalabrese) Perform the decay_sink as a cast to avoid moves
    if constexpr( std::is_rvalue_reference_v< QualifiedFut > )
      return fut_traits::destructive_then< FPackager >
      ( static_cast< QualifiedFut >( self )
      , call_detail::forward_and_sink< Exec >( exec )
      , call_detail::decay_sink( ARGOT_MOVE( fun ) )
      );
    else
      return fut_traits::persistent_then< FPackager >
      ( static_cast< QualifiedFut >( self )
      , call_detail::forward_and_sink< Exec >( exec )
      , call_detail::decay_sink( ARGOT_MOVE( fun ) )
      );
  }
};

template< class FPackager >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< then_fn< FPackager > > constexpr then{};

template< class FPackager, class Fut, class Exec, class Fun >
using result_of_then_t
  = basic_result_of_t< then_fn< FPackager > const&, Fut, Exec, Fun >;

template< class FPackager, class Fut, class Exec, class Fun >
using result_of_then
  = basic_result_of< then_fn< FPackager > const&, Fut, Exec, Fun >;

} // namespace argot::fut_traits

#endif  // ARGOT_FUTURE_TRAITS_THEN_HPP_
