/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_REGULARITY_TESTING_HPP_
#define ARGOT_TEST_REGULARITY_TESTING_HPP_

#include <argot/concepts/constructible.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test_utilities.hpp>
#include <argot/detail/constexpr_swap.hpp>
#include <argot/gen/concept_ensure.hpp>

#include <cstddef>
#include <functional>
#include <tuple>
#include <utility>

#include "regularity_facilities.hpp"

namespace argot_test {
namespace detail_regularity_testing {

template< class Fun >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t
test_with_each_parameter( Fun const& fun )
{
  return 0;
}

template< class Fun, class Head, class... Tail >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t
test_with_each_parameter
( Fun const& fun, Head const& head, Tail const&... tail )
{
  ARGOT_TEST_SUCCESS( fun( head ) );

  return ( test_with_each_parameter )( fun, tail... );
}

template< class... T, class Fun >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t
for_every_2( std::tuple< T... > const& tup, Fun const& fun )
{
  return std::apply
  ( [ &tup, &fun ]( auto&... lhs_params )
    {
      return ( test_with_each_parameter )
      ( [ &tup, &fun ]( auto& lhs )
        {
          return std::apply
          ( [ &lhs, &fun ]( auto&... rhs_params )
            {
              return ( test_with_each_parameter )
              ( [ &lhs, &fun ]( auto& rhs ){ return fun( lhs, rhs ); }
              , rhs_params...
              );
            }
          , tup
          );
        }
      , lhs_params...
      );
    }
  , tup
  );
}

template< class T, class RegularityProfile >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t
attempt_equality_check( T const& lhs, T const& rhs )
{
  if constexpr(    RegularityProfile::equality_comparable_kind
                != equality_comparable::no
              )
  {
    ARGOT_TEST_EQ( lhs, rhs );
  }
  else
    if constexpr(    RegularityProfile::inequality_comparable_kind
                  != inequality_comparable::no
                )
    {
      ARGOT_TEST_FAIL_NE( lhs, rhs );
    }
    else
    {
      if constexpr(    RegularityProfile::less_comparable_kind
                    != less_comparable::no
                  )
      {
        ARGOT_TEST_FAIL_LT( lhs, rhs );
      }

      if constexpr(    RegularityProfile::less_equal_comparable_kind
                    != less_equal_comparable::no
                  )
      {
        ARGOT_TEST_LE( lhs, rhs );
      }

      if constexpr(    RegularityProfile::greater_equal_comparable_kind
                    != greater_equal_comparable::no
                  )
      {
        ARGOT_TEST_GE( lhs, rhs );
      }

      if constexpr(    RegularityProfile::greater_comparable_kind
                    != greater_comparable::no
                  )
      {
        ARGOT_TEST_FAIL_GT( lhs, rhs );
      }
    }

  return 0;
}

template< class T, class RegularityProfile
        , class GeneratorRange
        >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t
test_equivalence_class( GeneratorRange const& equivalence_class )
{
  ARGOT_TEST_SUCCESS
  ( std::apply
    ( []( auto const&... generators )
        -> ::argot::call_detail::constexpr_block_result_t
      {
        return ( test_with_each_parameter )
        ( []( auto const& generator )
            -> ::argot::call_detail::constexpr_block_result_t
          {
            decltype( auto ) value = generator();

            ARGOT_CONCEPT_ENSURE( ::argot::SameType< decltype( value ), T > );

            auto const& const_value = value;

            if constexpr
            (    RegularityProfile::move_constructible_kind
              != move_constructible::no
            )
            {
              T const object = std::move( generator() );

              ARGOT_TEST_SUCCESS
              ( ( attempt_equality_check< T, RegularityProfile > )
                ( object, const_value )
              );
            }

            if constexpr
            (    RegularityProfile::copy_constructible_kind
              != copy_constructible::no
            )
            {
              T const object = const_value;

              ARGOT_TEST_SUCCESS
              ( ( attempt_equality_check< T, RegularityProfile > )
                ( object, const_value )
              );
            }

            // TODO(mattcalabrese) Test when not constexpr.
            #if 0
            if constexpr
            (    RegularityProfile::default_constructible_kind
              != default_constructible::no
            )
            {
              if constexpr
              (    RegularityProfile::move_assignable_kind
                != move_assignable::no
              )
              {
                T object;
                object = std::move( generator() );
                T const& const_object = object;

                ARGOT_TEST_SUCCESS
                ( ( attempt_equality_check< T, RegularityProfile > )
                  ( const_object, const_value )
                );
              }

              if constexpr
              (    RegularityProfile::copy_assignable_kind
                != copy_assignable::no
              )
              {
                T object;
                object = const_value;
                T const& const_object = object;

                ARGOT_TEST_SUCCESS
                ( ( attempt_equality_check< T, RegularityProfile > )
                  ( const_object, const_value )
                );
              }
            }
            #endif

            if constexpr( ARGOT_IS_MODELED( argot::Constructible< T > ) )
            {
              if constexpr
              (    RegularityProfile::move_assignable_kind
                != move_assignable::no
              )
              {
                // TODO(mattcalabrese) Also test default-init when constexpr
                T object = T();
                object = std::move( generator() );
                T const& const_object = object;

                ARGOT_TEST_SUCCESS
                ( ( attempt_equality_check< T, RegularityProfile > )
                  ( const_object, const_value )
                );
              }

              if constexpr
              (    RegularityProfile::copy_assignable_kind
                != copy_assignable::no
              )
              {
                // TODO(mattcalabrese) Also test default-init when constexpr
                T object = T();
                object = const_value;
                T const& const_object = object;

                ARGOT_TEST_SUCCESS
                ( ( attempt_equality_check< T, RegularityProfile > )
                  ( const_object, const_value )
                );
              }
            }

            // Self move-assign
            if constexpr
            (    RegularityProfile::move_assignable_kind
              != move_assignable::no
            )
            {
              T object = generator();
              object = std::move( object );
              static_cast< void >( object );

              // NOTE: No equality (self move-assign has weak post-conditions).
            }

            // Self copy-assign
            if constexpr
            (    RegularityProfile::copy_assignable_kind
              != copy_assignable::no
            )
            {
              T object = generator();
              T const& const_object = object;
              object = const_object;

              ARGOT_TEST_SUCCESS
              ( ( attempt_equality_check< T, RegularityProfile > )
                ( const_object, const_value )
              );
            }

            return 0;
          }
        , generators...
        );
      }
    , equivalence_class
    )
  );

  return ( for_every_2 )
  ( equivalence_class
  , []( auto const& lhs_fun, auto const& rhs_fun )
      -> ::argot::call_detail::constexpr_block_result_t
    {
      decltype( auto ) lhs = lhs_fun();
      decltype( auto ) rhs = rhs_fun();

      auto const& const_lhs = lhs;
      auto const& const_rhs = rhs;

      if constexpr
      (    RegularityProfile::equality_comparable_kind
        != equality_comparable::no
      )
      {
        ARGOT_TEST_EQ( const_lhs, const_rhs );
        ARGOT_TEST_EQ( const_rhs, const_lhs );
      }

      if constexpr
      (    RegularityProfile::inequality_comparable_kind
        != inequality_comparable::no
      )
      {
        ARGOT_TEST_FAIL_NE( const_lhs, const_rhs );
        ARGOT_TEST_FAIL_NE( const_rhs, const_lhs );
      }

      if constexpr
      (    RegularityProfile::less_comparable_kind
        != less_comparable::no
      )
      {
        ARGOT_TEST_FAIL_LT( const_lhs, const_rhs );
        ARGOT_TEST_FAIL_LT( const_rhs, const_lhs );
      }

      if constexpr
      (    RegularityProfile::less_equal_comparable_kind
        != less_equal_comparable::no
      )
      {
        ARGOT_TEST_LE( const_lhs, const_rhs );
        ARGOT_TEST_LE( const_rhs, const_lhs );
      }

      if constexpr
      (    RegularityProfile::greater_equal_comparable_kind
        != greater_equal_comparable::no
      )
      {
        ARGOT_TEST_GE( const_lhs, const_rhs );
        ARGOT_TEST_GE( const_rhs, const_lhs );
      }

      if constexpr
      (    RegularityProfile::greater_comparable_kind
        != greater_comparable::no
      )
      {
        ARGOT_TEST_FAIL_GT( const_lhs, const_rhs );
        ARGOT_TEST_FAIL_GT( const_rhs, const_lhs );
      }

      if constexpr
      (    RegularityProfile::move_assignable_kind
        != move_assignable::no
      )
      {
        T object = lhs_fun();
        object = rhs_fun();

        ARGOT_TEST_SUCCESS
        ( ( attempt_equality_check< T, RegularityProfile > )
          ( object, const_rhs )
        );
      }

      if constexpr
      (    RegularityProfile::copy_assignable_kind
        != copy_assignable::no
      )
      {
        T object = lhs_fun();
        object = const_rhs;

        ARGOT_TEST_SUCCESS
        ( ( attempt_equality_check< T, RegularityProfile > )
          ( object, const_rhs )
        );
      }

      if constexpr( RegularityProfile::swappable_kind != swappable::no )
      {
        decltype( auto ) lhs_duplicate = lhs_fun();
        decltype( auto ) rhs_duplicate = rhs_fun();

        ARGOT_TEST_SUCCESS
        ( ( attempt_equality_check< T, RegularityProfile > )
          ( lhs_duplicate, lhs )
        );

        ARGOT_TEST_SUCCESS
        ( ( attempt_equality_check< T, RegularityProfile > )
          ( rhs_duplicate, rhs )
        );

        detail_argot_swap::constexpr_swap( lhs_duplicate, rhs_duplicate );

        ARGOT_TEST_SUCCESS
        ( ( attempt_equality_check< T, RegularityProfile > )
          ( lhs_duplicate, rhs )
        );

        ARGOT_TEST_SUCCESS
        ( ( attempt_equality_check< T, RegularityProfile > )
          ( rhs_duplicate, lhs )
        );
      }

      if constexpr( RegularityProfile::hashable_kind != hashable::no )
      {
        std::size_t const lhs_hash_value = std::hash< T >()( const_lhs );

        std::size_t const rhs_hash_value = std::hash< T >()( const_rhs );

        ARGOT_TEST_EQ( lhs_hash_value, rhs_hash_value );
      }

      return 0;
    }
  );
}

template< class T, class RegularityProfile >
struct test_value_with_greater_value_fn
{
  template< class LhsFun, class RhsFun >
  [[nodiscard]]
  constexpr ::argot::call_detail::constexpr_block_result_t
  operator ()( LhsFun const& lhs_fun, RhsFun const& rhs_fun ) const
  {
    decltype( auto ) lhs = lhs_fun();
    decltype( auto ) rhs = rhs_fun();

    ARGOT_CONCEPT_ENSURE( ::argot::SameType< decltype( lhs ), T > );
    ARGOT_CONCEPT_ENSURE( ::argot::SameType< decltype( rhs ), T > );

    auto const& const_lhs = lhs;
    auto const& const_rhs = rhs;

    if constexpr
    (    RegularityProfile::equality_comparable_kind
      != equality_comparable::no
    )
    {
      ARGOT_TEST_FAIL_EQ( const_lhs, const_rhs );
      ARGOT_TEST_FAIL_EQ( const_rhs, const_lhs );
    }

    if constexpr
    (    RegularityProfile::inequality_comparable_kind
      != inequality_comparable::no
    )
    {
      ARGOT_TEST_NE( const_lhs, const_rhs );
      ARGOT_TEST_NE( const_rhs, const_lhs );
    }

    if constexpr
    (    RegularityProfile::less_comparable_kind
      != less_comparable::no
    )
    {
      ARGOT_TEST_LT( const_lhs, const_rhs );
      ARGOT_TEST_FAIL_LT( const_rhs, const_lhs );
    }

    if constexpr
    (    RegularityProfile::less_equal_comparable_kind
      != less_equal_comparable::no
    )
    {
      ARGOT_TEST_LE( const_lhs, const_rhs );
      ARGOT_TEST_FAIL_LE( const_rhs, const_lhs );
    }

    if constexpr
    (    RegularityProfile::greater_equal_comparable_kind
      != greater_equal_comparable::no
    )
    {
      ARGOT_TEST_FAIL_GE( const_lhs, const_rhs );
      ARGOT_TEST_GE( const_rhs, const_lhs );
    }

    if constexpr
    (    RegularityProfile::greater_comparable_kind
      != greater_comparable::no
    )
    {
      ARGOT_TEST_FAIL_GT( const_lhs, const_rhs );
      ARGOT_TEST_GE( const_rhs, const_lhs );
    }

    if constexpr
    (    RegularityProfile::move_assignable_kind
      != move_assignable::no
    )
    {
      T object = lhs_fun();
      object = rhs_fun();

      ARGOT_TEST_SUCCESS
      ( ( attempt_equality_check< T, RegularityProfile > )
        ( object, const_rhs )
      );
    }

    if constexpr
    (    RegularityProfile::copy_assignable_kind
      != copy_assignable::no
    )
    {
      T object = lhs_fun();
      object = const_rhs;

      ARGOT_TEST_SUCCESS
      ( ( attempt_equality_check< T, RegularityProfile > )
        ( object, const_rhs )
      );
    }

    if constexpr
    (    RegularityProfile::swappable_kind
      != swappable::no
    )
    {
      decltype( auto ) lhs_duplicate = lhs_fun();
      decltype( auto ) rhs_duplicate = rhs_fun();

      ARGOT_TEST_SUCCESS
      ( ( attempt_equality_check< T, RegularityProfile > )
        ( lhs_duplicate, lhs )
      );

      ARGOT_TEST_SUCCESS
      ( ( attempt_equality_check< T, RegularityProfile > )
        ( rhs_duplicate, rhs )
      );

      detail_argot_swap::constexpr_swap( lhs_duplicate, rhs_duplicate );

      ARGOT_TEST_SUCCESS
      ( ( attempt_equality_check< T, RegularityProfile > )
        ( lhs_duplicate, rhs )
      );

      ARGOT_TEST_SUCCESS
      ( ( attempt_equality_check< T, RegularityProfile > )
        ( rhs_duplicate, lhs )
      );
    }

    return 0;
  }
};

template< class T, class RegularityProfile >
constexpr test_value_with_greater_value_fn< T, RegularityProfile >
test_value_with_greater_value{};

template< class T, class RegularityProfile >
struct test_value_with_greater_equivalence_classes_fn;

template< class T, class RegularityProfile >
constexpr test_value_with_greater_equivalence_classes_fn< T, RegularityProfile >
test_value_with_greater_equivalence_classes{};

template< class T, class RegularityProfile >
struct test_value_with_greater_equivalence_classes_fn
{
  template< class LhsFun >
  [[nodiscard]]
  constexpr ::argot::call_detail::constexpr_block_result_t
  operator ()( LhsFun const& lhs_fun ) const { return 0; }

