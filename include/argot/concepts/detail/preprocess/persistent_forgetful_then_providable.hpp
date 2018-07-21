/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 49 "../../concepts/persistent_forgetful_then_providable.hpp"
template< class ConcProv, class Exec >
struct PersistentForgetfulThenProvidable { using ArgotDetailConceptSpec = PersistentForgetfulThenProvidable ; static bool constexpr argot_gen_detail_is_auto_concept_v = false; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< ForgetfulThenProvidable< ConcProv, Exec > >::type; struct assertion : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {}; };
template< class ConcProv, class Exec >
struct make_concept_map
< PersistentForgetfulThenProvidable< ConcProv, Exec >
, typename ::argot::requires_< ForgetfulThenProvidable< ConcProv, Exec > >::_::template ARGOT_RESULT
<>
>
{
template< class ExecP, class Fun >
static constexpr void
forgetful_then_provide( ConcProv const& self, ExecP&& exec, Fun&& fun )
{
fut_traits::forgetful_then
( conc_traits::as_future( self )
, static_cast< ::argot::forward_detail::direct_identity_t< ExecP >&& >( exec )
, static_cast< ::argot::forward_detail::direct_identity_t< Fun >&& >( fun ) 
);
}
};
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
