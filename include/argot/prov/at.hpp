/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_AT_HPP_
#define ARGOT_PROV_AT_HPP_

//[description
/*`
prov::at is a facility for forwarding exactly one argument of an argument list
after provision.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/convertible_to_type_or_constant.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/max_argument_list_length.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/variadic_range.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/bind_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/unreachable.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/prov_traits/argument_list_kinds_of.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <algorithm>
#include <cstddef>
#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct at_fn
{
  //<-
  struct impl
  {
    template< std::size_t I, class... P >
    constexpr auto
    operator()( std::integral_constant< std::size_t, I >, P&&... args ) const
    {
      // The argument to access must be a valid index for the number of
      // arguments, so if the amount is too large then this invocation yields a
      // prov::unreachable.
      // Note that these situations aren't always known at compile time when
      // dealing with a branching argument provider, since the index may be fine
      // for some branches and yet not for others.

      if constexpr( I < sizeof...( P ) )
        return detail_argot::variadic_sized_range_run< I, 1 >
        ( prov::reference_to
        , ARGOT_FORWARD( P )( args )...
        );
      else // Otherwise, the index is too large...
        return prov::unreachable;
    }
  };
  //->
  template
  < class SizeT, class... Providers
  , ARGOT_REQUIRES
    ( ConvertibleToTypeOrConstant< SizeT, std::size_t > )
    ( ArgumentProvider< detail_argot::remove_cvref_t< Providers >... > )
    ( Sinkable< Providers&& >... )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( SizeT&& i, Providers&&... provs ) const//=;
  //<-
  {
    return prov::bind_call
    ( impl()
    , prov::value_in_range
      < std::size_t
      , 0
      , (   detail_argot::max_argument_list_length_v
            < prov_traits::argument_list_kinds_of_t< Providers&& > >
          + ...
        )
      >( ARGOT_FORWARD( SizeT )( i ) )
    , ARGOT_FORWARD( Providers )( provs )...
    );
  } //->
} inline constexpr at{};

template< std::size_t ArgumentIndex >
struct at_v_fn
{
  //<-
  struct impl
  {
    template< class... P >
    constexpr auto operator()( P&&... args ) const
    {
      // The argument to access must be a valid index for the number of
      // arguments, so if the amount is too large then this invocation yields a
      // prov::unreachable.
      // Note that these situations aren't always known at compile time when
      // dealing with a branching argument provider, since the index may be fine
      // for some branches and yet not for others.

      if constexpr( ArgumentIndex < sizeof...( P ) )
        return detail_argot::variadic_sized_range_run< ArgumentIndex, 1 >
        ( prov::reference_to
        , ARGOT_FORWARD( P )( args )...
        );
      else // Otherwise, the index is too large...
        return prov::unreachable;
    }
  };
  //->
  template
  < class... Providers
  , ARGOT_REQUIRES
    ( ArgumentProvider< detail_argot::remove_cvref_t< Providers >... > )
    ( Sinkable< Providers&& >... )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Providers&&... provs ) const//=;
  //<-
  {
    return prov::bind_call( impl(), ARGOT_FORWARD( Providers )( provs )... );
  } //->
};

template< std::size_t ArgumentIndex >
inline constexpr at_v_fn< ArgumentIndex > at_{}; 

template< class SizeT, class... Providers >
using result_of_at_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< at_fn const&, SizeT, Providers... >; //->

} // namespace (argot::prov)

//]

#endif // ARGOT_PROV_AT_HPP_
