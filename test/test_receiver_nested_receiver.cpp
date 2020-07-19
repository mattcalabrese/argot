/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver/return_argument_references.hpp>
#include <argot/receiver/nested_receiver.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>

#include <stdexcept>

namespace {

using argot::SameType;
using argot::discriminated_union;

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

enum class foo { zero, a, b, c };
enum class bar { zero, a, b, c };

namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;
namespace tuple_traits = argot::tuple_traits;
namespace variant_traits = argot::variant_traits;

// TODO(mattcalabrese) Test SFINAE behavior with call_detail::is_detected_v
// TODO(mattcalabrese) Test nested_receiver of nested_receiver

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonmodifying_nonbranching )
{
  decltype( auto ) rec
    = receiver::nested_receiver
      ( return_argument_references()
      , argument_list_kinds()
      , argument_list_kinds()
      );

  using rec_type = decltype( rec );

  // TODO(mattcalabrese) Make sure it's an ArgumentReceiver (not a reference)

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver_t
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t<>
      , argument_list_kinds_t<>
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t<>
      , argument_list_kinds_t<>
      >::type
    >
  );

  // NOTE: The result is not required to be the input receiver, but
  //       this implementation does result in it to simplify types.
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , result_of_return_argument_references_t
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    int one = 1;
    long two = 2;

    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds()
        , argument_list_kinds()
        , std::move( one )
        , two
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union< argot::struct_< int&&, long& > >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , int&&, long&
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
        , int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 0 );
    auto& tup = variant_traits::get< 0 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 2 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_nonmodifying_branching )
{
  decltype( auto ) rec
    = receiver::nested_receiver
      ( return_argument_references()
      , argument_list_kinds()
      , argument_list_kinds()
      );

  using rec_type = decltype( rec );

  // TODO(mattcalabrese) Make sure it's an ArgumentReceiver (not a reference)

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver_t
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t<>
      , argument_list_kinds_t<>
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t<>
      , argument_list_kinds_t<>
      >::type
    >
  );

  // NOTE: The result is not required to be the input receiver, but
  //       this implementation does result in it to simplify types.
  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , result_of_return_argument_references_t
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    int one = 1;
    long two = 2;

    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds( argument_types< float&&, char& > )
        , argument_list_kinds
          ( argument_types<>
          , argument_types< double const& >
          )
        , std::move( one )
        , two
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< float&&, char& >
        , argot::struct_< int&&, long& >
        , argot::struct_<>
        , argot::struct_< double const& >
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< float&&, char& > >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< double const& >
          >
        , int&&, long&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< float&&, char& > >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< double const& >
          >
        , int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 1 );
    auto& tup = variant_traits::get< 1 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 2 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_modifying_nonbranching )
{
  decltype( auto ) rec
    = receiver::nested_receiver
      ( return_argument_references()
      , argument_list_kinds
        ( argument_types< wchar_t&, long long&& >
        , argument_types< bool& >
        )
      , argument_list_kinds
        ( argument_types< short& >
        , argument_types<>
        )
      );

  using rec_type = decltype( rec );

  // TODO(mattcalabrese) Make sure it's an ArgumentReceiver (not a reference)

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver_t
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t
        < argument_types_t< wchar_t&, long long&& >
        , argument_types_t< bool& >
        >
      , argument_list_kinds_t
        < argument_types_t< short& >
        , argument_types_t<>
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t
        < argument_types_t< wchar_t&, long long&& >
        , argument_types_t< bool& >
        >
      , argument_list_kinds_t
        < argument_types_t< short& >
        , argument_types_t<>
        >
      >::type
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    int one = 1;
    long two = 2;

    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds()
        , argument_list_kinds()
        , std::move( one )
        , two
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< wchar_t&, long long&& >
        , argot::struct_< bool& >
        , argot::struct_< int&&, long& >
        , argot::struct_< short& >
        , argot::struct_<>
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
        , int&&, long&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , typename result_of_receive_branch
        < rec_type&&
        , argument_list_kinds_t<>
        , argument_list_kinds_t<>
        , int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 2 );
    auto& tup = variant_traits::get< 2 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 2 );
  }

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_modifying_branching )
{
  decltype( auto ) rec
    = receiver::nested_receiver
      ( return_argument_references()
      , argument_list_kinds
        ( argument_types< wchar_t&, long long&& >
        , argument_types< bool& >
        )
      , argument_list_kinds
        ( argument_types< short& >
        , argument_types<>
        )
      );

  using rec_type = decltype( rec );

  // TODO(mattcalabrese) Make sure it's an ArgumentReceiver (not a reference)

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver_t
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t
        < argument_types_t< wchar_t&, long long&& >
        , argument_types_t< bool& >
        >
      , argument_list_kinds_t
        < argument_types_t< short& >
        , argument_types_t<>
        >
      >
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < rec_type
    , receiver::result_of_nested_receiver
      < result_of_return_argument_references_t&&
      , argument_list_kinds_t
        < argument_types_t< wchar_t&, long long&& >
        , argument_types_t< bool& >
        >
      , argument_list_kinds_t
        < argument_types_t< short& >
        , argument_types_t<>
        >
      >::type
    >
  );

  // rvalue receiver
  // TODO(mattcalabrese) Make sure it's actually called as an rvalue
  {
    int one = 1;
    long two = 2;

    decltype( auto ) args
      = receive_branch
        ( std::move( rec )
        , argument_list_kinds( argument_types< float&&, char& > )
        , argument_list_kinds
          ( argument_types<>
          , argument_types< double const& >
          )
        , std::move( one )
        , two
        );

    using result_type = decltype( args );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , discriminated_union
        < argot::struct_< wchar_t&, long long&& >
        , argot::struct_< bool& >
        , argot::struct_< float&&, char& >
        , argot::struct_< int&&, long& >
        , argot::struct_<>
        , argot::struct_< double const& >
        , argot::struct_< short& >
        , argot::struct_<>
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , result_of_receive_branch_t
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< float&&, char& > >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< double const& >
          >
        , int&&, long&
        >
      >
    );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , typename result_of_receive_branch
        < rec_type&&
        , argument_list_kinds_t
          < argument_types_t< float&&, char& > >
        , argument_list_kinds_t
          < argument_types_t<>
          , argument_types_t< double const& >
          >
        , int&&, long&
        >::type
      >
    );

    ARGOT_TEST_EQ( variant_traits::index_of( args ), 3 );
    auto& tup = variant_traits::get< 3 >( args );

    ARGOT_TEST_EQ( &tuple_traits::get< 0 >( tup ), &one );
    ARGOT_TEST_EQ( tuple_traits::get< 0 >( tup ), 1 );

    ARGOT_TEST_EQ( &tuple_traits::get< 1 >( tup ), &two );
    ARGOT_TEST_EQ( tuple_traits::get< 1 >( tup ), 2 );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
