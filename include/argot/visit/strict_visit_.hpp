/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VISIT_STRICT_VISIT_TO_HPP_
#define ARGOT_VISIT_STRICT_VISIT_TO_HPP_

#include <argot/concepts/argot_invocable_with_persistent_reduction.hpp>
#include <argot/concepts/return_type.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/alternative_of.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/to.hpp>
#include <argot/remove_cvref.hpp>

namespace argot {

template< class Ret >
struct strict_visit_to_fn
{
  ARGOT_CONCEPT_ASSERT( ReturnType< Ret > );

  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( VariantLike< remove_cvref_t< P > >... )
    ( ArgotInvocableWithPersistentReduction
      < reducer::to_t< Ret >
      , Fun&&, prov::result_of_alternative_of_t< P&& >...
      >
    )
    ()
  >
  constexpr auto operator()( Fun&& fun, P&&... args ) const
  {
    return prov_traits::destructive_provide
    ( prov::group( prov::alternative_of( ARGOT_FORWARD( P )( args ) )... )
    , receiver::reduced_invoke
      ( reducer::to< Ret >
      , argot_detail::invoker< Fun&& >{ { ARGOT_FORWARD( Fun )( fun ) } }
      )
    );
  }
};

template< class Ret >
ARGOT_REQUIRES( ReturnType< Ret > )
< strict_visit_to_fn< Ret > > constexpr strict_visit_{};

}  // namespace argot

#endif  // ARGOT_VISIT_STRICT_VISIT_TO_HPP_
