/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_INDEX_OF_HPP_
#define ARGOT_PROV_INDEX_OF_HPP_

//[description
/*`
prov::index_of is a function object that takes a VariantLike type and returns an
ArgumentProvider that provides the currently active index of the VariantLike in
the form of a `std::integral_constant` instantation.

[warning
  For a std::variant, the `valueless_by_exception` state has no active
  /alternative/. It is a precondition violation to call prov::index_of when the
  std::variant is in such a state. 
]

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/variant_index.hpp>
#include <argot/variant_traits/index_of.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct index_of_fn
{
  template< class Var
          , ARGOT_REQUIRES
            ( VariantLike< Var > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Var const& var ) const//=;
  //<-
  {
    return prov::variant_index< Var >( variant_traits::index_of( var ) );
  } //->
} inline constexpr index_of{};

template< class Var >
using result_of_index_of//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< index_of_fn const&, Var >; //->

template< class Var >
using result_of_index_of_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< index_of_fn const&, Var >; //->

} // namespace (argot::prov)

/*`
[element_spec_heading]

[table Parameters of `operator()`
 [[Parameter][_Expects][Description]]
 [[`Var const& var`]
  [A reference to a VariantLike that must not be partially-formed or in the
   `valueless_by_exception` state]
  [The VariantLike for which the index is to be provided]
 ]
]

[table Requirements for `operator()`
 [[Element]                [Specification]]
 [[Effects_Equivalent_to_Provider ] [

```
    return prov::variant_index< Var >( variant_traits::index_of( var ) );
```
 ]]
]

[provider_properties_heading]

[note In the following table, assume `i` is a parameter pack of all valid
      /indices/ of `Var` in ascending order.
]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision][The index of the currently active alternative in the form
                      of a `std::integral_constant`]]
  [[Possible Argument Types]
  [[itemized_list [```( std::integral_constant< variant_traits::index_type_t< Var >, i > )...```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_INDEX_OF_HPP_
