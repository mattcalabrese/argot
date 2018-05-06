/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/intermediate_reducer.hpp>
#include <argot/detail/type_list.hpp>
#include <argot/reducer_of.hpp>
#include <argot/reducer_traits/is_homogeneous.hpp>

#include <type_traits>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using argot::call_detail::forward_intermediate_reducer;
using argot::call_detail::type_list;
using argot::reducer_of;

struct eat_all
{
  template< class T >
  eat_all( T&& ) {}
};

struct trivial_reducer_spec
{
  template< class... T >
  using return_type = eat_all;
};

using trivial_reducer
  = argot::reducer_traits::reducer_of_t
    < trivial_reducer_spec, int, float, char >;

ARGOT_CONCEPT_ENSURE
( SameType
  < trivial_reducer&&
  , decltype
    ( forward_intermediate_reducer< 2 >( std::declval< trivial_reducer >() ) )
  >::value

);

struct nontrivial_reducer_spec
{
  template< class... T >
  using return_type = std::size_t;

  template< class... T >
  struct reduction_function_specifier
  {
    template< class Self, class Fun, class BranchIndex >
    static return_type< T... > reduce( Self&& self, Fun&& fun, BranchIndex )
    {
      // TODO(mattcalabrese) Test invocation of fun.
      return BranchIndex::value;
    }
  };

  return 0;
} nontrivial_reducer_spec_instance;

template< std::size_t I >
using index = std::integral_constant< std::size_t, I >;

auto nontrivial_reducer
  = reducer_of
    < index< 0 >, index< 1 >, index< 2 >, index< 3 >, index< 4 >, index< 5 >
    , index< 6 >, index< 7 >, index< 8 >, index< 9 >, index< 10 >, index< 11 >
    , index< 12 >, index< 13 >, index< 14 >, index< 15 >
    >( std::move( nontrivial_reducer_spec_instance ) );

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( nontrivial_reducer )&&
  , decltype
    ( forward_intermediate_reducer< 0 >( std::move( nontrivial_reducer ) ) )
  >::value

);

auto intermediate_reducer
  = forward_intermediate_reducer< 3 >( std::move( nontrivial_reducer ) );

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( intermediate_reducer )
  , decltype
    ( forward_intermediate_reducer< 0 >( std::move( intermediate_reducer ) ) )
  >::value

);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( nontrivial_reducer )::return_type
  , decltype( intermediate_reducer )::return_type
  >::value

);

static_assert
( !argot::reducer_traits::is_homogeneous
  < decltype( intermediate_reducer ) >::value

);

BOOST_AUTO_TEST_CASE( nontrivial_intermediate_reducer )
{
  using argot::reducer_traits::reduce;

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 0 >() ) )
    == 3u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 1 >() ) )
    == 4u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 2 >() ) )
    == 5u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 3 >() ) )
    == 6u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 4 >() ) )
    == 7u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 5 >() ) )
    == 8u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 6 >() ) )
    == 9u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 7 >() ) )
    == 10u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 8 >() ) )
    == 11u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 9 >() ) )
    == 12u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 10 >() ) )
    == 13u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 11 >() ) )
    == 14u
  );

  BOOST_TEST
  ( ( reduce( std::move( intermediate_reducer ), []{}, index< 12 >() ) )
    == 15u
  );

  return 0;
}

auto intermediate_reducer2
  = forward_intermediate_reducer< 5 >( std::move( intermediate_reducer ) );

auto flat_reducer
  = forward_intermediate_reducer< 8 >( std::move( nontrivial_reducer ) );

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( intermediate_reducer2 )
  , decltype( flat_reducer )
  >::value

);
