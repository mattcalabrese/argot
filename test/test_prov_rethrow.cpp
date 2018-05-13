/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/impossible.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/exceptional_argument_provider.hpp>
#include <argot/concepts/exceptional_persistent_argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/rethrow.hpp>
#include <argot/prov_traits/argument_list_kinds_of_destructive.hpp>
#include <argot/prov_traits/argument_list_kinds_of_persistent.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/prov_traits/persistent_provide.hpp>
#include <argot/receiver/return_argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>

#include <utility>

namespace {

namespace prov = argot::prov;
namespace prov_traits = argot::prov_traits;
namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;

using argot::ArgumentProvider;
using argot::ExceptionalArgumentProvider;
using argot::ExceptionalPersistentArgumentProvider;
using argot::PersistentArgumentProvider;
using argot::SameType;
using argot::impossible;
using prov::rethrow;
using prov::rethrow_t;
using prov_traits::argument_list_kinds_of_destructive_t;
using prov_traits::argument_list_kinds_of_persistent_t;
using prov_traits::destructive_provide;
using prov_traits::persistent_provide;
using receiver::return_argument_list_kinds;
using receiver_traits::argument_list_kinds_t;

// TODO(mattcalabrese) Test the throw_ion actually fires

enum class construction_form { explicit_, move, copy };

struct exception_type
{
  int value = 0;
};

ARGOT_REGISTER_TEST( test_rethrow )
{
  {
    using rethrow_type = decltype( rethrow );

    ARGOT_CONCEPT_ENSURE
    ( SameType< rethrow_type, rethrow_t const > );
  }

  auto provider = rethrow;

  using provider_type = decltype( provider );

  ARGOT_CONCEPT_ENSURE( ArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( PersistentArgumentProvider< provider_type > );
  ARGOT_CONCEPT_ENSURE( ExceptionalArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( ExceptionalPersistentArgumentProvider< provider_type > );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_destructive_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < argument_list_kinds_of_persistent_t< provider_type >
    , argument_list_kinds_t<>
    >
  );

  // lvalue provision
  {
    try
    {
      throw exception_type{ 5 };
    }
    catch( exception_type const& /*except*/ )
    {
      try
      {
        decltype( auto ) result
          = persistent_provide( provider, return_argument_list_kinds() );

        using provision_result_type = decltype( result );

        ARGOT_CONCEPT_ENSURE( SameType< provision_result_type, impossible > );
      }
      catch( exception_type const& except )
      {
        ARGOT_TEST_EQ( except.value, 5 );
      }
    }
  }

  // rvalue provision
  {
    try
    {
      throw exception_type{ 5 };
    }
    catch( exception_type const& /*except*/ )
    {
      try
      {
        decltype( auto ) result
          = destructive_provide( std::move( provider )
                               , return_argument_list_kinds()
                               );

        using provision_result_type = decltype( result );

        ARGOT_CONCEPT_ENSURE( SameType< provision_result_type, impossible > );

      }
      catch( exception_type const& except )
      {
        ARGOT_TEST_EQ( except.value, 5 );
      }
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
