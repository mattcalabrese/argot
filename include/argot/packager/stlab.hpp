/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PACKAGER_STLAB_HPP_
#define ARGOT_PACKAGER_STLAB_HPP_

// TODO(mattcalabrese)
// Possibly make it an error to include this file if stlab support isn't enabled.

//[description
/*`
packager::stlab is a FuturePackager that generates stlab::future objects.

[note This facility depends on the [stlab]. If it is not installed then the
      facilities specified in this header will not exist.
]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/executor_traits/execute.hpp>
#include <argot/fut_traits/config.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/packager/packager_base.hpp>

#ifdef ARGOT_HAS_STLAB_FUTURE
#include <stlab/concurrency/future.hpp>
#endif

//[docs
/*`
[synopsis_heading]
*/

namespace argot::packager {
//<-
namespace stlab_packager_detail {

template< class Exec >
struct stlab_executor_from_executor
{
  // TODO(mattcalabrese) Concept check

  template< class Fun >
  constexpr void operator ()( Fun&& fun )
  {
    executor_traits::execute
    ( ARGOT_MOVE( exec ), ARGOT_FORWARD( Fun )( fun ) );
  }

  // TODO(mattcalabrese) Have overload for persistent iff Exec is persistent.

  ARGOT_NO_UNIQUE_ADDRESS Exec exec;
};

template< class Fun >
struct lvalue_callable
{
  template< class... P >
  constexpr basic_result_of_t< Fun&&, P&&... > operator()( P&&... args )
  {
    return ARGOT_MOVE( fun )( ARGOT_FORWARD( P )( args )... );
  }

  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
};

} // namespace argot::packager(::stlab_packager_detail)
//->
struct stlab {};

} // namespace (argot::packager)

//]

namespace argot {

template<>
struct make_concept_map< FuturePackager< packager::stlab > >
{
  template< class... P, class Exec, class Fun >
  static constexpr auto package( Exec&& exec, Fun&& fun )
  {
    auto [ task, fut ]
      = stlab::package
        < basic_result_of_t
          < detail_argot::remove_cvref_t< Fun >&&, P&&... >( P&&... ) >
        ( packager::stlab_packager_detail::stlab_executor_from_executor  // TODO(mattcalabrese) More sophisticated conversion, see Thenable
          < detail_argot::remove_cvref_t< Exec > >
          { ARGOT_FORWARD( Exec )( exec ) }
        , packager::stlab_packager_detail::lvalue_callable
          < detail_argot::remove_cvref_t< Fun > >
          { ARGOT_FORWARD( Fun )( fun ) }
        );

    using task_t = decltype( task );
    using future_t = decltype( fut );

    struct result
    {
      ARGOT_NO_UNIQUE_ADDRESS task_t task;
      ARGOT_NO_UNIQUE_ADDRESS future_t future;
    };

    return result{ ARGOT_MOVE( task ), ARGOT_MOVE( fut ) };
  }
};

} // namespace argot

#endif  // ARGOT_PACKAGER_STLAB_HPP_
