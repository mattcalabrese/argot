/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_IS_MODELED_HPP_
#define ARGOT_GEN_IS_MODELED_HPP_

//[description
/*`
ARGOT_IS_MODELED is a macro that takes a /concept-instance/ and produces a core
constant `bool` of value `true` if the checkable portion of the concept is
modeled, otherwise `false`.

[note In most cases, this macro should not be used directly. Instead, prefer to
      use either ARGOT_REQUIRES when in cases where you wish to enable a
      template based on the concept requirements, or use either
      ARGOT_CONCEPT_ASSERT or ARGOT_CONCEPT_ENSURE when you wish to trigger a
      `static_assert` if the concept is not modeled. Those facilities will
      produce better error messages that have the ability to describe why the
      concept is not modeled. The most common place that ARGOT_IS_MODELED is
      useful is when calculating the `noexcept` specifier for an operation that
      is conditionally-noexcept. 
]
*/
//]

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

// TODO(mattcalabrese)
//   static_assert that the concept map is valid whenever it is specialized.

namespace argot {

template< class ConceptSpec >
bool constexpr is_modeled_v
  = ConceptSpec::template argot_gen_detail_is_modeled_impl< ConceptSpec >
    ::value;

template< class ConceptSpec >
struct is_modeled : std::bool_constant< is_modeled_v< ConceptSpec > > {};

} // namespace argot

#define ARGOT_IS_MODELED( ... ) ::argot::is_modeled_v< __VA_ARGS__ >

//[docs
/*`
[synopsis_heading]

```
``#define ARGOT_IS_MODELED( ... ) [unspecified_expansion]``
```
*/
//]

#endif  // ARGOT_GEN_IS_MODELED_HPP_
