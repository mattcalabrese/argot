/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_NET_EXECUTOR_HPP_
#define ARGOT_CONCEPTS_NET_EXECUTOR_HPP_

#include <argot/concepts/copy_constructible.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/detail/concepts_preprocessing_helpers.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/explicit_concept.hpp>
#include <argot/gen/requires.hpp>

#if !defined( ARGOT_GENERATE_PREPROCESSED_CONCEPTS )

#include <argot/declval.hpp>

#include <boost/asio/execution_context.hpp>

#endif // !defined( ARGOT_GENERATE_PREPROCESSED_CONCEPTS )

namespace argot {

#define ARGOT_DETAIL_PREPROCESSED_CONCEPT_HEADER_NAME()                        \
s/net_executor.h

#ifdef ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER
#include ARGOT_CONCEPTS_DETAIL_PREPROCESSED_HEADER
#else

#include <argot/concepts/detail/preprocess_header_begin.hpp>

ARGOT_CONCEPTS_DETAIL_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO(mattcalabrese) Don't require move constructible
template< class NetExec >
ARGOT_EXPLICIT_CONCEPT( NetExecutor )
( UnqualifiedObject< NetExec >
, CopyConstructible< NetExec >
, Destructible< NetExec >
//, EqualityComparable< NetExec >
);

#include <argot/concepts/detail/preprocess_header_end.hpp>

#endif  // ARGOT_CONCEPTS_DETAIL_SHOULD_INCLUDE_PREPROCESSED_HEADER

#if !defined( ARGOT_GENERATE_PREPROCESSED_CONCEPTS )
/*
template< class ExecContext >
struct make_concept_map
< ExecutionContext< ExecContext >
, ARGOT_REQUIRES
  ( UnqualifiedObject< ExecContext > )
  ( Destructible< ExecContext > )

  <>
>
{
  using executor_type_t = typename ExecContext::executor_type;

  static constexpr executor_type_t get_net_executor( ExecContext& self )
  {
    return self.get_executor();
  }
};
*/
#endif // !defined( ARGOT_GENERATE_PREPROCESSED_CONCEPTS )

}  // namespace argot

#endif  // ARGOT_CONCEPTS_NET_EXECUTOR_HPP_
