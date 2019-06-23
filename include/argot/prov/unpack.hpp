/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_UNPACK_HPP_
#define ARGOT_PROV_UNPACK_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/concepts/volatile_object.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/receiver_traits/receive.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/tuple_traits/num_elements.hpp>

#include <memory>
#include <type_traits>

namespace argot {
namespace prov {

struct unpack_fn
{
  template< class Tuple >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( TupleLike< detail_argot::remove_cvref_t< Tuple > > );
    ARGOT_CONCEPT_ASSERT( Reference< Tuple > );

    ARGOT_CONCEPT_ASSERT
    ( Not< VolatileObject< std::remove_reference_t< Tuple > > > );

    using index_type = tuple_traits::index_type_t< detail_argot::remove_cvref_t< Tuple > >;
    using indices_type
      = std::make_integer_sequence
        < typename prov::unpack_fn::impl< Tuple >::index_type
        , tuple_traits::num_elements_v< detail_argot::remove_cvref_t< Tuple > >
        >;

// TODO(mattcalabrese) Fill these out
/*
    using lvalue_unpacked_argument_kinds
      =

    using rvalue_unpacked_argument_kinds
      =
*/
    template< class Receiver, index_type... Indices >
    static constexpr decltype( auto )
    rvalue_receive( impl self, Receiver&& rec
                  , std::integer_sequence< index_type, Indices... >
                  )
    {
      return receiver_traits::receive
      ( ARGOT_FORWARD( Receiver )( rec )
      , tuple_traits::get< Indices >( ARGOT_FORWARD( Tuple )( *self.tup ) )...
      );
    }

    template< class Receiver, index_type... Indices >
    static constexpr decltype( auto )
    lvalue_receive( impl self, Receiver&& rec
                  , std::integer_sequence< index_type, Indices... >
                  )
    {
      return receiver_traits::receive
      ( ARGOT_FORWARD( Receiver )( rec )
      , tuple_traits::get< Indices >( *self.tup )...
      );
    }

    std::remove_reference_t< Tuple >* tup;
  };
 public:
  template< class Tuple
          , ARGOT_REQUIRES
            ( TupleLike< detail_argot::remove_cvref_t< Tuple > > )
            ( Not< VolatileObject< std::remove_reference_t< Tuple > > > )
            ()
          >
  [[nodiscard]] constexpr auto operator ()( Tuple&& tup ) const noexcept
  {
    return impl< Tuple&& >{ std::addressof( tup ) };
  }
} inline constexpr unpack{};

template< class Tuple >
using result_of_unpack = basic_result_of< unpack_fn const&, Tuple >;

template< class Tuple >
using result_of_unpack_t = basic_result_of_t< unpack_fn const&, Tuple >;

}  // namespace argot(::prov)

template< class Tuple >
struct make_concept_map< ArgumentProvider< prov::unpack_fn::impl< Tuple > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov::unpack_fn::impl< Tuple > self, Receiver&& rec )
  {
    return self.rvalue_receive
    ( self, ARGOT_FORWARD( Receiver )( rec )
    , typename prov::unpack_fn::impl< Tuple >::indices_type()
    );
  }
};

template< class Tuple >
struct make_concept_map
< PersistentArgumentProvider< prov::unpack_fn::impl< Tuple > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov::unpack_fn::impl< Tuple > self, Receiver&& rec )
  {
    return self.lvalue_receive
    ( self, ARGOT_FORWARD( Receiver )( rec )
    , typename prov::unpack_fn::impl< Tuple >::indices_type()
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_UNPACK_HPP_
