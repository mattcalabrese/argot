/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_REFERENCE_TO_HPP_
#define ARGOT_CONC_REFERENCE_TO_HPP_

//[description
/*`
conc::reference_to is a facility for binding arguments by reference into a
PersistentConcurrentArgumentProvider. When provision is performed on the
resultant ConcurrentArgumentProvider as an rvalue, all bound references undergo
perfect-forwarding. When provision is performed on the result
ConcurrentArgumentProvider as an lvalue, all arguments are forwarded as lvalue
reference, matching standard reference-collapsing rules.

[warning
  Capturing arguments by reference in a ConcurrentArgumentProvider is usually
  not thread-safe and so valid uses of this facility tend to be rare. In
  general, arguments should instead be bound by value, such as with
  conc::value_of.
]
*/
//]

#include <argot/conc/conc_generator.hpp>
#include <argot/prov/reference_to.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

inline constexpr auto reference_to = conc::conc_generator( prov::reference_to );

using reference_to_fn
  = conc::result_of_conc_generator_t< prov::reference_to_fn const& >;

} // namespace (argot::conc)

//]

#endif  // ARGOT_CONC_REFERENCE_TO_HPP_
