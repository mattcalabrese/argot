/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_SWITCH_DETAIL_GENERATE_SWITCH_PROVISION_HPP_
#define ARGOT_PROV_SWITCH_DETAIL_GENERATE_SWITCH_PROVISION_HPP_

#ifndef ARGOT_PREPROCESSING_MODE

#include <argot/concepts/switch_body_default.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/forward.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/prov/switch_/detail/config.hpp>
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

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <cstddef>

namespace argot::prov::switch_detail {

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID

////////////////////////////////////////////////////////////////////////////////
// Begin generation of switch_provision specializations...                    //
////////////////////////////////////////////////////////////////////////////////
#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( 1, ARGOT_MAX_PREPROCESSED_SWITCH_CASES                                  \
     , <argot/prov/switch_/detail/generation/switch_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
////////////////////////////////////////////////////////////////////////////////
// End generation of switch_provision specializations.                        //
////////////////////////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////////////////////////
// Begin generation of cases...                                               //
////////////////////////////////////////////////////////////////////////////////
#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( 0, ARGOT_MAX_PREPROCESSED_SWITCH_CASES - 1                              \
     , <argot/prov/switch_/detail/generation/case_generation.hpp>              \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
////////////////////////////////////////////////////////////////////////////////
// End generation of cases.                                                   //
////////////////////////////////////////////////////////////////////////////////
     default:
      return switch_provision
      < NumRemainingCases - ARGOT_MAX_PREPROCESSED_SWITCH_CASES, Kind >::run
      ( static_cast
        < with_qualifiers_t
          < prov::switch_detail::switch_impl< ValueType, Bodies... > >
        >( self )
      , static_cast< Receiver&& >( receiver )
      );
    }
  }
};

#endif  // ARGOT_MAX_PREPROCESSED_SWITCH_CASES_IS_VALID

}  // namespace (argot::prov::switch_detail)

#else  // Otherwise, we are generating the preprocessed forms as files...

#define ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE ( 1, 2 )
#include <argot/prov/switch_/detail/generate_switch_provision_default_definition.hpp>
#include <argot/prov/switch_/detail/generate_switch_provision_range.hpp>

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES >= 3

#define ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE ( 3, 4 )
#include <argot/prov/switch_/detail/generate_switch_provision_default_definition.hpp>
#include <argot/prov/switch_/detail/generate_switch_provision_range.hpp>

#endif

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES >= 5

#define ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE ( 5, 8 )
#include <argot/prov/switch_/detail/generate_switch_provision_default_definition.hpp>
#include <argot/prov/switch_/detail/generate_switch_provision_range.hpp>

#endif

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES >= 9

#define ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE ( 9, 16 )
#include <argot/prov/switch_/detail/generate_switch_provision_default_definition.hpp>
#include <argot/prov/switch_/detail/generate_switch_provision_range.hpp>

#endif

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES >= 17

#define ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE ( 17, 32 )
#include <argot/prov/switch_/detail/generate_switch_provision_default_definition.hpp>
#include <argot/prov/switch_/detail/generate_switch_provision_range.hpp>

#endif

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES >= 33

#define ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE ( 33, 64 )
#include <argot/prov/switch_/detail/generate_switch_provision_default_definition.hpp>
#include <argot/prov/switch_/detail/generate_switch_provision_range.hpp>

#endif

#if ARGOT_MAX_PREPROCESSED_SWITCH_CASES >= 65

#error User requested preprocessing for switches with more than 64 cases.

#endif

#undef ARGOT_PROV_SWITCH_DETAIL_PREPROCESSING_PROVISION_RANGE

#endif  // End of preprocessing mode checks

#endif  // ARGOT_PROV_SWITCH_DETAIL_GENERATE_SWITCH_PROVISION_HPP_
