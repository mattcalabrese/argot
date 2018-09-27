/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_NOTHING_HPP_
#define ARGOT_CONC_NOTHING_HPP_

//[description
/*`
conc::nothing is a PersistentConcurrentArgumentProvider of an empty argument list.
*/
//]

#include <argot/conc/lift.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/prov/nothing.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::conc {

inline constexpr auto nothing = conc::lift( prov::nothing );

// TODO(mattcalabrese) use result_of_lift_t
using nothing_t = detail_argot::remove_cvref_t< decltype( nothing ) >;

} // namespace (argot::conc)

//]

#endif  // ARGOT_CONC_NOTHING_HPP_
