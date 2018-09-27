/*==============================================================================
  Copyright (c) 2016 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef CALL_EXAMPLE_MACROS_HPP_
#define CALL_EXAMPLE_MACROS_HPP_

// #include <argot/prov_traits/provide.hpp>
// #include <argot/receiver/graphviz_dot.hpp>

#define namespaceQ boost_ext

#define synopsis_access_tuple_tQ synopsis_access_tuple_t
#define synopsis_access_union_tQ synopsis_access_union_t
#define synopsis_access_variant_tQ synopsis_access_variant_t
#define synopsis_active_alternative_of_tQ synopsis_active_alternative_of_t
#define synopsis_bind_call_tQ synopsis_bind_call_t
#define synopsis_bind_transform_tQ synopsis_bind_transform_t
#define synopsis_call_tQ synopsis_call_t
#define synopsis_compose_tQ synopsis_compose_t
#define synopsis_conditional_tQ synopsis_conditional_t
#define synopsis_constant_variant_index_of_tQ synopsis_constant_variant_index_of_t
#define synopsis_deep_provide_tQ synopsis_deep_provide_t
#define synopsis_default_to_reference_to_tQ synopsis_default_to_reference_to_t
#define synopsis_default_to_value_of_tQ synopsis_default_to_value_of_t
#define synopsis_eat_tQ synopsis_eat_t
#define synopsis_for_tQ synopsis_for_t
#define synopsis_group_tQ synopsis_group_t
#define synopsis_if_tQ synopsis_if_t
#define synopsis_nothing_tQ synopsis_nothing_t
#define synopsis_reference_to_tQ synopsis_reference_to_t
#define synopsis_switch_tQ synopsis_switch_t
#define synopsis_transform_tQ synopsis_transform_t
#define synopsis_bool_tQ synopsis_bool_t
#define synopsis_to_constant_in_range_tQ synopsis_to_constant_in_range_t
#define synopsis_to_constant_tuple_index_tQ synopsis_to_constant_tuple_index_t
#define synopsis_to_constant_union_index_tQ synopsis_to_constant_union_index_t
#define synopsis_to_constant_variant_index_tQ synopsis_to_constant_variant_index_t
#define synopsis_tuple_indices_tQ synopsis_tuple_indices_t
#define synopsis_union_indices_tQ synopsis_union_indices_t
#define synopsis_unpack_tQ synopsis_unpack_t
#define synopsis_unpack_integer_sequence_tQ synopsis_unpack_integer_sequence_t
#define synopsis_value_of_tQ synopsis_value_of_t
#define synopsis_variant_indices_tQ synopsis_variant_indices_t

#define synopsis_access_tupleQ synopsis_access_tuple
#define synopsis_access_unionQ synopsis_access_union
#define synopsis_access_variantQ synopsis_access_variant
#define synopsis_active_alternative_ofQ synopsis_active_alternative_of
#define synopsis_bind_callQ synopsis_bind_call
#define synopsis_bind_transformQ synopsis_bind_transform
#define synopsis_callQ synopsis_call
#define synopsis_composeQ synopsis_compose
#define synopsis_conditionalQ synopsis_conditional
#define synopsis_constant_variant_index_ofQ synopsis_constant_variant_index_of
#define synopsis_deep_provideQ synopsis_deep_provide
#define synopsis_default_to_reference_toQ synopsis_default_to_reference_to
#define synopsis_default_to_value_ofQ synopsis_default_to_value_of
#define synopsis_eatQ synopsis_eat
#define synopsis_for_Q synopsis_for_
#define synopsis_groupQ synopsis_group
#define synopsis_if_Q synopsis_if_
#define synopsis_nothingQ synopsis_nothing
#define synopsis_reference_toQ synopsis_reference_to
#define synopsis_switch_Q synopsis_switch_
#define synopsis_transformQ synopsis_transform
#define synopsis_boolQ synopsis_bool
#define synopsis_to_constant_in_rangeQ synopsis_to_constant_in_range
#define synopsis_to_constant_tuple_indexQ synopsis_to_constant_tuple_index
#define synopsis_to_constant_union_indexQ synopsis_to_constant_union_index
#define synopsis_to_constant_variant_indexQ synopsis_to_constant_variant_index
#define synopsis_tuple_indicesQ synopsis_tuple_indices
#define synopsis_union_indicesQ synopsis_union_indices
#define synopsis_unpackQ synopsis_unpack
#define synopsis_unpack_integer_sequenceQ synopsis_unpack_integer_sequence
#define synopsis_value_ofQ synopsis_value_of
#define synopsis_variant_indicesQ synopsis_variant_indices

#define callQ call
#define qualified_callQ argot::call

#define prov_access_tupleQ prov::access_tuple
#define prov_access_unionQ prov::access_union
#define prov_access_variantQ prov::access_variant
#define prov_active_alternative_ofQ prov::active_alternative_of
#define prov_bind_provisionQ prov::bind_provision
#define prov_bind_callQ prov::bind_call
#define prov_bind_transformQ prov::bind_transform
#define prov_composeQ prov::compose
#define prov_conditionalQ prov::conditional
#define prov_constant_variant_index_ofQ prov::constant_variant_index_of
#define prov_deep_provideQ prov::deep_provide
#define prov_default_to_reference_toQ prov::default_to_reference_to
#define prov_default_to_value_ofQ prov::default_to_value_of
#define prov_eatQ prov::eat
#define prov_for_Q prov::for_
#define prov_groupQ prov::group
#define prov_if_Q prov::if_
#define prov_nothingQ prov::nothing
#define prov_reference_toQ prov::reference_to
#define prov_switch_Q prov::switch_
#define prov_transformQ prov::transform
#define prov_boolQ prov::bool_
#define prov_to_constant_in_rangeQ prov::to_constant_in_range
#define prov_to_constant_tuple_indexQ prov::to_constant_tuple_index
#define prov_to_constant_union_indexQ prov::to_constant_union_index
#define prov_to_constant_variant_indexQ prov::to_constant_variant_index
#define prov_tuple_indicesQ prov::tuple_indices
#define prov_union_indicesQ prov::union_indices
#define prov_unpackQ prov::unpack
#define prov_unpack_integer_sequenceQ prov::unpack_integer_sequence
#define prov_value_ofQ prov::value_of
#define prov_variant_indicesQ prov::variant_indices

#define prov_traits_provideQ prov_traits::provide

#define receiver_traits_result_of_receive_tQ receiver_traits::result_of_receive_t
#define receiver_traits_receiveQ receiver_traits::receive


#define rvr_always_returnQ rvr::always_return
#define rvr_provide_result_toQ rvr::provide_result_to
#define rvr_return_boost_variantQ rvr::return_boost_variant

#define rvr_traits_is_homogeneousQ rvr_traits::is_homogeneous
#define rvr_traits_is_homogeneous_vQ rvr_traits::is_homogeneous_v

#define access_tuple_tQ example_access_tuple_t
#define access_union_tQ example_access_union_t
#define access_variant_tQ example_access_variant_t
#define active_alternative_of_tQ example_active_alternative_of_t
#define bind_provision_tQ example_bind_provision_t
#define compose_tQ example_compose_t
#define conditional_tQ example_conditional_t
#define constant_variant_index_of_tQ example_constant_variant_index_of_t
#define deep_provide_tQ example_deep_provide_t
#define default_to_reference_to_tQ example_default_to_reference_to_t
#define default_to_value_of_tQ example_default_to_value_of_t
#define eat_tQ example_eat_t
#define for_tQ example_for_t
#define group_tQ example_group_t
#define if_tQ example_if_t
#define nothing_tQ example_nothing_t
#define reference_to_tQ example_reference_to_t
#define switch_tQ example_switch_t
#define transform_tQ example_transform_t
#define bool_tQ example_bool_t
#define to_constant_in_range_tQ example_to_constant_in_range_t
#define to_constant_tuple_index_tQ example_to_constant_tuple_index_t
#define to_constant_union_index_tQ example_to_constant_union_index_t
#define to_constant_variant_index_tQ example_to_constant_variant_index_t
#define tuple_indices_tQ example_tuple_indices_t
#define union_indices_tQ example_union_indices_t
#define unpack_tQ example_unpack_t
#define unpack_integer_sequence_tQ example_unpack_integer_sequence_t
#define value_of_tQ example_value_of_t
#define variant_indices_tQ example_variant_indices_t

#define access_tupleQ example_access_tuple
#define access_unionQ example_access_union
#define access_variantQ example_access_variant
#define active_alternative_ofQ example_active_alternative_of
#define bind_provisionQ example_bind_provision
#define composeQ example_compose
#define conditionalQ example_conditional
#define constant_variant_index_ofQ example_constant_variant_index_of
#define deep_provideQ example_deep_provide
#define default_to_reference_toQ example_default_to_reference_to
#define default_to_value_ofQ example_default_to_value_of
#define eatQ example_eat
#define for_Q example_for_
#define groupQ example_group
#define if_Q example_if_
#define nothingQ example_nothing
#define reference_toQ example_reference_to
#define switch_Q example_switch_
#define transformQ example_transform
#define boolQ example_bool
#define to_constant_in_rangeQ example_to_constant_in_range
#define to_constant_tuple_indexQ example_to_constant_tuple_index
#define to_constant_union_indexQ example_to_constant_union_index
#define to_constant_variant_indexQ example_to_constant_variant_index
#define tuple_indicesQ example_tuple_indices
#define union_indicesQ example_union_indices
#define unpackQ example_unpack
#define unpack_integer_sequenceQ example_unpack_integer_sequence
#define value_ofQ example_value_of
#define variant_indicesQ example_variant_indices

#define for_tQ example_for_t

#define SinkableQ Sinkable
#define SameTypeQ SameType
#define TupleLikeQ TupleLike
#define UnionLikeQ UnionLike
#define VariantLikeQ VariantLike
#define ArgumentProviderQ ArgumentProvider
#define ArgumentReceiverQ ArgumentReceiver
#define ReturnValueReducerQ ReturnValueReducer
#define HigherOrderArgumentProviderQ HigherOrderArgumentProvider

#define unqualify_tQ unqualify_t

#define unspecified_typeQ decltype( auto )
#define unspecified_valueQ 0

#define struct_expositionQ struct

#define ARGOT_TPL_REQUIRES_Q ARGOT_TPL_REQUIRES


#define BOOST_EXT_CALL_DETAIL_PROVISION_GRAPH_EXAMPLE( filename, ... )         \
::boost_ext::prov_traits::provide                                              \
( ::boost_ext::receiver::graphviz_dot                                          \
  < ::boost_ext::receiver::ignore_internal_nodes::yes >( name, #__VA_ARGS__ )  \
, __VA_ARGS__                                                                  \
)

#endif  // CALL_EXAMPLE_MACROS_HPP_
