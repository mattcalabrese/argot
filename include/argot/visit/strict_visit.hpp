/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VISIT_STRICT_VISIT_HPP_
#define ARGOT_VISIT_STRICT_VISIT_HPP_

#include <argot/concepts/argot_invocable.hpp>
#include <argot/concepts/argot_invocable_with_persistent_reduction.hpp>
#include <argot/concepts/argot_invocable_with_reduction.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/prov/alternative_of.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/same_type_or_fail.hpp>
#include <argot/remove_cvref.hpp>

namespace argot {

struct strict_visit_fn
{
  template< class Reducer >
  struct with_reducer
  {
    ARGOT_CONCEPT_ASSERT( ReturnValueReducer< Reducer > );

    template
    < class Fun, class... P
    , ARGOT_REQUIRES
      ( VariantLike< remove_cvref_t< P > > )
      ( ArgotInvocableWithReduction
        < Reducer, Fun&&, prov::result_of_alternative_of_t< P&& >... >
      )
      ()
    >
    constexpr decltype( auto ) operator()( Fun&& fun, P&&... args ) &&
    {
      return prov_traits::destructive_provide
      ( prov::group( prov::alternative_of( ARGOT_FORWARD( P )( args ) )... )
      , receiver::reduced_invoke
        ( ARGOT_MOVE( reducer )
        , argot_detail::invoker< Fun&& >{ { ARGOT_FORWARD( Fun )( fun ) } }
        )
      );
    }

    template
    < class Fun, class... P
    , ARGOT_REQUIRES
      ( VariantLike< remove_cvref_t< P > > )
      ( ArgotInvocableWithPersistentReduction
        < Reducer, Fun&&, prov::result_of_alternative_of_t< P&& >... >
      )
      ()
    >
    constexpr decltype( auto ) operator()( Fun&& fun, P&&... args ) const&
    {
      return prov_traits::destructive_provide
      ( prov::group( prov::alternative_of( ARGOT_FORWARD( P )( args ) )... )
      , receiver::reduced_invoke
        ( reducer
        , argot_detail::invoker< Fun&& >{ { ARGOT_FORWARD( Fun )( fun ) } }
        )
      );
    }

    Reducer reducer;
  };

  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( VariantLike< remove_cvref_t< P > >... )
    ( ArgotInvocable< Fun&&, prov::result_of_alternative_of_t< P&& >... >
    )
    ()
  >
  constexpr auto operator()( Fun&& fun, P&&... args ) const
  {
    return prov_traits::destructive_provide
    ( prov::group( prov::alternative_of( ARGOT_FORWARD( P )( args ) )... )
    , receiver::reduced_invoke
      ( reducer::same_type_or_fail
      , argot_detail::invoker< Fun&& >{ { ARGOT_FORWARD( Fun )( fun ) } }
      )
    );
  }

  template< class Reducer
          , ARGOT_REQUIRES( ReturnValueReducer< remove_cvref_t< Reducer > > )
                          ( Sinkable< Reducer&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator []( Reducer&& reducer ) const
  {
    return with_reducer< remove_cvref_t< Reducer > >
    { call_detail::forward_and_sink< Reducer >( reducer ) };
  }
} inline constexpr strict_visit{};

}  // namespace argot

#endif  // ARGOT_VISIT_VISIT_HPP_
