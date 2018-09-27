/*==============================================================================
  Copyright (c) 2016 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

//[invoke
/*`
[heading Description]

This tutorial is an introduction to the simplest use of the
__primary_call_overload__ without any sophisticated __argument_provision__. This
usage is equivalent in behavior to `std::invoke`.

[heading Prereq Tutorials]

This tutorial should be able to be understood without reading any other
tutorials in this documentation.

[heading Introduction]

In traditional C++, =function objects=...

In tr1 and in C++11, the standard introduced the notion of a `Callable`, which
is a generalization of the =function object= concept that also includes member
function pointers and member object pointers as objects that can be logically
invoked. Those who have used facilities such as `std::bind` or `std::function`
may be familiar with this concept as it is the requirement that allows binding
to a member function pointer in addition to standard [^function objects]. The
function template `std::invoke` is introduced in C++17 as a way for users to
call these objects in a way that is consistent with the standard library's uses.

At a high level, this library provides a generalization of the `std::invoke`
facility of C++17, though it is much more than that.
*/
#include <boost_ext/call/call.hpp>

int fun( char ) { return 5; }

struct foo
{
  int bar( char a )
  {
    return 5;
  }
};

int main()
{
  int const result = boost_ext::call( &fun, 'a' );
//<-
  return result != 5;
//->
}
/*`
[note
  Use of __call__ is only equivalent to std::invoke here because none of the
  arguments that we passed specialize how they behave with respect to
  __argument_provision__. This will be explained in detail in the tutorials that
  follow.
]
[heading Related References]

* __Primary_call_overload__
*/
//]
