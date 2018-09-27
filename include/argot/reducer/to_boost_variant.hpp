/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_TO_BOOST_VARIANT_HPP_
#define ARGOT_REDUCER_TO_BOOST_VARIANT_HPP_

#include <argot/concepts/return_value_reducer.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <boost/variant/variant.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace argot {

template< std::size_t I, class Field >
struct to_boost_variant_field
{
  using index = std::integral_constant< std::size_t, I >;
  using field_type = Field;
  field_type field;
};

namespace reducer {

struct to_boost_variant_t {} inline constexpr to_boost_variant{};

namespace to_boost_variant_detail {

template< class Indices, class HeadField, class... TailFields >
struct boost_variant_type;

// TODO(mattcalabrese) Only enable if inputs are valid for variant
//                     (i.e. not void)
template< std::size_t HeadIndex, std::size_t... TailIndices
        , class HeadField, class... TailFields
        >
struct boost_variant_type
< std::index_sequence< HeadIndex, TailIndices... >, HeadField, TailFields... >
{
  using type = boost::variant
               < to_boost_variant_field< HeadIndex, HeadField >
               , to_boost_variant_field< TailIndices, TailFields >...
               >;
};

template< class... T >
using return_type
  = typename boost_variant_type
    < std::make_index_sequence< sizeof...( T ) >, T... >::type;

} // namespace argot::reducer::to_boost_variant_detail
} // namespace argot::reducer

template<>
struct make_concept_map< ReturnValueReducer< reducer::to_boost_variant_t > >
{
  using is_homogeneous = std::false_type;

  template
  < class... LeadingReturnTypes, class... TrailingReturnTypes, class Fun >
  static constexpr typename reducer::to_boost_variant_detail::boost_variant_type
  < std::make_index_sequence
    < sizeof...( LeadingReturnTypes ) + 1 + sizeof...( TrailingReturnTypes ) >
  , LeadingReturnTypes..., std::invoke_result_t< Fun >, TrailingReturnTypes...
  >::type
  reduce
  ( reducer::to_boost_variant_t
  , reducer_traits::return_types_t< LeadingReturnTypes... >
  , reducer_traits::return_types_t< TrailingReturnTypes... >
  , Fun&& fun
  )
  {
    return reducer::to_boost_variant_detail::return_type
    < LeadingReturnTypes...
    , std::invoke_result_t< Fun >
    , TrailingReturnTypes...
    >
    ( to_boost_variant_field
      < sizeof...( LeadingReturnTypes ), std::invoke_result_t< Fun > >
      { ARGOT_FORWARD( Fun )( fun )() }
    );
  };
};

} // namespace argot

#endif  // ARGOT_REDUCER_TO_BOOST_VARIANT_HPP_
