/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VISIT_VISIT_TO_HPP_
#define ARGOT_VISIT_VISIT_TO_HPP_

#include <argot/concepts/argot_invocable_with_persistent_reduction.hpp>
#include <argot/concepts/return_type.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/default_.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/alternative_of.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/throw.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/to.hpp>
#include <argot/remove_cvref.hpp>

#include <variant>

namespace argot {

template< class Ret >
struct visit_to_fn
{
  ARGOT_CONCEPT_ASSERT( ReturnType< Ret > );

  template
  < class Fun, class... P
  , ARGOT_REQUIRES
    ( VariantLike< remove_cvref_t< P > >... )
    ( ArgotInvocableWithPersistentReduction
      < reducer::to_t< Ret >, Fun&&
      , prov::result_of_alternative_of_t
        < P&&
        , result_of_default_t
          < prov::result_of_throw_t< std::bad_variant_access > >
        >...
      >
    )
    ()
  >
  constexpr auto operator()( Fun&& fun, P&&... args ) const
  {
    return prov_traits::destructive_provide
    ( prov::group
      ( prov::alternative_of
        ( ARGOT_FORWARD( P )( args )
        , argot::default_( prov::throw_< std::bad_variant_access >() )
        )...
      )
    , receiver::reduced_invoke
      ( reducer::to< Ret >
      , argot_detail::invoker< Fun&& >{ { ARGOT_FORWARD( Fun )( fun ) } }
      )
    );
  }
};

template< class Ret >
ARGOT_REQUIRES( ReturnType< Ret > )
< visit_to_fn< Ret > > constexpr visit_{};

}  // namespace argot

#endif  // ARGOT_VISIT_VISIT_TO_HPP_
