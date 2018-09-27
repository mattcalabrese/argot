/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_PERSISTENT_RETURN_VALUE_REDUCER_OF_HPP_
#define ARGOT_CONCEPTS_PERSISTENT_RETURN_VALUE_REDUCER_OF_HPP_

#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/persistent_return_value_reducer.hpp>
#include <argot/concepts/return_type.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/concepts/valid.hpp>
#include <argot/detail/declval.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/auto_concept.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/unreachable.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/detail/remove_cvref.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace persistent_return_value_reducer_of_detail {

template< class ReturnType >
struct function_returning
{
  function_returning() = delete;
  function_returning( function_returning const& ) = delete;
  function_returning& operator =( function_returning const& ) = delete;
  ~function_returning() = delete;
  function_returning operator&() = delete;
  // TODO(mattcalabrese) Delete operators new/delete

  ReturnType operator()() && { ARGOT_DETAIL_UNREACHABLE(); }
};

template< class Reducer, class HeadReturnType, class... TailReturnTypes >
using result_of_raw_reduce_t
  = decltype
    ( access_raw_concept_map< PersistentReturnValueReducer< Reducer > >::reduce
      ( ARGOT_DECLVAL( Reducer const& )
      , reducer_traits::return_types<>
      , reducer_traits::return_types< TailReturnTypes... >
      , ARGOT_DECLVAL( function_returning< HeadReturnType >&& )
      )
    );

} // namespace argot(::persistent_return_value_reducer_of_detail)

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/persistent_return_value_reducer_of.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

template< class Reducer, class HeadReturnType, class... TailReturnTypes >
ARGOT_AUTO_CONCEPT( PersistentReturnValueReducerOf )
( PersistentReturnValueReducer< Reducer >
, ReturnType< HeadReturnType >
, ReturnType< TailReturnTypes >...
, Valid
  < persistent_return_value_reducer_of_detail::result_of_raw_reduce_t
  , Reducer, HeadReturnType, TailReturnTypes...
  >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

} // namespace argot

#endif  // ARGOT_CONCEPTS_PERSISTENT_RETURN_VALUE_REDUCER_OF_HPP_
