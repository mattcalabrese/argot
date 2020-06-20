/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/tuple_traits/get.hpp>

#include <stdexcept>

namespace {

using argot::SameType;

using argot::receiver::return_argument_references;
using argot::receiver::return_argument_references_t;
using argot::receiver::result_of_return_argument_references_t;
using argot::receiver_traits::receive_branch;
using argot::receiver_traits::argument_types;
using argot::receiver_traits::argument_types_t;
using argot::receiver_traits::argument_list_kinds;
using argot::receiver_traits::argument_list_kinds_t;
using argot::receiver_traits::result_of_receive_branch;
using argot::receiver_traits::result_of_receive_branch_t;

namespace tuple_traits = argot::tuple_traits;

enum class foo { zero, a, b, c };
enum class bar { zero, a, b, c };

// TODO(mattcalabrese) Test SFINAE behavior with call_detail::is_detected_v

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonbranching )
{
  {
    decltype( auto ) args
      = receive_branch
        ( return_argument_references()
        , argument_list_kinds()
        , argument_list_kinds()
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant< argot::struct_<> >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
  }

  {
    foo                foo_a = foo::a;
    foo const          const_foo_a = foo::a;
    foo volatile       volatile_foo_a = foo::a;
    foo volatile const const_volatile_foo_a = foo::a;

    bar                bar_a = bar::a;
    bar const          const_bar_a = bar::a;
    bar volatile       volatile_bar_a = bar::a;
    bar volatile const const_volatile_bar_a = bar::a;

    // lvalue
    {
      decltype( auto ) args
        = receive_branch
          ( return_argument_references()
          , argument_list_kinds()
          , argument_list_kinds()
          , foo_a, const_foo_a, volatile_foo_a, const_volatile_foo_a
          , bar_a, const_bar_a, volatile_bar_a, const_volatile_bar_a
          );

      using result_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < result_type
        , std::variant
          < argot::struct_
            < foo&, foo const&, foo volatile&, foo volatile const&
            , bar&, bar const&, bar volatile&, bar volatile const&
            >
          >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < result_type
        , result_of_receive_branch_t
          < result_of_return_argument_references_t&&
          , argument_list_kinds_t<>
          , argument_list_kinds_t<>
          , foo&, foo const&, foo volatile&, foo volatile const&
          , bar&, bar const&, bar volatile&, bar volatile const&
          >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < result_type
        , result_of_receive_branch
          < result_of_return_argument_references_t&&
          , argument_list_kinds_t<>
          , argument_list_kinds_t<>
          , foo&, foo const&, foo volatile&, foo volatile const&
          , bar&, bar const&, bar volatile&, bar volatile const&
          >::type
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );

      decltype( auto ) tup = std::get< 0 >( args );

      // lvalue foo value checks
      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), foo::a );
      ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), foo::a );

      // lvalue foo address checks
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &foo_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &const_foo_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &volatile_foo_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &const_volatile_foo_a );

      // lvalue bar value checks
      ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), bar::a );
      ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), bar::a );

      // lvalue bar address checks
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &bar_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &const_bar_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 6 >( tup ), &volatile_bar_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 7 >( tup ), &const_volatile_bar_a );
    }

    // rvalue
    {
      decltype( auto ) args
        = receive_branch
          ( return_argument_references()
          , argument_list_kinds()
          , argument_list_kinds()
          , std::move( foo_a ), std::move( const_foo_a )
          , std::move( volatile_foo_a ), std::move( const_volatile_foo_a )
          , std::move( bar_a ), std::move( const_bar_a )
          , std::move( volatile_bar_a ), std::move( const_volatile_bar_a )
          );

      using result_type = decltype( args );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < result_type
        , std::variant
          < argot::struct_
            < foo&&, foo const&&, foo volatile&&, foo volatile const&&
            , bar&&, bar const&&, bar volatile&&, bar volatile const&&
            >
          >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < result_type
        , result_of_receive_branch_t
          < result_of_return_argument_references_t&&
          , argument_list_kinds_t<>
          , argument_list_kinds_t<>
          , foo&&, foo const&&, foo volatile&&, foo volatile const&&
          , bar&&, bar const&&, bar volatile&&, bar volatile const&&
          >
        >
      );

      ARGOT_CONCEPT_ENSURE
      ( SameType
        < result_type
        , result_of_receive_branch
          < result_of_return_argument_references_t&&
          , argument_list_kinds_t<>
          , argument_list_kinds_t<>
          , foo&&, foo const&&, foo volatile&&, foo volatile const&&
          , bar&&, bar const&&, bar volatile&&, bar volatile const&&
          >::type
        >
      );

      ARGOT_TEST_EQ( args.index(), 0 );

      decltype( auto ) tup = std::get< 0 >( args );

      // rvalue foo value checks
      ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), foo::a );
      ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), foo::a );

      // rvalue foo address checks
      ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &foo_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &const_foo_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &volatile_foo_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &const_volatile_foo_a );

      // rvalue bar value checks
      ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), bar::a );
      ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), bar::a );

      // rvalue bar address checks
      ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &bar_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &const_bar_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 6 >( tup ), &volatile_bar_a );
      ARGOT_TEST_EQ( &tuple_traits::get< 7 >( tup ), &const_volatile_bar_a );
    }
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_branching )
{
  foo                foo_a = foo::a;
  foo const          const_foo_a = foo::a;

  bar                bar_a = bar::a;
  bar const          const_bar_a = bar::a;

  {
    decltype( auto ) args
      = receive_branch
        ( return_argument_references()
        , argument_list_kinds()
        , argument_list_kinds
          ( argument_types<>
          , argument_types<>
          , argument_types< foo const& >
          , argument_types< bar const&& >
          )
        , foo_a, std::move( bar_a )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< foo&, bar&& >
        , argot::struct_<>
        , argot::struct_<>
        , argot::struct_< foo const& >
        , argot::struct_< bar const&& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t<>
          , argument_types_t< foo const& >
          , argument_types_t< bar const&& >
          >
        , foo&, bar&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t<>
          , argument_types_t< foo const& >
          , argument_types_t< bar const&& >
          >
        , foo&, bar&&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );

    decltype( auto ) tup = std::get< 0 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), foo::a );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), bar::a );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &foo_a );
    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &bar_a );
  }

  {
    decltype( auto ) args
      = receive_branch
        ( return_argument_references()
        , argument_list_kinds( argument_types< foo&, bar&& > )
        , argument_list_kinds
          ( argument_types<>
          , argument_types< foo const& >
          , argument_types< bar const&& >
          )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< foo&, bar&& >
        , argot::struct_<>
        , argot::struct_<>
        , argot::struct_< foo const& >
        , argot::struct_< bar const&& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t< argument_types_t< foo&, bar&& > >
        , argument_list_kinds_t< argument_types_t<>
        , argument_types_t< foo const& >
        , argument_types_t< bar const&& > >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&, bar&& > >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< foo const& >
          , argument_types_t< bar const&& >
          >
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 1 );
  }

  {
    decltype( auto ) args
      = receive_branch
        ( return_argument_references()
        , argument_list_kinds( argument_types< foo&, bar&& >, argument_types<> )
        , argument_list_kinds
          ( argument_types< foo const& >
          , argument_types< bar const&& >
          )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< foo&, bar&& >
        , argot::struct_<>
        , argot::struct_<>
        , argot::struct_< foo const& >
        , argot::struct_< bar const&& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&, bar&& >
          , argument_types_t<>
          >
        , argument_list_kinds_t
          < argument_types_t< foo const& >
          , argument_types_t< bar const&& >
          >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&, bar&& >
          , argument_types_t<>
          >
        , argument_list_kinds_t
          < argument_types_t< foo const& >
          , argument_types_t< bar const&& >
          >
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 2 );
  }

  {
    decltype( auto ) args
      = receive_branch
        ( return_argument_references()
        , argument_list_kinds
          ( argument_types< foo&, bar&& >
          , argument_types<>
          , argument_types<>
          )
        , argument_list_kinds( argument_types< bar const&& > )
        , const_foo_a
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< foo&, bar&& >
        , argot::struct_<>
        , argot::struct_<>
        , argot::struct_< foo const& >
        , argot::struct_< bar const&& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&, bar&& >
          , argument_types_t<>
          , argument_types_t<>
          >
        , argument_list_kinds_t
          < argument_types_t< bar const&& > >
        , foo const&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&, bar&& >
          , argument_types_t<>
          , argument_types_t<>
          >
        , argument_list_kinds_t
          < argument_types_t< bar const&& > >
        , foo const&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 3 );

    decltype( auto ) tup = std::get< 3 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), foo::a );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &const_foo_a );
  }

  {
    decltype( auto ) args
      = receive_branch
        ( return_argument_references()
        , argument_list_kinds
          ( argument_types< foo&, bar&& >
          , argument_types<>
          , argument_types<>
          , argument_types< foo const& >
          )
        , argument_list_kinds()
        , std::move( const_bar_a )
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< foo&, bar&& >
        , argot::struct_<>
        , argot::struct_<>
        , argot::struct_< foo const& >
        , argot::struct_< bar const&& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&, bar&& >
          , argument_types_t<>
          , argument_types_t<>
          , argument_types_t< foo const& >
          >
        , argument_list_kinds_t<>
        , bar const&&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < result_of_return_argument_references_t&&
        , argument_list_kinds_t
          < argument_types_t< foo&, bar&& >
          , argument_types_t<>
          , argument_types_t<>
          , argument_types_t< foo const& >
          >
        , argument_list_kinds_t<>
        , bar const&&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 4 );

    decltype( auto ) tup = std::get< 4 >( args );

    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), bar::a );
    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &const_bar_a );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
