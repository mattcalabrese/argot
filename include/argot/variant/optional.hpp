/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VARIANT_OPTIONAL_HPP_
#define ARGOT_VARIANT_OPTIONAL_HPP_

#include <argot/concepts/constructible.hpp>
#include <argot/concepts/union.hpp>
#include <argot/concepts/variant.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/union/destructible_union.hpp>
#include <argot/variant_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>
#include <argot/void_.hpp>

#include <initializer_list>

namespace argot {

// TODO(mattcalabrese) Conditionally comparable, hashable, swappable
template< class T >
class optional
{
 private:
  using adjusted_value_type = regular_void_if_void_t< T >;
 public:
  struct nullopt_t
  {
    explicit nullopt_t() = default;
  };

  static nullopt_t constexpr nullopt{};
 public:
  optional() = default;

  // TODO(mattcalabrese) noexcept
  template< class... P
          , ARGOT_REQUIRES( Constructible< adjusted_value_type, P&&... > )()
          >
  explicit constexpr optional( std::in_place_t const /*in_place*/, P&&... args )
    : alternatives( std::in_place_index< 1 >, ARGOT_FORWARD( P )( args )... ) {}

  // TODO(mattcalabrese) noexcept
  template< class U, class... P
          , ARGOT_REQUIRES
            ( Constructible
              < adjusted_value_type
              , std::initializer_list< U >&, P&&...
              >
            )()
          >
  explicit constexpr optional( std::in_place_t const /*in_place*/
                             , std::initializer_list< U > ilist, P&&... args
                             )
    : alternatives( std::in_place_index< 1 >
                  , ilist, ARGOT_FORWARD( P )( args )...
                  ) {}

  // TODO(mattcalabrese) Emplacement.

  // TODO(mattcalabrese) operator ->.

  // TODO(mattcalabrese) Possibly volatile-qualified overloads?

  [[nodiscard]] constexpr adjusted_value_type& operator*() & noexcept
  {
    return variant_traits::get< 1 >( alternatives );
  }

  [[nodiscard]] constexpr adjusted_value_type& operator*() const& noexcept
  {
    return variant_traits::get< 1 >( alternatives );
  }

  [[nodiscard]] constexpr adjusted_value_type&& operator*() && noexcept
  {
    return variant_traits::get< 1 >( ARGOT_MOVE( alternatives ) );
  }

  [[nodiscard]] constexpr adjusted_value_type&& operator*() const && noexcept
  {
    return variant_traits::get< 1 >( ARGOT_MOVE( alternatives ) );
  }

  [[nodiscard]] explicit constexpr operator bool() const noexcept
  {
    return variant_traits::index_of( alternatives ) != 0;
  }

  // TODO(mattcalabrese) Possibly return reference to nullopt?
  constexpr void reset() noexcept { alternatives.template emplace< 0 >(); }

  // TODO(mattcalabrese) Constrain and noexcept
  constexpr T& assign( adjusted_value_type const& other )
  {
    if( variant_traits::index_of( alternatives ) == 0 )
      return alternatives.template emplace< 1 >( other );
    else
    {
      auto& object = variant_traits::get< 1 >( alternatives );
      object = other;
      return object;
    }

    return variant_traits::get< 1 >( alternatives );
  }

  // TODO(mattcalabrese) Constrain and noexcept
  constexpr T& assign( adjusted_value_type&& other )
  {
    if( variant_traits::index_of( alternatives ) == 0 )
      return alternatives.template emplace< 1 >( ARGOT_MOVE( other ) );
    else
    {
      auto& object = variant_traits::get< 1 >( alternatives );
      object = ARGOT_MOVE( other );
      return object;
    }
  }

  // TODO(mattcalabrese) noexcept
  template< class... P
          , ARGOT_REQUIRES( Constructible< adjusted_value_type, P&&... > )()
          >
  constexpr T& emplace( P&&... args )
  {
    return alternatives.template emplace< 1 >( ARGOT_FORWARD( P )( args )... );
  }

  // TODO(mattcalabrese) noexcept
  template< class U, class... P
          , ARGOT_REQUIRES
            ( Constructible
              < adjusted_value_type
              , std::initializer_list< U >&, P&&...
              >
            )()
          >
  constexpr T& emplace( std::initializer_list< U > ilist, P&&... args )
  {
    alternatives.template emplace< 1 >( ilist, ARGOT_FORWARD( P )( args )... );
  }

  // TODO(mattcalabrese) Make -> overloads iif sensible (non-reference)
 private:
  ARGOT_NO_UNIQUE_ADDRESS discriminated_union< nullopt_t, T > alternatives;
};

}  // namespace argot

#endif  // ARGOT_VARIANT_OPTIONAL_HPP_
