/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_PARTITIONED_PROVIDER_TYPES_HPP_
#define ARGOT_RECEIVER_TRAITS_PARTITIONED_PROVIDER_TYPES_HPP_

#if 0

#include <argot/receiver_traits/provider_types.hpp>
#include <argot/zipper.hpp>

#include <cstddef>
#include <type_traits>

namespace argot::receiver_traits {

template< class HeadProviders, class ThisProvider, class TailProviders >
using partitioned_provider_types
  = zipper< HeadProviders, ThisProvider, TailProviders >;

template< class Providers >
using partition_begin_t = zipper_begin_t< Providers >;

template< class Providers >
using partition_begin = zipper_begin< Providers >;

template< class Providers >
using partition_end_t = zipper_end_t< Providers >;

template< class Providers >
using partition_end = zipper_end< Providers >;

template< class PartitionedProviders >
using partition_next_t = zipper_next_t< PartitionedProviders >;

template< class PartitionedProviders >
using partition_next = zipper_next< PartitionedProviders >;

template< class Providers, std::size_t I >
using nth_partition_t = zipper_at_t< Providers, I >;

template< class Providers, std::size_t I >
using nth_partition = zipper_at< Providers, I >;

template< class PartitionedProviders, std::ptrdiff_t Offset >
using partition_advance_t = zipper_advance_t< PartitionedProviders, Offset >;

template< class PartitionedProviders, std::ptrdiff_t Offset >
using partition_advance = zipper_advance< PartitionedProviders, Offset >;

template< class PartitionedProviders >
using partition_previous_t = zipper_previous_t< PartitionedProviders >;

template< class PartitionedProviders >
using partition_previous = zipper_previous< PartitionedProviders >;

}  // namespace (argot::receiver_traits)

#endif

#endif  // ARGOT_RECEIVER_TRAITS_PARTITIONED_PROVIDER_TYPES_HPP_
