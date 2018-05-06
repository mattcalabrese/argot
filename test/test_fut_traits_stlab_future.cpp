/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include "future_like_testing.hpp"

#include <argot/concepts/future.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/fut_traits/destructive_then.hpp>
#include <argot/fut_traits/persistent_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/packager/stlab.hpp>
#include <argot/void_.hpp>

#include <boost/thread/barrier.hpp>

#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/immediate_executor.hpp>
#include <stlab/concurrency/future.hpp>

#include <thread>
#include <type_traits>
#include <utility>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

namespace {

namespace fut_traits = argot::fut_traits;
namespace executor = argot::executor;
namespace packager = argot::packager;

using executor::immediate;
using argot::Future;
using argot::PersistentFuture;
using argot::SameType;
using argot::void_;
using argot::void_to_regular_void_t;
using fut_traits::destructive_then;
using fut_traits::persistent_then;
using fut_traits::value_type_t;

using argot_future_like_testing::persistent_wrap;
using argot_future_like_testing::wrapped;
using argot_future_like_testing::wrap;

using packager_t = packager::stlab;

template< class T >
using future = stlab::future< T >;

template< class T >
using then_result = stlab::future< T >;

ARGOT_CONCEPT_ENSURE( Future< future< int > > );
ARGOT_CONCEPT_ENSURE( Future< future< void > > );
ARGOT_CONCEPT_ENSURE( Future< future< int& > > );

ARGOT_CONCEPT_ENSURE( SameType< value_type_t< future< int > >, int > );
ARGOT_CONCEPT_ENSURE( SameType< value_type_t< future< void > >, void_ > );
ARGOT_CONCEPT_ENSURE( SameType< value_type_t< future< int& > >, int& > );

ARGOT_CONCEPT_ENSURE( PersistentFuture< future< int > > );
ARGOT_CONCEPT_ENSURE( PersistentFuture< future< void > > );
ARGOT_CONCEPT_ENSURE( PersistentFuture< future< int& > > );

BOOST_AUTO_TEST_CASE( test_destructive_then_object_single_threaded )
{
  auto [ task, fut ]
    = stlab::package< int( int ) >
      ( stlab::immediate_executor
      , []( int v ) { return v; }
      );

  task( 5 );

  decltype( auto ) result
    = destructive_then< packager_t >
      ( std::move( fut ), immediate, wrap< int >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int > > > );

  wrapped< int > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( std::move( raw_result ).value() == 5 );
}

BOOST_AUTO_TEST_CASE( test_destructive_then_void_single_threaded )
{
  auto [ task, fut ]
    = stlab::package< void() >
      ( stlab::immediate_executor
      , []{}
      );

  task();

  decltype( auto ) result
    = destructive_then< packager_t >
      ( std::move( fut ), immediate, wrap< void_ >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< void_ > > > );

  wrapped< void_ > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  static_cast< void >( raw_result );
}

// TODO(mattcalabrese) Eventually support references (stlab doesn't support)
#if 0

BOOST_AUTO_TEST_CASE( test_destructive_then_reference_single_threaded )
{
  auto [ task, fut ]
    = stlab::package< int&( int& ) >
      ( stlab::immediate_executor
      , []( int& v ) -> int& { return v; }
      );
  int val = 5;

  task( val );

  decltype( auto ) result
    = destructive_then< packager_t >( std::move( fut ), immediate, wrap< int& >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int& > > > );

  wrapped< int& > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( &std::move( raw_result ).value() == &val );
}

#endif

BOOST_AUTO_TEST_CASE( test_destructive_then_object_multi_threaded )
{
  auto [ task, fut ]
    = stlab::package< int( int ) >
      ( stlab::default_executor
      , []( int v ) { return v; }
      );

  task( 5 );

  decltype( auto ) result
    = destructive_then< packager_t >
      ( std::move( fut ), immediate, wrap< int >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int > > > );

  wrapped< int > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( std::move( raw_result ).value() == 5 );
}

BOOST_AUTO_TEST_CASE( test_destructive_then_void_multi_threaded )
{
  auto [ task, fut ]
    = stlab::package< void() >
      ( stlab::default_executor
      , []{}
      );

  task();

  decltype( auto ) result
    = destructive_then< packager_t >
      ( std::move( fut ), immediate, wrap< void_ >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< void_ > > > );

  wrapped< void_ > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  static_cast< void >( raw_result );
}

// TODO(mattcalabrese) Eventually support references (stlab doesn't support)
#if 0

BOOST_AUTO_TEST_CASE( test_destructive_then_reference_multi_threaded )
{
  auto [ task, fut ]
    = stlab::package< int&( int& ) >
      ( stlab::default_executor
      , []( int& v ) -> int& { return v; }
      );
  int val = 5;

  task( val );

  decltype( auto ) result
    = destructive_then< packager_t >( std::move( fut ), immediate, wrap< int& >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int& > > > );

  wrapped< int& > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( &std::move( raw_result ).value() == &val );
}

#endif

BOOST_AUTO_TEST_CASE( test_persistent_then_object_single_threaded )
{
  auto [ task, fut ]
    = stlab::package< int( int ) >
      ( stlab::immediate_executor
      , []( int v ) { return v; }
      );

  task( 5 );

  decltype( auto ) result
    = persistent_then< packager_t >( fut, immediate, persistent_wrap< int >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int > > > );

  wrapped< int > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( std::move( raw_result ).value() == 5 );
}

BOOST_AUTO_TEST_CASE( test_persistent_then_void_single_threaded )
{
  auto [ task, fut ]
    = stlab::package< void() >
      ( stlab::immediate_executor
      , []{}
      );

  task();

  decltype( auto ) result
    = persistent_then< packager_t >
      ( fut, immediate, persistent_wrap< void_ >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< void_ > > > );

  wrapped< void_ > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  static_cast< void >( raw_result );
}

// TODO(mattcalabrese) Eventually support references (stlab doesn't support)
#if 0

BOOST_AUTO_TEST_CASE( test_persistent_then_reference_single_threaded )
{
  auto [ task, fut ]
    = stlab::package< int&( int& ) >
      ( stlab::immediate_executor
      , []( int& v ) -> int& { return v; }
      );
  int val = 5;

  task( val );

  decltype( auto ) result = persistent_then< packager_t >( fut, immediate, persistent_wrap< int& >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int& > > > );

  wrapped< int& > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( &std::move( raw_result ).value() == &val );
}

#endif

BOOST_AUTO_TEST_CASE( test_persistent_then_object_multi_threaded )
{
  auto [ task, fut ]
    = stlab::package< int( int ) >
      ( stlab::default_executor
      , []( int v ) { return v; }
      );

  task( 5 );

  decltype( auto ) result
    = persistent_then< packager_t >( fut, immediate, persistent_wrap< int >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int > > > );

  wrapped< int > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( std::move( raw_result ).value() == 5 );
}

BOOST_AUTO_TEST_CASE( test_persistent_then_void_multi_threaded )
{
  auto [ task, fut ]
    = stlab::package< void() >
      ( stlab::default_executor
      , []{}
      );

  task();

  decltype( auto ) result
    = persistent_then< packager_t >
      ( fut, immediate, persistent_wrap< void_ >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< void_ > > > );

  wrapped< void_ > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  static_cast< void >( raw_result );
}

// TODO(mattcalabrese) Eventually support references (stlab doesn't support)
#if 0

BOOST_AUTO_TEST_CASE( test_persistent_then_reference_multi_threaded )
{
  auto [ task, fut ]
    = stlab::package< int&( int& ) >
      ( stlab::default_executor
      , []( int& v ) -> int& { return v; }
      );
  int val = 5;

  task( val );

  decltype( auto ) result = persistent_then< packager_t >( fut, immediate, persistent_wrap< int& >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int& > > > );

  wrapped< int& > raw_result
    = [ &result ]
      {
        for( ; ; std::this_thread::yield() )
          if( auto optional_res = result.get_try(); optional_res )
            return *optional_res;
      }();

  BOOST_TEST( &std::move( raw_result ).value() == &val );
}

#endif

}  // namespace
