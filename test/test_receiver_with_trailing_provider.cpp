/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/concepts/argument_receiver.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver/with_trailing_provider.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/tuple_traits/get.hpp>

#include <stdexcept>

namespace {

using argot::ArgumentReceiver;
using argot::SameType;

using argot::prov::reference_to;
using argot::prov::result_of_reference_to;
using argot::prov::result_of_reference_to_t;
using argot::receiver::with_trailing_provider;
using argot::receiver::with_trailing_provider_t;
using argot::receiver::result_of_with_trailing_provider;
using argot::receiver::result_of_with_trailing_provider_t;
using argot::receiver::result_of_return_argument_references_t;
using argot::receiver::return_argument_references;
using argot::receiver::return_argument_references_t;
using argot::receiver_traits::receive_branch;
using argot::receiver_traits::argument_types;
using argot::receiver_traits::argument_types_t;
using argot::receiver_traits::argument_list_kinds;
using argot::receiver_traits::argument_list_kinds_t;
using argot::receiver_traits::result_of_receive_branch;
using argot::receiver_traits::result_of_receive_branch_t;

namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace tuple_traits = argot::tuple_traits;

// TODO(mattcalabrese) Test SFINAE behavior with call_detail::is_detected_v
// TODO(mattcalabrese) Test with_trailing_provider of with_trailing_provider

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonbranching_nonbranching )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < decltype( with_trailing_provider )
    , with_trailing_provider_t const
    >
  );

  char one = 1;
  short two = 2;
  int three = 3;
  long four = 4;
  long long five = 5;
  long double six = 6.;

  decltype( auto ) rec
    = with_trailing_provider
      ( return_argument_references()
      , reference_to( std::move( one ), two, std::move( three ), four )
      );

  using rec_type = decltype( rec );

  ARGOT_CONCEPT_ENSURE( ArgumentReceiver< rec_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider_t
      < result_of_return_argument_references_t&&
      , result_of_reference_to_t< char&&, short&, int&&, long& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider
      < result_of_return_argument_references_t&&
      , result_of_reference_to_t< char&&, short&, int&&, long& >
      >::type
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds()
        , argument_list_kinds()
        , std::move( five ), six
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_
          < long long&&, long double&, char&&, short&, int&&, long& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , long long&&, long double&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < rec_type&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , long long&&, long double&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 0 );
    auto& tup = std::get< 0 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &five );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 5 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &six );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 6. );

    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 2 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 3 >( tup ), 2 );

    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &three );
    ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), 3 );

    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &four );
    ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), 4 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonbranching_branching )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < decltype( with_trailing_provider )
    , with_trailing_provider_t const
    >
  );

  char one = 1;
  short two = 2;
  int three = 3;
  long four = 4;
  long long five = 5;
  long double six = 6.;


  decltype( auto ) rec
    = with_trailing_provider
      ( return_argument_references()
      , reference_to( std::move( one ), two, std::move( three ), four )
      );

  using rec_type = decltype( rec );

  // TODO(mattcalabrese) Make sure it's an ArgumentReceiver (not a reference)

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider_t
      < result_of_return_argument_references_t&&
      , result_of_reference_to_t< char&&, short&, int&&, long& >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider
      < result_of_return_argument_references_t&&
      , result_of_reference_to_t< char&&, short&, int&&, long& >
      >::type
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds( argument_types< float&&, wchar_t& > )
        , argument_list_kinds
          ( argument_types<>
          , argument_types< double const& >
          )
        , std::move( five ), six
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< float&&, wchar_t&, char&&, short&, int&&, long& >
        , argot::struct_< long long&&, long double&, char&&, short&, int&&, long& >
        , argot::struct_< char&&, short&, int&&, long& >
        , argot::struct_< double const&, char&&, short&, int&&, long& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< float&&, wchar_t& > >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< double const& >
          >
        , long long&&, long double&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< float&&, wchar_t& > >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< double const& >
          >
        , long long&&, long double&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 1 );
    auto& tup = std::get< 1 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &five );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 5 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &six );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 6. );

    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 2 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 3 >( tup ), 2 );

    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &three );
    ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), 3 );

    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &four );
    ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), 4 );
  }

  return 0;
}

/*
ARGOT_REGISTER_CONSTEXPR_TEST( test_branching_nonbranching )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < decltype( with_trailing_provider )
    , with_trailing_provider_t const
    >
  );

  char one = 1;
  short two = 2;
  int three = 3;
  long four = 4;
  long long five = 5;
  long double six = 6.;


  decltype( auto ) rec
    = with_trailing_provider
      ( return_argument_references()
      , argument_list_kinds( argument_types< float&&, wchar_t& > )
      , argument_list_kinds
        ( argument_types<>
        , argument_types< double const& >
        )
      , std::move( five ), six
      );

  using rec_type = decltype( rec );

  // TODO(mattcalabrese) Make sure it's an ArgumentReceiver (not a reference)

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider_t
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t< argument_types_t< float&&, wchar_t& > >
      , argument_list_kinds_t
        < argument_types_t<>
        , argument_types_t< double const& >
        >
      , long long&&, long double&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t< argument_types_t< float&&, wchar_t& > >
      , argument_list_kinds_t
        < argument_types_t<>
        , argument_types_t< double const& >
        >
      , long long&&, long double&
      >::type
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds()
        , argument_list_kinds()
        , std::move( one ), two, std::move( three ), four
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< float&&, wchar_t&, char&&, short&, int&&, long& >
        , argot::struct_< long long&&, long double&, char&&, short&, int&&, long& >
        , argot::struct_< char&&, short&, int&&, long& >
        , argot::struct_< double const&, char&&, short&, int&&, long& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , char&&, short&, int&&, long&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < rec_type&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , char&&, short&, int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 1 );
    auto& tup = std::get< 1 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &five );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 5 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &six );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 6. );

    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 2 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 3 >( tup ), 2 );

    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &three );
    ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), 3 );

    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &four );
    ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), 4 );
  }

  // lvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an lvalue
  {
    decltype( auto ) args
      = receive_branch
        ( rec
        , argument_list_kinds()
        , argument_list_kinds()
        , std::move( one ), two, std::move( three ), four
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< float&&, wchar_t&, char&&, short&, int&&, long& >
        , argot::struct_< long long&, long double&, char&&, short&, int&&, long& >
        , argot::struct_< char&&, short&, int&&, long& >
        , argot::struct_< double const&, char&&, short&, int&&, long& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , char&&, short&, int&&, long&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < rec_type&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , char&&, short&, int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 1 );
    auto& tup = std::get< 1 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &five );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 5 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &six );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 6. );

    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 2 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 3 >( tup ), 2 );

    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &three );
    ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), 3 );

    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &four );
    ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), 4 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_branching_branching )
{
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < decltype( with_trailing_provider )
    , with_trailing_provider_t const
    >
  );

  char one = 1;
  short two = 2;
  int three = 3;
  long four = 4;
  long long five = 5;
  long double six = 6.;


  decltype( auto ) rec
    = with_trailing_provider
      ( return_argument_references()
      , argument_list_kinds( argument_types< float&&, wchar_t& > )
      , argument_list_kinds
        ( argument_types<>
        , argument_types< double const& >
        )
      , std::move( five ), six
      );

  using rec_type = decltype( rec );

  // TODO(mattcalabrese) Make sure it's an ArgumentReceiver (not a reference)

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider_t
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t< argument_types_t< float&&, wchar_t& > >
      , argument_list_kinds_t
        < argument_types_t<>
        , argument_types_t< double const& >
        >
      , long long&&, long double&
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_with_trailing_provider
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t< argument_types_t< float&&, wchar_t& > >
      , argument_list_kinds_t
        < argument_types_t<>
        , argument_types_t< double const& >
        >
      , long long&&, long double&
      >::type
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds
          ( argument_types< unsigned char&& >
          , argument_types<>
          , argument_types< unsigned short&, unsigned int&& >
          )
        , argument_list_kinds
          ( argument_types< unsigned long&&, unsigned long long& >
          , argument_types< signed char& >
          )
        , std::move( one ), two, std::move( three ), four
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< float&&, wchar_t&, unsigned char&& >
        , argot::struct_< float&&, wchar_t& >
        , argot::struct_< float&&, wchar_t&, unsigned short&, unsigned int&& >
        , argot::struct_< float&&, wchar_t&, char&&, short&, int&&, long& >
        , argot::struct_< float&&, wchar_t&, unsigned long&&, unsigned long long& >
        , argot::struct_< float&&, wchar_t&, signed char& >
        , argot::struct_< long long&&, long double&, unsigned char&& >
        , argot::struct_< long long&&, long double& >
        , argot::struct_
          < long long&&, long double&, unsigned short&, unsigned int&& >
        , argot::struct_< long long&&, long double&, char&&, short&, int&&, long& >
        , argot::struct_
          < long long&&, long double&, unsigned long&&, unsigned long long& >
        , argot::struct_< long long&&, long double&, signed char& >
        , argot::struct_< unsigned char&& >
        , argot::struct_<>
        , argot::struct_< unsigned short&, unsigned int&& >
        , argot::struct_< char&&, short&, int&&, long& >
        , argot::struct_< unsigned long&&, unsigned long long& >
        , argot::struct_< signed char& >
        , argot::struct_< double const&, unsigned char&& >
        , argot::struct_< double const& >
        , argot::struct_< double const&, unsigned short&, unsigned int&& >
        , argot::struct_< double const&, char&&, short&, int&&, long& >
        , argot::struct_< double const&, unsigned long&&, unsigned long long& >
        , argot::struct_< double const&, signed char& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< unsigned char&& >
          , argument_types_t<>
          , argument_types_t< unsigned short&, unsigned int&& >
          >
        , argument_list_kinds_t
          < argument_types_t< unsigned long&&, unsigned long long& >
          , argument_types_t< signed char& >
          >
        , char&&, short&, int&&, long&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< unsigned char&& >
          , argument_types_t<>
          , argument_types_t< unsigned short&, unsigned int&& >
          >
        , argument_list_kinds_t
          < argument_types_t< unsigned long&&, unsigned long long& >
          , argument_types_t< signed char& >
          >
        , char&&, short&, int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 9 );
    auto& tup = std::get< 9 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &five );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 5 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &six );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 6. );

    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 2 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 3 >( tup ), 2 );

    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &three );
    ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), 3 );

    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &four );
    ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), 4 );
  }

  // lvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an lvalue
  {
    decltype( auto ) args
      = receive_branch
        ( rec
        , argument_list_kinds
          ( argument_types< unsigned char&& >
          , argument_types<>
          , argument_types< unsigned short&, unsigned int&& >
          )
        , argument_list_kinds
          ( argument_types< unsigned long&&, unsigned long long& >
          , argument_types< signed char& >
          )
        , std::move( one ), two, std::move( three ), four
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , std::variant
        < argot::struct_< float&&, wchar_t&, unsigned char&& >
        , argot::struct_< float&&, wchar_t& >
        , argot::struct_< float&&, wchar_t&, unsigned short&, unsigned int&& >
        , argot::struct_< float&&, wchar_t&, char&&, short&, int&&, long& >
        , argot::struct_< float&&, wchar_t&, unsigned long&&, unsigned long long& >
        , argot::struct_< float&&, wchar_t&, signed char& >
        , argot::struct_< long long&, long double&, unsigned char&& >
        , argot::struct_< long long&, long double& >
        , argot::struct_
          < long long&, long double&, unsigned short&, unsigned int&& >
        , argot::struct_< long long&, long double&, char&&, short&, int&&, long& >
        , argot::struct_
          < long long&, long double&, unsigned long&&, unsigned long long& >
        , argot::struct_< long long&, long double&, signed char& >
        , argot::struct_< unsigned char&& >
        , argot::struct_<>
        , argot::struct_< unsigned short&, unsigned int&& >
        , argot::struct_< char&&, short&, int&&, long& >
        , argot::struct_< unsigned long&&, unsigned long long& >
        , argot::struct_< signed char& >
        , argot::struct_< double const&, unsigned char&& >
        , argot::struct_< double const& >
        , argot::struct_< double const&, unsigned short&, unsigned int&& >
        , argot::struct_< double const&, char&&, short&, int&&, long& >
        , argot::struct_< double const&, unsigned long&&, unsigned long long& >
        , argot::struct_< double const&, signed char& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&
        , argument_list_kinds_t
          < argument_types_t< unsigned char&& >
          , argument_types_t<>
          , argument_types_t< unsigned short&, unsigned int&& >
          >
        , argument_list_kinds_t
          < argument_types_t< unsigned long&&, unsigned long long& >
          , argument_types_t< signed char& >
          >
        , char&&, short&, int&&, long&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < rec_type&
        , argument_list_kinds_t
          < argument_types_t< unsigned char&& >
          , argument_types_t<>
          , argument_types_t< unsigned short&, unsigned int&& >
          >
        , argument_list_kinds_t
          < argument_types_t< unsigned long&&, unsigned long long& >
          , argument_types_t< signed char& >
          >
        , char&&, short&, int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( args.index(), 9 );
    auto& tup = std::get< 9 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &five );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 5 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &six );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 6. );

    ARGOT_TEST_EQ( &tuple_traits::get< 2 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 2 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 3 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 3 >( tup ), 2 );

    ARGOT_TEST_EQ( &tuple_traits::get< 4 >( tup ), &three );
    ARGOT_TEST_EQ( tuple_traits::get< 4 >( tup ), 3 );

    ARGOT_TEST_EQ( &tuple_traits::get< 5 >( tup ), &four );
    ARGOT_TEST_EQ( tuple_traits::get< 5 >( tup ), 4 );

  }

  return 0;
}
*/

ARGOT_EXECUTE_TESTS();

}  // namespace
