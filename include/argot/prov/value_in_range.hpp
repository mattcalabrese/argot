/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_VALUE_IN_RANGE_HPP_
#define ARGOT_PROV_VALUE_IN_RANGE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/case/case_range.hpp>
#include <argot/concepts/convertible_to_type_or_constant.hpp>
#include <argot/concepts/default.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/std_integral_constant.hpp>
#include <argot/concepts/switch_condition.hpp>
#include <argot/default_.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov/switch_.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot::prov {

// TODO(mattcalabrese) Make sure this is a valid range.
template< class ValueType, ValueType Begin, ValueType End >
struct value_in_range_fn
{
  ARGOT_CONCEPT_ASSERT( SwitchCondition< ValueType > );

  // TODO(mattcalabrese)
  //   Don't require Def to be default, just require combinability.
  template< class Type, class Def = default_unreachable_t
          , ARGOT_REQUIRES
            ( ConvertibleToTypeOrConstant< Type, ValueType > )
            ( Default< detail_argot::remove_cvref_t< Def > > )
            ( Sinkable< Def&& > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Type&& value, Def&& def = {} ) const
  {
    if constexpr
    ( is_modeled_v< StdIntegralConstant< detail_argot::remove_cvref_t< Type > > > )
      return prov::switch_
      ( std::integral_constant< ValueType, detail_argot::remove_cvref_t< Type >::value >()
      , argot::case_range< Begin, End >.as_constant
      , ARGOT_FORWARD( Def )( def )
      );
    else
    {
      ValueType const typed_value = ARGOT_FORWARD( Type )( value );

      return prov::switch_( typed_value
                          , argot::case_range< Begin, End >.as_constant
                          , ARGOT_FORWARD( Def )( def )
                          );
    }
  }
};

// TODO(mattcalabrese) Make sure this is a valid range.
template< class ValueType, ValueType Begin, ValueType End >
ARGOT_REQUIRES( SwitchCondition< ValueType > )
< value_in_range_fn< ValueType, Begin, End > > constexpr value_in_range{};

template< class ValueType, ValueType Begin, ValueType End, class V
        , class Default = default_unreachable_t
        >
using result_of_value_in_range
  = basic_result_of
    < value_in_range_fn< ValueType, Begin, End > const&, V, Default >;

template< class ValueType, ValueType Begin, ValueType End, class V
        , class Default = default_unreachable_t
        >
using result_of_value_in_range_t
  = basic_result_of_t
    < value_in_range_fn< ValueType, Begin, End > const&, V, Default >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_VALUE_IN_RANGE_HPP_
