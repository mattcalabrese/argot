/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_EXECUTOR_POST_TO_HPP_
#define ARGOT_EXECUTOR_POST_TO_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/allocator.hpp>
#include <argot/concepts/default_constructible.hpp>
#include <argot/concepts/executor.hpp>
#include <argot/concepts/net_executor.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/post_to_executor.hpp>
#include <argot/detail/sink.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/remove_cvref.hpp>

#include <memory>

namespace argot {
namespace executor {

struct post_to_fn
{
  template< class NetExec, class Alloc >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( NetExecutor< NetExec > );
    ARGOT_CONCEPT_ASSERT( Allocator< Alloc > );

    ARGOT_NO_UNIQUE_ADDRESS NetExec net_exec;
    ARGOT_NO_UNIQUE_ADDRESS Alloc alloc;
  };

  template< class NetExec, class Alloc = std::allocator< void >
          , ARGOT_REQUIRES( NetExecutor< remove_cvref_t< NetExec > > )
                          ( Allocator< remove_cvref_t< Alloc > > )
                          ( Sinkable< NetExec&& > )
                          ( Sinkable< Alloc&& > )
                          ()
          >
  constexpr auto operator ()
  ( NetExec&& net_exec
  , Alloc&& alloc
      = ARGOT_REQUIRES
        ( DefaultConstructible< remove_cvref_t< Alloc > > )
        < remove_cvref_t< Alloc > >()
  ) const
  {
    return impl< remove_cvref_t< NetExec >, remove_cvref_t< Alloc > >
    { call_detail::forward_and_sink< NetExec >( net_exec )
    , call_detail::forward_and_sink< Alloc >( alloc )
    };
  }

} inline constexpr post_to;

template< class NetExec, class Alloc = std::allocator< void > >
using result_of_post_to_t
  = basic_result_of_t< post_to_fn const&, NetExec, Alloc >;

template< class NetExec, class Alloc = std::allocator< void > >
using result_of_post_to
  = basic_result_of< post_to_fn const&, NetExec, Alloc >;

}  // namespace argot(::executor)

template< class NetExec, class Alloc >
struct make_concept_map
< Executor< executor::post_to_fn::impl< NetExec, Alloc > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Fun >
  static constexpr void
  execute( executor::post_to_fn::impl< NetExec, Alloc > const& self, Fun&& fun )
  {
    (void)self.net_exec.post( ARGOT_FORWARD( Fun )( fun ), self.alloc );
  }
};

} // namespace argot

#endif  // ARGOT_EXECUTOR_POST_TO_HPP_
