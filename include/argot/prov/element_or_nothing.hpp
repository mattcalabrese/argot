/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ELEMENT_OR_NOTHING_HPP_
#define ARGOT_PROV_ELEMENT_OR_NOTHING_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/declval.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/opt_traits/get.hpp>
#include <argot/opt_traits/has_value.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/remove_cvref.hpp>

#include <memory>
#include <type_traits>

namespace argot {
namespace prov {

struct element_or_nothing_fn
{
  template< class Opt >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( OptionalLike< remove_cvref_t< Opt > > );
    ARGOT_CONCEPT_ASSERT( Not< VolatileObject< remove_cvref_t< Opt > > > );
    ARGOT_CONCEPT_ASSERT( Reference< Opt > );

    std::remove_reference_t< Opt >* opt;
  };

  template< class Opt
          , ARGOT_REQUIRES( OptionalLike< remove_cvref_t< Opt > > )
                          ( Not< VolatileObject< remove_cvref_t< Opt > > > )
                          ()
          >
  [[nodiscard]] constexpr auto operator ()( Opt&& opt ) const
  {
    return impl< Opt&& >{ std::addressof( opt ) };
  }
} inline constexpr element_or_nothing{};

template< class Opt >
using result_of_element_or_nothing
  = basic_result_of< element_or_nothing_fn const&, Opt >;

template< class Opt >
using result_of_element_or_nothing_t
  = basic_result_of_t< element_or_nothing_fn const&, Opt >;

}  // namespace argot(::prov)

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

}  // namespace argot

#endif  // ARGOT_PROV_ELEMENT_OR_NOTHING_HPP_
