/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/declval.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/gen/concept_ensure.hpp>

#include <type_traits>

namespace {

using argot::SameType;

struct empty_dummy_type {};

template< class T >
struct dummy_type { T member; };

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type ) )
  , empty_dummy_type&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type const ) )
  , empty_dummy_type const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type volatile ) )
  , empty_dummy_type volatile&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type volatile const ) )
  , empty_dummy_type volatile const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type&& ) )
  , empty_dummy_type&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type const&& ) )
  , empty_dummy_type const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type volatile&& ) )
  , empty_dummy_type volatile&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type volatile const&& ) )
  , empty_dummy_type volatile const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type& ) )
  , empty_dummy_type&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type const& ) )
  , empty_dummy_type const&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type volatile& ) )
  , empty_dummy_type volatile&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( empty_dummy_type volatile const& ) )
  , empty_dummy_type volatile const&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > ) )
  , dummy_type< int >&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > const ) )
  , dummy_type< int > const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > volatile ) )
  , dummy_type< int > volatile&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > volatile const ) )
  , dummy_type< int > volatile const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int >&& ) )
  , dummy_type< int >&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > const&& ) )
  , dummy_type< int > const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > volatile&& ) )
  , dummy_type< int > volatile&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > volatile const&& ) )
  , dummy_type< int > volatile const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int >& ) )
  , dummy_type< int >&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > const& ) )
  , dummy_type< int > const&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > volatile& ) )
  , dummy_type< int > volatile&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< int > volatile const& ) )
  , dummy_type< int > volatile const&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > ) )
  , dummy_type< long double >&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > const ) )
  , dummy_type< long double > const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > volatile ) )
  , dummy_type< long double > volatile&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > volatile const ) )
  , dummy_type< long double > volatile const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double >&& ) )
  , dummy_type< long double >&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > const&& ) )
  , dummy_type< long double > const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > volatile&& ) )
  , dummy_type< long double > volatile&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > volatile const&& ) )
  , dummy_type< long double > volatile const&&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double >& ) )
  , dummy_type< long double >&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > const& ) )
  , dummy_type< long double > const&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > volatile& ) )
  , dummy_type< long double > volatile&
  >
);

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( ARGOT_DECLVAL( dummy_type< long double > volatile const& ) )
  , dummy_type< long double > volatile const&
  >
);

}  // namespace
