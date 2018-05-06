/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/argot_invocable_before_reduction.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/conditional.hpp>
#include <argot/prov/reference_to.hpp>

using argot::ArgotInvocableBeforeReduction;
using argot::Not;

using argot::prov::result_of_conditional_t;
using argot::prov::result_of_reference_to_t;

struct a_ {};
struct b_ {};
struct c_ {};

using a = a_&&;
using b = b_&&;
using c = c_&&;

using fun = char( a, b, c );

struct foo {};

using foo_data_member = int foo::*;

using foo_member_function = int (foo::*)( a, b, c );
using foo_const_member_function = int (foo::*)( a, b, c ) const;

using foo_lvalue_member_function = int (foo::*)( a, b, c )&;
using foo_lvalue_const_member_function = int (foo::*)( a, b, c ) const&;

using foo_rvalue_member_function = int (foo::*)( a, b, c ) &&;
using foo_rvalue_const_member_function = int (foo::*)( a, b, c ) const&&;

struct fun_object
{
  double operator()( a, b, c, a ) &&;
  double operator()( a, b, c, b ) &&;
};

struct ret0 {};
struct ret1 {};

struct fun_object_different_returns
{
  ret0 operator()( a, b, c, a ) &&;
  ret1 operator()( a, b, c, b ) &&;
};

ARGOT_CONCEPT_ENSURE
( ArgotInvocableBeforeReduction< foo_member_function, foo, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< ArgotInvocableBeforeReduction< foo_member_function, foo, a, b&, c > > );

ARGOT_CONCEPT_ENSURE
( Not
  < ArgotInvocableBeforeReduction
    < foo_member_function, result_of_reference_to_t< foo, a, b&, c > >
  >
);

ARGOT_CONCEPT_ENSURE
( ArgotInvocableBeforeReduction< fun_object, a, b, c, a > );

ARGOT_CONCEPT_ENSURE
( ArgotInvocableBeforeReduction< fun_object, a, b, c, b > );

ARGOT_CONCEPT_ENSURE
( Not< ArgotInvocableBeforeReduction< fun_object&, a, b, c, a > > );

ARGOT_CONCEPT_ENSURE
( ArgotInvocableBeforeReduction
  < fun_object
  , a, b, c
  , result_of_conditional_t
    < bool
    , result_of_reference_to_t< a >
    , result_of_reference_to_t< b >
    >
  >
);

ARGOT_CONCEPT_ENSURE
( Not
  < ArgotInvocableBeforeReduction
    < fun_object
    , a, b, c
    , result_of_conditional_t
      < bool
      , result_of_reference_to_t< a >
      , result_of_reference_to_t< c >
      >
    >
  >
);

ARGOT_CONCEPT_ENSURE
( ArgotInvocableBeforeReduction
  < fun_object_different_returns
  , a, b, c
  , result_of_conditional_t
    < bool
    , result_of_reference_to_t< a >
    , result_of_reference_to_t< b >
    >
  >
);

ARGOT_CONCEPT_ENSURE
( Not
  < ArgotInvocableBeforeReduction
    < fun_object_different_returns
    , a, b, c
    , result_of_conditional_t
      < bool
      , result_of_reference_to_t< a >
      , result_of_reference_to_t< c >
      >
    >
  >
);
