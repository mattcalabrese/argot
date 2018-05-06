/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/invocable_with.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>

// TODO(mattcalabrese) Make these tests more rigorous.

using argot::InvocableWith;
using argot::Not;

struct a {};
struct b {};
struct c {};

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
  double operator()( a, b, c ) const& { return 0.; }
};

ARGOT_CONCEPT_ENSURE( InvocableWith< fun, a, b, c > );
ARGOT_CONCEPT_ENSURE( InvocableWith< fun&, a, b, c > );
ARGOT_CONCEPT_ENSURE( InvocableWith< fun&&, a, b, c > );
ARGOT_CONCEPT_ENSURE( InvocableWith< fun*, a, b, c > );

ARGOT_CONCEPT_ENSURE( Not< InvocableWith< fun, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< InvocableWith< fun&, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< InvocableWith< fun&&, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< InvocableWith< fun*, a, b > > );

ARGOT_CONCEPT_ENSURE( InvocableWith< fun_object&, a, b, c > );
ARGOT_CONCEPT_ENSURE( InvocableWith< fun_object const&, a, b, c > );
ARGOT_CONCEPT_ENSURE( InvocableWith< fun_object, a, b, c > );
ARGOT_CONCEPT_ENSURE( InvocableWith< fun_object&&, a, b, c > );
ARGOT_CONCEPT_ENSURE( Not< InvocableWith< fun_object volatile &, a, b, c > > );

ARGOT_CONCEPT_ENSURE( InvocableWith< foo_data_member, foo& > );
ARGOT_CONCEPT_ENSURE( InvocableWith< foo_data_member, foo&& > );
ARGOT_CONCEPT_ENSURE( InvocableWith< foo_data_member, foo* > );
ARGOT_CONCEPT_ENSURE( InvocableWith< foo_data_member, foo const* > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_member_function, foo&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_member_function, foo const&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_member_function, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_const_member_function, foo&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_const_member_function, foo const&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_const_member_function, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_member_function, foo*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_member_function, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_const_member_function, foo*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_const_member_function, foo const*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_lvalue_member_function, foo&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_lvalue_member_function, foo const&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_lvalue_member_function, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_lvalue_const_member_function, foo&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_lvalue_const_member_function, foo const&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_lvalue_const_member_function, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_lvalue_member_function, foo*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_lvalue_member_function, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_lvalue_const_member_function, foo*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_lvalue_const_member_function, foo const*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_rvalue_member_function, foo&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_rvalue_member_function, foo const&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_rvalue_member_function, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_rvalue_const_member_function, foo&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not
  < InvocableWith< foo_rvalue_const_member_function, foo const&, a, b, c > >
);

ARGOT_CONCEPT_ENSURE
( InvocableWith< foo_rvalue_const_member_function, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_rvalue_member_function, foo*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_rvalue_member_function, foo const*, a, b, c > > );


ARGOT_CONCEPT_ENSURE
( Not< InvocableWith< foo_rvalue_const_member_function, foo*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not
  < InvocableWith< foo_rvalue_const_member_function, foo const*, a, b, c > >
);
