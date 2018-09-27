/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ELEMENT_OR_HPP_
#define ARGOT_PROV_ELEMENT_OR_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/gen/not.hpp>
#include <argot/detail/move.hpp>
#include <argot/opt_traits/get.hpp>
#include <argot/opt_traits/has_value.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <memory>

namespace argot {
namespace prov {

struct element_or_fn
{
  template< class Opt, class Otherwise >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( OptionalLike< detail_argot::remove_cvref_t< Opt > > );
    ARGOT_CONCEPT_ASSERT( Not< VolatileObject< detail_argot::remove_cvref_t< Opt > > > );
    ARGOT_CONCEPT_ASSERT( Reference< Opt > );
    ARGOT_CONCEPT_ASSERT( Reference< Otherwise > );

    std::remove_reference_t< Opt >* opt;
    std::remove_reference_t< Otherwise >* otherwise;
  };

  // TODO(mattcalabrese) Concept check
  template< class Opt, class Otherwise >
  [[nodiscard]]
  constexpr auto operator ()( Opt&& opt, Otherwise&& otherwise ) const
  {
    return impl< Opt&&, Otherwise&& >
    { std::addressof( opt ), std::addressof( otherwise ) };
  }
} inline constexpr element_or{};

template< class Opt, class Otherwise >
using result_of_element_or//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< element_or_fn const&, Opt, Otherwise >; //->

template< class Opt, class Otherwise >
using result_of_element_or_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< element_or_fn const&, Opt, Otherwise >; //->

} // namespace argot(::prov)

template< class Opt, class Otherwise >
struct make_concept_map
< ArgumentProvider< prov::element_or_fn::impl< Opt, Otherwise > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t
        < opt_traits::result_of_get_t< Opt&& > >
      , receiver_traits::argument_types_t< Otherwise&& >
      >
    )()
  >
  static constexpr decltype( auto )
  provide( prov::element_or_fn::impl< Opt, Otherwise > self
         , Receiver&& receiver
         )
  {
    return   opt_traits::has_value( *self.opt )
           ? receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t< Otherwise&& > >{}
             , opt_traits::get( ARGOT_FORWARD( Opt )( *self.opt ) )
             )
           : receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t
                 < opt_traits::result_of_get_t< Opt&& > >
               >{}
             , receiver_traits::argument_list_kinds()
             , ARGOT_FORWARD( Otherwise )( *self.otherwise )
             );
  }
};

template< class Opt, class Otherwise >
struct make_concept_map
< PersistentArgumentProvider< prov::element_or_fn::impl< Opt, Otherwise > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t
        < opt_traits::result_of_get_t< Opt const& > >
      , receiver_traits::argument_types_t< Otherwise const& >
      >
    )()
  >
  static constexpr decltype( auto )
  provide( prov::element_or_fn::impl< Opt, Otherwise > self
         , Receiver&& receiver
         )
  {
    return   opt_traits::has_value( *self.opt )
           ? receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t< Otherwise const& > >{}
             , opt_traits::get( *self.opt )
             )
           : receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t
                 < opt_traits::result_of_get_t< Opt const& > >
               >{}
             , receiver_traits::argument_list_kinds()
             , *self.otherwise
             );
  }
};

} // namespace argot

#endif  // ARGOT_PROV_ELEMENT_OR_HPP_
