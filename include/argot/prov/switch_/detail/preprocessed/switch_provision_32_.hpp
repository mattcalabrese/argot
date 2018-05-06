/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# include <argot/prov/switch_/detail/preprocessed/switch_provision_16_.hpp>
template< provision_kind Kind >
struct switch_provision< 17, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 17;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 18, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 18;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 19, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 19;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 20, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 20;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 21, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 21;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 22, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 22;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 23, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 23;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 24, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 24;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 25, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 25;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 26, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 26;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 27, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 27;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 28, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 28;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 29, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 29;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 30, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 30;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 29 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 29 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 29 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 29 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 31, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 31;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 29 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 29 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 30 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 30 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 29 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 29 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 30 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 30 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
template< provision_kind Kind >
struct switch_provision< 32, Kind >
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
  template
  < class ValueType, class... Bodies, class Receiver
  , ARGOT_REQUIRES
    ( ArgumentReceiverOfKinds
      < Receiver
      , argument_list_kinds_of_body_t
        < typename prov::switch_detail::switch_impl< ValueType, Bodies... >
          ::body_t
        , ValueType
        >
      >
    )
    ()
  >
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
      = switch_traits::num_cases_v< body_t > - 32;
    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 29 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 29 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 30 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 30 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 31 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 31 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       default:
        if constexpr( is_modeled_v< SwitchBodyDefault< body_t > > )
          return provide_default_t()
          ( static_cast< qualified_body_t >( self.body ), self.value
          , static_cast< Receiver&& >( receiver )
          );
        else
          return unreachable_function
          < receiver_traits::result_of_unbound_receive_branch_t
            < Receiver&&
            , argument_list_kinds_of_body_t< body_t, ValueType >
            >
          >();
      }
    else
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
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 2 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 2 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 3 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 3 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 4 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 4 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 5 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 5 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 6 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 6 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 7 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 7 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 8 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 8 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 9 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 9 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 10 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 10 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 11 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 11 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 12 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 12 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 13 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 13 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 14 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 14 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 15 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 15 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 16 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 16 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 17 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 17 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 18 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 18 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 19 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 19 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 20 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 20 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 21 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 21 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 22 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 22 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 23 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 23 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 24 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 24 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 25 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 25 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 26 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 26 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 27 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 27 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 28 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 28 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 29 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 29 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 30 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 30 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + 31 >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + 31 >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
