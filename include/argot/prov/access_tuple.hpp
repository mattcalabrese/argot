/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ACCESS_TUPLE_HPP_
#define ARGOT_PROV_ACCESS_TUPLE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/convertible_to_type_or_constant.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/default_.hpp>
#include <argot/forward.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/tuple_index.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/tuple_traits/natural_get.hpp>

#include <type_traits>

namespace argot::prov {

struct access_tuple_fn
{
  template
  < class Tuple, class Index, class Def = default_unreachable_t
  , ARGOT_REQUIRES
    ( TupleLike< remove_cvref_t< Tuple > > )
    ( Not< VolatileObject< std::remove_reference_t< Tuple > > > )
    ( ConvertibleToTypeOrConstant
      < Index, tuple_traits::index_type_t< remove_cvref_t< Tuple > > >
    )
    ( Default< Def > )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()
  ( Tuple&& tuple_to_access, Index&& index, Def def = Def{} ) const
  {
    return prov::lift_call
    ( tuple_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Tuple )( tuple_to_access ) )
    , prov::tuple_index< remove_cvref_t< Tuple > >
      ( ARGOT_FORWARD( Index )( index ), ARGOT_MOVE( def ) )
    );
  }
} inline constexpr access_tuple{};

template< class Tuple, class Index, class Def = default_unreachable_t >
using result_of_access_tuple
  = basic_result_of< access_tuple_fn const&, Tuple, Index, Def >;

template< class Tuple, class Index, class Def = default_unreachable_t >
using result_of_access_tuple_t
  = basic_result_of_t< access_tuple_fn const&, Tuple, Index, Def >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_ACCESS_TUPLE_HPP_
