/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_TRAITS_PARTITIONED_ARGUMENT_LIST_KINDS_HPP_
#define ARGOT_RECEIVER_TRAITS_PARTITIONED_ARGUMENT_LIST_KINDS_HPP_

#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <cstddef>
#include <type_traits>

namespace argot {
namespace receiver_traits {

template< class HeadLists, class ThisList, class TailLists >
struct partitioned_argument_list_kinds;

template< class... HeadLists, class... P, class... TailLists >
struct partitioned_argument_list_kinds
< argument_list_kinds_t< HeadLists... >
, argument_types_t< P... >
, argument_list_kinds_t< TailLists... >
>
{
  using all_argument_list_kinds_t
    = all_argument_list_kinds< HeadLists..., ThisList, TailLists... >;
  using index_t
    = std::integral_constant< std::size_t, sizeof...( HeadLists ) >;
  using head_argument_list_kinds_t = argument_list_kinds_t< HeadLists... >;
  using this_argument_list = argument_types_t< P... >;
  using tail_argument_list_kinds_t = argument_list_kinds_t< TailLists... >;

  static head_argument_list_kinds_t constexpr head_argument_list_kinds{};
  static tail_argument_list_kinds_t constexpr tail_argument_list_kinds{};

  static bool constexpr is_end = false;
};

// TODO(mattcalabrese) This should fail substitution, not be undefined.
template< class ArgumentListKinds >
struct partition_end_t;

template< class... ArgumentListKinds >
struct partition_end_t< argument_list_kinds_t< ArgumentListKinds... > >
{
  using all_argument_list_kinds_t
    = argument_list_kinds_t< ArgumentListKinds... >;
  using index_t
    = std::integral_constant< std::size_t, sizeof...( ArgumentListKinds ) >;
  static bool constexpr is_end = true;
};

template< class ArgumentListKinds >
struct partition_end {};

template< class... ArgumentListKinds >
struct partition_end< argument_list_kinds_t< ArgumentListKinds... > >
{
  using type
    = partition_end_t< argument_list_kinds_t< ArgumentListKinds... > >;
};

template< class ArgumentListKinds >
struct partition_begin {};

template< class HeadArgumentListKind, class... TailArgumentListKinds >
struct partition_begin
< argument_list_kinds_t< HeadArgumentListKind, TailArgumentListKinds... > >
{
  using type
    = partitioned_argument_list_kinds
      < argument_list_kinds_t<>
      , HeadArgumentListKind
      , argument_list_kinds_t< TailArgumentListKinds... >
      >;
};

template<>
struct partition_begin< argument_list_kinds_t<> >
{
  using type = partition_end_t< argument_list_kinds_t<> >;
};

template< class ArgumentListKinds >
using partition_begin_t
  = typename partition_begin< ArgumentListKinds >::type;

template< class PartitionedArgumentListKinds >
struct partition_next {};

template< class... HeadArgumentListKinds, class ThisArgumentList
        , class HeadTailArgumentListKinds, class... TailTailArgumentListKinds
        >
struct partition_next
< partitioned_argument_list_kinds
  < argument_list_kinds_t< HeadArgumentListKinds... >
  , ThisArgumentList
  , argument_list_kinds_t
    < HeadTailArgumentListKinds, TailTailArgumentListKinds... >
  >
>
{
  using type
    = partitioned_argument_list_kinds
      < argument_list_kinds_t< HeadTailArgumentListKinds..., ThisArgumentList >
      , HeadTailArgumentListKinds
      , argument_list_kinds_t< TailTailArgumentListKinds... >
      >;
};

template< class... HeadArgumentListKinds, class ThisArgumentList >
struct partition_next
< partitioned_argument_list_kinds
  < argument_list_kinds_t< HeadArgumentListKinds... >
  , ThisArgumentList
  , argument_list_kinds_t<>
  >
>
{
  using type
    = partition_end_t
      < argument_list_kinds_t< HeadArgumentListKinds..., ThisArgumentList > >;
};

template< class PartitionedArgumentLists >
using partition_next_t
  = typename partition_next< PartitionedArgumentLists >::type;

template< class ArgumentListKinds, std::size_t I >
struct nth_partition {};

template< class... ArgumentListKinds >
struct nth_partition< argument_list_kinds_t< ArgumentListKinds... >, 0 >
{
  using type
    = typename partition_begin
      < argument_list_kinds_t< ArgumentListKinds... > >::type;
};

// TODO(mattcalabrese) SFINAE
template< class... ArgumentListKinds, std::size_t I >
struct nth_partition< argument_list_kinds_t< ArgumentListKinds... >, I >
{
  using type
    = typename partition_next
      < typename nth_partition
        < argument_list_kinds_t< ArgumentListKinds... >, I - 1 >::type
      >::type;
};

template< class ArgumentListKinds, std::size_t I >
using nth_partition_t
  = typename nth_partition< ArgumentListKinds, I >::type;

// TODO(mattcalabrese) SFINAE
template< class PartitionedArgumentListKinds, std::ptrdiff_t Offset >
struct partition_advance
{
  using type
    = nth_partition_t
      < typename PartitionedArgumentListKinds::all_argument_list_kinds_t
      , PartitionedArgumentListKinds::index_t::value + Offset
      >;
};

template< class PartitionedArgumentListKinds, std::ptrdiff_t Offset >
using partition_advance_t
  = typename partition_advance< PartitionedArgumentListKinds, Offset >::type;

template< class PartitionedArgumentListKinds >
struct partition_previous {};

// TODO(mattcalabrese) Specialize the end case
template< class HeadHeadArgumentListKinds, class... TailHeadArgumentListKinds
        , class ThisArgumentList
        , class... TailArgumentListKinds
        >
struct partition_previous
< partitioned_argument_list_kinds
  < argument_list_kinds_t
    < HeadHeadArgumentListKinds, TailHeadArgumentListKinds... >
  , ThisArgumentList
  , argument_list_kinds_t< TailArgumentListKinds... >
  >
>
{
  using type
    = nth_partition_t
      < argument_list_kinds_t
        < HeadHeadArgumentListKinds, TailHeadArgumentListKinds...
        , ThisArgumentList
        , TailArgumentListKinds...
        >
      , sizeof...( TailHeadArgumentListKinds )
      >;
};

template< class ArgumentListKinds >
using partition_previous_t
  = typename partition_previous< ArgumentListKinds >::type;

}  // namespace argot::receiver_traits
}  // namespace argot

#endif  // ARGOT_RECEIVER_TRAITS_PARTITIONED_ARGUMENT_LIST_KINDS_HPP_
