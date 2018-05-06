/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
#define ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_

#include <argot/impossible.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <type_traits>
#include <utility>

namespace argot::prov_traits {
namespace argument_list_kinds_of_persistent_detail {

template< class Provider >
using explicit_argument_list_kinds_of_t
  = typename access_raw_concept_map< PersistentArgumentProvider< Provider > >
    ::argument_list_kinds_of_persistent_t;

template< class Provider >
struct deduce_argument_list_kinds_of
{
 private:
  using detected_result_type
    = decltype
      ( access_raw_concept_map< PersistentArgumentProvider< Provider > >
        ::provide
        ( ARGOT_DECLVAL( Provider const& )
        , ARGOT_DECLVAL( receiver::result_of_return_argument_list_kinds_t )
        )
      );
 public:
  using type
    = typename argot_detail::conditional
      < std::is_same_v< detected_result_type, impossible > >
      ::template apply
      < receiver_traits::argument_list_kinds_t<>
      , detected_result_type
      >;
};

}  // namespace argot::prov_traits(::argument_list_kinds_of_persistent_detail)

template< class Provider >
using argument_list_kinds_of_persistent_t
  = ARGOT_REQUIRES( PersistentArgumentProvider< Provider > )
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

}  // namespace (argot::prov_traits)

#endif  // ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
