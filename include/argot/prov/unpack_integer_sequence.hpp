/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNPACK_INTEGER_SEQUENCE_HPP_
#define ARGOT_UNPACK_INTEGER_SEQUENCE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver_of.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace prov {

struct unpack_integer_sequence_fn
{
 public:  // TODO(mattcalabrese) private
  template< class ValueType, ValueType... Values >
  struct impl {};
 public:
  template< class ValueType, ValueType... Values >
  [[nodiscard]] constexpr auto operator ()
  ( std::integer_sequence< ValueType, Values... > ) const noexcept
  {
    if constexpr( sizeof...( Values ) == 0 ) return nothing;
    else return impl< ValueType, Values... >{};
  }
} inline constexpr unpack_integer_sequence{};

template< class IntegerSequence >
using result_of_unpack_integer_sequence
  = basic_result_of< unpack_integer_sequence_fn const&, IntegerSequence >;

template< class IntegerSequence >
using result_of_unpack_integer_sequence_t
  = basic_result_of_t< unpack_integer_sequence_fn const&, IntegerSequence >;

}  // namespace argot(::prov)

template< class ValueType, ValueType... Values >
struct make_concept_map
< ArgumentProvider
  < prov::unpack_integer_sequence_fn::impl< ValueType, Values... > >
>
{
  // TODO(mattcalabrese) Possibly don't add && to integral_constant
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t
        < std::integral_constant< ValueType, Values >&&... >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::unpack_integer_sequence_fn::impl< ValueType, Values... >
         , Receiver&& receiver
         )
  {
    return receiver_traits::receive
    ( ARGOT_MOVE( receiver )
    , std::integral_constant< ValueType, Values >()...
    );
  }
};

template< class ValueType, ValueType... Values >
struct make_concept_map
< PersistentArgumentProvider
  < prov::unpack_integer_sequence_fn::impl< ValueType, Values... > >
>
{
  // TODO(mattcalabrese) Possibly don't add && to integral_constant
  template
  < class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOf
      < Receiver
      , receiver_traits::argument_types_t
        < std::integral_constant< ValueType, Values >&&... >
      >
    )
    ()
  >
  static constexpr decltype( auto )
  provide( prov::unpack_integer_sequence_fn::impl< ValueType, Values... >
         , Receiver&& receiver
         )
  {
    return receiver_traits::receive
    ( ARGOT_MOVE( receiver )
    , std::integral_constant< ValueType, Values >()...
    );
  }
};

}  // namespace argot

#endif  // ARGOT_UNPACK_INTEGER_SEQUENCE_HPP_
