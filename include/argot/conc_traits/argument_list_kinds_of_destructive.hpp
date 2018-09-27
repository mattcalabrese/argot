/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONC_TRAITS_ARGUMENT_LIST_KINDS_OF_DESTRUCTIVE_HPP_
#define ARGOT_CONC_TRAITS_ARGUMENT_LIST_KINDS_OF_DESTRUCTIVE_HPP_

#include <argot/conc_traits/as_future.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/then_providable.hpp>
#include <argot/detail/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/detection.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/prov_traits/argument_list_kinds_of.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>

#include <type_traits>
#include <utility>

namespace argot::conc_traits {

#if 0

namespace argument_list_kinds_of_destructive_detail {

template< class Provider >
using explicit_argument_list_kinds_of_t
  = typename access_raw_concept_map< ConcurrentArgumentProvider< Provider > >
    ::argument_list_kinds_of_destructive_t;

struct dummy_function
{
  template< class... P >
  constexpr void operator ()( P&&... ) const noexcept {}
};

struct dummy_packager {};

template< class Provider >
struct deduce_argument_list_kinds_of
{
 private:
  using detected_result_type
    = fut_traits::value_type_t
      < decltype
        ( access_raw_concept_map
          < ThenProvidable< Provider, dummy_packager, executor::immediate_t > >
          ::template then_provide< dummy_packager >
          ( ARGOT_DECLVAL( Provider&& )
          , ARGOT_DECLVAL( executor::immediate_t )
          , ARGOT_DECLVAL( receiver::result_of_return_argument_list_kinds_t&& )
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

} // namespace argot::conc_traits(::argument_list_kinds_of_destructive_detail)

template< class Provider >
using argument_list_kinds_of_destructive_t
  = ARGOT_REQUIRES( ConcurrentArgumentProvider< Provider > )
    < typename argot_detail::conditional
      < call_detail::is_detected_v
        < argument_list_kinds_of_destructive_detail
          ::explicit_argument_list_kinds_of_t
        , Provider
        >
      >::template apply
      < call_detail::lazy_expand
        < argument_list_kinds_of_destructive_detail
          ::explicit_argument_list_kinds_of_t
        , Provider
        >
      , argument_list_kinds_of_destructive_detail
        ::deduce_argument_list_kinds_of< Provider >
      >::type
    >;

template< class Provider >
using argument_list_kinds_of_destructive
  = call_detail::lazy_expand< argument_list_kinds_of_destructive_t, Provider >;

template< class Provider >
argument_list_kinds_of_destructive_t< Provider > constexpr
argument_list_kinds_of_destructive_v{};

} // namespace argot(::conc_traits)

template<>
struct make_concept_map
< FuturePackager
  < conc_traits::argument_list_kinds_of_destructive_detail::dummy_packager >
>
{
  // TODO(mattcalabrese) Don't use pair
  template< class... P, class Exec, class Fun >
  static constexpr std::pair
  < conc_traits::argument_list_kinds_of_destructive_detail::dummy_function
  , ready_fn::impl< basic_result_of_t< detail_argot::remove_cvref_t< Fun >&&, P&&... > >
  >
  package( Exec&& exec, Fun&& fun ) noexcept
  {
    return {};
  }
};

#else

template< class ConcProvider >
using argument_list_kinds_of_destructive_t
  = ARGOT_REQUIRES( ConcurrentArgumentProvider< ConcProvider > )
    < prov_traits::argument_list_kinds_of_t
      < result_of_as_future_t< ConcProvider&& > >
    >;

template< class ConcProvider >
using argument_list_kinds_of_destructive
  = call_detail::lazy_expand
    < argument_list_kinds_of_destructive_t, ConcProvider >;

template< class ConcProvider >
argument_list_kinds_of_destructive_t< ConcProvider > constexpr
argument_list_kinds_of_destructive_v{};

#endif

} // namespace (argot::conc_traits)

#endif  // ARGOT_CONC_TRAITS_ARGUMENT_LIST_KINDS_OF_DESTRUCTIVE_HPP_
