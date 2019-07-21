/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/receiver/do_nothing.hpp>

#include <argot/concepts/same_type.hpp>
#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/detection.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive_branch.hpp>

namespace {

using argot::SameType;

namespace receiver = argot::receiver;
namespace receiver_traits = argot::receiver_traits;

using receiver_traits::receive_branch;
using receiver_traits::argument_list_kinds;
using receiver_traits::argument_types;

using receiver::do_nothing_fn;
using receiver::do_nothing;

ARGOT_CONCEPT_ENSURE
( SameType
  < decltype( do_nothing )
  , do_nothing_fn const
  >
);

ARGOT_REGISTER_CONSTEXPR_TEST( test_do_nothing )
{
  {
    receive_branch
    ( do_nothing()
    , argument_list_kinds()
    , argument_list_kinds()
    );

    using result_type
      = decltype
        ( receive_branch
          ( do_nothing()
          , argument_list_kinds()
          , argument_list_kinds()
          )
        );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );
  }

  {
    receive_branch
    ( do_nothing()
    , argument_list_kinds()
    , argument_list_kinds()
    , 1
    , 'a'
    , 3.5
    );

    using result_type
      = decltype
        ( receive_branch
          ( do_nothing()
          , argument_list_kinds()
          , argument_list_kinds()
          , 1
          , 'a'
          , 3.5
          )
        );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );
  }

  {
    receive_branch
    ( do_nothing()
    , argument_list_kinds( argument_types< int&, float&& > )
    , argument_list_kinds( argument_types< float&, int&& > )
    , 1
    , 'a'
    , 3.5
    );

    using result_type
      = decltype
        ( receive_branch
          ( do_nothing()
          , argument_list_kinds( argument_types< int&, float&& > )
          , argument_list_kinds( argument_types< float&, int&& > )
          , 1
          , 'a'
          , 3.5
          )
        );

    ARGOT_CONCEPT_ENSURE
    ( SameType
      < result_type
      , void
      >
    );
  }

  return 0;
}

ARGOT_EXECUTE_TESTS();

}  // namespace
