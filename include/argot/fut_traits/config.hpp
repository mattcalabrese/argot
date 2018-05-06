/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUTURE_TRAITS_CONFIG_HPP_
#define ARGOT_FUTURE_TRAITS_CONFIG_HPP_

#ifdef ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION
#error ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION was manually defined but should not be.
#elif    defined( BOOST_THREAD_PROVIDES_FUTURE )                               \
      && defined( BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION )                  \
      && defined( BOOST_THREAD_PROVIDES_EXECUTORS )
#define ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION 1
#define ARGOT_BOOST_FUTURE_HEADER_IF_SUPPORTED() <boost/thread/future.hpp>
#else
#define ARGOT_BOOST_FUTURE_HEADER_IF_SUPPORTED()                               \
<argot/detail/copyright_and_license.hpp>
#endif  // ARGOT_HAS_BOOST_FUTURE_WITH_CONTINUATION

#ifdef ARGOT_HAS_STLAB_FUTURE
#error ARGOT_HAS_STLAB_FUTURE was manually defined but should not be.
#elif __has_include( <stlab/concurrency/future.hpp> )
#define ARGOT_HAS_STLAB_FUTURE 1
#define ARGOT_STLAB_FUTURE_HEADER_IF_SUPPORTED()                               \
<argot/fut_traits/detail/stlab_future.hpp>
#else
#define ARGOT_STLAB_FUTURE_HEADER_IF_SUPPORTED()                               \
<argot/detail/copyright_and_license.hpp>
#endif  // ARGOT_HAS_STLAB_FUTURE

#ifdef ARGOT_HAS_STD_EXPERIMENTAL_FUTURE
#error ARGOT_HAS_STD_EXPERIMENTAL_FUTURE was manually defined but should not be.
#elif __has_include( <experimental/future> )
#define ARGOT_HAS_STD_EXPERIMENTAL_FUTURE 1
#define ARGOT_STD_EXPERIMENTAL_FUTURE_HEADER_IF_SUPPORTED()                    \
<experimental/future>
#else
#define ARGOT_STD_EXPERIMENTAL_FUTURE_HEADER_IF_SUPPORTED()                    \
<argot/detail/copyright_and_license.hpp>
#endif  // ARGOT_HAS_STD_EXPERIMENTAL_FUTURE

#ifdef ARGOT_HAS_STD_EXPERIMENTAL_SHARED_FUTURE
#error ARGOT_HAS_STD_EXPERIMENTAL_SHARED_FUTURE was manually defined but should not be.
#elif __has_include( <experimental/shared_future> )
#define ARGOT_HAS_STD_EXPERIMENTAL_SHARED_FUTURE 1
#define ARGOT_STD_EXPERIMENTAL_SHARED_FUTURE_HEADER_IF_SUPPORTED()             \
<experimental/shared_future>
#else
#define ARGOT_STD_EXPERIMENTAL_SHARED_FUTURE_HEADER_IF_SUPPORTED()             \
<argot/detail/copyright_and_license.hpp>
#endif  // ARGOT_HAS_STD_EXPERIMENTAL_SHARED_FUTURE

#endif  // ARGOT_FUTURE_TRAITS_CONFIG_HPP_
