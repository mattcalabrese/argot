/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_TYPE_HPP_
#define ARGOT_GEN_TYPE_HPP_

//[description
/*`
argot::Type is a unary concept that takes a type and is always modeled.
*/
//]

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <type_traits>

#endif

namespace argot {

template< class T >
struct Type
{
  static bool constexpr argot_gen_detail_is_auto_concept_v = true;

  template< class ConceptSpec >
  using argot_gen_detail_is_modeled_impl = std::true_type;

  using assertion = std::true_type;
};

} // namespace argot

//[docs
/*`
[synopsis_heading]

```
namespace argot {

template< class >
ARGOT_AUTO_CONCEPT( Type )
(
);

} // namespace argot
```
*/
//]

#endif  // ARGOT_GEN_TYPE_HPP_
