/*==============================================================================
  Copyright (c) 2016, 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
#define ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_

//[description
/*`
prov_traits::argument_list_kinds_of_persistent_t is a template alias that
is a receiver_traits::argument_list_kinds_t instantiation that represents the
possible argument lists that a user-specified PersistentArgumentProvider can
produce when undergoing /persistent provision/.

[note An ArgumentProvider may produce different arguments when undergoing
      /destructive provision/ from when it undergoes /persistent provision/.
      Most frequently this is the case when arguments are passed as rvalues when
      performing destructive provision, but as lvalues when performing
      persistent provision. If you need to check which argument lists may be
      produced from destructive provision, you should use
      prov_traits::argument_list_kinds_of_destructive_t instead.
]
*/
//]

#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov_traits {
//<-
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

} // namespace argot::prov_traits(::argument_list_kinds_of_persistent_detail)
//->

template< class Provider >
using argument_list_kinds_of_persistent_t
  = ARGOT_REQUIRES( PersistentArgumentProvider< Provider > )
    //=< ``[unspecified_type]`` >;
  //<-
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
    >; //->

template< class Provider >
using argument_list_kinds_of_persistent
  = call_detail::lazy_expand< argument_list_kinds_of_persistent_t, Provider >;

template< class Provider >
argument_list_kinds_of_persistent_t< Provider > constexpr
argument_list_kinds_of_persistent_v{};

} // namespace (argot::prov_traits)

//]

#endif  // ARGOT_PROV_TRAITS_ARGUMENT_LIST_KINDS_OF_PERSISTENT_HPP_
