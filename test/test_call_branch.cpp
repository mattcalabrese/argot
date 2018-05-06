/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/call.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/forward_arguments_as_tuple.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/group.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/value_of.hpp>
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

auto dummy0 = dummy_provider< std::integral_constant< std::size_t, 0 > >();
auto dummy1 = dummy_provider< std::integral_constant< std::size_t, 1 > >();
auto dummy2 = dummy_provider< std::integral_constant< std::size_t, 2 > >();
auto dummy3 = dummy_provider< std::integral_constant< std::size_t, 3 > >();
auto dummya = dummy_provider< std::integral_constant< char, 'a' > >();
auto dummyb = dummy_provider< std::integral_constant< char, 'b' > >();
auto dummyA = dummy_provider< std::integral_constant< char, 'A' > >();
auto dummyB = dummy_provider< std::integral_constant< char, 'B' > >();

using dummy0_type = decltype( dummy0 );
using dummy1_type = decltype( dummy1 );
using dummy2_type = decltype( dummy2 );
using dummy3_type = decltype( dummy3 );
using dummya_type = decltype( dummya );
using dummyb_type = decltype( dummyb );
using dummyA_type = decltype( dummyA );
using dummyB_type = decltype( dummyB );

auto raw0 = std::integral_constant< std::size_t, 0 >();
auto raw1 = std::integral_constant< std::size_t, 1 >();
auto raw2 = std::integral_constant< std::size_t, 2 >();
auto raw3 = std::integral_constant< std::size_t, 3 >();

using raw0_type = decltype( raw0 );
using raw1_type = decltype( raw1 );
using raw2_type = decltype( raw2 );
using raw3_type = decltype( raw3 );


// TODO(mattcalabrese) Rewrite to make a simple chooser here (remove dependency)
template< class T, class U >
auto branching_provider( const std::size_t branch, T& arg0, U& arg1 )
{
  BOOST_TEST( branch <= 1u );
  return prov::conditional
  ( branch == 0
  , prov::group( prov::value_of( std::integral_constant< std::size_t, 0 >() )
               , prov::reference_to( arg0 )
               )
  , prov::group( prov::value_of( std::integral_constant< std::size_t, 1 >() )
               , prov::reference_to( arg1 )
               )
  );
}

BOOST_AUTO_TEST_CASE( branch_call_arguments )
{
  decltype( auto ) res0
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 0, dummy0, dummy1 )
      );

  decltype( auto ) res1
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 1, dummy0, dummy1 )
      );

  using argument_list0
    = std::tuple< std::integral_constant< std::size_t, 0 >&&, dummy0_type& >;

  using argument_list1
    = std::tuple< std::integral_constant< std::size_t, 1 >&&, dummy1_type& >;

  using variant_field0 = to_boost_variant_field< 0, argument_list0 >;
  using variant_field1 = to_boost_variant_field< 1, argument_list1 >;

  using expected_res_type = boost::variant< variant_field0, variant_field1 >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res0 ), expected_res_type > );

  {
    auto& underlying_res0 = boost::get< variant_field0 >( res0 );
    BOOST_TEST( &std::get< 1 >( underlying_res0.field ) == &dummy0 );
  }

  {
    auto& underlying_res1 = boost::get< variant_field1 >( res1 );
    BOOST_TEST( &std::get< 1 >( underlying_res1.field ) == &dummy1 );
  }
}

