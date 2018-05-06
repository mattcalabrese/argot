/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include "future_like_testing.hpp"

#include <argot/concepts/future.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/fut_traits/destructive_then.hpp>
#include <argot/fut_traits/persistent_then.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/void_.hpp>

#include <argot/gen/concept_ensure.hpp>

#include <boost/thread/barrier.hpp>

#include <experimental/future>

#include <thread>
#include <type_traits>
#include <utility>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

namespace {

namespace fut_traits = argot::fut_traits;

using argot::Future;
using argot::SameType;
using argot::void_;
using argot::void_to_regular_void_t;
using fut_traits::destructive_then;
using fut_traits::value_type_t;

using argot_future_like_testing::wrapped;
using argot_future_like_testing::wrap;

template< class T >
using hesitate
  = argot_future_like_testing::hesitate< std::experimental::promise, T >;

template< class T >
using promise = std::experimental::promise< T >;

template< class T >
using future = std::experimental::future< T >;

template< class T >
using then_result = std::experimental::future< T >;

ARGOT_CONCEPT_ENSURE( Future< future< int > > );
ARGOT_CONCEPT_ENSURE( Future< future< void > > );
ARGOT_CONCEPT_ENSURE( Future< future< int& > > );

ARGOT_CONCEPT_ENSURE( SameType< value_type_t< future< int > >, int > );
ARGOT_CONCEPT_ENSURE( SameType< value_type_t< future< void > >, void_ > );
ARGOT_CONCEPT_ENSURE( SameType< value_type_t< future< int& > >, int& > );

BOOST_AUTO_TEST_CASE( test_destructive_then_object_single_threaded )
{
  promise< int > prom;
  future< int > fut = prom.get_future();

  prom.set_value( 5 );

  decltype( auto ) result
    = destructive_then( std::move( fut ), wrap< int >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int > > > );

  BOOST_TEST( result.get().value() == 5 );
}

BOOST_AUTO_TEST_CASE( test_destructive_then_void_single_threaded )
{
  promise< void > prom;
  future< void > fut = prom.get_future();

  prom.set_value();

  decltype( auto ) result
    = destructive_then( std::move( fut ), wrap< void_ >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< void_ > > > );

  result.get();
}

BOOST_AUTO_TEST_CASE( test_destructive_then_reference_single_threaded )
{
  promise< int& > prom;
  future< int& > fut = prom.get_future();
  int val = 5;

  prom.set_value( val );

  decltype( auto ) result
    = destructive_then( std::move( fut ), wrap< int& >() );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( result ), then_result< wrapped< int& > > > );

  BOOST_TEST( &result.get().value() == &val );
}

BOOST_AUTO_TEST_CASE( test_destructive_then_object_multi_threaded )
{
  promise< int > prom;
  future< int > fut = prom.get_future();
  boost::barrier wall( 2 );

  std::thread other_thread( hesitate< int >{ std::move( prom ), &wall, 5 } );

  decltype( auto ) result
    = destructive_then( std::move( fut ), wrap< int >() );

  wall.wait();

  BOOST_TEST( result.get().value() == 5 );

  other_thread.join();
}

BOOST_AUTO_TEST_CASE( test_destructive_then_void_multi_threaded )
{
  promise< void > prom;
  future< void > fut = prom.get_future();
  boost::barrier wall( 2 );

  std::thread other_thread( hesitate< void >{ std::move( prom ), &wall, {} } );

  decltype( auto ) result
    = destructive_then( std::move( fut ), wrap< void_ >() );

  wall.wait();

  result.get();

  other_thread.join();
}

BOOST_AUTO_TEST_CASE( test_destructive_then_reference_multi_threaded )
{
  promise< int& > prom;
  future< int& > fut = prom.get_future();
  int val = 5;
  boost::barrier wall( 2 );

  std::thread other_thread( hesitate< int& >{ std::move( prom ), &wall, val } );

  decltype( auto ) result
    = destructive_then( std::move( fut ), wrap< int& >() );

  wall.wait();

  BOOST_TEST( &result.get().value() == &val );

  other_thread.join();
}

}  // namespace
