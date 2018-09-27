/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_CONCEPT_ASSERT_HPP_
#define ARGOT_GEN_CONCEPT_ASSERT_HPP_

//[description
/*`
ARGOT_CONCEPT_ASSERT is a macro that expands to a `static_assert` that checks
whether or not one or more concepts are modeled.

[note If the macro `ARGOT_DISABLE_CONCEPT_ASSERTS` is defined, then the macro
      will expand to `static_assert( true )`. This can be useful if the concept
      checks that are involved occupy considerable compile-time resources. If
      you wish to have a `static_assert` that checks the concepts even when
      `ARGOT_DISABLE_CONCEPT_ASSERTS` is defined, such as when writing tests,
      use `ARGOT_CONCEPT_ENSURE` instead.
]
*/
//]

#include <argot/gen/requires.hpp>

#ifndef ARGOT_DISABLE_CONCEPT_ASSERTS

#define ARGOT_CONCEPT_ASSERT( ... )                                            \
static_assert                                                                  \
( ::argot::requires_detail::requires_impl< __VA_ARGS__ >::type::assertion      \
  ::value                                                                      \
)

#else  // Otherwise, ignore concept asserts.

#define ARGOT_CONCEPT_ASSERT( ... ) static_assert( true )

#endif  // ARGOT_DISABLE_CONCEPT_ASSERTS

//[docs
/*`
[synopsis_heading]

```
``#define ARGOT_CONCEPT_ASSERT( ... ) static_assert( [unspecified_expansion] )``
```
*/
//]

#endif  // ARGOT_GEN_CONCEPT_ASSERT_HPP_
