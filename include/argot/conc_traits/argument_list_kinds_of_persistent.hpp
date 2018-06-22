/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
#define ARGOT_CONC_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_

#include <argot/conc_traits/as_future.hpp>
#include <argot/concepts/persistent_concurrent_argument_provider.hpp>
#include <argot/concepts/persistent_then_providable.hpp>
#include <argot/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/prov_traits/argument_list_kinds_of.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <type_traits>
#include <utility>

namespace argot::conc_traits {

#if 0

namespace argument_list_kinds_of_persistent_detail {

template< class Provider >
using explicit_argument_list_kinds_of_t
  = typename access_raw_concept_map
    < PersistentConcurrentArgumentProvider< Provider > >
    ::argument_list_kinds_of_persistent_t;

using dummy_packager
  = argument_list_kinds_of_destructive_detail::dummy_packager;

template< class Provider >
struct deduce_argument_list_kinds_of
{
 private:
  using detected_result_type
    = fut_traits::value_type_t
      < decltype
        ( access_raw_concept_map
          < PersistentThenProvidable
            < Provider, dummy_packager, executor::immediate_t >
          >::template then_provide< dummy_packager >
          ( ARGOT_DECLVAL( Provider const& )
          , ARGOT_DECLVAL( executor::immediate_t )
          , ARGOT_DECLVAL( receiver::result_of_return_argument_list_kinds_t )
          )
        )
      >;
 public:
  using type
    = typename argot_detail::conditional
      < std::is_same_v< detected_result_type, impossible > >
      ::template apply
      < receiver_traits::argument_list_kinds_t<>
      , detected_result_type
      >;
};

}  // namespace argot::conc_traits(::argument_list_kinds_of_persistent_detail)

template< class Provider >
using argument_list_kinds_of_persistent_t
  = ARGOT_REQUIRES( PersistentConcurrentArgumentProvider< Provider > )
    < typename argot_detail::conditional
      < call_detail::is_detected_v
        < argument_list_kinds_of_persistent_detail
          ::explicit_argument_list_kinds_of_t
        , Provider
        >
      >::template apply
      < call_detail::lazy_expand
        < argument_list_kinds_of_persistent_detail
          ::explicit_argument_list_kinds_of_t
        , Provider
        >
      , argument_list_kinds_of_persistent_detail
        ::deduce_argument_list_kinds_of< Provider >
      >::type
    >;

template< class Provider >
using argument_list_kinds_of_persistent
  = call_detail::lazy_expand< argument_list_kinds_of_persistent_t, Provider >;

template< class Provider >
argument_list_kinds_of_persistent_t< Provider > constexpr
argument_list_kinds_of_persistent_v{};

#else


template< class ConcProvider >
using argument_list_kinds_of_persistent_t
  = ARGOT_REQUIRES( PersistentConcurrentArgumentProvider< ConcProvider > )
    < prov_traits::argument_list_kinds_of_t
      < result_of_as_future_t< ConcProvider const& > >
    >;

template< class ConcProvider >
using argument_list_kinds_of_persistent
  = call_detail::lazy_expand
    < argument_list_kinds_of_persistent_t, ConcProvider >;

template< class ConcProvider >
argument_list_kinds_of_persistent_t< ConcProvider > constexpr
argument_list_kinds_of_persistent_v{};

#endif

}  // namespace (argot::conc_traits)

#endif  // ARGOT_CONC_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
