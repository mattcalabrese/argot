/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 0 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 0 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 1 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 1 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
     default:
      return switch_provision
      < NumRemainingCases - 2
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
