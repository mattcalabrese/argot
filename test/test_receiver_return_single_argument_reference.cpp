/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/receiver/return_single_argument_reference.hpp>
#include <argot/receiver_traits/receive_branch.hpp>

#include <argot/type_list.hpp>

#include <stdexcept>
#include <tuple>

namespace {

using argot::receiver::return_single_argument_reference;
using argot::receiver::return_single_argument_reference_t;
using argot::receiver_traits::receive_branch;
using argot::receiver_traits::result_of_receive_branch;
using argot::receiver_traits::result_of_receive_branch_t;
using argot::type_list;

template<class>
struct immovable {
  explicit constexpr immovable( int const value ) : value( value ) {}

  constexpr immovable( immovable&& other ) = delete;

  int value;
};

using foo = immovable<class foo_t>;
using bar = immovable<class bar_t>;

// TODO(mattcalabrese) Test that move is used

// TODO(mattcalabrese) Test SFINAE behavior with call_detail::is_detected_v

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonbranching )
{
  {
    foo foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list<>{}
        , type_list<>{}
        , foo_1
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo& >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 0 );
    foo& v = std::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_EQ( &v, &foo_1 );
  }

  {
    foo foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list<>{}
        , type_list<>{}
        , std::move( foo_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo&& >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo&&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 0 );
    foo& v = std::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_EQ( &v, &foo_1 );
  }

  {
    foo const foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list<>{}
        , type_list<>{}
        , foo_1
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo const& >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo const&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 0 );
    foo const& v = std::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_EQ( &v, &foo_1 );
  }

  {
    foo const foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list<>{}
        , type_list<>{}
        , std::move( foo_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo const&& >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo const&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list<>
        , foo const&&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 0 );
    foo const& v = std::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_EQ( &v, &foo_1 );
  }

  return 0;
}
/*
ARGOT_REGISTER_CONSTEXPR_TEST( test_branching )
{
  foo foo_1( 1 );
  foo const foo_2( 2 );

  bar bar_1( 1 );
  bar const bar_2( 2 );

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list<>{}
        , type_list
          < type_list< foo const& >
          , type_list< bar&& >, type_list< bar const& >
          >{}
        , std::move( foo_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list
          < type_list< foo const& >
          , type_list< bar&& >, type_list< bar const& >
          >
        , foo&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list<>
        , type_list
          < type_list< foo const& >
          , type_list< bar&& >, type_list< bar const& >
          >
        , foo&&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 0 );
    foo& v = std::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_TRUE( foo_1.moved );
  }

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list< type_list< foo&& > >{}
        , type_list
          < type_list< bar&& >, type_list< bar const& > >{}
        , foo_2
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list< type_list< foo&& > >
        , type_list
          < type_list< bar&& >, type_list< bar const& > >
        , foo const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list< type_list< foo&& > >
        , type_list
          < type_list< bar&& >, type_list< bar const& > >
        , foo const&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 1 );
    foo& v = std::get< 1 >( result );

    ARGOT_TEST_EQ( v.value, 2 );
    ARGOT_TEST_FALSE( foo_2.moved );
  }

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list< type_list< foo&& >, type_list< foo const& > >{}
        , type_list
          < type_list< bar const& > >{}
        , std::move( bar_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list< type_list< foo&& >, type_list< foo const& > >
        , type_list
          < type_list< bar const& > >
        , bar&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list< type_list< foo&& >, type_list< foo const& > >
        , type_list
          < type_list< bar const& > >
        , bar&&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 2 );
    bar& v = std::get< 2 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_TRUE( bar_1.moved );
  }

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_reference
        , type_list
          < type_list< foo&& >, type_list< foo const& >
          , type_list< bar&& >
          >{}
        , type_list<>{}
        , bar_2
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < return_single_argument_reference_t const&
        , type_list
          < type_list< foo&& >, type_list< foo const& >
          , type_list< bar&& >
          >
        , type_list<>
        , bar const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < return_single_argument_reference_t const&
        , type_list
          < type_list< foo&& >, type_list< foo const& >
          , type_list< bar&& >
          >
        , type_list<>
        , bar const&
        >::type
      >
    );

    ARGOT_TEST_EQ( result.index(), 3 );
    bar& v = std::get< 3 >( result );

    ARGOT_TEST_EQ( v.value, 2 );
    ARGOT_TEST_FALSE( bar_2.moved );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
