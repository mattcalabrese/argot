/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/transformation_with.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>

// TODO(mattcalabrese) Make these tests more rigorous.

using argot::TransformationWith;
using argot::Not;

struct a {};
struct b {};
struct c {};

using fun = char( a, b, c );
using void_fun = void( a, b, c );

struct foo {};

using foo_data_member = int foo::*;

using foo_mem_fun = int (foo::*)( a, b, c );
using foo_const_mem_fun = int (foo::*)( a, b, c ) const;

using foo_lvalue_mem_fun = int (foo::*)( a, b, c )&;
using foo_lvalue_const_mem_fun = int (foo::*)( a, b, c ) const&;

using foo_rvalue_mem_fun = int (foo::*)( a, b, c ) &&;
using foo_rvalue_const_mem_fun = int (foo::*)( a, b, c ) const&&;

using void_foo_mem_fun = void (foo::*)( a, b, c );
using void_foo_const_mem_fun = void (foo::*)( a, b, c ) const;

using void_foo_lvalue_mem_fun = void (foo::*)( a, b, c )&;
using void_foo_lvalue_const_mem_fun = void (foo::*)( a, b, c ) const&;

using void_foo_rvalue_mem_fun = void (foo::*)( a, b, c ) &&;
using void_foo_rvalue_const_mem_fun = void (foo::*)( a, b, c ) const&&;

struct fun_object
{
  double operator()( a, b, c ) const&;
};

struct void_fun_object
{
  void operator()( a, b, c ) const&;
};

ARGOT_CONCEPT_ENSURE( TransformationWith< fun, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun&, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun&&, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun*, a, b, c > );

ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun&, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun&&, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun*, a, b > > );

ARGOT_CONCEPT_ENSURE
( TransformationWith< fun_object&, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun_object const&, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun_object, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun_object&&, a, b, c > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< fun_object volatile &, a, b, c > > );

ARGOT_CONCEPT_ENSURE( TransformationWith< foo_data_member, foo& > );
ARGOT_CONCEPT_ENSURE( TransformationWith< foo_data_member, foo&& > );
ARGOT_CONCEPT_ENSURE( TransformationWith< foo_data_member, foo* > );
ARGOT_CONCEPT_ENSURE( TransformationWith< foo_data_member, foo const* > );

ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_mem_fun, foo&, a, b, c > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_mem_fun, foo const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE( TransformationWith< foo_mem_fun, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE( TransformationWith< foo_const_mem_fun, foo&, a, b, c > );
ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_const_mem_fun, foo const&, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< foo_const_mem_fun, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_mem_fun, foo*, a, b, c > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE( TransformationWith< foo_const_mem_fun, foo*, a, b, c > );
ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_const_mem_fun, foo const*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_lvalue_mem_fun, foo&, a, b, c > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_lvalue_mem_fun, foo const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_lvalue_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_lvalue_const_mem_fun, foo&, a, b, c > );
ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_lvalue_const_mem_fun, foo const&, a, b, c > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_lvalue_const_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_lvalue_mem_fun, foo*, a, b, c > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_lvalue_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_lvalue_const_mem_fun, foo*, a, b, c > );
ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_lvalue_const_mem_fun, foo const*, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_mem_fun, foo&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_mem_fun, foo const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_rvalue_mem_fun, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_const_mem_fun, foo&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_const_mem_fun, foo const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( TransformationWith< foo_rvalue_const_mem_fun, foo&&, a, b, c > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_const_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< foo_rvalue_const_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE( TransformationWith< fun, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun&, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun&&, a, b, c > );
ARGOT_CONCEPT_ENSURE( TransformationWith< fun*, a, b, c > );

ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun&, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun&&, a, b > > );
ARGOT_CONCEPT_ENSURE( Not< TransformationWith< fun*, a, b > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_fun_object&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_fun_object const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_fun_object, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_fun_object&&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_fun_object volatile &, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_mem_fun, foo&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_mem_fun, foo const&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_const_mem_fun, foo&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_const_mem_fun, foo const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_const_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_const_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_const_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_mem_fun, foo&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_mem_fun, foo const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_const_mem_fun, foo&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not
  < TransformationWith< void_foo_lvalue_const_mem_fun, foo const&, a, b, c > >
);
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_const_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_lvalue_const_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not
  < TransformationWith< void_foo_lvalue_const_mem_fun, foo const*, a, b, c > >
);

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_mem_fun, foo&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_mem_fun, foo const&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_const_mem_fun, foo&, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not
  < TransformationWith< void_foo_rvalue_const_mem_fun, foo const&, a, b, c > >
);
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_const_mem_fun, foo&&, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_mem_fun, foo const*, a, b, c > > );

ARGOT_CONCEPT_ENSURE
( Not< TransformationWith< void_foo_rvalue_const_mem_fun, foo*, a, b, c > > );
ARGOT_CONCEPT_ENSURE
( Not
  < TransformationWith< void_foo_rvalue_const_mem_fun, foo const*, a, b, c > >
);
