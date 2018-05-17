/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/union_.hpp>

#include <argot/concepts/constructible.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/union_traits/alternative_type.hpp>
#include <argot/union_traits/get.hpp>
#include <argot/union_traits/index_constant.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/num_alternatives.hpp>

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>

// TODO(mattcalabrese) Test "odd" types (references, void).

namespace {

namespace union_traits = argot::union_traits;

using argot::Constructible;
using argot::Not;
using argot::SameType;
using argot::SameValue;
using argot::UnionLike;

using argot::union_;

ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary_union )
{
  using union_t = union_<>;

  ARGOT_CONCEPT_ENSURE( UnionLike< union_t > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < union_traits::index_type_t< union_t >
    , std::size_t
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameValue
    < union_traits::num_alternatives_v< union_t >
    , std::size_t{ 0 }
    >
  );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_unary_union )
{
  {
    using alt_t = int;
    using union_t = union_< alt_t >;

    ARGOT_CONCEPT_ENSURE( UnionLike< union_t > );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::index_type_t< union_t >
      , std::size_t
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameValue
      < union_traits::num_alternatives_v< union_t >
      , std::size_t{ 1 }
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::alternative_type_t< union_t, 0 >
      , alt_t
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t& >
      , alt_t&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t const& >
      , alt_t const&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t&& >
      , alt_t&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t const && >
      , alt_t const&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile& >
      , alt_t volatile&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile const& >
      , alt_t volatile const&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile&& >
      , alt_t volatile&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile const&& >
      , alt_t volatile const &&
      >
    );

    ARGOT_CONCEPT_ENSURE( Constructible< union_t > );

    {
      union_t un( std::in_place_index< 0 >, 5 );
      union_t const& const_un = un;

      auto const& res_const_lvalue = union_traits::get< 0 >( const_un );

      auto const&& res_const_rvalue
        = union_traits::get< 0 >( std::move( const_un ) );

      auto& res_lvalue = union_traits::get< 0 >( un );

      auto&& res_rvalue = union_traits::get< 0 >( std::move( un ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );
    }
  }

  return 0;
}

ARGOT_REGISTER_TEST( test_binary_union )
{
  {
    using alt0_t = int;
    using alt1_t = char;
    using union_t = union_< alt0_t, alt1_t >;

    ARGOT_CONCEPT_ENSURE( UnionLike< union_t > );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::index_type_t< union_t >
      , std::size_t
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameValue
      < union_traits::num_alternatives_v< union_t >
      , std::size_t{ 2 }
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::alternative_type_t< union_t, 0 >
      , alt0_t
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::alternative_type_t< union_t, 1 >
      , alt1_t
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t& >
      , alt0_t&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t const& >
      , alt0_t const&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t&& >
      , alt0_t&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t const && >
      , alt0_t const&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile& >
      , alt0_t volatile&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile const& >
      , alt0_t volatile const&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile&& >
      , alt0_t volatile&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 0, union_t volatile const&& >
      , alt0_t volatile const &&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t& >
      , alt1_t&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t const& >
      , alt1_t const&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t&& >
      , alt1_t&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t const && >
      , alt1_t const&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t volatile& >
      , alt1_t volatile&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t volatile const& >
      , alt1_t volatile const&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t volatile&& >
      , alt1_t volatile&&
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < union_traits::result_of_get_t< 1, union_t volatile const&& >
      , alt1_t volatile const &&
      >
    );

    {
      union_t un( std::in_place_index< 0 >, 5 );

      union_t const& const_un = un;

      auto const& res_const_lvalue = union_traits::get< 0 >( const_un );

      auto const&& res_const_rvalue
        = union_traits::get< 0 >( std::move( const_un ) );

      auto& res_lvalue = union_traits::get< 0 >( un );

      auto&& res_rvalue = union_traits::get< 0 >( std::move( un ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

      ARGOT_TEST_EQ( union_traits::get< 0 >( un ), 5 );
    }

    {
      union_t un( std::in_place_index< 1 >, 'A' );

      union_t const& const_un = un;

      auto const& res_const_lvalue = union_traits::get< 1 >( const_un );

      auto const&& res_const_rvalue
        = union_traits::get< 1 >( std::move( const_un ) );

      auto& res_lvalue = union_traits::get< 1 >( un );

      auto&& res_rvalue = union_traits::get< 1 >( std::move( un ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_lvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_rvalue ) );

      ARGOT_TEST_EQ
      ( std::addressof( res_lvalue ), std::addressof( res_const_rvalue ) );

      ARGOT_TEST_EQ( union_traits::get< 1 >( un ), 'A' );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
