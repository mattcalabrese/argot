/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_UNPACK_BY_VALUE_HPP_
#define ARGOT_PROV_UNPACK_BY_VALUE_HPP_

//[description
/*`
prov::unpack_by_value is used to expand out all of the elements of a TupleLike
type in-place in an argument list.

[note A call to prov::unpack_by_value captures `tup` by value whereas a call to
      prov::unpack captures `tup` by reference. This difference affects not only
      what is captured, but also the qualifiers and value category of each
      argument passed during provision as described below.
]

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/receiver_traits/receive.hpp>
#include <argot/tuple_traits/apply.hpp>

#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

struct unpack_by_value_fn
{
//<-
  template< class Tup >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( TupleLike< Tup > );

// TODO(mattcalabrese) Fill these out
/*
    using lvalue_unpacked_argument_kinds
      =

    using rvalue_unpacked_argument_kinds
      =
*/
    ARGOT_NO_UNIQUE_ADDRESS Tup tup;
  };
 public:
 //->
  template< class Tup
          , ARGOT_REQUIRES
            ( TupleLike< detail_argot::remove_cvref_t< Tup > > )
            ( Sinkable< Tup&& > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( Tup&& tup ) const//=;
  //<-
  {
    return impl< detail_argot::remove_cvref_t< Tup > >
    { ARGOT_FORWARD( Tup )( tup ) };
  } //->
} inline constexpr unpack_by_value{};

template< class Tup >
using result_of_unpack_by_value//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< unpack_by_value_fn const&, Tup >; //->

template< class Tup >
using result_of_unpack_by_value_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< unpack_by_value_fn const&, Tup >; //->

} // namespace (argot::prov)

//<-
namespace argot {

template< class Tup >
struct make_concept_map
< ArgumentProvider< prov::unpack_by_value_fn::impl< Tup > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov::unpack_by_value_fn::impl< Tup >&& self, Receiver&& rec )
  {
    // TODO(calabrese) Hoist the lambda to a detail
    return tuple_traits::apply
    ( [ &rec ]( auto&&... args ) -> decltype( auto )
      {
        // TODO(calabrese) Use raw concept map
        return receiver_traits::receive
        ( ARGOT_FORWARD( Receiver )( rec )
        , ARGOT_FORWARD( decltype( args ) )( args )...
        );
      }
    , ARGOT_FORWARD( Tup )( *self.tup )
    );
  }
};

template< class Tup >
struct make_concept_map
< PersistentArgumentProvider< prov::unpack_by_value_fn::impl< Tup > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov::unpack_by_value_fn::impl< Tup > const& self, Receiver&& rec )
  {
    // TODO(calabrese) Hoist the lambda to a detail
    return tuple_traits::apply
    ( [ &rec ]( auto&&... args ) -> decltype( auto )
      {
        // TODO(calabrese) Use raw concept map
        return receiver_traits::receive
        ( ARGOT_FORWARD( Receiver )( rec )
        , ARGOT_FORWARD( decltype( args ) )( args )...
        );
      }
    , *self.tup
    );
  }
};

} // namespace argot
//->

/*`
[table Parameters
 [[Parameter][Requirement][Description]]
 [[`Tup&& tup`]
  [A Sinkable reference to a possibly-qualified TupleLike type]
  [The TupleLike object whose elements are to be provided
  ]
 ]
]

[provider_properties_heading]

[note In the following tables, assume `i` is a parameter pack of all valid
      /indices/ of `tup` in ascending order.
]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [A reference to each /element/ of `tup`]
 ]
 [[Possible Argument Types of Destructive Provision]
  [[itemized_list [```( tuple_traits::result_of_get_t< i, detail_argot::remove_cvref_t< Tup >&& >... )```]]]
 ]
 [[Possible Argument Types of Persistent Provision]
  [[itemized_list [```( tuple_traits::result_of_get_t< i, detail_argot::remove_cvref_t< Tup > const& >... )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_UNPACK_BY_VALUE_HPP_
