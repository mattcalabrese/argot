/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EXECUTOR_STLAB_HPP_
#define ARGOT_EXECUTOR_STLAB_HPP_

#include <argot/concepts/executor.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/stlab_executor.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot {
namespace executor {

struct stlab_fn
{
  template< class StlabExec >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( StlabExecutor< StlabExec > );

    ARGOT_NO_UNIQUE_ADDRESS StlabExec stlab_exec;
  };

  template< class StlabExec
          , ARGOT_REQUIRES( StlabExecutor< detail_argot::remove_cvref_t< StlabExec > > )
                          ( Sinkable< StlabExec&& > )
                          <>
          >
  constexpr auto operator ()( StlabExec&& stlab_exec ) const
  {
    return impl< detail_argot::remove_cvref_t< StlabExec > >
    { call_detail::forward_and_sink< StlabExec >( stlab_exec ) };
  }

} inline constexpr stlab;

} // namespace argot(::executor)

template< class StlabExec >
struct make_concept_map< Executor< executor::stlab_fn::impl< StlabExec > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Fun >
  static constexpr void
  execute( executor::stlab_fn::impl< StlabExec > const& self, Fun&& fun )
  {
    (void)self.stlab_exec( ARGOT_FORWARD( Fun )( fun )() );
  }
};

} // namespace argot

#endif  // ARGOT_EXECUTOR_STLAB_HPP_
