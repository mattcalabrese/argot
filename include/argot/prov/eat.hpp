/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_EAT_HPP_
#define ARGOT_PROV_EAT_HPP_

//[description
/*`
prov::eat is a function object that returns an ArgumentProvider of an empty
argument list.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/prov/nothing.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct eat_fn
{
  template< class... P >
  [[nodiscard]]
  constexpr auto operator ()( P&&... args ) const noexcept//=;
  //<-
    -> prov::nothing_t
  {
    return {};
  } //->
} inline constexpr eat{};

template< class... P >
using result_of_eat//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< eat_fn const&, P... >; //->

template< class... P >
using result_of_eat_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< eat_fn const&, P... >; //->

} // namespace (argot::prov)

/*`

[element_spec_heading]

[table Parameters of `operator()`
 [[Parameter][_Expects][Description]]
 [[`P&&... args`]
  [Each of `P&&...` is a valid reference type.]
  [Parameters that are entirely ignored]
 ]
]

[table Requirements for `operator()`
 [[Element]                [Specification]]
 [[Effects_Equivalent_to_Provider ] [

```
return prov::nothing;
```
 ]]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision][Empty argument list]]
 [[Possible Argument Types]
  [[itemized_list [```()```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_EAT_HPP_
