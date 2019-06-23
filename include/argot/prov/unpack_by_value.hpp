/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_UNPACK_BY_VALUE_HPP_
#define ARGOT_PROV_UNPACK_BY_VALUE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/persistent_argument_provider.hpp>
#include <argot/concepts/reference.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/detail/sink.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/receiver_traits/receive.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/tuple_traits/get.hpp>
#include <argot/tuple_traits/index_type.hpp>
#include <argot/tuple_traits/num_elements.hpp>

#include <utility>

namespace argot {
namespace prov {

struct unpack_by_value_fn
{
  template< class Tup >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( TupleLike< Tup > );

    using index_type = tuple_traits::index_type_t< Tup >;
    using indices_type
      = std::make_integer_sequence
        < index_type
        , tuple_traits::num_elements_v< Tup >
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
    destructive_receive( impl&& self, Receiver&& rec
                       , std::integer_sequence< index_type, Indices... >
                       )
    {
      return receiver_traits::receive
      ( ARGOT_FORWARD( Receiver )( rec )
      , tuple_traits::get< Indices >( ARGOT_MOVE( self.tup ) )...
      );
    }

    template< class Receiver, index_type... Indices >
    static constexpr decltype( auto )
    persistent_receive( impl const& self, Receiver&& rec
                      , std::integer_sequence< index_type, Indices... >
                      )
    {
      return receiver_traits::receive
      ( ARGOT_FORWARD( Receiver )( rec )
      , tuple_traits::get< Indices >( self.tup )...
      );
    }

    ARGOT_NO_UNIQUE_ADDRESS Tup tup;
  };
 public:
  template< class Tup
          , ARGOT_REQUIRES( TupleLike< detail_argot::remove_cvref_t< Tup > > )
                          ( Sinkable< Tup&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator ()( Tup&& tup ) const
  {
    return impl< detail_argot::remove_cvref_t< Tup > >{ ARGOT_FORWARD( Tup )( tup ) };
  }
} inline constexpr unpack_by_value{};

template< class Tup >
using result_of_unpack_by_value
  = basic_result_of< unpack_by_value_fn const&, Tup >;

template< class Tup >
using result_of_unpack_by_value_t
  = basic_result_of_t< unpack_by_value_fn const&, Tup >;

}  // namespace argot(::prov)

template< class Tup >
struct make_concept_map
< ArgumentProvider< prov::unpack_by_value_fn::impl< Tup > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov::unpack_by_value_fn::impl< Tup >&& self, Receiver&& rec )
  {
    return self.destructive_receive
    ( ARGOT_MOVE( self ), ARGOT_FORWARD( Receiver )( rec )
    , typename prov::unpack_by_value_fn::impl< Tup >::indices_type()
    );
  }
};

template< class Tup >
struct make_concept_map
< PersistentArgumentProvider< prov::unpack_by_value_fn::impl< Tup > > >
{
  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide( prov::unpack_by_value_fn::impl< Tup > const& self, Receiver&& rec )
  {
    return self.persistent_receive
    ( self, ARGOT_FORWARD( Receiver )( rec )
    , typename prov::unpack_by_value_fn::impl< Tup >::indices_type()
    );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_UNPACK_BY_VALUE_HPP_
