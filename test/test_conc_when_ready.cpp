/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/async_call.hpp>
#include <argot/conc/value_of.hpp>
#include <argot/conc/when_ready.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/forward_arguments_as_tuple.hpp>
#include <argot/fut/ready.hpp>
#include <argot/packager/stlab.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/reducer/to_variant.hpp>

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <utility>
#include <variant>

namespace {

using argot::async_call;
using argot::SameType;
namespace conc = argot::conc;
namespace executor = argot::executor;
namespace fut = argot::fut;
namespace packager = argot::packager;
namespace prov = argot::prov;
namespace reducer = argot::reducer;

struct make_tuple_fn
{
  template< class... P >
  constexpr auto operator ()( P&&... args ) const
  {
    return std::make_tuple( std::forward< P >( args )... );
  }
} inline constexpr make_tuple{};

template< class T >
struct move_only
{
  move_only( move_only&& ) = default;
  move_only& operator=( move_only&& ) = default;
  T value;
};

ARGOT_REGISTER_TEST( no_call_arguments )
{
  decltype( auto ) res
    = async_call< packager::stlab >[ reducer::to_variant ]
      ( executor::immediate, make_tuple );

  using expected_res_type
    = stlab::future< std::variant< argot::struct_<> > >;

  ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), expected_res_type > );

  return 0;
}

ARGOT_REGISTER_TEST( basic_call_arguments_no_then )
{
  int a = 1;
  move_only< char > b{ 2 };
  const double c = 3.;

  decltype( auto ) res
    = async_call< packager::stlab >[ reducer::to_variant ]
      ( executor::immediate
      , make_tuple
      , a, std::move( b ), c
      );

  using expected_res_type
    = stlab::future
      < std::variant< argot::struct_< int, move_only< char >, double > > >;

  ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), expected_res_type > );

  auto opt_res = res.get_try();

  ARGOT_TEST_TRUE( opt_res );

  auto& underlying_res = std::get< 0 >( *opt_res );

  ARGOT_TEST_EQ( std::get< 0 >( underlying_res ), 1 );
  ARGOT_TEST_EQ( std::get< 1 >( underlying_res ).value, 2 );
  ARGOT_TEST_EQ( std::get< 2 >( underlying_res ), 3. );

  return 0;
}

ARGOT_REGISTER_TEST( basic_call_arguments )
{
  int a = 1;
  move_only< char > b{ 2 };
  const double c = 3.;

  decltype( auto ) res
    = async_call< packager::stlab >[ reducer::to_variant ]
      ( executor::immediate
      , make_tuple
      , a, conc::when_ready( fut::ready( std::move( b ) ) ), c
      );

  using expected_res_type
    = stlab::future
      < std::variant< argot::struct_< int, move_only< char >, double > > >;

  ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), expected_res_type > );

  auto opt_res = res.get_try();

  ARGOT_TEST_TRUE( opt_res );

  auto& underlying_res = std::get< 0 >( *opt_res );

  ARGOT_TEST_EQ( std::get< 0 >( underlying_res ), 1 );
  ARGOT_TEST_EQ( std::get< 1 >( underlying_res ).value, 2 );
  ARGOT_TEST_EQ( std::get< 2 >( underlying_res ), 3. );

  return 0;
}

ARGOT_REGISTER_TEST( basic_call_arguments_two )
{
  int a = 1;
  move_only< char > b{ 2 };
  const double c = 3.;

  decltype( auto ) res
    = async_call< packager::stlab >[ reducer::to_variant ]
      ( executor::immediate
      , make_tuple
      , conc::when_ready( fut::ready( a ) ), std::move( b )
      , conc::when_ready( fut::ready( c ) )
      );

  using expected_res_type
    = stlab::future
      < std::variant< argot::struct_< int, move_only< char >, double > > >;

  ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), expected_res_type > );

  auto opt_res = res.get_try();

  ARGOT_TEST_TRUE( opt_res );

  auto& underlying_res = std::get< 0 >( *opt_res );

  ARGOT_TEST_EQ( std::get< 0 >( underlying_res ), 1 );
  ARGOT_TEST_EQ( std::get< 1 >( underlying_res ).value, 2 );
  ARGOT_TEST_EQ( std::get< 2 >( underlying_res ), 3. );

  return 0;
}

