/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_HPP_
#define ARGOT_UNION_HPP_

#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/move_assignable.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/construct.hpp>
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

namespace detail_union_adl {

template< class Child >
struct adl_base {};

// TODO(mattcalabrese) Remove once std swap is constexpr.
template< class... T
        , ARGOT_REQUIRES( MoveConstructible< union_< T... > > )
                        ( MoveAssignable< union_< T... > > )
                        ( Destructible< union_< T... > > )
                        ()
        >
constexpr void swap( union_< T... >& lhs, union_< T... >& rhs ) noexcept
{
  union_< T... > temp = ARGOT_MOVE( lhs );
  lhs = ARGOT_MOVE( rhs );
  rhs = ARGOT_MOVE( temp );
}

} // namespace argot(::detail_union_adl)

// Note:
//   The default definition is used only up to the preprocessed maximum.
template< class... T >
class union_
  : detail_union_adl::adl_base< union_< T... > >
{
  template< std::size_t >
  friend struct detail_union::union_impl_preprocessed;

  template< class... >
  friend class union_;
 private:
  template< std::size_t Index >
  using alternative_type_t
    = typename detail_union::union_impl< sizeof...( T ), Index >
      ::template alternative_type_t< T... >;

  template< std::size_t Index >
  static constexpr bool const& alternative_is_pure_v
    = std::is_same_v< call_detail::holder< alternative_type_t< Index > >
                    , alternative_type_t< Index >
                    >;

  static constexpr bool const& is_pure_v
    = std::is_same_v
      < argot::union_< call_detail::holder< T >... >
      , union_
      >;

  using impl_type
    = typename argot_detail::conditional< is_pure_v >::template meta_apply
      < detail_union::union_base
      , union_
      , call_detail::holder< T >...
      >;
 public:
  using pure_type = typename argot::union_< call_detail::holder< T >... >;

  union_() = default;

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  template
  < std::size_t I, class Fun, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_with_result_fn< alternative_type_t< I > >
          const&
      , Fun&&, P&&...
      >
    )
    ()
  >
  explicit constexpr union_
  ( in_place_index_with_result_t< I > const /*in_place_index_with_result*/
  , Fun&& fun, P&&... args
  ) noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
    : alternatives
      ( in_place_index_with_result< I >
      , call_detail::emplace_holder_with_result< alternative_type_t< I > >
      , ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )...
      ) {}

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
    : alternatives
      ( in_place_index_with_result< I >
      , call_detail::emplace_holder< alternative_type_t< I > >
      , ARGOT_FORWARD( P )( args )...
      ) {}

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
      ( in_place_index_with_result< I >
      , call_detail::emplace_holder< alternative_type_t< I > >
      , ilist, ARGOT_FORWARD( P )( args )...
      ) {}

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class Fun, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_with_result_fn< alternative_type_t< I > >
          const&
      , Fun&&, P&&...
      >
    )
    ()
  >
  constexpr auto& emplace_with_result( Fun&& fun, P&&... args )
  {
    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( *::new
       ( static_cast< void* >( std::addressof( pure().alternatives ) ) )
       call_detail::holder< alternative_type_t< I > >
       ( call_detail::emplace_holder_with_result_fn< alternative_type_t< I > >
         ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... )
       )
    );
  }

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
    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( *::new
       ( static_cast< void* >( std::addressof( pure().alternatives ) ) )
       call_detail::holder< alternative_type_t< I > >
       ( call_detail::emplace_holder< alternative_type_t< I > >
         ( ARGOT_FORWARD( P )( args )... )
       )
    );
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
    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( *::new
       ( static_cast< void* >( std::addressof( pure().alternatives ) ) )
       call_detail::holder< alternative_type_t< I > >
       ( call_detail::emplace_holder< alternative_type_t< I > >
         ( ilist, ARGOT_FORWARD( P )( args )... )
       )
    );
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
    return call_detail::assign_holder< alternative_type_t< I > >
    ( detail_union::union_impl_preprocessed< I >::get( pure() )
    , ARGOT_FORWARD( P )( arg )
    );
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
    return call_detail::assign_holder< alternative_type_t< I > >
    ( detail_union::union_impl_preprocessed< I >::get( pure() )
    , ilist
    );
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
    if constexpr
    ( !std::is_trivially_destructible_v
      < call_detail::holder< alternative_type_t< I > > >
    )
      std::destroy_at
      ( std::addressof
        ( detail_union::union_impl_preprocessed< I >::get( pure() ) )
      );
  }

  constexpr pure_type& pure() & noexcept
  {
    if constexpr( is_pure_v )
      return *this;
    else
      return alternatives;
  }

  constexpr pure_type const& pure() const& noexcept
  {
    if constexpr( is_pure_v )
      return *this;
    else
      return alternatives;
  }

  constexpr pure_type&& pure() && noexcept
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *this );
    else
      return ARGOT_MOVE( alternatives );
  }

  constexpr pure_type const&& pure() const && noexcept
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *this );
    else
      return ARGOT_MOVE( alternatives );
  }
 private:
  ARGOT_NO_UNIQUE_ADDRESS impl_type alternatives;
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
    if constexpr
    ( std::is_same_v
      < alternative_type_t< Index >
      , call_detail::holder< alternative_type_t< Index > >
      >
    )
      return detail_union::union_impl< sizeof...( T ), Index >
      ::get( ARGOT_FORWARD( Self )( self ) );
    else
      return call_detail::access_holder
      ( detail_union::union_impl< sizeof...( T ), Index >
        ::get( ARGOT_FORWARD( Self )( self ).pure() )
      );
  }
};

}  // namespace argot

#endif  // ARGOT_UNION_HPP_
