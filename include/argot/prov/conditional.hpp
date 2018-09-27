/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_CONDITIONAL_HPP_
#define ARGOT_PROV_CONDITIONAL_HPP_

//[description
/*`
prov::conditional is a function object that takes a `bool` or a
`std::bool_constant` instantiation, an ArgumentProvider `if_true` and an
ArgumentProvider `if_false`. The return value is an ArgumentProvider that
provides what `if_true` provides if the `bool` value is `true`, otherwise it
provides what `if_false` provides. The returned ArgumentProvider is a
PersistentArgumentProvider if each of `if_true` and `if_false` is a
PersistentArgumentProvider.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of_kinds.hpp>
#include <argot/concepts/bool_or_constant.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/concatenate.hpp>
#include <argot/detail/detection.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/receiver_traits/branch_to_provision.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct conditional_fn
{
  //<-
  template< class IfTrue, class IfFalse >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentProvider< IfTrue > );
    ARGOT_CONCEPT_ASSERT( ArgumentProvider< IfFalse > );

    ARGOT_NO_UNIQUE_ADDRESS IfTrue if_true;
    ARGOT_NO_UNIQUE_ADDRESS IfFalse if_false;
    bool value;
  };
  //->
  template< class Bool, class IfTrue, class IfFalse
          , ARGOT_REQUIRES
            ( BoolOrConstant< Bool > )
            ( ArgumentProvider< detail_argot::remove_cvref_t< IfTrue > > )
            ( ArgumentProvider< detail_argot::remove_cvref_t< IfFalse > > )
            ( Sinkable< IfTrue&& > )
            ( Sinkable< IfFalse&& > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Bool const condition
                            , IfTrue&& if_true, IfFalse&& if_false
                            ) const//=;
  //<-
  {
    if constexpr( std::is_same_v< Bool, bool > )
      return impl< detail_argot::remove_cvref_t< IfTrue >
                 , detail_argot::remove_cvref_t< IfFalse >
                 >
      { call_detail::forward_and_sink< IfTrue >( if_true )
      , call_detail::forward_and_sink< IfFalse >( if_false )
      , condition
      };
    else
      if constexpr( Bool::value )
        return call_detail::forward_and_sink< IfTrue >( if_true );
      else  // Otherwise, it's a false boolean constant.
        return call_detail::forward_and_sink< IfFalse >( if_false );

  } //->
} inline constexpr conditional{};

template< class Condition, class IfTrue, class IfFalse >
using result_of_conditional//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< conditional_fn const&, Condition, IfTrue, IfFalse >; //->

template< class Condition, class IfTrue, class IfFalse >
using result_of_conditional_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< conditional_fn const&, Condition, IfTrue, IfFalse >; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Bool const condition`]
  [A `bool` or a `std::bool_constant` instantiation]
  [The condition used to determine which one of `if_true` and `if_false` undergoes provision]
 ]
 [[`IfTrue&& if_true`]
  [A forwarding-reference to a possibly-cv-qualified ArgumentProvider that is Sinkable]
  [The ArgumentProvider to undergo provision if the value of `condition` is `true`]
 ]
 [[`IfFalse&& if_false`]
  [A forwarding-reference to a possibly-cv-qualified ArgumentProvider that is Sinkable]
  [The ArgumentProvider to undergo provision if the value of `condition` is `false`]
 ]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision][If the value of `condition` is `true`, provides what `if_true` provides, otherwise provides what `if_false` provides.]]
 [[Possible Argument Types of Provision]
  [TODO(mattcalabrese) Describe the possible argument list types]
 ]
]
*/

//]

namespace argot {

template< class IfTrue, class IfFalse >
struct make_concept_map
< ArgumentProvider< prov::conditional_fn::impl< IfTrue, IfFalse > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , call_detail::concatenate_t
        < prov_traits::argument_list_kinds_of_destructive_t< IfTrue >
        , prov_traits::argument_list_kinds_of_destructive_t< IfFalse >
        >
      >
    )()
  >
  static constexpr decltype( auto )
  provide( prov::conditional_fn::impl< IfTrue, IfFalse >&& self
         , Receiver&& receiver
         )
  {
    return   self.value
           ? receiver_traits::branch_to_provision
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , prov_traits::argument_list_kinds_of_destructive_t< IfFalse >{}
             , ARGOT_MOVE( self.if_true )
             )
           : receiver_traits::branch_to_provision
             ( ARGOT_MOVE( receiver )
             , prov_traits::argument_list_kinds_of_destructive_t< IfTrue >{}
             , receiver_traits::argument_list_kinds()
             , ARGOT_MOVE( self.if_false )
             );
  }
};

template< class IfTrue, class IfFalse >
struct make_concept_map
< PersistentArgumentProvider< prov::conditional_fn::impl< IfTrue, IfFalse > >
, ARGOT_REQUIRES( PersistentArgumentProvider< IfTrue > )
                ( PersistentArgumentProvider< IfFalse > )
                <>
>
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , call_detail::concatenate_t
        < prov_traits::argument_list_kinds_of_persistent_t< IfTrue >
        , prov_traits::argument_list_kinds_of_persistent_t< IfFalse >
        >
      >
    )()
  >
  static constexpr decltype( auto )
  provide( prov::conditional_fn::impl< IfTrue, IfFalse > const& self
         , Receiver&& receiver
         )
  {
    return   self.value
           ? receiver_traits::branch_to_provision
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , prov_traits::argument_list_kinds_of_persistent_t< IfFalse >{}
             , self.if_true
             )
           : receiver_traits::branch_to_provision
             ( ARGOT_MOVE( receiver )
             , prov_traits::argument_list_kinds_of_persistent_t< IfTrue >{}
             , receiver_traits::argument_list_kinds()
             , self.if_false
             );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_CONDITIONAL_HPP_