ARGOT_REGISTER_TEST( basic_call_arguments_three )
{
  int a = 1;
  move_only< char > b{ 2 };
  const double c = 3.;

  decltype( auto ) res
    = async_call< packager::stlab >[ reducer::to_variant ]
      ( executor::immediate
      , make_tuple
      , conc::when_ready( fut::ready( a ) )
      , conc::when_ready( fut::ready( std::move( b ) ) )
      , conc::when_ready( fut::ready( c ) )
      );

  using expected_res_type
    = stlab::future
      < std::variant< argot::struct_< int, move_only< char >, double > > >;

  ARGOT_CONCEPT_ENSURE( SameType< decltype( res ), expected_res_type > );

  auto opt_res = res.get_try();

  ARGOT_TEST_TRUE( opt_res );

  auto& underlying_res = std::get< 0 >( *opt_res );

  ARGOT_TEST_EQ( std::get< 0 >( underlying_res ), 1 );
  ARGOT_TEST_EQ( std::get< 1 >( underlying_res ).value, 2 );
  ARGOT_TEST_EQ( std::get< 2 >( underlying_res ), 3. );

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace

#if 0
BOOST_AUTO_TEST_CASE( no_call_arguments )
{
  decltype( auto ) res
    = async_call[ argot::reducer::to_boost_variant ]
      ( make_tuple );

  using expected_argument_list = argot::struct_<>;

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
    = async_call[ argot::reducer::to_boost_variant ]
      ( make_tuple, a, std::move( b ), c );

  using expected_argument_list
    = argot::struct_< int&, char&&, double const& >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  ARGOT_TEST_EQ( &std::get< 0 >( underlying_res.field ) == &a );
  ARGOT_TEST_EQ( &std::get< 1 >( underlying_res.field ) == &b );
  ARGOT_TEST_EQ( &std::get< 2 >( underlying_res.field ) == &c );
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
    ARGOT_TEST_EQ( false );
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
    = async_call[ argot::reducer::to_boost_variant ]
      ( make_tuple
      , prov::reference_to( dummy_2, dummy_1 )
      );

  using expected_argument_list
    = argot::struct_
      < dummy_provider_type< std::integral_constant< std::size_t, 2 > >&
      , dummy_provider_type< std::integral_constant< std::size_t, 1 > >&
      >;

  using expected_variant_field
    = to_boost_variant_field< 0, expected_argument_list >;

  using expected_res_type = boost::variant< expected_variant_field >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res ), expected_res_type > );

  auto& underlying_res = boost::get< expected_variant_field >( res );

  ARGOT_TEST_EQ( &std::get< 0 >( underlying_res.field ) == &dummy_2 );
  ARGOT_TEST_EQ( &std::get< 1 >( underlying_res.field ) == &dummy_1 );
}

BOOST_AUTO_TEST_CASE( trailing_expanded_call_arguments )
{
  decltype( auto ) res
    = async_call[ argot::reducer::to_boost_variant ]
      ( make_tuple
      , raw_3, prov::reference_to( dummy_2, dummy_1 )
      );

  using expected_argument_list
    = argot::struct_
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

  ARGOT_TEST_EQ( &std::get< 0 >( underlying_res.field ) == &raw_3 );
  ARGOT_TEST_EQ( &std::get< 1 >( underlying_res.field ) == &dummy_2 );
  ARGOT_TEST_EQ( &std::get< 2 >( underlying_res.field ) == &dummy_1 );
}

BOOST_AUTO_TEST_CASE( leading_expanded_call_arguments )
{
  decltype( auto ) res
    = async_call[ argot::reducer::to_boost_variant ]
      ( make_tuple
      , prov::reference_to( dummy_2, dummy_1 ), raw_0
      );

  using expected_argument_list
    = argot::struct_
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

  ARGOT_TEST_EQ( &std::get< 0 >( underlying_res.field ) == &dummy_2 );
  ARGOT_TEST_EQ( &std::get< 1 >( underlying_res.field ) == &dummy_1 );
  ARGOT_TEST_EQ( &std::get< 2 >( underlying_res.field ) == &raw_0 );
}

BOOST_AUTO_TEST_CASE( leading_trailing_expanded_call_arguments )
{
  decltype( auto ) res
    = async_call[ argot::reducer::to_boost_variant ]
      ( make_tuple
      , raw_3, prov::reference_to( dummy_2, dummy_1 ), raw_0
      );

  using expected_argument_list
    = argot::struct_
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

  ARGOT_TEST_EQ( &std::get< 0 >( underlying_res.field ) == &raw_3 );
  ARGOT_TEST_EQ( &std::get< 1 >( underlying_res.field ) == &dummy_2 );
  ARGOT_TEST_EQ( &std::get< 2 >( underlying_res.field ) == &dummy_1 );
  ARGOT_TEST_EQ( &std::get< 3 >( underlying_res.field ) == &raw_0 );
}

BOOST_AUTO_TEST_CASE( multiple_expanded_call_arguments )
{
  decltype( auto ) res
    = async_call[ argot::reducer::to_boost_variant ]
      ( make_tuple
      , prov::reference_to( dummy_3, dummy_2 )
      , prov::reference_to( dummy_1, dummy_0 )
      );

  using expected_argument_list
    = argot::struct_
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

  ARGOT_TEST_EQ( &std::get< 0 >( underlying_res.field ) == &dummy_3 );
  ARGOT_TEST_EQ( &std::get< 1 >( underlying_res.field ) == &dummy_2 );
  ARGOT_TEST_EQ( &std::get< 2 >( underlying_res.field ) == &dummy_1 );
  ARGOT_TEST_EQ( &std::get< 3 >( underlying_res.field ) == &dummy_0 );
}
#endif
