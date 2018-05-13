/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

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
#include <argot/prov/assert_.hpp>
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
using prov::assert_;
using prov::assert_t;
using prov_traits::argument_list_kinds_of_destructive_t;
using prov_traits::argument_list_kinds_of_persistent_t;
using prov_traits::destructive_provide;
using prov_traits::persistent_provide;
using receiver::return_argument_list_kinds;
using receiver_traits::argument_list_kinds_t;

// TODO(mattcalabrese) Test the assertion actually fires

ARGOT_REGISTER_CONSTEXPR_TEST( test_nullary )
{
  {
    using assert_type = decltype( assert_ );

    ARGOT_CONCEPT_ENSURE( SameType< assert_type, assert_t const > );
  }

  auto provider = assert_;

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

  // rvalue provision
  {
    using provision_result_type
      = decltype
        ( destructive_provide
          ( std::move( provider ), return_argument_list_kinds() )
        );

    ARGOT_CONCEPT_ENSURE( SameType< provision_result_type, impossible > );
  }

  // lvalue provision
  {
    using provision_result_type
      = decltype
        ( persistent_provide( assert_, return_argument_list_kinds() ) );

    ARGOT_CONCEPT_ENSURE( SameType< provision_result_type, impossible > );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
