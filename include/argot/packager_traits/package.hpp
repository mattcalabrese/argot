/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PACKAGER_PACKAGE_HPP_
#define ARGOT_PACKAGER_PACKAGE_HPP_

//[description
/*`
packager_traits::package is a facility for creating a function object that
executes a user-specified InvocableObjectWith via a user-specified Executor.
Calls to the resultant function object produce a Future to the result type of
the user-specified InvocableObjectWith.
*/
//]

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::packager_traits {

template< class FPackager, class... P >
struct package_fn
{
  //<-
  // TODO(mattcalabrese) Assert valid argument types.
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );
  //->
  template< class Exec, class Fun
          , ARGOT_REQUIRES
            ( Executor< detail_argot::remove_cvref_t< Exec > > )
            ( InvocableWith< std::decay_t< Fun >, P... > )
            ( Sinkable< Exec&& > )
            ( DecaySinkable< Fun&& > )
            ()
          >
  constexpr auto operator ()( Exec&& exec, Fun&& fun ) const//=;
  //<-
  {
    return access_raw_concept_map< FuturePackager< FPackager > >
    ::template package< P... >
    ( call_detail::forward_and_sink< Exec >( exec )
    , call_detail::forward_and_decay_sink< Fun >( fun )
    );
  } //->
};

// TODO(mattcalabrese) Require valid argument types.
template< class FPackager, class... P >
ARGOT_REQUIRES( FuturePackager< FPackager > )
< package_fn< FPackager, P... > > constexpr package{};

// TODO(mattcalabrese) Result of metafunctions

} // namespace (argot::packager_traits)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class FPackager`]
  [A FuturePackager type]
  [The FuturePackager that is used to create a Future whenever `fun` is invoked]
 ]
 [[`class... P`]
  [Each type of `P...` is a ParameterType]
  [The parameter types of resultant Invocable]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`Exec&& exec`]
  [A Sinkable reference to a possibly-qualified Executor]
  [The Executor through which `fun` is executed when the resultant
   InvocableObject is called
  ]
 ]
 [[`Fun&& fun`]
  [A DecaySinkable reference to a possibly-qualified InvocableWith for argument
   types `P...`
  ]
  [The user-specified InvocableWith to be run when the resultant
   InvocableObjectWith is called]
 ]
]
*/

//]

#endif  // ARGOT_PACKAGER_PACKAGE_HPP_
