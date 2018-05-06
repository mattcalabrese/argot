/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_FUTURE_LIKE_TESTING_HPP_
#define ARGOT_TEST_FUTURE_LIKE_TESTING_HPP_

#include <argot/void_.hpp>

#include <boost/thread/barrier.hpp>

#include <memory>
#include <type_traits>
#include <utility>

namespace argot_future_like_testing {

template< class T >
class wrapped
{
 public:
  explicit wrapped( T&& v ) : value_( std::move( v ) ) {}
  explicit wrapped( T const& v ) : value_( v ) {}

  T value() && { return std::forward< T >( value_ ); }
 private:
  T value_;
};

template< class T >
class wrapped< T& >
{
 public:
  explicit wrapped( T& v ) : value_( std::addressof( v ) ) {}

  T& value() && { return *value_; }
 private:
  T* value_;
};

template< class T >
struct wrap
{
  wrapped< T > operator()( T const& value ) &&
  {
    return wrapped< T >( value );
  }

  wrapped< T > operator()( T&& value ) &&
  {
    return wrapped< T >( std::move( value ) );
  }
};

template< class T >
struct wrap< T& >
{
  wrapped< T& > operator()( T& value ) &&
  {
    return wrapped< T& >( value );
  }
};

template< class T >
struct persistent_wrap
{
  wrapped< T > operator()( T const& value ) &&
  {
    return wrapped< T >( value );
  }

  wrapped< T > operator()( T&& value ) &&
  {
    return wrapped< T >( std::move( value ) );
  }
};

template< class T >
struct persistent_wrap< T& >
{
  wrapped< T& > operator()( T& value ) &&
  {
    return wrapped< T& >( value );
  }
};

template< template< class > class Promise, class T >
struct hesitate
{
  Promise< T > prom;
  boost::barrier* wall;
  argot::void_to_regular_void_t< T > value;

  void operator()() &&
  {
    wall->wait();

    if constexpr( std::is_void_v< T > )
      prom.set_value();
    else
      prom.set_value( value );
  }
};

}  // namespace argot_future_like_testing

#endif  // ARGOT_TEST_FUTURE_LIKE_TESTING_HPP_
