/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_VALUE_OF_HPP_
#define ARGOT_PROV_VALUE_OF_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/instantiation_of.hpp>
#include <argot/contained.hpp>
#include <argot/detail/argument_pack.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/detail/provide_receiver.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <boost/config.hpp>

namespace argot {
namespace prov {

struct value_of_fn
{
 public:
  template< class... P >
  struct impl
  {
    using elements_type = call_detail::argument_pack_t< P const... >;
    ARGOT_NO_UNIQUE_ADDRESS elements_type elements;
  };

// GCC has a bug that prevents us from specializing our variable template.
#if defined( BOOST_GCC )

  template< class T >
  static bool constexpr is_unary_value_of_v
    = ARGOT_IS_MODELED( InstantiationOf< impl, T > );

#else // Otherwise, no workaround is necessary.

  template< class T >
  static bool constexpr is_unary_value_of_v = false;

  template< class P >
  static bool constexpr is_unary_value_of_v< impl< P > > = true;

#endif // defined( BOOST_GCC )

  template< class H, class... T >
  static constexpr H const& head_value( impl< H, T... > const& v ) noexcept
  {
    return argot::access_contained( v.elements.head );
  }

  template< class H, class... T >
  static constexpr H&& head_value( impl< H, T... >&& v ) noexcept
  {
    return argot::access_contained( ARGOT_MOVE( v.elements.head ) );
  }
 public:
  // TODO(mattcalabrese) Do this without multiple overloads
  constexpr nothing_t operator ()() const noexcept { return {}; }

  // TODO(mattcalabrese) Constrain
  template< class Head, class... Tail >
  [[nodiscard]]
  constexpr impl< detail_argot::remove_cvref_t< Head >, detail_argot::remove_cvref_t< Tail >... >
  operator ()( Head&& head, Tail&&... tail ) const
  {
    return
    { call_detail::argument_pack_as_values
      ( call_detail::forward_and_sink< Head >( head )
      , call_detail::forward_and_sink< Tail >( tail )...
      )
    };
  }
} inline constexpr value_of{};

template< class... P >
using result_of_value_of = basic_result_of< value_of_fn const&, P... >;

template< class... P >
using result_of_value_of_t = basic_result_of_t< value_of_fn const&, P... >;

}  // namespace argot(::prov)

template< class... P >
struct make_concept_map< ArgumentProvider< prov::value_of_fn::impl< P... > > >
{
  // TODO(mattcalabrese) Constrain
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver, receiver_traits::argument_types_t< P&&... > >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::value_of_fn::impl< P... >&& self, Receiver&& rec )
  {
    return prov::value_of_fn::impl< P... >::elements_type::make_invoker
    ( ARGOT_MOVE( self.elements ) )()
    ( typename prov::prov_detail::provide_receiver< Receiver >
      { ARGOT_MOVE( rec ) }
    );
  }
};

template< class... P >
struct make_concept_map
< PersistentArgumentProvider< prov::value_of_fn::impl< P... > > >
{
  // TODO(mattcalabrese) Constrain
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver, receiver_traits::argument_types_t< P const&... > >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::value_of_fn::impl< P... > const& self, Receiver&& rec )
  {
    return prov::value_of_fn::impl< P... >::elements_type::make_invoker
    ( self.elements )()
    ( typename prov::prov_detail::provide_receiver< Receiver >
      { ARGOT_MOVE( rec ) }
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_VALUE_OF_HPP_