BOOST_AUTO_TEST_CASE( branch_call_nested )
{
  decltype( auto ) res0
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , prov::conditional
        ( true, prov::conditional( true, prov::reference_to( dummy0, raw0 )
                                       , prov::reference_to( dummy1, raw1 )
                                 )
              , prov::conditional( true, prov::reference_to( dummy2, raw2 )
                                       , prov::reference_to( dummy3, raw3 )
                                 )
        )
      );

  decltype( auto ) res1
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , prov::conditional
        ( true, prov::conditional( false, prov::reference_to( dummy0, raw0 )
                                        , prov::reference_to( dummy1, raw1 )
                                 )
              , prov::conditional( true, prov::reference_to( dummy2, raw2 )
                                       , prov::reference_to( dummy3, raw3 )
                                 )
        )
      );

  decltype( auto ) res2
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , prov::conditional
        ( false, prov::conditional( true, prov::reference_to( dummy0, raw0 )
                                        , prov::reference_to( dummy1, raw1 )
                                  )
               , prov::conditional( true, prov::reference_to( dummy2, raw2 )
                                        , prov::reference_to( dummy3, raw3 )
                                  )
        )
      );

  decltype( auto ) res3
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , prov::conditional
        ( false, prov::conditional( true, prov::reference_to( dummy0, raw0 )
                                        , prov::reference_to( dummy1, raw1 )
                                  )
               , prov::conditional( false, prov::reference_to( dummy2, raw2 )
                                         , prov::reference_to( dummy3, raw3 )
                                  )
        )
      );

  using argument_list0 = std::tuple< dummy0_type&, raw0_type& >;
  using argument_list1 = std::tuple< dummy1_type&, raw1_type& >;
  using argument_list2 = std::tuple< dummy2_type&, raw2_type& >;
  using argument_list3 = std::tuple< dummy3_type&, raw3_type& >;

  using variant_field0 = to_boost_variant_field< 0, argument_list0 >;
  using variant_field1 = to_boost_variant_field< 1, argument_list1 >;
  using variant_field2 = to_boost_variant_field< 2, argument_list2 >;
  using variant_field3 = to_boost_variant_field< 3, argument_list3 >;

  using expected_res_type
    = boost::variant
      < variant_field0, variant_field1, variant_field2, variant_field3 >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res0 ), expected_res_type > );

  {
    auto& underlying_res0 = boost::get< variant_field0 >( res0 );
    BOOST_TEST( &std::get< 0 >( underlying_res0.field ) == &dummy0 );
    BOOST_TEST( &std::get< 1 >( underlying_res0.field ) == &raw0 );
  }

  {
    auto& underlying_res1 = boost::get< variant_field1 >( res1 );
    BOOST_TEST( &std::get< 0 >( underlying_res1.field ) == &dummy1 );
    BOOST_TEST( &std::get< 1 >( underlying_res1.field ) == &raw1 );
  }

  {
    auto& underlying_res2 = boost::get< variant_field2 >( res2 );
    BOOST_TEST( &std::get< 0 >( underlying_res2.field ) == &dummy2 );
    BOOST_TEST( &std::get< 1 >( underlying_res2.field ) == &raw2 );
  }

  {
    auto& underlying_res3 = boost::get< variant_field3 >( res3 );
    BOOST_TEST( &std::get< 0 >( underlying_res3.field ) == &dummy3 );
    BOOST_TEST( &std::get< 1 >( underlying_res3.field ) == &raw3 );
  }
}

BOOST_AUTO_TEST_CASE( two_branch_call_arguments_ordering )
{

  decltype( auto ) res0
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 0, dummy0, dummy1 )
      , branching_provider( 0, dummya, dummyb )
      );

  decltype( auto ) res1
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 0, dummy0, dummy1 )
      , branching_provider( 1, dummya, dummyb )
      );

  decltype( auto ) res2
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 1, dummy0, dummy1 )
      , branching_provider( 0, dummya, dummyb )
      );

  decltype( auto ) res3
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 1, dummy0, dummy1 )
      , branching_provider( 1, dummya, dummyb )
      );

  using argument_list0
    = std::tuple< std::integral_constant< std::size_t, 0 >&&, dummy0_type&
                , std::integral_constant< std::size_t, 0 >&&, dummya_type&
                >;

  using argument_list1
    = std::tuple< std::integral_constant< std::size_t, 0 >&&, dummy0_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyb_type&
                >;

  using argument_list2
    = std::tuple< std::integral_constant< std::size_t, 1 >&&, dummy1_type&
                , std::integral_constant< std::size_t, 0 >&&, dummya_type&
                >;

  using argument_list3
    = std::tuple< std::integral_constant< std::size_t, 1 >&&, dummy1_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyb_type&
                >;

  using variant_field0 = to_boost_variant_field< 0, argument_list0 >;
  using variant_field1 = to_boost_variant_field< 1, argument_list1 >;
  using variant_field2 = to_boost_variant_field< 2, argument_list2 >;
  using variant_field3 = to_boost_variant_field< 3, argument_list3 >;

  using expected_res_type
    = boost::variant
      < variant_field0, variant_field1, variant_field2, variant_field3 >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res0 ), expected_res_type > );

  {
    auto& underlying_res0 = boost::get< variant_field0 >( res0 );
    BOOST_TEST( &std::get< 1 >( underlying_res0.field ) == &dummy0 );
    BOOST_TEST( &std::get< 3 >( underlying_res0.field ) == &dummya );
  }

  {
    auto& underlying_res1 = boost::get< variant_field1 >( res1 );
    BOOST_TEST( &std::get< 1 >( underlying_res1.field ) == &dummy0 );
    BOOST_TEST( &std::get< 3 >( underlying_res1.field ) == &dummyb );
  }

  {
    auto& underlying_res2 = boost::get< variant_field2 >( res2 );
    BOOST_TEST( &std::get< 1 >( underlying_res2.field ) == &dummy1 );
    BOOST_TEST( &std::get< 3 >( underlying_res2.field ) == &dummya );
  }

  {
    auto& underlying_res3 = boost::get< variant_field3 >( res3 );
    BOOST_TEST( &std::get< 1 >( underlying_res3.field ) == &dummy1 );
    BOOST_TEST( &std::get< 3 >( underlying_res3.field ) == &dummyb );
  }
}

