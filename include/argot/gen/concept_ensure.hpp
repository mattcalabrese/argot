/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_ENSURE_HPP_
#define ARGOT_GEN_CONCEPT_ENSURE_HPP_

//[description
/*`
ARGOT_CONCEPT_ENSURE is a macro that expands to a `static_assert` that checks
whether or not one or more concepts are modeled.

[note If you wish to have the ability to enable and disable such a
      `static_assert`, use `ARGOT_CONCEPT_ASSERT` instead.
]
*/
//]

#include <argot/gen/requires.hpp>

// Always enabled, regardless of configuration.
#define ARGOT_CONCEPT_ENSURE( ... )                                            \
static_assert                                                                  \
( ::argot::requires_detail::requires_impl< __VA_ARGS__ >::type::assertion      \
  ::value                                                                      \
)

//[docs
/*`
[synopsis_heading]

```
``#define ARGOT_CONCEPT_ENSURE( ... ) static_assert( [unspecified_expansion] )``
```
*/
//]

#endif  // ARGOT_GEN_CONCEPT_ENSURE_HPP_
