/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_NO_DUPLICATES_HPP_
#define ARGOT_DETAIL_NO_DUPLICATES_HPP_

#include <argot/declval.hpp>
#include <argot/value_list.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace call_detail {

template< class ValueType, ValueType... Values >
struct no_duplicates_impl;

template< class ValueType >
struct no_duplicates_impl< ValueType >
{
  using result = std::true_type;

  template< ValueType Value >
  std::true_type operator ()( std::integral_constant< ValueType, Value >&& ) &&
  { return {}; }
};

template< class ValueType, ValueType Head, ValueType... Tail >
struct no_duplicates_impl< ValueType, Head, Tail... >
  : no_duplicates_impl< ValueType, Tail... >
{
  using no_duplicates_impl< ValueType, Tail... >::operator ();

  // TODO(mattcalabrese)
  //   Possibly use std::invoke_result_t here instead of decltype, short-circuit
  using result
    = std::integral_constant
      < bool
      ,    no_duplicates_impl< ValueType, Tail... >::result::value
        && decltype
           ( ARGOT_DECLVAL( no_duplicates_impl< ValueType, Tail... > )
             ( ARGOT_DECLVAL( std::integral_constant< ValueType, Head > ) )
           )::value
      >;

  std::false_type operator ()( std::integral_constant< ValueType, Head >&& ) &&
  { return {}; }
};

template< class IntegerSequence >
struct no_duplicates{};

template< class ValueType, ValueType... Values >
struct no_duplicates< std::integer_sequence< ValueType, Values... > >
  : no_duplicates_impl< ValueType, Values... >::result{};

template< class IntegerSequence >
bool constexpr no_duplicates_v
  = no_duplicates< IntegerSequence >::value;

template< class IntegerSequence >
struct value_type_of_integer_sequence{};

template< class ValueType, ValueType... Values >
struct value_type_of_integer_sequence
< std::integer_sequence< ValueType, Values... > >
{
  using type = ValueType;
};

template< class IntegerSequence >
using value_type_of_integer_sequence_t
  = typename value_type_of_integer_sequence< IntegerSequence >::type;

template< class IntegerSequence
        , value_type_of_integer_sequence_t< IntegerSequence > Value
        >
struct value_is_in_sequence;

template
< class ValueType, ValueType... Values
, value_type_of_integer_sequence_t
  < std::integer_sequence< ValueType, Values... > > Value
>
struct value_is_in_sequence
< std::integer_sequence< ValueType, Values... >, Value >
  : std::integral_constant
    < bool
    , !decltype
      ( ARGOT_DECLVAL( no_duplicates_impl< ValueType, Values... > )
        ( ARGOT_DECLVAL( std::integral_constant< ValueType, Value > ) )
      )::value
    >{};

template< class IntegerSequence
        , value_type_of_integer_sequence_t< IntegerSequence > Value
        >
bool constexpr value_is_in_sequence_v
  = value_is_in_sequence< IntegerSequence, Value >::value;

// TODO(calabrese) Make SFINAE aware
template< class ValueType, class IntegerSequence >
struct integer_sequence_cast{};

template< class ValueType, class SourceValueType, SourceValueType... Values >
struct integer_sequence_cast< ValueType, std::integer_sequence< SourceValueType, Values... > >
{
  using type = std::integer_sequence< ValueType, static_cast< ValueType >( Values )... >;
};

template< class ValueType, auto... Values >
struct integer_sequence_cast< ValueType, value_list_t< Values... > >
{
  using type = std::integer_sequence< ValueType, static_cast< ValueType >( Values )... >;
};

template< class ValueType, class IntegerSequence >
using integer_sequence_cast_t = typename integer_sequence_cast< ValueType, IntegerSequence >::type;

}  // namespace argot::call_detail
}  // namespace argot

#endif  // ARGOT_DETAIL_NO_DUPLICATES_HPP_
