#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif

       case switch_traits::case_value_for_type_at_v
       < body_t, ValueType, index_offset + BOOST_PP_ITERATION() >:
        return typename base_t::template provide_case_t
        < switch_traits::case_value_for_type_at_v
          < body_t, ValueType, index_offset + BOOST_PP_ITERATION() >
        >()( static_cast< qualified_body_t >( self.body )
           , static_cast< Receiver&& >( receiver )
           );
