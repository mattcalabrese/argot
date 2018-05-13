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
#include <argot/prov/reference_to.hpp>
#include <argot/prov/throw_.hpp>
#include <argot/prov/value_of.hpp>
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
using prov::reference_to;
using prov::result_of_reference_to_t;
using prov::result_of_throw_;
using prov::result_of_throw_t;
using prov::result_of_value_of_t;
using prov::throw_;
using prov::throw_fn;
using prov::value_of;
using prov_traits::argument_list_kinds_of_destructive_t;
using prov_traits::argument_list_kinds_of_persistent_t;
using prov_traits::destructive_provide;
using prov_traits::persistent_provide;
using receiver::return_argument_list_kinds;
using receiver_traits::argument_list_kinds_t;

// TODO(mattcalabrese) Test the throw_ion actually fires

enum class construction_form { explicit_, move, copy };

struct value_type
{
  explicit value_type( int value )
    : form( construction_form::explicit_ ), value( value ) {}

  value_type( value_type const& other )
    : form( construction_form::copy ), value( other.value ) {}

  value_type( value_type&& other ) noexcept
    : form( construction_form::move ), value( other.value ) {}

  construction_form form;
  int value;
};

struct exception_type
{
  template< class P0, class P1, class P2 >
  explicit exception_type( P0&& value0, P1&& value1, P2&& value2 )
    : value0( std::forward< P0 >( value0 ) )
    , value1( std::forward< P1 >( value1 ) )
    , value2( std::forward< P2 >( value2 ) ) {}

  value_type value0;
  value_type value1;
  value_type value2;
};

value_type v0( 5 );
value_type v1( 10 );
value_type v2( 42 );

ARGOT_REGISTER_TEST( test_throw )
{
  {
    using throw_type = decltype( throw_< exception_type > );

    ARGOT_CONCEPT_ENSURE
    ( SameType< throw_type, throw_fn< exception_type > const > );
  }

  auto provider
    = throw_< exception_type >
      ( value_of( v0 ), reference_to( v1 ), reference_to( std::move( v2 ) ) );

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

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_throw_
      < exception_type
      , result_of_value_of_t< value_type& >
      , result_of_reference_to_t< value_type& >
      , result_of_reference_to_t< value_type&& >
      >::type
    >
  );

  ARGOT_CONCEPT_ENSURE
  ( SameType
    < provider_type
    , result_of_throw_t
      < exception_type
      , result_of_value_of_t< value_type& >
      , result_of_reference_to_t< value_type& >
      , result_of_reference_to_t< value_type&& >
      >
    >
  );

  // lvalue provision
  {
    using provision_result_type
      = decltype
        ( persistent_provide( provider, return_argument_list_kinds() ) );

    ARGOT_CONCEPT_ENSURE( SameType< provision_result_type, impossible > );

    try
    {
      persistent_provide( provider, return_argument_list_kinds() );
    }
    catch( exception_type const& except )
    {
      ARGOT_TEST_EQ( except.value0.value, 5 );
      ARGOT_TEST_EQ( except.value1.value, 10 );
      ARGOT_TEST_EQ( except.value2.value, 42 );

      ARGOT_TEST_EQ( except.value0.form, construction_form::copy );
      ARGOT_TEST_EQ( except.value1.form, construction_form::copy );
      ARGOT_TEST_EQ( except.value2.form, construction_form::copy );
    }
  }

  // rvalue provision
  {
    using provision_result_type
      = decltype
        ( destructive_provide
          ( std::move( provider ), return_argument_list_kinds() )
        );

    ARGOT_CONCEPT_ENSURE( SameType< provision_result_type, impossible > );

    try
    {
      destructive_provide
      ( std::move( provider ), return_argument_list_kinds() );
    }
    catch( exception_type const& except )
    {
      ARGOT_TEST_EQ( except.value0.value, 5 );
      ARGOT_TEST_EQ( except.value1.value, 10 );
      ARGOT_TEST_EQ( except.value2.value, 42 );

      ARGOT_TEST_EQ( except.value0.form, construction_form::move );
      ARGOT_TEST_EQ( except.value1.form, construction_form::copy );
      ARGOT_TEST_EQ( except.value2.form, construction_form::move );
    }
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
