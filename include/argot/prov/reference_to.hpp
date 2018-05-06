/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_REFERENCE_TO_HPP_
#define ARGOT_PROV_REFERENCE_TO_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/detail/argument_pack.hpp>
#include <argot/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/detail/provide_receiver.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace prov {

struct reference_to_fn
{
 public:  // TODO(mattcalabrese) Change to private
  // TODO(mattcalabrese) Require reference type here.
  template< class... P >
  struct impl
  {
    using elements_type = call_detail::argument_pack_t< P&&... >;
    ARGOT_NO_UNIQUE_ADDRESS elements_type elements;
  };
 public:
  // TODO(mattcalabrese) Make this a single overload that uses if constexpr.
  constexpr nothing_t operator ()() const noexcept
  {
    return {};
  }

  template< class Head, class... Tail >
  [[nodiscard]]
  constexpr impl< Head, Tail... >
  operator ()( Head&& head, Tail&&... tail ) const noexcept
  {
    return
    { call_detail::argument_pack_as_references
      ( ARGOT_FORWARD( Head )( head ), ARGOT_FORWARD( Tail )( tail )... )
    };
  }
} inline constexpr reference_to{};

template< class... P >
using result_of_reference_to
  = basic_result_of< reference_to_fn const&, P... >;

template< class... P >
using result_of_reference_to_t
  = basic_result_of_t< reference_to_fn const&, P... >;

}  // namespace argot(::prov)

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

}  // namespace argot

#endif  // ARGOT_PROV_REFERENCE_TO_HPP_
