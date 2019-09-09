/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_DROP_WHILE_HPP_
#define ARGOT_PROV_DROP_WHILE_HPP_

//[description
/*`
prov::drop_while is a facility for forwarding the tail of an argument list,
starting at the first argument for which the given predicate returns `false`.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/bind_call.hpp>
#include <argot/prov/drop.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/union_traits/natural_get.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct drop_while_fn
{
  //<-
  template< class Pred >
  struct impl
  {
    template< class... P >
    constexpr auto operator ()( P&&... args ) const
    {
      // TODO(mattcalabrese) Make a version that is optimized for returns that
      // are std::true_type or std::false_type.

      std::size_t index_of_mismatch = 0;

      // Calculates the index of the mismatch
      // TODO(mattcalabrese)
      //   Figure out better implementation or make sure it optimizes away adds.
      static_cast< void >
      ( (    (   argot_detail::constexpr_invoke
                 ( pred
                 , static_cast< std::remove_reference_t< P > const& >( args )
                 )
               ? ( static_cast< void >( ++index_of_mismatch ), true )
               : false
             )
          && ...
        )
      );

      return prov::drop
      ( index_of_mismatch
      , prov::reference_to( ARGOT_FORWARD( P )( args )... )
      );
    }

    ARGOT_NO_UNIQUE_ADDRESS Pred pred;
  };
  //->
  // TODO(mattcalabrese) Make sure predicate is invokable with each argument.
  template
  < class Pred, class... Providers
  , ARGOT_REQUIRES
    ( ArgumentProvider< detail_argot::remove_cvref_t< Providers >... > )
    ( DecaySinkable< Pred&& > )
    ( Sinkable< Providers&& >... )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Pred&& pred, Providers&&... provs ) const//=;
  //<-
  {
    return prov::bind_call
    ( impl< std::decay_t< Pred > >
      { call_detail::forward_and_decay_sink< Pred >( pred ) }
    , ARGOT_FORWARD( Providers )( provs )...
    );
  } //->
} inline constexpr drop_while{};

template< class Pred, class... Providers >
using result_of_drop_while_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< drop_while_fn const&, Pred, Providers... >; //->

} // namespace (argot::prov)

//]

#endif // ARGOT_PROV_DROP_WHILE_HPP_
