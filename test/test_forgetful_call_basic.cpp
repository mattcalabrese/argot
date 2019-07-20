/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/forgetful_call.hpp>
#include <argot/forward_arguments_as_tuple.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/prov/reference_to.hpp>

#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <utility>
#include <variant>

namespace {

// An argument provider that is an error when expanded.
// This is useful in tests to make sure that argument providers which yield
// argument providers undergo the proper number of expansions.

template< class T >
struct dummy_provider_impl{};

template< class T >
struct dummy_provider_t
{
  constexpr dummy_provider_impl< T > operator ()() const
  {
    return dummy_provider_impl< T >();
  }
};

} // namespace

namespace argot {

template< class T >
struct make_concept_map< ArgumentProvider< dummy_provider_impl< T > > >
{
  template< class Self, class Receiver >
  static constexpr void provide( Self&&, Receiver&& )
  {
    throw 1;
  }
};

} // namespace argot

namespace {

template< class T >
/*inline*/ extern dummy_provider_t< T > constexpr dummy_provider{};

template< class T >
using dummy_provider_type = decltype( dummy_provider< T >() );

auto dummy_0 = dummy_provider< std::integral_constant< std::size_t, 0 > >();
auto dummy_1 = dummy_provider< std::integral_constant< std::size_t, 1 > >();
auto dummy_2 = dummy_provider< std::integral_constant< std::size_t, 2 > >();
auto dummy_3 = dummy_provider< std::integral_constant< std::size_t, 3 > >();

[[maybe_unused]] auto raw_0 = std::integral_constant< std::size_t, 0 >();
[[maybe_unused]] auto raw_1 = std::integral_constant< std::size_t, 1 >();
[[maybe_unused]] auto raw_2 = std::integral_constant< std::size_t, 2 >();
[[maybe_unused]] auto raw_3 = std::integral_constant< std::size_t, 3 >();

using argot::SameType;

using argot::forgetful_call;
namespace receiver_traits = argot::receiver_traits;
namespace prov = argot::prov;

enum class was_called { no, yes, multiple };
enum class was_called_with_expected_types { no, yes };
enum class call_qualifiers { lvalue, const_lvalue, rvalue, const_rvalue };

template< call_qualifiers, class... >
struct unique_return_type {};

template< class Tup >
struct arguments_to_tuple_of_pointers;

template< class... T >
struct arguments_to_tuple_of_pointers
< receiver_traits::argument_types_t< T... > >
{
  using type = std::tuple< std::remove_reference_t< T >*... >;
};

template< class Tup >
using arguments_to_tuple_of_pointers_t
  = typename arguments_to_tuple_of_pointers< Tup >::type;

template< class Tup, class RTup, std::size_t... I >
constexpr void constexpr_tuple_assign_impl
( Tup& lhs, RTup&& rhs, std::index_sequence< I... > )
{
  ( static_cast< void >
    ( std::get< I >( lhs ) = std::get< I >( std::forward< RTup >( rhs ) ) )
  , ...
  );
}

template< class Tup, class RTup >
constexpr void constexpr_tuple_assign( Tup& lhs, RTup&& rhs )
{
  ( constexpr_tuple_assign_impl )
  ( lhs, rhs, std::make_index_sequence< std::tuple_size_v< Tup > >() );
}

template< class ArgsType >
class store_arguments
{
 public:
  using arguments_state
    = arguments_to_tuple_of_pointers_t< ArgsType >;

  store_arguments( store_arguments const& ) = delete;
  store_arguments& operator=( store_arguments const& ) = delete;

  constexpr store_arguments() {}

  template< class... P >
  constexpr unique_return_type< call_qualifiers::lvalue, P&&... >
  operator()( P&&... args ) &
  {
    update_num_calls();
    call_qualifiers_ = call_qualifiers::lvalue;

    if constexpr
    ( std::is_same_v
      < ArgsType, receiver_traits::argument_types_t< P&&... > >
    )
    {
      ( constexpr_tuple_assign )
      ( arguments_, std::make_tuple( std::addressof( args )... ) );
      was_called_with_expected_types_ = was_called_with_expected_types::yes;
    }

    return {};
  }

  template< class... P >
  constexpr unique_return_type< call_qualifiers::rvalue, P&&... >
  operator()( P&&... args ) &&
  {
    update_num_calls();
    call_qualifiers_ = call_qualifiers::rvalue;

    if constexpr
    ( std::is_same_v
      < ArgsType, receiver_traits::argument_types_t< P&&... > >
    )
    {
      ( constexpr_tuple_assign )
      ( arguments_, std::make_tuple( std::addressof( args )... ) );
      was_called_with_expected_types_ = was_called_with_expected_types::yes;
    }

    return {};
  }

  template< class... P >
  constexpr unique_return_type< call_qualifiers::const_lvalue, P&&... >
  operator()( P&&... args ) const&
  {
    update_num_calls();
    call_qualifiers_ = call_qualifiers::const_lvalue;

    if constexpr
    ( std::is_same_v
      < ArgsType, receiver_traits::argument_types_t< P&&... > >
    )
    {
      ( constexpr_tuple_assign )
      ( arguments_, std::make_tuple( std::addressof( args )... ) );
      was_called_with_expected_types_ = was_called_with_expected_types::yes;
    }

    return {};
  }

