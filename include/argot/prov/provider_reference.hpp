/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_PROVIDER_REFERENCE_HPP_
#define ARGOT_PROV_PROVIDER_REFERENCE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/contained.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot {
namespace prov {

struct provider_reference_fn
{
 public:
  template< class ProviderReference >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT
    ( ArgumentProvider< detail_argot::remove_cvref_t< ProviderReference > > );

    ARGOT_CONCEPT_ASSERT( Reference< ProviderReference > );

    contained< ProviderReference > provider;
  };
public:
  template< class Provider
          , ARGOT_REQUIRES( ArgumentProvider< detail_argot::remove_cvref_t< Provider > > )()
          >
  [[nodiscard]] constexpr auto operator ()( Provider&& provider ) const noexcept
  {
    return impl< Provider&& >
    { argot::make_contained< Provider&& >
      ( ARGOT_FORWARD( Provider )( provider ) )
    };
  }
} inline constexpr provider_reference{};

template< class Provider >
using result_of_provider_reference
  = basic_result_of< provider_reference_fn const&, Provider >;

template< class Provider >
using result_of_provider_reference_t
  = basic_result_of_t< provider_reference_fn const&, Provider >;

}  // namespace argot(::prov)

// TODO(mattcalabrese) Also do PersistentArgumentProvider (constrained)
template< class ProviderReference >
struct make_concept_map
< ArgumentProvider< prov::provider_reference_fn::impl< ProviderReference > > >
{
  // TODO(mattcalabrese) SFINAE
  template< class Self, class Receiver >
  static constexpr decltype( auto )
  provide( Self&& self, Receiver&& receiver )
  {
    return prov_traits::provide
    ( argot::access_contained( ARGOT_FORWARD( Self )( self ).provider )
    , ARGOT_MOVE( receiver )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_PROVIDER_REFERENCE_HPP_
