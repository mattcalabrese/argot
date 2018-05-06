/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_DEFAULT_TO_REFERENCE_TO_HPP_
#define ARGOT_PROV_DEFAULT_TO_REFERENCE_TO_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/true.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/reference_to.hpp>

namespace argot::prov {

struct default_to_reference_to_fn
{
 private:
  struct provider_forwarder
  {
    template< class T >
    static constexpr decltype( auto ) run( T&& arg ) noexcept
    {
      return call_detail::forward_and_sink< T >( arg );
    }
  };

  struct provider_maker
  {
    template< class T >
    static constexpr auto run( T&& arg ) noexcept
    {
      return prov::reference_to( ARGOT_FORWARD( T )( arg ) );
    }
  };
 public:
  template
  < class... P
  , ARGOT_REQUIRES
    ( typename argot_detail::conditional
      < is_modeled_v< ArgumentProvider< remove_cvref_t< P > > > >
      ::template half_meta_apply< Sinkable, True< true >, P&& >...
    )
    ()
  >
  [[nodiscard]] constexpr auto operator ()( P&&... args ) const
  {
    return prov::group
    ( argot_detail::conditional
      < is_modeled_v< ArgumentProvider< remove_cvref_t< P > > > >
      ::template apply< provider_forwarder, provider_maker >
      ::run( ARGOT_FORWARD( P )( args ) )...
    );
  }
} inline constexpr default_to_reference_to{};

template< class... P >
using result_of_default_to_reference_to
  = basic_result_of< default_to_reference_to_fn const&, P... >;

template< class... P >
using result_of_default_to_reference_to_t
  = basic_result_of_t< default_to_reference_to_fn const&, P... >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_DEFAULT_TO_REFERENCE_TO_HPP_
