/*==============================================================================
  Copyright (c) 2020 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/struct_.hpp>
#include <argot/tuple_traits/apply.hpp>
#include <argot/tuple_traits/get.hpp>

#include <tuple>
#include <type_traits>
#include <variant>

#include <type_traits>

namespace {

namespace tuple_traits = argot::tuple_traits;

using tuple_traits::apply;
using tuple_traits::apply_fn;
using tuple_traits::result_of_apply;
using tuple_traits::result_of_apply_t;
using argot::make_referential_struct;
using argot::make_referential_struct_fn;
using argot::struct_;
using argot::SameType;

ARGOT_REGISTER_CONSTEXPR_TEST( test_apply_nullary )
{
  using tuple_type = std::tuple<>;
  tuple_type tup{};

  using expected_result_type = struct_<>;

  // rvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type&& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type&& >::type
      , expected_result_type
      >
    );

    decltype( auto ) result
      = apply
        ( make_referential_struct
        , std::move( tup )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );
  }

  // lvalue
  {
    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type& >::type
      , expected_result_type
      >
    );

    decltype( auto ) result
      = apply
        ( make_referential_struct
        , tup
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_apply_ternary )
{
  using tuple_type = std::tuple< int, float, char >;
  tuple_type tup( 1, 2.f, '3' );

  // rvalue
  {
    using expected_result_type = struct_< int&&, float&&, char&& >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type&& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type&& >::type
      , expected_result_type
      >
    );

    decltype( auto ) result
      = apply
        ( make_referential_struct
        , std::move( tup )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( result ), &std::get< 0 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( result ), &std::get< 1 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( result ), &std::get< 2 >( tup ) );
  }

  // lvalue
  {
    using expected_result_type = struct_< int&, float&, char& >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type& >::type
      , expected_result_type
      >
    );
    
    decltype( auto ) result
      = apply
        ( make_referential_struct
        , tup
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( result ), &std::get< 0 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( result ), &std::get< 1 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( result ), &std::get< 2 >( tup ) );
  }

  // const lvalue
  {
    using expected_result_type
      = struct_< int const&, float const&, char const& >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type const& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type const& >::type
      , expected_result_type
      >
    );
    
    decltype( auto ) result
      = apply
        ( make_referential_struct
        , std::as_const( tup )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( result ), &std::get< 0 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( result ), &std::get< 1 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( result ), &std::get< 2 >( tup ) );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_apply_ternary_qualified_elements )
{
  using tuple_type = std::tuple< int, float&, const char&& >;
  float float_ = 2.f;
  char const char_ = '3';
  tuple_type tup( 1, float_, std::move( char_ ) );

  // rvalue
  {
    using expected_result_type = struct_< int&&, float&, char const&& >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type&& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type&& >::type
      , expected_result_type
      >
    );

    decltype( auto ) result
      = apply
        ( make_referential_struct
        , std::move( tup )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( result ), &std::get< 0 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( result ), &std::get< 1 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( result ), &std::get< 2 >( tup ) );
  }

  // lvalue
  {
    using expected_result_type = struct_< int&, float&, char const& >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type& >::type
      , expected_result_type
      >
    );
    
    decltype( auto ) result
      = apply
        ( make_referential_struct
        , tup
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( result ), &std::get< 0 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( result ), &std::get< 1 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( result ), &std::get< 2 >( tup ) );
  }

  // const lvalue
  {
    using expected_result_type
      = struct_< int const&, float&, char const& >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply_t
        < make_referential_struct_fn const&, tuple_type const& >
      , expected_result_type
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_of_apply
        < make_referential_struct_fn const&, tuple_type const& >::type
      , expected_result_type
      >
    );
    
    decltype( auto ) result
      = apply
        ( make_referential_struct
        , std::as_const( tup )
        );

    using result_type = decltype( result );

    ARGOT_CONCEPT_ENSURE
    ( SameType< result_type, expected_result_type > );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 0 >( result ), &std::get< 0 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 1 >( result ), &std::get< 1 >( tup ) );

    ARGOT_TEST_EQ
    ( &tuple_traits::get< 2 >( result ), &std::get< 2 >( tup ) );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
