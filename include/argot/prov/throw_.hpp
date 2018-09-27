/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_THROW_HPP_
#define ARGOT_PROV_THROW_HPP_

//[description
/*`
prov::throw_ is used to create an ExceptionalArgumentProvider that throws an
exception during provision.

[global_function_object_template_designator]
*/
//]

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/constructible.hpp>
#include <argot/concepts/constructible_with_kinds.hpp>
#include <argot/concepts/exception.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/reducer/same_type_or_fail.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {
//<-
namespace throw_detail {

template< class Excep, class Provider >
struct throw_impl
{
  ARGOT_CONCEPT_ASSERT( Exception< Excep > );
  ARGOT_CONCEPT_ASSERT( ArgumentProvider< Provider > );
  ARGOT_CONCEPT_ASSERT
  ( ConstructibleWithKinds
    < Excep
    , prov_traits::argument_list_kinds_of_destructive_t< Provider >
    >
  );

  ARGOT_NO_UNIQUE_ADDRESS Provider provider;
};

template< class Excep >
struct throwing_function
{
  ARGOT_CONCEPT_ASSERT( Exception< Excep > );

  template
  < class... P
  , ARGOT_REQUIRES( Constructible< Excep, P&&... > )()
  >
  [[noreturn]] impossible operator()( P&&... args ) const
  {
    throw Excep( ARGOT_FORWARD( P )( args )... );
  }
};

} // namespace argot::prov(::throw_detail)
//->

template< class Excep >
struct throw_fn
{
  //<-
  ARGOT_CONCEPT_ASSERT( Exception< Excep > );
  //->
  template
  < class... P
  , ARGOT_REQUIRES
    ( ArgumentProvider< detail_argot::remove_cvref_t< P > >... )
    ( Sinkable< P&& >... )
    ( ConstructibleWithKinds
      < Excep
      , prov_traits::argument_list_kinds_of_destructive_t
        < prov::result_of_group_t< P&&... > >
      >
    )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( P&&... providers ) const//=;
  //<-
  {
    return throw_detail::throw_impl
    < Excep, result_of_group_t< P&&... > >
    { prov::group( call_detail::forward_and_sink< P >( providers )... ) };
  } //->
};

template< class Excep >
ARGOT_REQUIRES( Exception< Excep > )
< throw_fn< Excep > > constexpr throw_{};

template< class Excep, class... P >
using result_of_throw_//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of< throw_fn< Excep > const&, P... >; //->

template< class Excep, class... P >
using result_of_throw_t//= = ``[see_prologue_result_of]``;
//<-
  = ARGOT_REQUIRES( Exception< Excep > )
    < basic_result_of_t< throw_fn< Excep > const&, P... > >; //->

} // namespace (argot::prov)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class Excep`]
  [An Exception type]
  [The type of the exception to be thrown]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`P&&... providers`]
  [Each type in `P&&...` is a Sinkable reference to a possibly-qualified
   ArgumentProvider
  ]
  [After provision, the arguments to construct the exception as if by direct
   non-list initialization
  ]
 ]
]
*/

//]

namespace argot {

template< class ExceptionType, class Provider >
struct make_concept_map
< ArgumentProvider
  < prov::throw_detail::throw_impl< ExceptionType, Provider > >
>
{
  using argument_list_kinds_of_destructive_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver >
  [[noreturn]] static ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
  < impossible > provide
  ( prov::throw_detail::throw_impl< ExceptionType, Provider >&& self
  , Receiver&& receiver
  )
  {
    // TODO(mattcalabrese) Replace reduced_invoke with invoke
    prov_traits::destructive_provide
    ( ARGOT_MOVE( self.provider )
    , receiver::reduced_invoke
      ( reducer::same_type_or_fail
      , prov::throw_detail::throwing_function< ExceptionType >()
      )
    );

    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< class ExceptionType, class Provider >
struct make_concept_map
< PersistentArgumentProvider
  < prov::throw_detail::throw_impl< ExceptionType, Provider > >
, ARGOT_REQUIRES
  ( ConstructibleWithKinds
    < ExceptionType
    , prov_traits::argument_list_kinds_of_persistent_t< Provider >
    >
  )
  <>
>
{
  using argument_list_kinds_of_persistent_t
    = receiver_traits::argument_list_kinds_t<>;

  template< class Receiver >
  [[noreturn]] static ARGOT_REQUIRES( ArgumentReceiver< Receiver > )
  < impossible > provide
  ( prov::throw_detail::throw_impl< ExceptionType, Provider > const& self
  , Receiver&& receiver
  )
  {
    // TODO(mattcalabrese) Replace reduced_invoke with invoke
    prov_traits::persistent_provide
    ( self.provider
    , receiver::reduced_invoke
      ( reducer::same_type_or_fail
      , prov::throw_detail::throwing_function< ExceptionType >()
      )
    );

    ARGOT_DETAIL_UNREACHABLE();
  }
};

} // namespace argot

#endif  // ARGOT_PROV_THROW_HPP_
