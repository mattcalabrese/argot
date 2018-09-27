/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_FOR_HPP_
#define ARGOT_PROV_FOR_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_type.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/transparent_requirement.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/nothing.hpp>

#include <type_traits>
#include <utility>

namespace argot::prov {
namespace for_detail {

template< class State, class Condition, class Step, class ProviderGenerator >
struct loop_requirements;

template< class Condition, class State >
struct invocation_returns_bool_constant
{
  using result_type = std::invoke_result_t< Condition&&, State&& >;

  template< template< class... > class Req >
  using expand_requirements
    = Req
      < Or  // TODO(mattcalabrese) Eliminate Or requirement (pattern match)
        < SameType< result_type, std::true_type >
        , SameType< result_type, std::false_type >
        >
      >;
};

template< class ProviderGenerator, class State >
struct invocation_returns_sinkable_argument_provider
{
  using result_type = std::invoke_result_t< ProviderGenerator&&, State& >;

  template< template< class... > class Req >
  using expand_requirements
    = Req< ArgumentProvider< detail_argot::remove_cvref_t< result_type > >
         , Sinkable< result_type&& >
         >;
};

template< class State, class Condition, class Step, class ProviderGenerator >
struct next_iteration_requirements
  : loop_requirements
    < std::invoke_result_t< Step&, State&& >&&, Condition, Step
    , ProviderGenerator
    > {};

template< class Step, class State >
struct invocation_returns_argument_type
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< ArgumentType< std::invoke_result_t< Step&, State&& > > >;
};

template< class State, class Condition, class Step, class ProviderGenerator >
struct iteration_requirements_if_condition_is_true
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < InvocableWith< ProviderGenerator&&, State& >
      , TransparentRequirement
        < invocation_returns_sinkable_argument_provider
          < ProviderGenerator, State >
        >
      , InvocableWith< Step&, State&& >
      , TransparentRequirement< invocation_returns_argument_type< Step&, State&& > >
      , TransparentRequirement
        < next_iteration_requirements
          < State, Condition, Step, ProviderGenerator >
        >
      >;
};

template< class State, class Condition, class Step, class ProviderGenerator >
struct iteration_requirements_if_condition_is_false
{
  template< template< class... > class Req >
  using expand_requirements = Req<>;
};

template< class State, class Condition, class Step, class ProviderGenerator >
struct iteration_requirements
  : argot_detail::conditional
    < std::is_same_v
      < std::invoke_result_t< Condition&&, State& >, std::true_type >
    >::template apply
       < iteration_requirements_if_condition_is_true
         < State, Condition, Step, ProviderGenerator >
       , iteration_requirements_if_condition_is_false
         < State, Condition, Step, ProviderGenerator >
       > {};

template< class State, class Condition, class Step, class ProviderGenerator >
struct loop_requirements
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < InvocableWith< Condition&&, State& >
      , TransparentRequirement
        < invocation_returns_bool_constant< Condition&&, State& > >
      , TransparentRequirement
        < iteration_requirements< State, Condition, Step, ProviderGenerator > >
      >;
};

} // namespace argot::prov(::for_detail)

struct for_fn
{
  // TODO(mattcalabrese) Properly constrain (tough)
  template
  < class State, class Condition, class Step, class ProviderGenerator
  , ARGOT_REQUIRES
    ( TransparentRequirement
      < for_detail::loop_requirements
        < State, Condition, Step, ProviderGenerator >
      >
    )()
  >
  [[nodiscard]]
  constexpr auto operator ()( State&& state, Condition&& condition, Step&& step
                            , ProviderGenerator&& provider_generator
                            ) const
  {
    if constexpr( !std::invoke_result_t< Condition&&, State&& >::value )
      return nothing;
    else
    {
      // TODO(mattcalabrese) Constexpr invoke
      auto local_arguments = provider_generator( state );

      // TODO(mattcalabrese) Either avoid group of group here or handle in group
      return group
      ( std::move( local_arguments )
      , ( *this )
        ( step( std::forward< State >( state ) )
        , std::forward< Condition >( condition )
        , std::forward< Step >( step )
        , std::forward< ProviderGenerator >( provider_generator )
        )
      );
    }
  }
} inline constexpr for_{};

template< class State, class Condition, class Step, class ProviderGenerator >
using result_of_for
  = basic_result_of< for_fn const&, State, Condition, Step, ProviderGenerator >;

template< class State, class Condition, class Step, class ProviderGenerator >
using result_of_for_t
  = basic_result_of_t
    < for_fn const&, State, Condition, Step, ProviderGenerator >;

} // namespace (argot::prov)

#endif  // ARGOT_PROV_FOR_HPP_
