/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_ACCESS_UNION_HPP_
#define ARGOT_PROV_ACCESS_UNION_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/default_.hpp>
#include <argot/forward.hpp>
#include <argot/gen/not.hpp>
#include <argot/move.hpp>
#include <argot/prov/lift_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/union_index.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/union_traits/natural_get.hpp>
#include <argot/union_traits/index_type.hpp>

#include <type_traits>

namespace argot::prov {

struct access_union_fn
{
  // TODO(mattcalabrese) Have an overload for integral_constants
  // TODO(mattcalabrese) Handle the Index concept checking
  template< class Union, class Index, class Def = default_unreachable_t
          , ARGOT_REQUIRES
            ( UnionLike< remove_cvref_t< Union > > )
            ( Not< VolatileObject< std::remove_reference_t< Union > > > )
            ( ConvertibleToTypeOrConstant
              < Index, union_traits::index_type_t< remove_cvref_t< Union > > >
            )
            ( Default< Def > )
            ()
          >
  [[nodiscard]] constexpr auto operator ()
  ( Union&& union_to_access, Index&& index, Def def = {} ) const
  {
    return prov::lift_call
    ( union_traits::natural_get
    , prov::reference_to( ARGOT_FORWARD( Union )( union_to_access ) )
    , prov::union_index< remove_cvref_t< Union > >
      ( ARGOT_FORWARD( Index )( index ), ARGOT_MOVE( def ) )
    );
  }
} inline constexpr access_union{};

template< class Union, class Index, class Def = default_unreachable_t >
using result_of_access_union
  = basic_result_of< access_union_fn const&, Union, Index, Def >;

template< class Union, class Index, class Def = default_unreachable_t >
using result_of_access_union_t
  = basic_result_of_t< access_union_fn const&, Union, Index, Def >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_ACCESS_UNION_HPP_
