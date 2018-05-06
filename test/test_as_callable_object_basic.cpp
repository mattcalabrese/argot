/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/as_call_object.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/call.hpp>
#include <argot/forward_arguments_as_tuple.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/reducer/to_boost_variant.hpp>

#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <utility>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using argot::SameType;

using argot::call;
using argot::to_boost_variant_field;
namespace prov = argot::prov;

inline constexpr auto forward_args
  = argot::as_call_object( argot::forward_arguments_as_tuple );

BOOST_AUTO_TEST_CASE( no_call_arguments )
{
  decltype( auto ) res
    = forward_args[ argot::reducer::to_boost_variant ]
      ();

  using expected_argument_list = std::tuple<>;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );
}

BOOST_AUTO_TEST_CASE( basic_call_arguments )
{
  int a = 0;
  char b = 0;
  const double c = 0;

  decltype( auto ) res
    = forward_args[ argot::reducer::to_boost_variant ]
      ( a, std::move( b ), c );

  using expected_argument_list
    = std::tuple< int&, char&&, double const& >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  BOOST_TEST( &std::get< 0 >( underlying_res.field ) == &a );
  BOOST_TEST( &std::get< 1 >( underlying_res.field ) == &b );
  BOOST_TEST( &std::get< 2 >( underlying_res.field ) == &c );
}

// An argument provider that is an error when expanded.
// This is useful in tests to make sure that argument providers which yield
// argument providers undergo the proper number of expansions.

template< class T >
struct dummy_provider_impl{};

template< class T >
struct dummy_provider_t
{
  dummy_provider_impl< T > operator ()() const
  {
    return dummy_provider_impl< T >();
  }
};

namespace argot {

template< class T >
struct make_concept_map< ArgumentProvider< dummy_provider_impl< T > > >
{
  template< class Self, class Receiver >
  static void provide( Self&&, Receiver&& )
  {
    BOOST_TEST( false );
  }
};

}  // namespace argot

template< class T >
/*inline*/ extern dummy_provider_t< T > constexpr dummy_provider{};

template< class T >
using dummy_provider_type = decltype( dummy_provider< T >() );

auto dummy_0 = dummy_provider< std::integral_constant< std::size_t, 0 > >();
auto dummy_1 = dummy_provider< std::integral_constant< std::size_t, 1 > >();
auto dummy_2 = dummy_provider< std::integral_constant< std::size_t, 2 > >();
auto dummy_3 = dummy_provider< std::integral_constant< std::size_t, 3 > >();

auto raw_0 = std::integral_constant< std::size_t, 0 >();
auto raw_1 = std::integral_constant< std::size_t, 1 >();
auto raw_2 = std::integral_constant< std::size_t, 2 >();
auto raw_3 = std::integral_constant< std::size_t, 3 >();

BOOST_AUTO_TEST_CASE( sole_expanded_call_arguments )
{
  decltype( auto ) res
    = forward_args[ argot::reducer::to_boost_variant ]
      ( prov::reference_to( dummy_2, dummy_1 )
      );

  using expected_argument_list
    = std::tuple
      < dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  BOOST_TEST( &std::get< 0 >( underlying_res.field ) == &dummy_2 );
  BOOST_TEST( &std::get< 1 >( underlying_res.field ) == &dummy_1 );
}

BOOST_AUTO_TEST_CASE( trailing_expanded_call_arguments )
{
  decltype( auto ) res
    = forward_args[ argot::reducer::to_boost_variant ]
      ( raw_3, prov::reference_to( dummy_2, dummy_1 )
      );

  using expected_argument_list
    = std::tuple
      < std::integral_constant< std::size_t, 3 >&
      , dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  BOOST_TEST( &std::get< 0 >( underlying_res.field ) == &raw_3 );
  BOOST_TEST( &std::get< 1 >( underlying_res.field ) == &dummy_2 );
  BOOST_TEST( &std::get< 2 >( underlying_res.field ) == &dummy_1 );
}

BOOST_AUTO_TEST_CASE( leading_expanded_call_arguments )
{
  decltype( auto ) res
    = forward_args[ argot::reducer::to_boost_variant ]
      ( prov::reference_to( dummy_2, dummy_1 ), raw_0
      );

  using expected_argument_list
    = std::tuple
      < dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      , std::integral_constant< std::size_t, 0 >&
      >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  BOOST_TEST( &std::get< 0 >( underlying_res.field ) == &dummy_2 );
  BOOST_TEST( &std::get< 1 >( underlying_res.field ) == &dummy_1 );
  BOOST_TEST( &std::get< 2 >( underlying_res.field ) == &raw_0 );
}

BOOST_AUTO_TEST_CASE( leading_trailing_expanded_call_arguments )
{
  decltype( auto ) res
    = forward_args[ argot::reducer::to_boost_variant ]
      ( raw_3, prov::reference_to( dummy_2, dummy_1 ), raw_0
      );

  using expected_argument_list
    = std::tuple
      < std::integral_constant< std::size_t, 3 >&
      , dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      , std::integral_constant< std::size_t, 0 >&
      >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  BOOST_TEST( &std::get< 0 >( underlying_res.field ) == &raw_3 );
  BOOST_TEST( &std::get< 1 >( underlying_res.field ) == &dummy_2 );
  BOOST_TEST( &std::get< 2 >( underlying_res.field ) == &dummy_1 );
  BOOST_TEST( &std::get< 3 >( underlying_res.field ) == &raw_0 );
}

BOOST_AUTO_TEST_CASE( multiple_expanded_call_arguments )
{
  decltype( auto ) res
    = forward_args[ argot::reducer::to_boost_variant ]
      ( prov::reference_to( dummy_3, dummy_2 )
      , prov::reference_to( dummy_1, dummy_0 )
      );

  using expected_argument_list
    = std::tuple
      < dummy_provider_type< std::integral_constant< std::size_t, 3 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 0 > >&
      >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  BOOST_TEST( &std::get< 0 >( underlying_res.field ) == &dummy_3 );
  BOOST_TEST( &std::get< 1 >( underlying_res.field ) == &dummy_2 );
  BOOST_TEST( &std::get< 2 >( underlying_res.field ) == &dummy_1 );
  BOOST_TEST( &std::get< 3 >( underlying_res.field ) == &dummy_0 );
}
