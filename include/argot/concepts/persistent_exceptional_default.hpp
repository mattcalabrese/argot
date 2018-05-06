/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

// TODO(mattcalabrese) Remove this file

#if 0

#ifndef ARGOT_CONCEPTS_PERSISTENT_EXCEPTIONAL_DEFAULT_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_EXCEPTIONAL_DEFAULT_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/exceptional_default.hpp>
#include <argot/gen/explicit_concept.hpp>

namespace argot {

template< class T >
ARGOT_EXPLICIT_CONCEPT( PersistentExceptionalDefault )
(
  ExceptionalDefault< T >
);

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_EXCEPTIONAL_DEFAULT_HPP_

#endif
