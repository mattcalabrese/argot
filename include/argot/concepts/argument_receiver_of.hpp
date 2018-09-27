/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_HPP_
#define ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_HPP_

//[description
/*`
ArgumentReceiverOf is an [argot_gen_concept] that is satisfied by an
ArgumentReceiver and a compatible series of `receive` argument types.
*/
//]

#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/argument_types.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/instantiation_of.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/valid.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/auto_concept.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/conditional.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <utility>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace argument_receiver_of_detail {

// TODO(mattcalabrese)
//   static_assert that the return types are the same.
//   This is because they can only differ if the concept_map is incorrect.
//   Possibly only do the check in the concept map checker.

struct result_of_raw_receive_impl_no_possibilities
{
  using type = void;
};

template< class Enabler, class Receiver, class... Possibilities >
struct result_of_raw_receive_impl_ {};

template< class Receiver
        , class...  HeadPossibilityArgumentTypes, class... TailPossibilities
        >
struct result_of_raw_receive_impl_
< std::void_t
  < decltype
    ( access_raw_concept_map< ArgumentReceiver< Receiver > >::receive_branch
      ( ARGOT_DECLVAL( Receiver )
      , receiver_traits::argument_list_kinds()
      , receiver_traits::argument_list_kinds( TailPossibilities()... )
      , ARGOT_DECLVAL( HeadPossibilityArgumentTypes&& )...
      )
    )
  >
, Receiver
, receiver_traits::argument_types_t< HeadPossibilityArgumentTypes... >
, TailPossibilities...
>
{
  using type = void;
};

template< class Receiver, class... Possibilities >
struct result_of_raw_receive_impl
  : result_of_raw_receive_impl_< void, Receiver, Possibilities... > {};

template< class Receiver, class... Possibilities >
using result_of_raw_receive_t
  = typename argot_detail::conditional< sizeof...( Possibilities ) == 0 >
    ::template apply
    < result_of_raw_receive_impl_no_possibilities
    , result_of_raw_receive_impl< Receiver, Possibilities... >
    >::type;

} // namespace argot(::argument_receiver_of_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/argument_receiver_of.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Don't unqualify. Require unqualified receiver.
template< class Receiver, class... Possibilities >
ARGOT_AUTO_CONCEPT( ArgumentReceiverOf )
( ArgumentReceiver< Receiver >
, ArgumentTypes< Possibilities >...
, Valid
  < argument_receiver_of_detail::result_of_raw_receive_t
  , Receiver, Possibilities...
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_ARGUMENT_RECEIVER_OF_HPP_
