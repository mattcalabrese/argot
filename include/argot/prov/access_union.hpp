/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ACCESS_UNION_HPP_
#define ARGOT_PROV_ACCESS_UNION_HPP_

//[description
/*`
prov::access_union is a function object that returns an ArgumentProvider of a
single alternative of a UnionLike type using an index that may be either a
compile-time constant or a run-time value.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/default_.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/not.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/union_index.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/natural_get.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct access_union_fn
{
  template< class Un, class Index, class Def = argot::default_unreachable_t
          , ARGOT_REQUIRES
            ( UnionLike< detail_argot::remove_cvref_t< Un > > )
            ( Not< VolatileObject< std::remove_reference_t< Un > > > )
            ( ConvertibleToTypeOrConstant
              < Index
              , union_traits::index_type_t< detail_argot::remove_cvref_t< Un > >
              >
            )
            ( Default< Def > )
            ()
          >
  [[nodiscard]] constexpr auto operator ()
  ( Un&& un, Index&& index, Def def = Def() ) const//=;
  //<-
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Un )( un ) )
    , prov::union_index< detail_argot::remove_cvref_t< Un > >
      ( ARGOT_FORWARD( Index )( index ), ARGOT_MOVE( def ) )
    );
  } //->
} inline constexpr access_union{};

template< class Un, class Index, class Def = argot::default_unreachable_t >
using result_of_access_union//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< access_union_fn const&, Un, Index, Def >; //->

template< class Un, class Index, class Def = argot::default_unreachable_t >
using result_of_access_union_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< access_union_fn const&, Un, Index, Def >; //->

} // namespace (argot::prov)

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Un&& un`]
  [Forwarding-reference to a possibly-const UnionLike]
  [The UnionLike of which an alternative is to be provided]
 ]
 [[`Index&& index`]
  [Either: [ordered_list [Forwarding-reference convertible to `un`'s index
  type /or/][Forwarding-reference to a `std::integral_constant` with un's
  index type as the value type.]]
  ]
  [The index of the alternative to be provided]
 ]
 [[`Def def`]
  [A model of Default]
  [The handler to be used if `index` is out of range for `un`]
 ]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Un` in ascending order.
]

[table Resultant Provider
 [[Property][Dynamic Index][Static Index]]
 [[Logical Provision][Reference to the corresponding alternative]
                     [Reference to the corresponding alternative]]
 [[Possible Argument Types]
  [[itemized_list [```( union_traits::result_of_get_t< Un&&, i > )...```]]]
  [[itemized_list [```( union_traits::result_of_get_t< Un&&, index.value > )```]]]
 ]
]
*/
//]

#endif  // ARGOT_PROV_ACCESS_UNION_HPP_
