/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_COMPOSE_HPP_
#define ARGOT_COMPOSE_HPP_

//[description
/*`
argot::compose is a facility for combining a series of unary /invocable objects/
into a single function object where the output of the first invocable object
acts as the input to the next, whose output acts as the input to the next, and
so on, with the return of the final invocable acting as the return of the
resultant function object. A call to argot::compose with no arguments produces
an identity function that perfect-forwards its input into its output by
reference.

The function object that is returned by argot::compose contains each of the
parameters it was given, by value.
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/composable.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/persistent_composable.hpp>
#include <argot/concepts/potentially_invocable_object.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/referential_identity.hpp>
#include <argot/void_.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

struct compose_fn
{
  //<-
 private:
  template< class Head, class Next, class... Tail >
  struct impl;

  template< class... Transformations >
  struct impl_of;

  template< class Head >
  struct impl_of< Head >
  {
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Head > );

    using type = Head;
  };

  template< class Head, class Next, class... Tail >
  struct impl_of< Head, Next, Tail... >
  {
    using type = impl< Head, Next, Tail... >;
  };

  // TODO(mattcalabrese) Exploit empty-base optimization
  template< class Head, class Next, class... Tail >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( PotentiallyInvocableObject< Head > );

    using rest_type = typename impl_of< Next, Tail... >::type;

    // TODO(mattcalabrese) Conditional noexcept
    template< class T
            , ARGOT_REQUIRES( Composable< T&&, Head, Next, Tail... > )()
            >
    constexpr decltype( auto ) operator ()( T&& arg ) &&
    {
      // TODO(mattcalabrese) Inline the void_to_regular_void_invoke manually.
      //                     That will reduce stack depth in backtraces.
      return (regular_void_to_void_invoke)
      ( ARGOT_MOVE( rest )
      , (void_to_regular_void_invoke)
        ( ARGOT_MOVE( head ), ARGOT_FORWARD( T )( arg ) )
      );
    }

    // TODO(mattcalabrese) Conditional noexcept
    // TODO(mattcalabrese)
    //   Possibly handle this via an implicit conversion trick so that there is
    //   only one overload in error messages.
    //   (may not be possible; only a vague idea).
    template< class T
            , ARGOT_REQUIRES
              ( PersistentComposable< T&&, Head, Next, Tail... > )()
            >
    constexpr decltype( auto ) operator ()( T&& arg ) const&
    {
      // TODO(mattcalabrese) Inline the void_to_regular_void_invoke manually.
      //                     That will reduce stack depth in backtraces.
      return (regular_void_to_void_invoke)
      ( rest
      , (void_to_regular_void_invoke)( head, ARGOT_FORWARD( T )( arg ) )
      );
    }

    ARGOT_NO_UNIQUE_ADDRESS Head head;
    ARGOT_NO_UNIQUE_ADDRESS rest_type rest;
  };

  template< class Transformation >
  static constexpr std::decay_t< Transformation >
  make_impl( Transformation&& transformation )
  {
    return ARGOT_FORWARD( Transformation )( transformation );
  }

  template
  < class HeadTransformation, class NextTransformation
  , class... TailTransformations
  >
  static constexpr typename impl_of
  < std::decay_t< HeadTransformation >
  , std::decay_t< NextTransformation >
  , std::decay_t< TailTransformations >...
  >::type
  make_impl
  ( HeadTransformation&& head_transformation
  , NextTransformation&& next_transformation
  , TailTransformations&&... tail_transformations
  )
  {
    return
    { ARGOT_FORWARD( HeadTransformation )( head_transformation )
    , make_impl
      ( ARGOT_FORWARD( NextTransformation )( next_transformation )
      , ARGOT_FORWARD( TailTransformations )( tail_transformations )...
      )
    };
  }
 public: //->
  template< class... Transformations
          , ARGOT_REQUIRES
            ( PotentiallyInvocableObject< std::decay_t< Transformations > >... )
            ( DecaySinkable< Transformations&& >... )
            ()
          >
  [[nodiscard]]
  constexpr auto operator()( Transformations&&... transformations ) const//=;
  //<-
  {
    // TODO(mattcalabrese) Possibly change to return by value in this case
    // Make a "referential_compose" for when the terminating case is a
    // referential identity.
    if constexpr( sizeof...( Transformations ) == 0 )
      return referential_identity;
    else
      return make_impl
      ( call_detail::forward_and_decay_sink< Transformations >
        ( transformations )...
      );
  } //->
} inline constexpr compose{};

template< class... Transformations >
using result_of_compose//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< compose_fn const&, Transformations... >; //->

template< class... Transformations >
using result_of_compose_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< compose_fn const&, Transformations... >; //->

} // namespace argot

//]

#endif  // ARGOT_COMPOSE_HPP_
