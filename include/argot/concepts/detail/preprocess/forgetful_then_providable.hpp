/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 50 "../../concepts/forgetful_then_providable.hpp"
template< class ConcProv, class Exec >
struct ForgetfulThenProvidable { using ArgotDetailConceptSpec = ForgetfulThenProvidable ; static bool constexpr argot_gen_detail_is_auto_concept_v = false; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< ConcurrentArgumentProvider< ConcProv > 
>::type; struct assertion : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {}; };
template< class ConcProv, class Exec >
struct make_concept_map
< ForgetfulThenProvidable< ConcProv, Exec >
, typename ::argot::requires_< ConcurrentArgumentProvider< ConcProv > >::_::template and_< ForgetfulThenable 
< conc_traits::result_of_as_future_t< ConcProv&& >, Exec > >::_::template ARGOT_RESULT_
<>
>
{
template< class ExecP, class Fun >
static constexpr void
forgetful_then_provide( ConcProv&& self, ExecP&& exec, Fun&& fun )
{
fut_traits::forgetful_then
( conc_traits::as_future( ARGOT_MOVE( self ) )
, static_cast< ::argot::forward_detail::direct_identity_t< ExecP >&& >( exec )
, static_cast< ::argot::forward_detail::direct_identity_t< Fun >&& >( fun ) 
);
}
};
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
