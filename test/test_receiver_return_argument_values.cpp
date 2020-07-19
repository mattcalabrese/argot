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
#include <argot/receiver/return_argument_values.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <stdexcept>

namespace {

using argot::SameType;
using argot::discriminated_union;
using argot::receiver::result_of_return_argument_values_t;
using argot::receiver::return_argument_values;
using argot::receiver::return_argument_values_t;
using argot::receiver_traits::argument_types;
using argot::receiver_traits::argument_types_t;
using argot::receiver_traits::receive_branch;
using argot::receiver_traits::argument_list_kinds;
using argot::receiver_traits::argument_list_kinds_t;
using argot::receiver_traits::result_of_receive_branch;
using argot::receiver_traits::result_of_receive_branch_t;

namespace tuple_traits = argot::tuple_traits;
namespace variant_traits = argot::variant_traits;

struct move_only_foo {
  explicit constexpr move_only_foo( int const value ) : value( value ) {}
  constexpr move_only_foo( move_only_foo&& other )
    : value( other.value ) {}
  int value;
};

struct foo {
  explicit constexpr foo( int const value ) : value( value ) {}
  int value;
};

// TODO(mattcalabrese) Test with move-only types
// TODO(mattcalabrese) Test SFINAE behavior with call_detail::is_detected_v

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonbranching )
{
  {
    decltype( auto ) args
      = receive_branch
        ( return_argument_values()
        , argument_list_kinds()
        , argument_list_kinds()
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< argot::struct_<> >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
  }

  {
    foo foo_1( 1 );
    foo const const_foo_1( 1 );

    move_only_foo move_only_foo_1( 1 );

    decltype( auto ) args
      = receive_branch
        ( return_argument_values()
        , argument_list_kinds()
        , argument_list_kinds()
        , foo_1, const_foo_1
        , std::move( foo_1 ), std::move( const_foo_1 )
        , std::move( move_only_foo_1 )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< foo, foo, foo, foo, move_only_foo > >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo&, foo const&, foo&&, foo const&&, move_only_foo&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , foo&, foo const&, foo&&, foo const&&, move_only_foo&&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );

    decltype( auto ) tup = variant_traits::get< 0 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ).value, 1 );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ).value, 1 );
    ARGOT_TEST_EQ( tuple_traits::get< 2 >( tup ).value, 1 );
    ARGOT_TEST_EQ( tuple_traits::get< 3 >( tup ).value, 1 );
    ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ).value, 1 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_branching )
{
  {
    foo foo_1( 1 );
    foo const const_foo_1( 1 );

    move_only_foo move_only_foo_1( 1 );

    decltype( auto ) args
      = receive_branch
        ( return_argument_values()
        , argument_list_kinds()
        , argument_list_kinds
          ( argument_types< foo const& >
          ,argument_types< foo&&, foo const&& >
          , argument_types<>
          , argument_types< move_only_foo&& >
          )
        , foo_1
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< foo >
        , argot::struct_< foo >
        , argot::struct_< foo, foo >
        , argot::struct_<>
        , argot::struct_< move_only_foo >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t
          < argument_types_t< foo const& >
          , argument_types_t< foo&&, foo const&& >
          , argument_types_t<>
          , argument_types_t< move_only_foo&& >
          >
        , foo&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t
          < argument_types_t< foo const& >
          , argument_types_t< foo&&, foo const&& >
          , argument_types_t<>
          , argument_types_t< move_only_foo&& >
          >
        , foo&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );

    decltype( auto ) tup = variant_traits::get< 0 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ).value, 1 );
  }

  {
    foo foo_1( 1 );
    foo const const_foo_1( 1 );

    move_only_foo move_only_foo_1( 1 );

    decltype( auto ) args
      = receive_branch
        ( return_argument_values()
        , argument_list_kinds( argument_types< foo& > )
        , argument_list_kinds
          ( argument_types< foo&&, foo const&& >
          , argument_types<>
          , argument_types< move_only_foo&& >
          )
        , const_foo_1
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< foo >
        , argot::struct_< foo >
        , argot::struct_< foo, foo >
        , argot::struct_<>
        , argot::struct_< move_only_foo >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& > >
        , argument_list_kinds_t
          < argument_types_t< foo&&, foo const&& >
          , argument_types_t<>
          , argument_types_t< move_only_foo&& >
          >
        , foo const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& > >
        , argument_list_kinds_t
          < argument_types_t< foo&&, foo const&& >
          , argument_types_t<>
          , argument_types_t< move_only_foo&& >
          >
        , foo const&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 1 );

    decltype( auto ) tup = variant_traits::get< 1 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ).value, 1 );
  }

  {
    foo foo_1( 1 );
    foo const const_foo_1( 1 );

    move_only_foo move_only_foo_1( 1 );

    decltype( auto ) args
      = receive_branch
        ( return_argument_values()
        , argument_list_kinds
          ( argument_types< foo& >
          , argument_types< foo const& >
          )
        , argument_list_kinds
          ( argument_types<>
          , argument_types< move_only_foo&& >
          )
        , std::move( foo_1 ), std::move( const_foo_1 )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< foo >
        , argot::struct_< foo >
        , argot::struct_< foo, foo >
        , argot::struct_<>
        , argot::struct_< move_only_foo >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& >
          , argument_types_t< foo const& >
          >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< move_only_foo&& >
          >
        , foo&&, foo const&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& >
          , argument_types_t< foo const& >
          >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< move_only_foo&& >
          >
        , foo&&, foo const&&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 2 );

    decltype( auto ) tup = variant_traits::get< 2 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ).value, 1 );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ).value, 1 );
  }

  {
    foo foo_1( 1 );
    foo const const_foo_1( 1 );

    move_only_foo move_only_foo_1( 1 );

    decltype( auto ) args
      = receive_branch
        ( return_argument_values()
        , argument_list_kinds
          ( argument_types< foo& >
          , argument_types< foo const& >
          , argument_types< foo&&, foo const&& >
          )
        , argument_list_kinds
          ( argument_types< move_only_foo&& > )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< foo >
        , argot::struct_< foo >
        , argot::struct_< foo, foo >
        , argot::struct_<>
        , argot::struct_< move_only_foo >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& >
          , argument_types_t< foo const& >
          , argument_types_t< foo&&, foo const&& >
          >
        , argument_list_kinds_t
          < argument_types_t< move_only_foo&& > >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& >
          , argument_types_t< foo const& >
          , argument_types_t< foo&&, foo const&& >
          >
        , argument_list_kinds_t
          < argument_types_t< move_only_foo&& > >
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 3 );
  }

  {
    foo foo_1( 1 );
    foo const const_foo_1( 1 );

    move_only_foo move_only_foo_1( 1 );

    decltype( auto ) args
      = receive_branch
        ( return_argument_values()
        , argument_list_kinds
          ( argument_types< foo& >
          , argument_types< foo const& >
          , argument_types< foo&&, foo const&& >
          , argument_types<>
          )
        , argument_list_kinds()
        , std::move( move_only_foo_1 )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< foo >
        , argot::struct_< foo >
        , argot::struct_< foo, foo >
        , argot::struct_<>
        , argot::struct_< move_only_foo >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& >
          , argument_types_t< foo const& >
          , argument_types_t< foo&&, foo const&& >
          , argument_types_t<>
          >
        , argument_list_kinds_t<>
        , move_only_foo&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_values_t&&
        , argument_list_kinds_t
          < argument_types_t< foo& >
          , argument_types_t< foo const& >
          , argument_types_t< foo&&, foo const&& >
          , argument_types_t<>
          >
        , argument_list_kinds_t<>
        , move_only_foo&&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 4 );

    decltype( auto ) tup = variant_traits::get< 4 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ).value, 1 );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
