/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
# line 40 "../../concepts/stlab_executor.hpp"
template< class StlabExec >
struct StlabExecutor { static bool constexpr argot_gen_detail_is_auto_concept_v = true; template< class ArgotDetailSelf > using argot_gen_detail_is_modeled_impl = ::argot::auto_concept_detail::is_modeled_impl< ArgotDetailSelf >; using requirements = typename ::argot::requires_detail::requires_impl< UnqualifiedObject< StlabExec > , CopyConstructible< StlabExec > , BasicCallableWith < StlabExec&, detail_stlab_executor_concept::function_archetype const& > >::type; struct assertion : requirements::assertion {}; };
# undef ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME
