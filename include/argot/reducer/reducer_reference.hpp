/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_REDUCER_REDUCER_REFERENCE_HPP_
#define ARGOT_REDUCER_REDUCER_REFERENCE_HPP_

#include <argot/concepts/reference.hpp>
#include <argot/concepts/return_value_reducer.hpp>
#include <argot/contained.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/reducer_traits/is_homogeneous.hpp>
#include <argot/reducer_traits/reduce.hpp>
#include <argot/reducer_traits/return_types.hpp>
#include <argot/remove_cvref.hpp>

#include <type_traits>
#include <utility>

namespace argot {
namespace reducer {

struct reducer_reference_t
{
  template< class Reducer >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( Reference< Reducer > );
    ARGOT_CONCEPT_ASSERT
    ( ReturnValueReducer
      < std::remove_const_t< std::remove_reference_t< Reducer > > >
    );

    contained< Reducer > reducer;
  };

  template< class Reducer
          , ARGOT_REQUIRES( ReturnValueReducer< remove_cvref_t< Reducer > > )()
          >
  constexpr auto operator ()( Reducer&& red ) const
  {
    return impl< Reducer&& >{ argot::make_contained< Reducer&& >
                              ( ARGOT_FORWARD( Reducer )( red ) )
                            };
  }
} inline constexpr reducer_reference{};

template< class Reducer >
using result_of_reducer_reference_t
  = basic_result_of_t< reducer_reference_t const&, Reducer >;

template< class Reducer >
using result_of_reducer_reference
  = basic_result_of< reducer_reference_t const&, Reducer >;

}  // namespace argot::reducer

template< class Reducer >
struct make_concept_map
< ReturnValueReducer< reducer::reducer_reference_t::impl< Reducer > > >
{
  using is_homogeneous
    = reducer_traits::is_homogeneous< remove_cvref_t< Reducer > >;

  template
  < class Self
  , class... LeadingReturnTypes, class Fun, class... TrailingReturnTypes
  >
  static constexpr
  reducer_traits::result_of_reduce_t
  < call_detail::give_qualifiers_to_t< Self&&, Reducer >
  , reducer_traits::return_types_t< LeadingReturnTypes... >
  , reducer_traits::return_types_t< TrailingReturnTypes... >
  , Fun
  >
  reduce( Self&& self
        , reducer_traits::return_types_t< LeadingReturnTypes... >
        , reducer_traits::return_types_t< TrailingReturnTypes... >
        , Fun&& fun
        )
  {
    return reducer_traits::reduce
    ( argot::access_contained( ARGOT_FORWARD( Self )( self ).reducer )
    , reducer_traits::return_types_t< LeadingReturnTypes... >{}
    , reducer_traits::return_types_t< TrailingReturnTypes... >{}
    , ARGOT_FORWARD( Fun )( fun )
    );
  }
};

// TODO(mattcalabrese) Make persistent form

}  // namespace argot

#endif  // ARGOT_REDUCER_REDUCER_REFERENCE_HPP_
