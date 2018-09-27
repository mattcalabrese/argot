/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_VALUE_OF_HPP_
#define ARGOT_CONC_VALUE_OF_HPP_

//[description
/*`
conc::value_of is a facility for binding a variadic pack of arguments by
value into a PersistentConcurrentArgumentProvider. When provision is performed
on the resultant ConcurrentArgumentProvider as an rvalue, each bound object is
passed as an rvalue. When provision is performed on the result
ConcurrentArgumentProvider as an lvalue, each argument is forwarded as an
lvalue reference to `const`.
*/
//]

#include <argot/conc/conc_generator.hpp>
#include <argot/prov/value_of.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

using value_of_fn
  = conc::result_of_conc_generator_t< prov::value_of_fn const& >;

inline constexpr auto value_of = conc::conc_generator( prov::value_of );

// TODO(mattcalabrese) result_of calculator

} // namespace (argot::conc)

//]

#endif  // ARGOT_CONC_VALUE_OF_HPP_
