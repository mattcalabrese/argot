/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_ASYNC_CALL_DETAIL_CONTINUATION_WITH_REDUCER_HPP_
#define ARGOT_ASYNC_CALL_DETAIL_CONTINUATION_WITH_REDUCER_HPP_

#include <argot/concepts/future_packager.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/detail/invoker.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/reducer_reference.hpp>

namespace argot::detail_async_call {

template< class FPackager, class Reducer, class Fun >
struct continuation_with_reducer
{
  ARGOT_CONCEPT_ASSERT( FuturePackager< FPackager > );
  ARGOT_CONCEPT_ASSERT( ReturnValueReducer< Reducer > );

  // TODO(mattcalabrese) concept assert potentially invocable

  // TODO(mattcalabrese) conditional noexcept
  // TODO(mattcalabrese) take by forwarding reference
  template< class Provider >
  constexpr decltype( auto ) operator ()( Provider provider ) &&
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( provider )
    , receiver::reduced_invoke
      ( reducer::reducer_reference( ARGOT_MOVE( red ) )
      , argot_detail::invocable_to_basic_callable_by_reference
        ( ARGOT_FORWARD( Fun )( fun ) )
      )
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Reducer red;
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
};

} // namespace (argot::detail_async_call)


#endif  // ARGOT_ASYNC_CALL_DETAIL_CONTINUATION_WITH_REDUCER_HPP_
