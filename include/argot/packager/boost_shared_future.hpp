/*==============================================================================
  Copyright (c) 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PACKAGER_BOOST_SHARED_FUTURE_HPP_
#define ARGOT_PACKAGER_BOOST_SHARED_FUTURE_HPP_

//[description
/*`
packager::boost_shared_future is a FuturePackager that generates
`boost::shared_future` objects.

[note TODO(mattcalabrese) Explain how to enable continuations in boost.]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/future_packager.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/fut_traits/config.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/no_unique_address.hpp>

#include <boost/thread/future.hpp>

#include <exception>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::packager {
//<-
namespace detail_boost_shared_future_packager {

template< class Fun, class... P >
struct task_function
{
  // TODO(mattcalabrese) Concept assert

  void operator ()( P&&... args ) &&
  {
    try
    {
      promise.set_value( ARGOT_MOVE( fun )( ARGOT_FORWARD( P )( args )... ) );
    }
    catch( ... )
    {
      promise.set_exception( std::current_exception() );
    }
  }

  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  boost::promise< basic_result_of_t< Fun&&, P... > > promise;
};

template< class Fun, class... P >
struct packaged_t
{
  // TODO(mattcalabrese) Concept assert

  explicit constexpr packaged_t( Fun&& fun )
    : task{ ARGOT_MOVE( fun ) }
    , future( task.promise.get_shared_future() ) {}

  explicit constexpr packaged_t( Fun const& fun )
    : task{ fun }
    , future( task.promise.get_shared_future() ) {}

  task_function< Fun, P... > task;
  boost::shared_future< basic_result_of_t< Fun&&, P... > > future;
};

} // namespace argot::packager(::detail_boost_shared_future_packager)
//->

struct boost_shared_future {};

} // namespace (argot::packager)

//]

namespace argot {

template<>
struct make_concept_map< FuturePackager< packager::boost_shared_future > >
{
  // TODO(mattcalabrese) Constrain
  template< class... P, class Exec, class Fun >
  static constexpr auto package( Exec&& exec, Fun&& fun )
  {
    return packager::detail_boost_shared_future_packager::packaged_t
    < detail_argot::remove_cvref_t< Fun >, P... >
    ( ARGOT_FORWARD( Fun )( fun ) );
  }
};

} // namespace argot

#endif  // ARGOT_PACKAGER_BOOST_SHARED_FUTURE_HPP_
