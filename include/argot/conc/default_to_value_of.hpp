/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_DEFAULT_TO_VALUE_OF_HPP_
#define ARGOT_CONC_DEFAULT_TO_VALUE_OF_HPP_

//[description
/*`
conc::default_to_value_of is a facility for binding arguments by value into an
ConcurrentArgumentProvider. For each argument that is /not/ a
ConcurrentArgumentProvider, that argument is passed during provision. For each
argument that /is/ a ConcurrentArgumentProvider, that ConcurrentArgumentProvider 
s expanded in-place in the argument list during provision.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/conc/group.hpp>
#include <argot/conc/value_of.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

struct default_to_value_of_fn
{
  //<-
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
      return conc::value_of( call_detail::forward_and_sink< T >( arg ) );
    }
  };
 public: //->
  template< class... P
          , ARGOT_REQUIRES
            ( Sinkable< P&& >... )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( P&&... args ) const//=;
  //<-
  {
    // TODO(mattcalabrese) Use if constepxr
    return conc::group
    ( argot_detail::conditional
      < ARGOT_IS_MODELED
        ( ConcurrentArgumentProvider< detail_argot::remove_cvref_t< P > > )
      >::template apply< provider_forwarder, provider_maker >
      ::run( call_detail::forward_and_sink< P >( args ) )...
    );
  } //->
} inline constexpr default_to_value_of{};

template< class... P >
using result_of_default_to_value_of_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< default_to_value_of_fn const&, P... >; //->

template< class... P >
using result_of_default_to_value_of//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< default_to_value_of_fn const&, P... >; //->

} // namespace (argot::conc)

//]

#endif  // ARGOT_CONC_DEFAULT_TO_VALUE_OF_HPP_
