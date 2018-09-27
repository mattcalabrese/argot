/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OUTPUT_HPP_
#define ARGOT_OUTPUT_HPP_

//[description
/*`
argot::output is a facilty for streaming arguments to an object that supports
`operator <<`. The output function expands ArgumentProviders in a manner similar
to argot::call.
[related_tutorials_heading]
* [unpack_tutorial]
* [visitation_tutorial]
*/
//]

#include <argot/concepts/can_default_to_reference_to.hpp>
#include <argot/concepts/stream_insertable_with_provision.hpp>
#include <argot/detail/forward.hpp>
#include <argot/prov/default_to_reference_to.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/to.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot {
//<-
namespace detail_output {

// A function object that outputs any number of arguments to a stream.
struct impl_fn
{
  template< class Stream, class... P >
  constexpr void operator()( Stream& os, P&&... arg ) const
  {
    // NOTE: This intentionally does not rely of the stream operation returning
    //       a reference to the stream.
    ( static_cast< void >( os << ARGOT_FORWARD( P )( arg ) ), ... );
  }
};

} // namespace argot(::detail_output)
//->

struct output_fn
{
  // TODO(mattcalabrese) Don't depend on result_of_default_to_reference_to_t
  //                     in the requirement specification.
  template< class Stream, class... P
          , ARGOT_REQUIRES
            ( CanDefaultToReferenceTo< P >... )
            ( StreamInsertableWithProvision
              < Stream, prov::result_of_default_to_reference_to_t< P&& > >...
            )
            ()
          >
  constexpr Stream& operator()( Stream& os, P&&... args ) const//=;
  //<-
  {
    ( prov_traits::provide
      ( prov::default_to_reference_to( ARGOT_FORWARD( P )( args ) )
      , receiver::reduced_invoke
        ( reducer::to< void >, detail_output::impl_fn() )
      )
    , ...
    );

    return os;
  } //->
} inline constexpr output{};

} // namespace argot

// TODO(mattcalabrese) Complete the docs

//]

#endif  // ARGOT_OUTPUT_HPP_
