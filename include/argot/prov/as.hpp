/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_AS_HPP_
#define ARGOT_PROV_AS_HPP_

#include <argot/concepts/convertible.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/detail/argument_pack.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/detail/as_impl.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>

namespace argot::prov {

// TODO(mattcalabrese)
//   Collapse this to a single default definition.
//   Eliminate argument_pack_t and only have as_impl.
template< class... P >
struct as_fn;

template<>
struct as_fn<>
{
  constexpr nothing_t operator ()() const noexcept
  {
    return {};
  }
};

template< class Head, class... Tail >
struct as_fn< Head, Tail... >
{
  ARGOT_CONCEPT_ASSERT( MoveConstructible< Head > );
  ARGOT_CONCEPT_ASSERT( MoveConstructible< Tail >... );

  template< class HeadP, class... TailP
          , ARGOT_REQUIRES( Convertible< HeadP&&, Head > )
                          ( Convertible< TailP&&, Tail >... )
                          ()
          >
  [[nodiscard]] constexpr auto
  operator ()( HeadP&& head, TailP&&... tail ) const noexcept
  {
    return as_detail::as_impl< Head, Tail... >
    { { call_detail::make_argument_pack< Head const, Tail const... >
        ( ARGOT_FORWARD( HeadP )( head ), ARGOT_FORWARD( TailP )( tail )... )
      }
    };
  }
};

// TODO(mattcalabrese) Constrain (movable if object...)
template< class... P >
inline ARGOT_REQUIRES( MoveConstructible< P >... )
< as_fn< P... > > constexpr as{};

// TODO(mattcalabrese) Make result_of calculators

/*
template< class... P >
using result_of_as
  = basic_result_of< as_t const&, P&&... >;

template< class... P >
using result_of_as_t
  = basic_result_of_t< as_t const&, P&&... >;*/

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_AS_HPP_
