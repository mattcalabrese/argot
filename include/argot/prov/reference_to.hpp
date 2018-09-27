/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_REFERENCE_TO_HPP_
#define ARGOT_PROV_REFERENCE_TO_HPP_

//[description
/*`
prov::reference_to is a facility for binding arguments by reference into a
PersistentArgumentProvider. When provision is performed on the resultant
ArgumentProvider as an rvalue, all bound references undergo perfect-forwarding.
When provision is performed on the result ArgumentProvider as an lvalue, all
arguments are forwarded as lvalue reference, matching standard
reference-collapsing rules.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/detail/argument_pack.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/detail/provide_receiver.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct reference_to_fn
{
  //<-
  // TODO(mattcalabrese) Require reference type here.
  template< class... P >
  struct impl
  {
    using elements_type = call_detail::argument_pack_t< P&&... >;
    ARGOT_NO_UNIQUE_ADDRESS elements_type elements;
  };
 public: //->
  template< class... P >
  [[nodiscard]]
  constexpr auto operator ()( P&&... args ) const noexcept//=;
  //<-
  {
    if constexpr( sizeof...( P ) == 0 )
      return prov::nothing;
    else
      return impl< P&&... >
      { call_detail::argument_pack_as_references
        ( ARGOT_FORWARD( P )( args )... )
      };
  } //->
} inline constexpr reference_to{};

template< class... P >
using result_of_reference_to//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< reference_to_fn const&, P... >; //->

template< class... P >
using result_of_reference_to_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< reference_to_fn const&, P... >; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`P&&... args`]
  [Each of `P&&...` is a valid reference type.]
  [The references to be captured and provided]
 ]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [The references that were captured, appropriately-collapsed]
 ]
 [[Possible Argument Types of Destructive Provision]
  [[itemized_list [```( P&&... )```]]]
 ]
 [[Possible Argument Types of Persistent Provision]
  [[itemized_list [```( P&... )```]]]
 ]
]
*/

//]

namespace argot {

template< class... P >
struct make_concept_map
< ArgumentProvider< prov::reference_to_fn::impl< P... > > >
{
  // TODO(mattcalabrese) Constrain
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t< P&&... >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::reference_to_fn::impl< P... >&& self, Receiver&& receiver )
  {
    return prov::reference_to_fn::impl< P... >::elements_type::make_invoker
    ( ARGOT_MOVE( self.elements ) )()
    ( typename prov::prov_detail::provide_receiver< Receiver >
      { ARGOT_FORWARD( Receiver )( receiver ) }
    );
  }
};

template< class... P >
struct make_concept_map
< PersistentArgumentProvider< prov::reference_to_fn::impl< P... > > >
{
  // TODO(mattcalabrese) Constrain
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t< P&... >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::reference_to_fn::impl< P... > const& self, Receiver&& receiver )
  {
    return prov::reference_to_fn::impl< P... >::elements_type::make_invoker
    ( self.elements )()
    ( typename prov::prov_detail::provide_receiver< Receiver >
      { ARGOT_FORWARD( Receiver )( receiver ) }
    );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_REFERENCE_TO_HPP_