  template< class LhsFun, class... RhsFuns, class... Rest >
  [[nodiscard]]
  constexpr ::argot::call_detail::constexpr_block_result_t operator ()
  ( LhsFun const& lhs_fun
  , std::tuple< RhsFuns... > const& greater_equivalence_class
  , Rest const&... rest
  ) const
  {
    ARGOT_TEST_SUCCESS
    ( std::apply
      ( [ &lhs_fun ]( auto const&... rhs_funs )
          -> ::argot::call_detail::constexpr_block_result_t
        {
          return ( test_with_each_parameter )
          ( [ &lhs_fun ]( auto const& rhs_fun )
            {
              return test_value_with_greater_value< T, RegularityProfile >
              ( lhs_fun, rhs_fun );
            }
          , rhs_funs...
          );
        }
      , greater_equivalence_class
      )
    );

    return test_value_with_greater_equivalence_classes< T, RegularityProfile >
    ( lhs_fun, rest... );
  }

  template< class LhsFun, class RhsFun, class... Rest >
  [[nodiscard]]
  constexpr ::argot::call_detail::constexpr_block_result_t operator ()
  ( LhsFun const& lhs_fun
  , RhsFun const& greater_fun
  , Rest const&... rest
  ) const
  {
    return ( *this )( lhs_fun, std::make_tuple( greater_fun ), rest... );
  }
};

template< class T, class RegularityProfile >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t test_operations()
{
  return 0;
}

template< class T, class RegularityProfile
        , class FirstGenerator, class... TailGenerators
        >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t test_operations
( FirstGenerator const& first_generator
, TailGenerators const&... tail_equivalence_classes
);

template< class T, class RegularityProfile
        , class... EquivalenceClassGenerators, class... TailGeneratorRanges
        >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t test_operations
( std::tuple< EquivalenceClassGenerators... > const& first_equivalence_class
, TailGeneratorRanges const&... tail_equivalence_classes
)
{
  // TODO(mattcalabrese) Test true default-construction only when not constexpr.
  #if 0
  if constexpr
  (    RegularityProfile::default_constructible_kind
    != default_constructible::no
  )
  {
    T object;
    static_cast< void >( object );
  }
  #endif

  // NOTE: This tests value-initialization.
  if constexpr( ARGOT_IS_MODELED( argot::Constructible< T > ) )
  {
    T object = T();
    static_cast< void >( object );
  }

  ARGOT_TEST_SUCCESS
  ( ( test_equivalence_class< T, RegularityProfile > )
    ( first_equivalence_class )
  );

  // Everything not in an equivalence class should not compare equal
  ARGOT_TEST_SUCCESS
  ( std::apply
    ( [ & ]( auto const&... lhs_funs )
        -> ::argot::call_detail::constexpr_block_result_t
      {
        return ( test_with_each_parameter )
        ( [ & ]( auto const& lhs_fun )
          {
            return test_value_with_greater_equivalence_classes
            < T, RegularityProfile >( lhs_fun, tail_equivalence_classes... );
          }
        , lhs_funs...
        );
      }
    , first_equivalence_class
    )
  );

  return ( test_operations< T, RegularityProfile > )
  ( tail_equivalence_classes... );
}

template< class T, class RegularityProfile
        , class FirstGenerator, class... TailGenerators
        >
[[nodiscard]]
constexpr ::argot::call_detail::constexpr_block_result_t test_operations
( FirstGenerator const& first_generator
, TailGenerators const&... tail_equivalence_classes
)
{
  return ( test_operations< T, RegularityProfile > )
  ( std::make_tuple( first_generator )
  , tail_equivalence_classes...
  );
}

} // namespace argot_test(::detail_regularity_testing)

template< class T, class RegularityProfile >
struct test_regularity_fn
{
  template< class... Generators >
  [[nodiscard]]
  constexpr ::argot::call_detail::constexpr_block_result_t
  operator ()( Generators const&... generators ) const
  {
    ARGOT_CONCEPT_ENSURE( RegularityConcept< T, RegularityProfile > );

    return detail_regularity_testing::test_operations< T, RegularityProfile >
    ( generators... );
  }
};

// TODO(mattcalabrese) Constrain to regularity_profile
template< class T
        , class RegularityProfile = syntactic_regularity_profile_of_t< T >
        >
constexpr test_regularity_fn< T, RegularityProfile >
test_regularity{};

// TODO(mattcalabrese)
//   Make strict and loose forms that are either exact matches or allow partial
//   matches (for instance, allow the type to be syntactically copyable even
//   when the type is not specified to have a copy constructor -- just don't
//   test the semantics of that operation).

} // namespace argot_test

#endif // ARGOT_TEST_REGULARITY_TESTING_HPP_
