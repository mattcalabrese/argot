/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ELEMENT_OR_NOTHING_HPP_
#define ARGOT_PROV_ELEMENT_OR_NOTHING_HPP_

//[description
/*`
prov::element_or_nothing is a function object that takes an OptionalLike and
returns a PersistentArgumentProvider that provides a reference to the contained
element if the OptionalLike is engaged, otherwise it provides an empty argument
list.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/opt_traits/get.hpp>
#include <argot/opt_traits/has_value.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <memory>
#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct element_or_nothing_fn
{
  //<-
  template< class Opt >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( OptionalLike< detail_argot::remove_cvref_t< Opt > > );
    ARGOT_CONCEPT_ASSERT
    ( Not< VolatileObject< detail_argot::remove_cvref_t< Opt > > > );
    ARGOT_CONCEPT_ASSERT( Reference< Opt > );

    std::remove_reference_t< Opt >* opt;
  };
  //->
  template< class Opt
          , ARGOT_REQUIRES
            ( OptionalLike< detail_argot::remove_cvref_t< Opt > > )
            ( Not< VolatileObject< detail_argot::remove_cvref_t< Opt > > > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Opt&& opt ) const//=;
  //<-
  {
    return impl< Opt&& >{ std::addressof( opt ) };
  } //->
} inline constexpr element_or_nothing{};

template< class Opt >
using result_of_element_or_nothing//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< element_or_nothing_fn const&, Opt >; //->

template< class Opt >
using result_of_element_or_nothing_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< element_or_nothing_fn const&, Opt >; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Opt&& opt`]
  [`Opt&&` is a reference to a possibly-const OptionalLike.]
  [The OptionalLike for which the element may be provided]
 ]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision][Reference to the element if the OptionalLike is engaged, otherwise an empty argument list]]
 [[Possible Argument Types of Destructive Provision]
  [[itemized_list [```( opt_traits::result_of_get_t< Opt&& > )```]
                  [```()```]
   ]
  ]
 ]
 [[Possible Argument Types of Persistent Provision]
  [[itemized_list [```( opt_traits::result_of_get_t< Opt& > )```]
                  [```()```]
   ]
  ]
 ]
]
*/

//]

namespace argot {

template< class Opt >
struct make_concept_map
< ArgumentProvider< prov::element_or_nothing_fn::impl< Opt > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t
        < opt_traits::result_of_get_t< Opt&& > >
      , receiver_traits::argument_types_t<>
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::element_or_nothing_fn::impl< Opt > self
         , Receiver&& receiver
         )
  {
    return   opt_traits::has_value( *self.opt )
           ? receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t<> >{}
             , opt_traits::get( ARGOT_FORWARD( Opt )( *self.opt ) )
             )
           : receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t
                 < opt_traits::result_of_get_t< Opt&& > >
               >{}
             , receiver_traits::argument_list_kinds()
             );
  }
};

template< class Opt >
struct make_concept_map
< PersistentArgumentProvider< prov::element_or_nothing_fn::impl< Opt > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t
        < opt_traits::result_of_get_t< Opt const& > >
      , receiver_traits::argument_types_t<>
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::element_or_nothing_fn::impl< Opt > self
         , Receiver&& receiver
         )
  {
    return   opt_traits::has_value( *self.opt )
           ? receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t<> >{}
             , opt_traits::get( *self.opt )
             )
           : receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t
                 < opt_traits::result_of_get_t< Opt const& > >
               >{}
             , receiver_traits::argument_list_kinds()
             );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_ELEMENT_OR_NOTHING_HPP_
