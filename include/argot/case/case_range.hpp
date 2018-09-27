/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_CASE_RANGE_HPP_
#define ARGOT_CASE_CASE_RANGE_HPP_

#include <argot/case/detail/cases_base.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/identity.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/value_list.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace case_range_detail {

template< class T >
using underlying_type_or_self_t
  = typename argot_detail::conditional< std::is_enum_v< T > >::template apply
    < std::underlying_type< T >, argot_detail::identity< T > >::type;

template< class Indices, auto Offset >
struct offset_range_impl;

template< class ValueType, ValueType... Indices, auto Offset >
struct offset_range_impl
< std::integer_sequence< ValueType, Indices... >, Offset >
{
  using type
    = value_list_t< ( Indices + static_cast< ValueType >( Offset ) )... >;
};

template< auto UnderlyingBegin, auto UnderlyingEnd >
using offset_range_t
  = typename offset_range_impl
    < std::make_integer_sequence
      < decltype( UnderlyingEnd - UnderlyingBegin )
      , UnderlyingEnd - UnderlyingBegin
      >
    , static_cast< decltype( UnderlyingEnd - UnderlyingBegin ) >
      ( UnderlyingBegin )
    >::type;

template< template< auto... > class Template, class Indices, auto Offset >
struct expand_offset_range_impl;

template< template< auto... > class Template
        , class ValueType, ValueType... Indices, auto Offset
        >
struct expand_offset_range_impl
< Template, std::integer_sequence< ValueType, Indices... >, Offset >
{
  using type = Template< ( Indices + static_cast< ValueType >( Offset ) )... >;
};

template< template< auto... > class Template
        , auto UnderlyingBegin, auto UnderlyingEnd
        >
using expand_offset_range_t
  = typename offset_range_impl
    < std::make_integer_sequence
      < decltype( UnderlyingEnd - UnderlyingBegin )
      , UnderlyingEnd - UnderlyingBegin
      >
    , static_cast< decltype( UnderlyingEnd - UnderlyingBegin ) >
      ( UnderlyingBegin )
    >::type;

} // namespace argot(::case_range_detail)

// TODO(mattcalabrese) Constrain
template< auto Begin, auto End >
struct case_range_t
  : private case_detail::cases_base< case_range_t< Begin, End > >
{
  using base_t = case_detail::cases_base< case_range_t< Begin, End > >;
 public:
   using base_t::as_constant;
   using base_t::as_is;
   using base_t::operator();
   using base_t::unreachable;
};

// TODO(mattcalabrese) Constrain
template< auto Begin, auto End >
case_range_t< Begin, End > constexpr case_range{};

// TODO(mattcalabrese) Result of calculators

template< auto Begin, auto End >
struct make_concept_map< CaseLabels< case_range_t< Begin, End > > >
{
  using case_values_t
    = case_range_detail::offset_range_t
      < static_cast
        < case_range_detail::underlying_type_or_self_t< decltype( Begin ) > >
        ( Begin )
      , static_cast
        < case_range_detail::underlying_type_or_self_t< decltype( End ) > >
        ( End )
      >;

  template< template< auto... > class Template >
  using expand_case_values_t
    = case_range_detail::expand_offset_range_t
      < Template
      , static_cast
        < case_range_detail::underlying_type_or_self_t< decltype( Begin ) > >
        ( Begin )
      , static_cast
        < case_range_detail::underlying_type_or_self_t< decltype( End ) > >
        ( End )
      >;
};

} // namespace argot

#endif  // ARGOT_CASE_CASE_RANGE_HPP_
