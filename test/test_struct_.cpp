/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/struct_.hpp>

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/tuple_traits/natural_get.hpp>
#include <argot/tuple_traits/index_constant.hpp>

#include "regularity_archetypes.hpp"
#include "regularity_facilities.hpp"
#include "regularity_testing.hpp"

#include <type_traits>

namespace {

namespace tuple_traits = argot::tuple_traits;
using argot_test::syntactic_regularity_profile_of_t;
using argot_test::trivially_complete_profile;
using argot::SameType;
using argot::struct_;
using argot::make_struct;
using argot::make_referential_struct;

struct a{}; struct b{}; struct c{};
using tuple_type = struct_< a, b, c >;

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_lvalue )
{
  tuple_type tup( argot::in_place_with_result
                , []{ return a(); }
                , []{ return b(); }
                , []{ return c{}; }
                );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 0 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 0 > )
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 1 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 1 > )
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 2 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 2 > )
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_lvalue_const )
{
  tuple_type const tup( argot::in_place_with_result
                      , []{ return a(); }
                      , []{ return b(); }
                      , []{ return c{}; }
                      );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 0 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 0 > )
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 1 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 1 > )
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 2 >( tup )
  , &tuple_traits::natural_get
    ( tup, tuple_traits::index_constant_v< tuple_type, 2 > )
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_rvalue )
{
  tuple_type tup( argot::in_place_with_result
                , []{ return a(); }
                , []{ return b(); }
                , []{ return c{}; }
                );

  {
    a&& element_reference
      = tuple_traits::natural_get
        ( std::move( tup ), tuple_traits::index_constant_v< tuple_type, 0 > );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &element_reference );
  }

  {
    b&& element_reference
      = tuple_traits::natural_get
        ( std::move( tup ), tuple_traits::index_constant_v< tuple_type, 1 > );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &element_reference );
  }

  {
    c&& element_reference
      = tuple_traits::natural_get
        ( std::move( tup ), tuple_traits::index_constant_v< tuple_type, 2 > );

    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &element_reference );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_make_struct )
{
  float zero = 0.f;
  char x = 'x';
  const int three = 3;

  decltype( auto ) tup
    = make_struct( zero
                 , std::move( x )
                 , three
                 );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( tup ), struct_< float, char, int > > );

  ARGOT_TEST_EQ
  ( tuple_traits::get< 0 >( tup )
  , 0.f
  );

  ARGOT_TEST_EQ
  ( tuple_traits::get< 1 >( tup )
  , 'x'
  );

  ARGOT_TEST_EQ
  ( tuple_traits::get< 2 >( tup )
  , 3
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_make_referential_struct )
{
  float zero = 0.f;
  char x = 'x';
  const int three = 3;

  decltype( auto ) tup
    = make_referential_struct( zero
                             , std::move( x )
                             , three
                             );

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( tup ), struct_< float&, char&&, int const& > > );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 0 >( tup )
  , &zero
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 1 >( tup )
  , &x
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 2 >( tup )
  , &three
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_get_compatible_index_type )
{
  tuple_type tup( argot::in_place_with_result
                , []{ return a(); }
                , []{ return b(); }
                , []{ return c{}; }
                );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 0 >( tup )
  , &tuple_traits::natural_get( tup, std::integral_constant< char, 0 >() )
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 1 >( tup )
  , &tuple_traits::natural_get( tup, std::integral_constant< char, 1 >() )
  );

  ARGOT_TEST_EQ
  ( &tuple_traits::get< 2 >( tup )
  , &tuple_traits::natural_get( tup, std::integral_constant< char, 2 >() )
  );

  return 0;
}

// TODO(mattcalabrese) Test noexcept propagation.
template< class ExpectedStructProfile
        , class... ElementProfiles
        , std::size_t... Values
        >
constexpr ::argot::call_detail::constexpr_block_result_t
test_struct_of_archetypes_regularity( std::index_sequence< Values... >)
{
  static_assert( sizeof...( ElementProfiles ) >= 3 );

  {
    using tup
      = struct_
        < argot_test::regularity_archetype< ElementProfiles >... >;

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < syntactic_regularity_profile_of_t< tup >
      , ExpectedStructProfile
      >
    );

    ARGOT_TEST_SUCCESS
    ( argot_test::test_regularity< tup, ExpectedStructProfile >
      ( []{ return tup
            ( argot::in_place_with_result
            , []
              {
                return argot_test::regularity_archetype< ElementProfiles >
                       ::make( 0 );
              }...
            );
          }
      , []{ return tup
            ( argot::in_place_with_result
            , []
              {
                return argot_test::regularity_archetype< ElementProfiles >
                       ::make( Values / 2u );
              }...
            );
          }
      , []{ return tup
            ( argot::in_place_with_result
            , []
              {
                return argot_test::regularity_archetype< ElementProfiles >
                       ::make( Values );
              }...
            );
          }
      , []{ return tup
            ( argot::in_place_with_result
            , []
              {
                return argot_test::regularity_archetype< ElementProfiles >
                       ::make( sizeof...( ElementProfiles ) - Values );
              }...
            );
          }
      )
    );
  }

  return 0;
}

// TODO(mattcalabrese) Add a wider variety of test cases.
ARGOT_REGISTER_TEST // TODO(mattcalabrese) Make constexpr
( test_struct_regularity )
{
  using argot_test::combine_regularity_profiles_t;

  ARGOT_TEST_SUCCESS
  ( test_struct_of_archetypes_regularity
    < trivially_complete_profile
    , trivially_complete_profile
    , trivially_complete_profile
    , trivially_complete_profile
    >( std::make_index_sequence< 3 >() )
  );

  ARGOT_TEST_SUCCESS
  ( test_struct_of_archetypes_regularity
    < trivially_complete_profile
    , trivially_complete_profile
    , trivially_complete_profile
    , trivially_complete_profile
    , trivially_complete_profile
    >( std::make_index_sequence< 4 >() )
  );

  return 0;
}

ARGOT_EXECUTE_TESTS();

} // namespace