  template< class... P >
  constexpr unique_return_type< call_qualifiers::const_rvalue, P&&... >
  operator()( P&&... args ) const &&
  {
    update_num_calls();
    call_qualifiers_ = call_qualifiers::const_rvalue;

    if constexpr
    ( std::is_same_v
      < ArgsType, receiver_traits::argument_types_t< P&&... > >
    )
    {
      ( constexpr_tuple_assign )
      ( arguments_, std::make_tuple( std::addressof( args )... ) );
      was_called_with_expected_types_ = was_called_with_expected_types::yes;
    }

    return {};
  }

  constexpr bool this_was_called() const
  {
    return was_called_ != was_called::no;
  }

  constexpr bool this_was_called_once() const
  {
    return was_called_ == was_called::yes;
  }

  constexpr bool this_was_called_with_expected_types() const
  {
    return    was_called_with_expected_types_
           == was_called_with_expected_types::yes;
  }

  constexpr call_qualifiers this_call_qualifiers() const
  {
    return call_qualifiers_;
  }

  constexpr const arguments_state& arguments() const
  {
    return arguments_;
  }
 private:
  constexpr void update_num_calls() const
  {
    switch( was_called_ )
    {
     case was_called::no:
      was_called_ = was_called::yes;
      break;
     case was_called::yes:
      was_called_ = was_called::multiple;
      break;
     case was_called::multiple:
      was_called_ = was_called::multiple;
      break;
    }
  }
 private:
  mutable was_called was_called_ = was_called::no;
  mutable was_called_with_expected_types was_called_with_expected_types_
    = was_called_with_expected_types::no;
  mutable call_qualifiers call_qualifiers_ = call_qualifiers::const_rvalue;
  mutable arguments_state arguments_;
};

ARGOT_REGISTER_CONSTEXPR_TEST( no_call_arguments )
{
  using args_type = receiver_traits::argument_types_t<>;

  {
    std::tuple<> expected_result;

    store_arguments< args_type > fun;
    argot::forgetful_call( std::move( fun ) );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::rvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  {
    std::tuple<> expected_result;

    store_arguments< args_type > fun;
    argot::forgetful_call( fun );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  {
    std::tuple<> expected_result;

    const store_arguments< args_type > fun;
    argot::forgetful_call( fun );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  {
    std::tuple<> expected_result;

    const store_arguments< args_type > fun;
    argot::forgetful_call( std::move( fun ) );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_rvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( basic_call_arguments )
{
  using args_type
    = receiver_traits::argument_types_t< int&, char&&, double const& >;

  int a = 0;
  char b = 0;
  const double c = 0;

  {
    auto const expected_result = std::make_tuple( &a, &b, &c );

    const store_arguments< args_type > fun;
    argot::forgetful_call( fun, a, std::move( b ), c );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( sole_expanded_call_arguments )
{
  using args_type
    = receiver_traits::argument_types_t
      < dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      >;

  {
    auto const expected_result = std::make_tuple( &dummy_2, &dummy_1 );

    const store_arguments< args_type > fun;
    argot::forgetful_call( fun, prov::reference_to( dummy_2, dummy_1 ) );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( trailing_expanded_call_arguments )
{
  using args_type
    = receiver_traits::argument_types_t
      < std::integral_constant< std::size_t, 3 >&
      , dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      >;

  {
    auto const expected_result = std::make_tuple( &raw_3, &dummy_2, &dummy_1 );

    const store_arguments< args_type > fun;
    argot::forgetful_call( fun, raw_3, prov::reference_to( dummy_2, dummy_1 ) );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( leading_expanded_call_arguments )
{
  using args_type
    = receiver_traits::argument_types_t
      < dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      , std::integral_constant< std::size_t, 0 >&
      >;

  {
    auto const expected_result = std::make_tuple( &dummy_2, &dummy_1, &raw_0 );

    const store_arguments< args_type > fun;
    argot::forgetful_call( fun, prov::reference_to( dummy_2, dummy_1 ), raw_0 );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( leading_trailing_expanded_call_arguments )
{
  using args_type
    = receiver_traits::argument_types_t
      < std::integral_constant< std::size_t, 3 >&
      , dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      , std::integral_constant< std::size_t, 0 >&
      >;

  {
    auto const expected_result
      = std::make_tuple( &raw_3, &dummy_2, &dummy_1, &raw_0 );

    const store_arguments< args_type > fun;
    argot::forgetful_call
    ( fun, raw_3, prov::reference_to( dummy_2, dummy_1 ), raw_0 );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( multiple_expanded_call_arguments )
{
  using args_type
    = receiver_traits::argument_types_t
      < dummy_provider_type< std::integral_constant< std::size_t, 3 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 0 > >&
      >;

  {
    auto const expected_result
      = std::make_tuple( &dummy_3, &dummy_2, &dummy_1, &dummy_0 );

    const store_arguments< args_type > fun;
    argot::forgetful_call
    ( fun
    , prov::reference_to( dummy_3, dummy_2 )
    , prov::reference_to( dummy_1, dummy_0 )
    );

    ARGOT_TEST_TRUE( fun.this_was_called() );
    ARGOT_TEST_TRUE( fun.this_was_called_once() );
    ARGOT_TEST_TRUE( fun.this_was_called_with_expected_types() );
    ARGOT_TEST_EQ( fun.this_call_qualifiers(), call_qualifiers::const_lvalue );

    ARGOT_TEST_EQ( expected_result, fun.arguments() );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

} // namespace
