/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_PROVIDER_REFERENCE_HPP_
#define ARGOT_PROV_PROVIDER_REFERENCE_HPP_

//[description
/*`
prov::provider_reference is a facility that contains an ArgumentProvider by
reference and whose provision is that of its target. It is analogous to what
`std::ref` is to a function object.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider_to.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/contained.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/prov_traits/provide.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct provider_reference_fn
{
  //<-
 public:
  template< class ProviderReference >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT
    ( ArgumentProvider< detail_argot::remove_cvref_t< ProviderReference > > );

    ARGOT_CONCEPT_ASSERT( Reference< ProviderReference > );

    contained< ProviderReference > provider;
  };
public: //->
  // TODO(mattcalabrese) Only remove reference and const.
  template< class Provider
          , ARGOT_REQUIRES
            ( ArgumentProvider< detail_argot::remove_cvref_t< Provider > > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Provider&& provider ) const noexcept//=;
  //<-
  {
    return impl< Provider&& >
    { argot::make_contained< Provider&& >
      ( ARGOT_FORWARD( Provider )( provider ) )
    };
  } //->
} inline constexpr provider_reference{};

template< class Provider >
using result_of_provider_reference//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< provider_reference_fn const&, Provider >; //->

template< class Provider >
using result_of_provider_reference_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< provider_reference_fn const&, Provider >; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Provider&& provider`]
  [A reference to a possibly-const-qualified ArgumentProvider]
  [The ArgumentProvider to contain a reference to]
 ]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [The provision of the ArgumentProvider it references]
 ]
 [[Possible Argument Types of Destructive Provision]
  [[itemized_list [[~The possible argument list kinds of a provision of
                     `provider` (persitent provision if `Provider&&` is a
                     reference to a `const`-qualified ArgumentProvider or if
                     `Provider&&` is an lvalue reference)]]]]
 ]
 [[Possible Argument Types of Persistent Provision]
  [[itemized_list [[~The possible argument list kinds of a persistent provision
                    of `provider`]]]]
 ]
]
*/
//]

namespace argot {

template< class ProviderReference >
struct make_concept_map
< ArgumentProvider< prov::provider_reference_fn::impl< ProviderReference > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov::provider_reference_fn::impl< ProviderReference > self
         , Receiver&& receiver
         )
  {
    return prov_traits::provide
    ( argot::access_contained( ARGOT_MOVE( self ).provider )
    , ARGOT_FORWARD( Receiver )( receiver )
    );
  }
};

template< class ProviderReference >
struct make_concept_map
< PersistentArgumentProvider
  < prov::provider_reference_fn::impl< ProviderReference > >
, ARGOT_REQUIRES
  ( PersistentArgumentProvider
    < detail_argot::remove_cvref_t< ProviderReference > >
  )
  <>
>
{
  template< class Receiver
          , ARGOT_REQUIRES
            ( PersistentArgumentProviderTo
              < detail_argot::remove_cvref_t< ProviderReference >
              , Receiver
              >
            )
            ()
          >
  static constexpr decltype( auto )
  provide( prov::provider_reference_fn::impl< ProviderReference > self
         , Receiver&& receiver
         )
  {
    return prov_traits::persistent_provide
    ( argot::access_contained( self.provider )
    , ARGOT_FORWARD( Receiver )( receiver )
    );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_PROVIDER_REFERENCE_HPP_
