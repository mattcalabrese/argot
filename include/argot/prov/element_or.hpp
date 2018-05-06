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
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/declval.hpp>
#include <argot/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/remove_cvref.hpp>

#include <memory>

namespace argot {
namespace prov {

struct element_or_fn
{
  template< class Opt, class Otherwise >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Reference< Opt > );
    ARGOT_CONCEPT_ASSERT( Reference< Otherwise > );

    // TODDO(mattcalabrese) Use holder?
    std::remove_reference_t< Opt >* opt;
    std::remove_reference_t< Otherwise >* otherwise;
  };

  // TODO(mattcalabrese) Concept check
  template< class Opt, class Otherwise >
  [[nodiscard]]
  constexpr auto operator ()( Opt&& opt, Otherwise&& otherwise ) const
  {
    return impl< Opt&&, Otherwise&& >
    { std::addressof( ARGOT_FORWARD( Opt )( opt ) )
    , std::addressof( ARGOT_FORWARD( Otherwise )( otherwise ) )
    };
  }
} inline constexpr element_or{};

template< class Opt, class Otherwise >
using result_of_element_or
  = basic_result_of< element_or_fn const&, Opt, Otherwise >;

template< class Opt, class Otherwise >
using result_of_element_or_t
  = basic_result_of_t< element_or_fn const&, Opt, Otherwise >;

}  // namespace argot(::prov)

// TODO(mattcalabrese) Use traits
template< class Opt, class Otherwise >
struct make_concept_map
< ArgumentProvider< prov::element_or_fn::impl< Opt, Otherwise > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t< decltype( *ARGOT_DECLVAL( Opt& ) )&& >  // TODO(mattcalabrese) Use traits
      , receiver_traits::argument_types_t< Otherwise&& >
      >
    )()
  >
  static constexpr decltype( auto )
  provide( prov::element_or_fn::impl< Opt > self
         , Receiver&& receiver
         )
  {
    return   self.has_value()  // TODO(mattcalabrese) Use traits
           ? receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t<> >{}
             , receiver_traits::argument_list_kinds()
             , **self.opt  // TODO(mattcalabrese) Use traits
             )
           : receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t
                 < decltype( *ARGOT_DECLVAL( Opt& ) ) >  // TODO(mattcalabrese) Use traits
               >{}
             );
  }
};

// TODO(mattcalabrese) Use traits
template< class Opt >
struct make_concept_map
< PersistentArgumentProvider< prov::element_or_fn::impl< Opt > > >
{
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t< decltype( *ARGOT_DECLVAL( Opt ) )&& >  // TODO(mattcalabrese) Use traits
      , Otherwise const&
      >
    )()
  >
  static constexpr decltype( auto )
  provide( prov::element_or_fn::impl< Opt > self
         , Receiver&& receiver
         )
  {
    return   self.has_value()  // TODO(mattcalabrese) Use traits
           ? receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds()
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t
                 < decltype( *ARGOT_DECLVAL( Opt ) ) >  // TODO(mattcalabrese) Use traits
               >{}
             )
           : receiver_traits::receive_branch
             ( ARGOT_MOVE( receiver )
             , receiver_traits::argument_list_kinds_t
               < receiver_traits::argument_types_t<> >{}
             , receiver_traits::argument_list_kinds()
             , *ARGOT_FORWARD( Opt )( *self.opt )  // TODO(mattcalabrese) Use traits
             );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_ELEMENT_OR_HPP_
