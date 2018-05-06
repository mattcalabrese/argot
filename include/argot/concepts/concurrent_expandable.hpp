/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_CONCURRENT_EXPANDABLE_HPP_
#define ARGOT_CONCEPTS_CONCURRENT_EXPANDABLE_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/higher_order_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/gen/and.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/requires.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/conditional.hpp>
#include <argot/detail/sink.hpp>
#include <argot/move.hpp>
#include <argot/conc/alternative_of_by_value.hpp>
//#include <argot/conc/squash.hpp>
#include <argot/conc/unpack_by_value.hpp>
#include <argot/conc/when_ready.hpp>
#include <argot/remove_cvref.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/concurrent_expandable.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class T >
ARGOT_EXPLICIT_CONCEPT( ConcurrentExpandable )
(
  Reference< T >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot


#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS
/*
#include <argot/concepts/concurrent_argument_provider.hpp>
#include <argot/concepts/higher_order_concurrent_argument_provider.hpp>
#include <argot/concepts/persistent_concurrent_argument_provider.hpp>
#include <argot/concepts/expandable_concurrent_argument_provider.hpp>
#include <argot/concepts/persistent_expandable_concurrent_argument_provider.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/concepts/concurrent_expandable/detail/default_to_expand_arguments_to.hpp>
*/
#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {

// TODO(mattcalabrese) Use base-class trick like arg provider bases
template< class Tup >
struct make_concept_map
< ConcurrentExpandable< Tup >
, ARGOT_REQUIRES( Reference< Tup > )
                ( TupleLike< remove_cvref_t< Tup > > )
                ( Sinkable< Tup&& > )
                <>
>
{
  static constexpr auto expand( Tup&& tup )
  {
    return conc::unpack_by_value( ARGOT_FORWARD( Tup )( tup ) );
  }
};

// TODO(mattcalabrese) Use base-class trick like arg provider bases
template< class Var >
struct make_concept_map
< ConcurrentExpandable< Var >
, ARGOT_REQUIRES( Reference< Var > )
                ( VariantLike< remove_cvref_t< Var > > )
                ( Sinkable< Var&& > )
                <>
>
{
  static constexpr auto expand( Var&& var )
  {
    return conc::alternative_of_by_value( ARGOT_FORWARD( Var )( var ) );
  }
};

template< class Fut >
struct make_concept_map
< ConcurrentExpandable< Fut >
, ARGOT_REQUIRES( Reference< Fut > )
                ( Future< remove_cvref_t< Fut > > )
                ( Sinkable< Fut&& > )
                <>
>
{
  static constexpr auto expand( Fut&& fut )
  {
    return conc::when_ready( ARGOT_FORWARD( Fut )( fut ) );
  }
};

namespace detail_concurrent_expand_concept_map {
/*
template< class Provider >
struct higher_order_impl
{
  ARGOT_CONCEPT_ASSERT( ExpandableConcurrentArgumentProvider< Provider > );

  ARGOT_NO_UNIQUE_ADDRESS Provider provider;
};

template< class Provider >
struct higher_order_concept_map_move_base
{
  ARGOT_CONCEPT_ASSERT( ExpandableConcurrentArgumentProvider< Provider > );

  static constexpr auto expand( Provider&& provider )
  {
    if constexpr( std::is_same_v< Provider, conc::nothing_t > )
      return conc::nothing;
    else
      if constexpr
      ( ARGOT_IS_MODELED( HigherOrderConcurrentArgumentProvider< Provider > ) )
        if constexpr( conc::value_of_fn::is_unary_value_of_v< Provider > )
          return conc::value_of_fn::head_value
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
  ARGOT_CONCEPT_ASSERT( ExpandableConcurrentArgumentProvider< Provider > );

  static constexpr auto expand( Provider const& provider )
  {
    if constexpr( std::is_same_v< Provider, conc::nothing_t > )
      return conc::nothing;
    else
      if constexpr
      ( ARGOT_IS_MODELED( HigherOrderConcurrentArgumentProvider< Provider > ) )
        if constexpr( conc::value_of_fn::is_unary_value_of_v< Provider > )
          return conc::value_of_fn::head_value( provider );
        else
          return higher_order_impl< Provider >{ provider };
      else
        return higher_order_impl< Provider >{ provider };
  }
};
*/
} // namespace argot(::detail_concurrent_expand_concept_map)
/*
template< class Provider >
struct make_concept_map
< ConcurrentExpandable< Provider >
, ARGOT_REQUIRES
  ( Reference< Provider > )
  ( HigherOrderConcurrentArgumentProvider< remove_cvref_t< Provider > > )
  ( Or
    < SameType
      < call_detail::result_of_sinklike_cast_t< Provider >
      , remove_cvref_t< Provider >&
      >
    , And
      < HigherOrderPersistentConcurrentArgumentProvider
        < remove_cvref_t< Provider > >
      , SameType
        < call_detail::result_of_sinklike_cast_t< Provider >
        , remove_cvref_t< Provider > const&
        >
      >
    >
  )
  <>
> : argot_detail::conditional
    < is_modeled_v
      < SameType
        < call_detail::result_of_sinklike_cast_t< Provider >
        , remove_cvref_t< Provider >&
        >
      >
    >::template meta_apply
    < detail_concurrent_expand_concept_map::argument_provider_concept_map_base
    , detail_concurrent_expand_concept_map
      ::persistent_argument_provider_concept_map_base
    , remove_cvref_t< Provider >
    >
{
};
*/
}  // namespace argot

#endif  // ARGOT_CONCEPTS_CONCURRENT_EXPANDABLE_HPP_
