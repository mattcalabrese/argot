/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_HPP_
#define ARGOT_UNION_HPP_

#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/holder.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/union_/detail/config.hpp>
#include <argot/union_/detail/generate_union_backend.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot {

template< class... T >
class union_;

// Note:
//   The default definition is used only up to the preprocessed maximum and also
//   does not handle the "sizeof...( T ) == 0" case.
// TODO(mattcalabrese) Make copyable/assignable in the places it makes sense.
template< class... T >
class union_
{
  template< std::size_t >
  friend struct detail_union::union_impl_preprocessed;
 private:
  template< std::size_t Index >
  using alternative_type_t
    = typename detail_union::union_impl< sizeof...( T ), Index >
      ::template alternative_type_t< T... >;
 public:
  union_() = default;

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , P&&...
      >
    )
    ()
  >
  explicit constexpr union_
  ( std::in_place_index_t< I > const /*in_place_index*/, P&&... args )
    : alternatives( std::in_place_index< I >, ARGOT_FORWARD( P )( args )... ) {}

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class U, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , std::initializer_list< U >&, P&&...
      >
    )
    ()
  >
  explicit constexpr union_
  ( std::in_place_index_t< I > const /*in_place_index*/
  , std::initializer_list< U > ilist, P&&... args
  ) : alternatives
      ( std::in_place_index< I >, ilist, ARGOT_FORWARD( P )( args )... ) {}

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , P&&...
      >
    )
    ()
  >
  constexpr auto& emplace( P&&... args )
  {
    return detail_union::union_impl_preprocessed< I >
    ::emplace( *this, ARGOT_FORWARD( P )( args )... );
  }

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class U, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , std::initializer_list< U >&, P&&...
      >
    )
    ()
  >
  constexpr auto& emplace( std::initializer_list< U > ilist, P&&... args )
  {
    return detail_union::union_impl_preprocessed< I >
    ::emplace( *this, ilist, ARGOT_FORWARD( P )( args )... );
  }

  // TODO(mattcalabrese)
  //   Branch to Assignable for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )/*
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , P&&
      >
    )*/
    ()
  >
  constexpr auto& assign( P&& arg )
  {
    return detail_union::union_impl_preprocessed< I >
    ::assign( *this, ARGOT_FORWARD( P )( arg ) );
  }

  // TODO(mattcalabrese)
  //   Branch to Assignable for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class U
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )/*
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , std::initializer_list< U >&, P&&...
      >
    )*/
    ()
  >
  constexpr auto& assign( std::initializer_list< U > ilist )
  {
    return detail_union::union_impl_preprocessed< I >::assign( *this, ilist );
  }

  // TODO(mattcalabrese) Branch on const so there is a better error.
  // TODO(mattcalabrese) Make sure this is constexpr if trivially destructible.
  template
  < std::size_t I
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( Destructible< call_detail::holder< alternative_type_t< I > > > )
    ()
  >
  constexpr void destroy()
  noexcept
  ( std::is_nothrow_destructible_v
    < call_detail::holder< alternative_type_t< I > > >
  )
  {
    // TODO(mattcalabrese) Possibly just destroy the appropriate type?
    detail_union::union_impl_preprocessed< I >::destroy( *this );
  }
 private:
  ARGOT_NO_UNIQUE_ADDRESS
  detail_union::union_base< T... > alternatives;
};

// TODO(mattcalabrese) Define this. Make a balanced tree of preprocessed unions.
template
< BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, class T )
, class TN, class... U
>
class union_
< BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, T )
, TN, U...
>;

template< class... T >
struct make_concept_map< UnionLike< union_< T... > > >
{
  using index_type = std::size_t;  // TODO(mattcalabrese) Calculate minimal type

  static index_type constexpr num_alternatives = sizeof...( T );

  template< index_type Index >
  using alternative_type_t
    = typename detail_union::union_impl< sizeof...( T ), Index >
      ::template alternative_type_t< T... >;

  template< index_type Index, class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    return detail_union::union_impl< sizeof...( T ), Index >
    ::get( ARGOT_FORWARD( Self )( self ) );
  }
};

}  // namespace argot

#endif  // ARGOT_UNION_HPP_
