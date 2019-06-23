/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_AS_DETAIL_AS_IMPL_HPP_
#define ARGOT_PROV_AS_DETAIL_AS_IMPL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/convertible.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/detail/argument_pack.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov/detail/provide_receiver.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace prov::as_detail {

// TODO(mattcalabrese) Constrain
template< class Head, class... Tail >
struct as_impl
{
  ARGOT_CONCEPT_ASSERT( Or< Reference< Head >, Object< Head > > );
  ARGOT_CONCEPT_ASSERT( Or< Reference< Tail >, Object< Tail > >... );

  // TODO(mattcalabrese) Don't add const here.
  using elements_type
    = call_detail::argument_pack_t< Head const, Tail const... >;

  elements_type elements;
};

}  // namespace argot(::prov::as_detail)

template< class... P >
struct make_concept_map
< ArgumentProvider< prov::as_detail::as_impl< P... > > >
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
  provide( prov::as_detail::as_impl< P... >&& self, Receiver&& receiver )
  {
    return prov::as_detail::as_impl< P... >::elements_type::make_invoker
    ( ARGOT_MOVE( self.elements ) )()
    ( typename prov::prov_detail::provide_receiver< Receiver >
      { ARGOT_MOVE( receiver ) }
    );
  }
};

template< class... P >
struct make_concept_map
< PersistentArgumentProvider< prov::as_detail::as_impl< P... > > >
{
  // TODO(mattcalabrese) Constrain
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t< P const&... >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::as_detail::as_impl< P... > const& self, Receiver&& receiver )
  {
    return prov::as_detail::as_impl< P... >::elements_type::make_invoker
    ( self.elements )()
    ( typename prov::prov_detail::provide_receiver< Receiver >
      { ARGOT_MOVE( receiver ) }
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_AS_DETAIL_AS_IMPL_HPP_
