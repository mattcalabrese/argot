/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 66 "../../concepts/persistent_return_value_reducer_of.hpp"
template< class Reducer, class HeadReturnType, class... TailReturnTypes >
struct PersistentReturnValueReducerOf { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< PersistentReturnValueReducer< Reducer > , ReturnType< HeadReturnType > , ReturnType< TailReturnTypes >... , Valid < persistent_return_value_reducer_of_detail::result_of_raw_reduce_t , Reducer, HeadReturnType, TailReturnTypes... > >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
