/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_BOOL_HPP_
#define ARGOT_PROV_BOOL_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/bool_or_constant.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>

#include <type_traits>

namespace argot {
namespace prov {

struct bool_fn
{
  struct impl { bool value; };

  template< class Bool, ARGOT_REQUIRES( BoolOrConstant< Bool > )() >
  [[nodiscard]]
  constexpr auto operator()( Bool const value ) const noexcept
  {
    if constexpr( std::is_same_v< Bool, bool > ) return impl{ value };
    else return prov::value_of( value );
  }
} inline constexpr bool_{};

template< class V >
using result_of_bool = basic_result_of< bool_fn const&, V >;

template< class V >
using result_of_bool_t = basic_result_of_t< bool_fn const&, V >;

}  // namespace argot(::prov)

template<>
struct make_concept_map< ArgumentProvider< prov::bool_fn::impl > >
{
  // TODO(mattcalabrese)
  //   Possibly don't add reference to the argument types in the requirements.
  template< class Receiver
          , ARGOT_REQUIRES
            ( ArgumentReceiverOf
              < Receiver
              , receiver_traits::argument_types_t< std::false_type&& >
              , receiver_traits::argument_types_t< std::true_type&& >
              >
            )
            ()
          >
  static constexpr decltype( auto )
  provide( prov::bool_fn::impl self, Receiver&& receiver )
  {
    return self.value
    ? receiver_traits::receive_branch
      ( ARGOT_MOVE( receiver )
      , receiver_traits::argument_list_kinds
        ( receiver_traits::argument_types< std::false_type&& > )
      , receiver_traits::argument_list_kinds()
      , std::true_type()
      )
    : receiver_traits::receive_branch
      ( ARGOT_MOVE( receiver )
      , receiver_traits::argument_list_kinds()
      , receiver_traits::argument_list_kinds
        ( receiver_traits::argument_types< std::true_type&& > )
      , std::false_type()
      );
  }
};

template<>
struct make_concept_map< PersistentArgumentProvider< prov::bool_fn::impl > >
  : make_concept_map< ArgumentProvider< prov::bool_fn::impl > >
{};

}  // namespace argot

#endif  // ARGOT_PROV_BOOL_HPP_
