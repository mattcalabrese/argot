/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 45 "../../concepts/less_than.hpp"
template< auto V, auto W >
struct LessThan { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< Valid < less_than_concept_detail::less_than_is_valid_expression_t , decltype( V ), decltype( W ) > , Valid < less_than_concept_detail::contextually_convertible_to_bool_less_than_t , decltype( V ), decltype( W ) > , TransparentRequirement < less_than_concept_detail::less_than_requirement< V, W > > >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
