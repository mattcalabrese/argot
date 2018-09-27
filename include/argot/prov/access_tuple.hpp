/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ACCESS_TUPLE_HPP_
#define ARGOT_PROV_ACCESS_TUPLE_HPP_

//[description
/*`
prov::access_tuple is a function object that returns an ArgumentProvider of a
single element of a TupleLike type using an index that may be either a
compile-time constant or a run-time value.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/convertible_to_type_or_constant.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/default_.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/tuple_index.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/tuple_traits/natural_get.hpp>

#include <type_traits>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct access_tuple_fn
{
  template
  < class Tup, class Index, class Def = argot::default_unreachable_t
  , ARGOT_REQUIRES
    ( TupleLike< detail_argot::remove_cvref_t< Tup > > )
    ( Not< VolatileObject< std::remove_reference_t< Tup > > > )
    ( ConvertibleToTypeOrConstant
      < Index
      , tuple_traits::index_type_t< detail_argot::remove_cvref_t< Tup > >
      >
    )
    ( Default< Def > )
    ()
  >
  [[nodiscard]] constexpr auto operator ()
  ( Tup&& tup, Index&& index, Def def = Def() ) const//=;
  //<-
  {
    return prov::lift_call
    ( tuple_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Tup )( tup ) )
    , prov::tuple_index< detail_argot::remove_cvref_t< Tup > >
      ( ARGOT_FORWARD( Index )( index ), ARGOT_MOVE( def ) )
    );
  } //->
} inline constexpr access_tuple{};

template< class Tup, class Index, class Def = argot::default_unreachable_t >
using result_of_access_tuple//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< access_tuple_fn const&, Tup, Index, Def >; //->

template< class Tup, class Index, class Def = argot::default_unreachable_t >
using result_of_access_tuple_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< access_tuple_fn const&, Tup, Index, Def >; //->

} // namespace (argot::prov)

/*`
[element_spec_heading]

[table Parameters of `operator()`
 [[Parameter][_Expects][Description]]
 [[`Tup&& tup`]
  [Forwarding-reference to a possibly-const TupleLike]
  [The tuple of which an element is to be provided]
 ]
 [[`Index&& index`]
  [Either: [ordered_list [Forwarding-reference convertible to `tup`'s index
  type /or/][Forwarding-reference to a `std::integral_constant` with tup's
  index type as the value type.]]
  ]
  [The index of the element to be provided]
 ]
 [[`Def def`]
  [A model of Default]
  [The handler to be used if `index` is out of range for `tup`]
 ]
]

[table Requirements for `operator()`
 [[Element]                [Specification]]
 [[Effects_Equivalent_to_Provider ] [

```
return prov::lift_call
       ( tuple_traits::natural_get
       , prov::reference_to( std::forward< Tup >( tup ) )
       , prov::tuple_index< detail_argot::remove_cvref_t< Tup > >
         ( std::forward< Index >( index )
         , std::move( def )
         )
       );
```
 ]]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Tup` in ascending order.
]

[table Resultant Provider
 [[Property][Dynamic Index][Static Index]]
 [[Logical Provision][Reference to the corresponding tuple element]
                     [Reference to the corresponding tuple element]]
 [[Possible Argument Types]
  [[itemized_list [```( tuple_traits::result_of_get_t< Tup&&, i > )...```]]]
  [[itemized_list [```( tuple_traits::result_of_get_t< Tup&&, index.value > )```]]]
 ]
] 
*/

//]

#endif  // ARGOT_PROV_ACCESS_TUPLE_HPP_