BOOST_AUTO_TEST_CASE( three_branch_call_arguments_ordering )
{
  decltype( auto ) res0
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 0, dummy0, dummy1 )
      , branching_provider( 0, dummya, dummyb )
      , branching_provider( 0, dummyA, dummyB )
      );

  decltype( auto ) res1
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 0, dummy0, dummy1 )
      , branching_provider( 0, dummya, dummyb )
      , branching_provider( 1, dummyA, dummyB )
      );

  decltype( auto ) res2
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 0, dummy0, dummy1 )
      , branching_provider( 1, dummya, dummyb )
      , branching_provider( 0, dummyA, dummyB )
      );

  decltype( auto ) res3
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 0, dummy0, dummy1 )
      , branching_provider( 1, dummya, dummyb )
      , branching_provider( 1, dummyA, dummyB )
      );

  decltype( auto ) res4
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 1, dummy0, dummy1 )
      , branching_provider( 0, dummya, dummyb )
      , branching_provider( 0, dummyA, dummyB )
      );

  decltype( auto ) res5
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 1, dummy0, dummy1 )
      , branching_provider( 0, dummya, dummyb )
      , branching_provider( 1, dummyA, dummyB )
      );

  decltype( auto ) res6
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 1, dummy0, dummy1 )
      , branching_provider( 1, dummya, dummyb )
      , branching_provider( 0, dummyA, dummyB )
      );

  decltype( auto ) res7
    = call[ argot::reducer::to_boost_variant ]
      ( argot::forward_arguments_as_tuple
      , branching_provider( 1, dummy0, dummy1 )
      , branching_provider( 1, dummya, dummyb )
      , branching_provider( 1, dummyA, dummyB )
      );

  using argument_list0
    = std::tuple< std::integral_constant< std::size_t, 0 >&&, dummy0_type&
                , std::integral_constant< std::size_t, 0 >&&, dummya_type&
                , std::integral_constant< std::size_t, 0 >&&, dummyA_type&
                >;

  using argument_list1
    = std::tuple< std::integral_constant< std::size_t, 0 >&&, dummy0_type&
                , std::integral_constant< std::size_t, 0 >&&, dummya_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyB_type&
                >;

  using argument_list2
    = std::tuple< std::integral_constant< std::size_t, 0 >&&, dummy0_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyb_type&
                , std::integral_constant< std::size_t, 0 >&&, dummyA_type&
                >;

  using argument_list3
    = std::tuple< std::integral_constant< std::size_t, 0 >&&, dummy0_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyb_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyB_type&
                >;

  using argument_list4
    = std::tuple< std::integral_constant< std::size_t, 1 >&&, dummy1_type&
                , std::integral_constant< std::size_t, 0 >&&, dummya_type&
                , std::integral_constant< std::size_t, 0 >&&, dummyA_type&
                >;

  using argument_list5
    = std::tuple< std::integral_constant< std::size_t, 1 >&&, dummy1_type&
                , std::integral_constant< std::size_t, 0 >&&, dummya_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyB_type&
                >;

  using argument_list6
    = std::tuple< std::integral_constant< std::size_t, 1 >&&, dummy1_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyb_type&
                , std::integral_constant< std::size_t, 0 >&&, dummyA_type&
                >;

  using argument_list7
    = std::tuple< std::integral_constant< std::size_t, 1 >&&, dummy1_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyb_type&
                , std::integral_constant< std::size_t, 1 >&&, dummyB_type&
                >;

  using variant_field0 = to_boost_variant_field< 0, argument_list0 >;
  using variant_field1 = to_boost_variant_field< 1, argument_list1 >;
  using variant_field2 = to_boost_variant_field< 2, argument_list2 >;
  using variant_field3 = to_boost_variant_field< 3, argument_list3 >;
  using variant_field4 = to_boost_variant_field< 4, argument_list4 >;
  using variant_field5 = to_boost_variant_field< 5, argument_list5 >;
  using variant_field6 = to_boost_variant_field< 6, argument_list6 >;
  using variant_field7 = to_boost_variant_field< 7, argument_list7 >;

  using expected_res_type
    = boost::variant
      < variant_field0, variant_field1, variant_field2, variant_field3
      , variant_field4, variant_field5, variant_field6, variant_field7
      >;

  ARGOT_CONCEPT_ENSURE
  ( SameType< decltype( res0 ), expected_res_type > );

  {
    auto& underlying_res0 = boost::get< variant_field0 >( res0 );
    BOOST_TEST( &std::get< 1 >( underlying_res0.field ) == &dummy0 );
    BOOST_TEST( &std::get< 3 >( underlying_res0.field ) == &dummya );
    BOOST_TEST( &std::get< 5 >( underlying_res0.field ) == &dummyA );
  }

  {
    auto& underlying_res1 = boost::get< variant_field1 >( res1 );
    BOOST_TEST( &std::get< 1 >( underlying_res1.field ) == &dummy0 );
    BOOST_TEST( &std::get< 3 >( underlying_res1.field ) == &dummya );
    BOOST_TEST( &std::get< 5 >( underlying_res1.field ) == &dummyB );
  }

  {
    auto& underlying_res2 = boost::get< variant_field2 >( res2 );
    BOOST_TEST( &std::get< 1 >( underlying_res2.field ) == &dummy0 );
    BOOST_TEST( &std::get< 3 >( underlying_res2.field ) == &dummyb );
    BOOST_TEST( &std::get< 5 >( underlying_res2.field ) == &dummyA );
  }

  {
    auto& underlying_res3 = boost::get< variant_field3 >( res3 );
    BOOST_TEST( &std::get< 1 >( underlying_res3.field ) == &dummy0 );
    BOOST_TEST( &std::get< 3 >( underlying_res3.field ) == &dummyb );
    BOOST_TEST( &std::get< 5 >( underlying_res3.field ) == &dummyB );
  }

  {
    auto& underlying_res4 = boost::get< variant_field4 >( res4 );
    BOOST_TEST( &std::get< 1 >( underlying_res4.field ) == &dummy1 );
    BOOST_TEST( &std::get< 3 >( underlying_res4.field ) == &dummya );
    BOOST_TEST( &std::get< 5 >( underlying_res4.field ) == &dummyA );
  }

  {
    auto& underlying_res5 = boost::get< variant_field5 >( res5 );
    BOOST_TEST( &std::get< 1 >( underlying_res5.field ) == &dummy1 );
    BOOST_TEST( &std::get< 3 >( underlying_res5.field ) == &dummya );
    BOOST_TEST( &std::get< 5 >( underlying_res5.field ) == &dummyB );
  }

  {
    auto& underlying_res6 = boost::get< variant_field6 >( res6 );
    BOOST_TEST( &std::get< 1 >( underlying_res6.field ) == &dummy1 );
    BOOST_TEST( &std::get< 3 >( underlying_res6.field ) == &dummyb );
    BOOST_TEST( &std::get< 5 >( underlying_res6.field ) == &dummyA );
  }

  {
    auto& underlying_res7 = boost::get< variant_field7 >( res7 );
    BOOST_TEST( &std::get< 1 >( underlying_res7.field ) == &dummy1 );
    BOOST_TEST( &std::get< 3 >( underlying_res7.field ) == &dummyb );
    BOOST_TEST( &std::get< 5 >( underlying_res7.field ) == &dummyB );
  }
}
