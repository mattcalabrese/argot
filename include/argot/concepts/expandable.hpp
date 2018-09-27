/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_EXPANDABLE_HPP_
#define ARGOT_CONCEPTS_EXPANDABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/gen/explicit_concept.hpp>

//[description
/*`
Expandable is an [argot_gen_concept] that is satisfied by reference types for
which there is a reasonable associated default ArgumentProvider, which is
returned from an associated function of Expandable called `expand`. The
associated `expand` function is used when invoking prov::expand or when using
the [expansion_operator]. Users are encouraged to model this concept explicitly
in order to be usable with prov::expand and the [expansion_operator].

Type categories that are automatically considered to be Expandable are:

[table:expansions Expansions
 [[Category][Expands to]]
 [[TupleLike][prov::unpack(arg)]]
 [[VariantLike][prov::alternative_of(arg)]]
 [[HigherOrderArgumentProvider][TODO(mattcalabrese) Describe]]
 [[ExpandableArgumentProvider][TODO(mattcalabrese) Describe]]
]
*/
//]

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/expandable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( Expandable )
(
  Reference< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/expandable/detail/default_to_expand_arguments_to.hpp>
#include <argot/concepts/higher_order_argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/expandable_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/alternative_of.hpp>
#include <argot/prov/unpack.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/detail/remove_cvref.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

template< class Tup >
struct make_concept_map
< Expandable< Tup >
, ARGOT_REQUIRES( Reference< Tup > )
                ( TupleLike< detail_argot::remove_cvref_t< Tup > > )
                <>
>
{
  static constexpr auto expand( Tup&& tup )
  {
    return prov::unpack( ARGOT_FORWARD( Tup )( tup ) );
  }
};

template< class Var >
struct make_concept_map
< Expandable< Var >
, ARGOT_REQUIRES( Reference< Var > )
                ( VariantLike< detail_argot::remove_cvref_t< Var > > )
                <>
>
{
  static constexpr auto expand( Var&& var )
  {
    return prov::alternative_of( ARGOT_FORWARD( Var )( var ) );
  }
};

namespace detail_expand_concept_map {

template< class Provider >
struct higher_order_impl
{
  ARGOT_CONCEPT_ASSERT( ExpandableArgumentProvider< Provider > );

  ARGOT_NO_UNIQUE_ADDRESS Provider provider;
};

template< class Provider >
struct higher_order_concept_map_move_base
{
  ARGOT_CONCEPT_ASSERT( ExpandableArgumentProvider< Provider > );

  static constexpr auto expand( Provider&& provider )
  {
    if constexpr( std::is_same_v< Provider, prov::nothing_t > )
      return prov::nothing;
    else
      if constexpr
      ( ARGOT_IS_MODELED( HigherOrderArgumentProvider< Provider > ) )
        if constexpr( prov::value_of_fn::is_unary_value_of_v< Provider > )
          return prov::value_of_fn::head_value
          ( ARGOT_MOVE( provider ) );
        else
          return higher_order_impl< Provider >{ ARGOT_MOVE( provider ) };
      else
        return higher_order_impl< Provider >{ ARGOT_MOVE( provider ) };
  }
};

template< class Provider >
struct higher_order_concept_map_copy_base
{
  ARGOT_CONCEPT_ASSERT( ExpandableArgumentProvider< Provider > );

  static constexpr auto expand( Provider const& provider )
  {
    if constexpr( std::is_same_v< Provider, prov::nothing_t > )
      return prov::nothing;
    else
      if constexpr
      ( ARGOT_IS_MODELED( HigherOrderArgumentProvider< Provider > ) )
        if constexpr( prov::value_of_fn::is_unary_value_of_v< Provider > )
          return prov::value_of_fn::head_value( provider );
        else
          return higher_order_impl< Provider >{ provider };
      else
        return higher_order_impl< Provider >{ provider };
  }
};

} // namespace argot(::detail_expand_concept_map)

// TODO(mattcalabrese) Require sinkability of nested expandable/provider.
template< class Provider >
struct make_concept_map
< Expandable< Provider >
, ARGOT_REQUIRES
  ( Reference< Provider > )
  ( ExpandableArgumentProvider< detail_argot::remove_cvref_t< Provider > > )
  ( Sinkable< Provider > )
  <>
> : argot_detail::conditional
    < ARGOT_IS_MODELED
      ( SameType
        < call_detail::result_of_sinklike_cast_t< Provider >
        , detail_argot::remove_cvref_t< Provider >&&
        >
      )
    >::template meta_apply
    < detail_expand_concept_map::higher_order_concept_map_move_base
    , detail_expand_concept_map::higher_order_concept_map_copy_base
    , detail_argot::remove_cvref_t< Provider >
    >
{
};

template< class Provider >
struct make_concept_map
< ArgumentProvider< detail_expand_concept_map::higher_order_impl< Provider > > >
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
  provide( detail_expand_concept_map::higher_order_impl< Provider >&& self
         , Receiver&& rec
         )
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.provider )
    , detail_expandable::default_to_expand_arguments_to
      ( receiver::receiver_reference( ARGOT_MOVE( rec ) ) )
    );
  }
};

} // namespace argot

#include <argot/concepts/persistent_expandable_argument_provider.hpp>

#endif  // ARGOT_CONCEPTS_EXPANDABLE_HPP_
