/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_GENERATE_SWITCH_PROVISION_DEFAULT_DEFINITION_HPP_

#ifndef ARGOT_PREPROCESSING_MODE

#define ARGOT_PROV_SWITCH_DETAIL_GENERATE_SWITCH_PROVISION_DEFAULT_DEFINITION_HPP_

#include <argot/prov/switch_/detail/config.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <argot/concepts/switch_body_default.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/prov/switch_/detail/switch_impl_fwd.hpp>
#include <argot/prov/switch_/detail/switch_provision_base.hpp>
#include <argot/prov/switch_/detail/switch_provision_fwd.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/case_value_for_type_at.hpp>
#include <argot/switch_traits/destructive_provide_case.hpp>
#include <argot/switch_traits/destructive_provide_default.hpp>
#include <argot/switch_traits/num_cases.hpp>
#include <argot/switch_traits/persistent_provide_case.hpp>
#include <argot/switch_traits/persistent_provide_default.hpp>
#include <argot/unreachable_function.hpp>

#include <cstddef>

#define ARGOT_PROV_SWITCH_DETAIL_CURR_MAX_SWITCH_SIZE                          \
ARGOT_MAX_PREPROCESSED_SWITCH_CASES

namespace argot::prov::switch_detail {

#else

#include <argot/detail/forward.hpp>
#include <argot/prov/switch_/detail/config.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define ARGOT_PROV_SWITCH_DETAIL_CURR_MAX_SWITCH_SIZE                          \
BOOST_PP_TUPLE_ELEM                                                            \
( 1, ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE )

#define ARGOT_PROV_SWITCH_DETAIL_OUTPUT_HEADER                                 \
BOOST_PP_STRINGIZE                                                             \
( BOOST_PP_CAT                                                                 \
  ( BOOST_PP_CAT                                                               \
    ( preprocessed/switch_provision_default_definition_                        \
    , ARGOT_PROV_SWITCH_DETAIL_CURR_MAX_SWITCH_SIZE                            \
    )                                                                          \
  , _.hpp                                                                      \
  )                                                                            \
)

#pragma wave option( preserve: push )
#pragma wave option( preserve: 2 )
#pragma wave option( output: push )
#pragma wave option( output: ARGOT_PROV_SWITCH_DETAIL_OUTPUT_HEADER )
#include <argot/detail/copyright_and_license.hpp>

#endif  // ARGOT_PREPROCESSING_MODE

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID

// This default definition handles situations where there are more cases than
// can fit in a single, preprocessed switch-statement. An instantation
// represents either the first or an intermediate link in a chain of
// switch-statements whose maximum number of cases is
// ARGOT_MAX_PREPROCESSED_SWITCH_CASES.
template< std::size_t NumRemainingCases, provision_kind Kind >
struct switch_provision
  : switch_provision_base< Kind >
{
  using base_t = switch_provision_base< Kind >;

  template< class T >
  using with_qualifiers_t = typename base_t::template with_qualifiers_t< T >;

  template< auto V >
  using provide_case_t = typename base_t::template provide_case_t< V >;

  using provide_default_t = typename base_t::provide_default_t;

  template< class Body, class ValueType >
  using argument_list_kinds_of_body_t
    = typename base_t
      ::template argument_list_kinds_of_body_t< Body, ValueType >;

  /* TODO(mattcalabrese) Constrain*/
  template< class ValueType, class... Bodies, class Receiver >
  static constexpr decltype( auto ) run
  ( with_qualifiers_t
    < prov::switch_detail::switch_impl< ValueType, Bodies... > > self
  , Receiver&& receiver
  )
  {
    using body_t
      = typename prov::switch_detail::switch_impl< ValueType, Bodies... >
        ::body_t;

    using qualified_body_t = with_qualifiers_t< body_t >;

    std::size_t constexpr index_offset
      = switch_traits::num_cases_v< body_t > - NumRemainingCases;

    switch( self.value )
    {
#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( 0, ARGOT_PROV_SWITCH_DETAIL_CURR_MAX_SWITCH_SIZE - 1                              \
     , <argot/prov/switch_/detail/generation/case_generation.hpp>              \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
     default:
      return switch_provision
      < NumRemainingCases - ARGOT_PROV_SWITCH_DETAIL_CURR_MAX_SWITCH_SIZE
      , Kind
      >::run( static_cast
              < with_qualifiers_t
                < prov::switch_detail::switch_impl< ValueType, Bodies... > >
              >( self )
            , static_cast< Receiver&& >( receiver )
            );
    }
  }
};

#endif  // ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID

#ifndef ARGOT_PREPROCESSING_MODE

} // namespace (argot::prov::switch_detail)

#else

#pragma wave option( output: pop )
#pragma wave option( preserve: pop )

#undef ARGOT_PROV_SWITCH_DETAIL_OUTPUT_HEADER

#endif  // ARGOT_PREPROCESSING_MODE

#undef ARGOT_PROV_SWITCH_DETAIL_CURR_MAX_SWITCH_SIZE

#endif  // ARGOT_PROV_SWITCH_DETAIL_GENERATE_SWITCH_PROVISION_DEFAULT_DEFINITION_HPP_
