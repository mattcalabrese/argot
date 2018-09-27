/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 50 "../../concepts/then_providable.hpp"
template< class ConcProv, class FutPackager, class Exec >
struct ThenProvidable { using ArgotDetailConceptSpec = ThenProvidable ; static bool constexpr argot_gen_detail_is_auto_concept_v = false; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< ConcurrentArgumentProvider< ConcProv > 
>::type; struct assertion : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {}; };
template< class ConcProv, class FutPackager, class Exec >
struct make_concept_map
< ThenProvidable< ConcProv, FutPackager, Exec >
, typename ::argot::requires_< ConcurrentArgumentProvider< ConcProv > >::_::template and_< FuturePackager< FutPackager > >::_::template and_< Thenable 
< conc_traits::result_of_as_future_t< ConcProv&& >, FutPackager, Exec > >::_::template ARGOT_RESULT
<>
>
{
template< class ExecP, class Fun >
static constexpr auto
then_provide( ConcProv&& self, ExecP&& exec, Fun&& fun )
{
fut_traits::then< FutPackager >
( conc_traits::as_future( ARGOT_MOVE( self ) )
, static_cast< ::argot::detail_forward::direct_identity_t< ExecP >&& >( exec )
, static_cast< ::argot::detail_forward::direct_identity_t< Fun >&& >( fun ) 
);
}
};
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
