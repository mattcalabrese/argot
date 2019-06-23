/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_EXPANDABLE_ARGUMENT_PROVIDER_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_EXPANDABLE_ARGUMENT_PROVIDER_HPP_

#include <argot/concepts/expandable_argument_provider.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/gen/explicit_concept.hpp>

namespace argot {
namespace persistent_expandable_argument_provider_detail {

template< class Provider >
struct all_provisions_are_expandables;

}

// TODO(mattcalabrese) Implement this purely via the concepts

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_expandable_argument_provider.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Provider >
ARGOT_EXPLICIT_CONCEPT( PersistentExpandableArgumentProvider )
(
  ExpandableArgumentProvider< Provider >/*
, TransparentRequirement
  < expandable_argument_provider_detail::all_provisions_are_providers >*/
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot


#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/detection.hpp>
#include <argot/concepts/expandable.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/persistent_expandable_argument_provider/detail/is_persistent_expandable_argument_provider.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/receiver_reference.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

// TODO(mattcalabrese) Perform each ArgumentProvider check separately in SFINAE
template< class Provider >
struct make_concept_map
< PersistentExpandableArgumentProvider< Provider >
, call_detail::fast_enable_if_t
  < persistent_expandable_argument_provider_detail
    ::is_persistent_expandable_argument_provider_v< Provider >
  >
> {};

template< class Provider >
struct make_concept_map
< PersistentArgumentProvider
  < detail_expand_concept_map::higher_order_impl< Provider > >
, ARGOT_REQUIRES( PersistentExpandableArgumentProvider< Provider > )<>
>
{
  template
  < class Receiver
  /*, ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , detail_expand_arguments_to::expanded_argument_types_t< Provider >
      >
    )
    ()*/ // TODO(mattcalabrese) Fix this requirement
  >
  static constexpr decltype( auto )
  provide( detail_expand_concept_map::higher_order_impl< Provider > const& self
         , Receiver&& rec
         )
  {
    return prov_traits::persistent_provide
    ( self.provider
    , detail_expandable::default_to_expand_arguments_to
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) ) )
    );
  }
};

}  // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_EXPANDABLE_ARGUMENT_PROVIDER_HPP_
