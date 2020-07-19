/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver/return_single_argument_value.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <stdexcept>

namespace {

namespace variant_traits = argot::variant_traits;

using argot::SameType;

using argot::discriminated_union;
using argot::receiver::result_of_return_single_argument_value_t;
using argot::receiver::return_single_argument_value;
using argot::receiver::return_single_argument_value_t;
using argot::receiver_traits::receive_branch;
using argot::receiver_traits::result_of_receive_branch;
using argot::receiver_traits::result_of_receive_branch_t;
using argot::receiver_traits::argument_types;
using argot::receiver_traits::argument_types_t;
using argot::receiver_traits::argument_list_kinds;
using argot::receiver_traits::argument_list_kinds_t;

class read_from_moved_object_t
  : public std::exception
{
 public:
  char const* what() const noexcept { return "Read from moved object."; }
} const read_from_moved_object{};

template<class>
struct dummy {
  explicit constexpr dummy( int const value ) : value( value ) {}

  constexpr dummy( dummy&& other )
    : value( other.value )
  {
    if( other.moved )
    {
      throw read_from_moved_object;
    }

    other.moved = true;
  }

  constexpr dummy( dummy const& other )
    : value( other.value ), moved( false )
  {
    if( other.moved )
    {
      throw read_from_moved_object;
    }
  }

  int value;
  bool moved = false;
};

using foo = dummy<class foo_t>;
using bar = dummy<class bar_t>;

// TODO(mattcalabrese) Test that move is used

// TODO(mattcalabrese) Test SFINAE behavior with call_detail::is_detected_v

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonbranching )
{
  {
    foo foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds()
        , argument_list_kinds()
        , foo_1
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 0 );
    foo& v = variant_traits::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_FALSE( foo_1.moved );
  }

  {
    foo foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds()
        , argument_list_kinds()
        , std::move( foo_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo&&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 0 );
    foo& v = variant_traits::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_TRUE( foo_1.moved );
  }

  {
    foo const foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds()
        , argument_list_kinds()
        , foo_1
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo const&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 0 );
    foo& v = variant_traits::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_FALSE( foo_1.moved );
  }

  {
    foo const foo_1( 1 );

    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds()
        , argument_list_kinds()
        , std::move( foo_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo const&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo const&&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 0 );
    foo& v = variant_traits::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_FALSE( foo_1.moved );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_branching )
{
  foo foo_1( 1 );
  foo const foo_2( 2 );

  bar bar_1( 1 );
  bar const bar_2( 2 );

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds()
        , argument_list_kinds
          ( argument_types< foo const& >
          , argument_types< bar&& >
          , argument_types< bar const& >
          )
        , std::move( foo_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t
          < argument_types_t< foo const& >
          , argument_types_t< bar&& >
          , argument_types_t< bar const& >
          >
        , foo&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t
          < argument_types_t< foo const& >
          , argument_types_t< bar&& >
          , argument_types_t< bar const& >
          >
        , foo&&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 0 );
    foo& v = variant_traits::get< 0 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_TRUE( foo_1.moved );
  }

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds( argument_types< foo&& > )
        , argument_list_kinds
          ( argument_types< bar&& >
          , argument_types< bar const& >
          )
        , foo_2
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t< argument_types_t< foo&& > >
        , argument_list_kinds_t
          < argument_types_t< bar&& >
          , argument_types_t< bar const& >
          >
        , foo const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t< argument_types_t< foo&& > >
        , argument_list_kinds_t
          < argument_types_t< bar&& >, argument_types_t< bar const& > >
        , foo const&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 1 );
    foo& v = variant_traits::get< 1 >( result );

    ARGOT_TEST_EQ( v.value, 2 );
    ARGOT_TEST_FALSE( foo_2.moved );
  }

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds
          ( argument_types< foo&& >, argument_types< foo const& > )
        , argument_list_kinds
          ( argument_types< bar const& > )
        , std::move( bar_1 )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&& >, argument_types_t< foo const& > >
        , argument_list_kinds_t
          < argument_types_t< bar const& > >
        , bar&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&& >, argument_types_t< foo const& > >
        , argument_list_kinds_t
          < argument_types_t< bar const& > >
        , bar&&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 2 );
    bar& v = variant_traits::get< 2 >( result );

    ARGOT_TEST_EQ( v.value, 1 );
    ARGOT_TEST_TRUE( bar_1.moved );
  }

  {
    decltype( auto ) result
      = receive_branch
        ( return_single_argument_value()
        , argument_list_kinds
          ( argument_types< foo&& >
          , argument_types< foo const& >
          , argument_types< bar&& >
          )
        , argument_list_kinds()
        , bar_2
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< foo, foo, bar, bar >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&& >
          , argument_types_t< foo const& >
          , argument_types_t< bar&& >
          >
        , argument_list_kinds_t<>
        , bar const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_single_argument_value_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&& >
          , argument_types_t< foo const& >
          , argument_types_t< bar&& >
          >
        , argument_list_kinds_t<>
        , bar const&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( result ), 3 );
    bar& v = variant_traits::get< 3 >( result );

    ARGOT_TEST_EQ( v.value, 2 );
    ARGOT_TEST_FALSE( bar_2.moved );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
