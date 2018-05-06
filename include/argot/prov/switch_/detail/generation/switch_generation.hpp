#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif

template< provision_kind Kind >
struct switch_provision< BOOST_PP_ITERATION(), Kind >
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
      = switch_traits::num_cases_v< body_t > - BOOST_PP_ITERATION();

    if constexpr
    ( is_modeled_v< SwitchBodyDefault< body_t > > || index_offset != 0 )
      switch( self.value )
      {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, BOOST_PP_DEC( BOOST_PP_ITERATION() )                                 \
     , <argot/prov/switch_/detail/generation/case_generation.hpp>              \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
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
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, BOOST_PP_DEC( BOOST_PP_ITERATION() )                                 \
     , <argot/prov/switch_/detail/generation/case_generation.hpp>              \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
      }
    ARGOT_DETAIL_UNREACHABLE();
  }
};
