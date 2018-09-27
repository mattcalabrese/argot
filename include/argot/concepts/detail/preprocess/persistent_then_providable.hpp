/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 49 "../../concepts/persistent_then_providable.hpp"
template< class ConcProv, class FutPackager, class Exec >
struct PersistentThenProvidable { using ArgotDetailConceptSpec = PersistentThenProvidable ; static bool constexpr argot_gen_detail_is_auto_concept_v = false; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< ThenProvidable< ConcProv, FutPackager, Exec > >::type; struct assertion : ::argot::deduced_concept_assertion< ArgotDetailConceptSpec > {}; };
template< class ConcProv, class FutPackager, class Exec >
struct make_concept_map
< PersistentThenProvidable< ConcProv, FutPackager, Exec >
, typename ::argot::requires_< ThenProvidable< ConcProv, FutPackager, Exec > >::_::template ARGOT_RESULT
<>
>
{
template< class ExecP, class Fun >
static constexpr auto
then_provide( ConcProv const& self, ExecP&& exec, Fun&& fun )
{
return fut_traits::then< FutPackager >
( conc_traits::as_future( self )
, static_cast< ::argot::detail_forward::direct_identity_t< ExecP >&& >( exec )
, static_cast< ::argot::detail_forward::direct_identity_t< Fun >&& >( fun ) 
);
}
};
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
