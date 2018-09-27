/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_BLESS_HPP_
#define ARGOT_BLESS_HPP_

//[description
/*`
conc::bless is a facility that takes a Future whose /element type/ is an
ArgumentProvider and it returns a corresponding ConcurrentArgumentProvider that
provides what its /element type/ provides.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

struct bless_fn
{
  //<-
  template< class FutProv >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Future< FutProv > );
    ARGOT_CONCEPT_ASSERT
    ( ArgumentProvider< fut_traits::value_type_t< FutProv > > );

    ARGOT_NO_UNIQUE_ADDRESS FutProv fut_prov;
  };
  //->
  template
  < class FutProv
  , ARGOT_REQUIRES
    ( Future< detail_argot::remove_cvref_t< FutProv > > )
    ( ArgumentProvider
      < fut_traits::value_type_t< detail_argot::remove_cvref_t< FutProv > > >
    )
    ( Sinkable< FutProv&& > )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( FutProv&& fut_prov ) const//=;
  //<-
  {
    return impl< detail_argot::remove_cvref_t< FutProv > >
    { call_detail::forward_and_sink< FutProv >( fut_prov ) };
  } //->
} inline constexpr bless{};

template< class FutProv >
using result_of_bless_t//= = ``[see_prologue_result_of]``;
//<-
   = basic_result_of_t< bless_fn const&, FutProv >; //->

template< class FutProv >
using result_of_bless//= = ``[see_prologue_result_of]``;
//<-
   = basic_result_of< bless_fn const&, FutProv >; //->

} // namespace (argot::conc)

//]

namespace argot {

template< class FutProv >
struct make_concept_map
< ConcurrentArgumentProvider< conc::bless_fn::impl< FutProv > > >
{
  static constexpr FutProv&& as_future( conc::bless_fn::impl< FutProv >&& self )
  {
    return ARGOT_MOVE( self.fut_prov );
  }
};

} // namespace argot

#endif  // ARGOT_BLESS_HPP_
