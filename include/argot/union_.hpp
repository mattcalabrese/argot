/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_HPP_
#define ARGOT_UNION_HPP_

//[description
/*`
argot::union_ is a variadic class-template that takes a series of types as its
template parameters. Each parameter represents a different variant-member of a
core language `union`  that is to be logically represented by the template
instantiation. Special-member functions are generated in a similar to a core
`union` type, except that an argot::union_ always has a default constructor that
puts the object into a state with no alternative active, and it also always
has a destructor that does nothing. For MappedWhenContained template parameter
types, the corresponding alternatives are handled accordingly.

Each valid instantiation of argot::union_ is a UnionLike type.
*/
//]

#include <argot/concepts/assignable_when_contained.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/emplaceable_when_contained.hpp>
#include <argot/concepts/emplaceable_with_result_when_contained.hpp>
#include <argot/concepts/move_assignable.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/nothrow_assignable_when_contained.hpp>
#include <argot/concepts/nothrow_emplaceable_when_contained.hpp>
#include <argot/concepts/nothrow_emplaceable_with_result_when_contained.hpp>
#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/contained.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/construct.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/variadic_at.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/is_modeled.hpp>
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

//[docs
/*`
[synopsis_heading]
*/

namespace argot {

//<-
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
//->
template< class... T >
class union_
//<-
  : detail_union_adl::adl_base< union_< T... > > //->
{
  //<-
  template< std::size_t >
  friend struct detail_union::union_impl_preprocessed;

  // TODO(mattcalabrese) Remove this (go through core access)
  template< class, class >
  friend struct make_concept_map;

  template< class... >
  friend class union_;
 private:
  template< std::size_t Index >
  using alternative_type_t
    = detail_argot::variadic_at
      < Index, detail_forward::direct_identity_t
      , T...
      >;

  template< std::size_t Index >
  static constexpr bool alternative_is_pure_v
    = std::is_same_v< contained< alternative_type_t< Index > >
                    , alternative_type_t< Index >
                    >;

  static constexpr bool is_pure_v
    = std::is_same_v
      < argot::union_< contained< T >... >
      , union_
      >;

  using impl_type
    = typename argot_detail::conditional< is_pure_v >::template meta_apply
      < detail_union::union_base_picker
      , union_
      , contained< T >...
      >;
 public: //->
  using pure_type = argot::union_< argot::contained< T >... >;

  // Put the object into a valid-but-unspecified state.
  // This constructor is trivial if each of `T...` has a trivial default
  // constructor.
  constexpr union_() noexcept//=;
  //<-
  = default;
  //->

  // Destroys the object without calling the destructor of any of `T...`.
  // This destructor is trivial if each of `T...` has a trivial destructor.
  ~union_() noexcept//=;
  //<-
  = default;
  //->

  // TODO(mattcalabrese) Document the rest of the special-member-functions.

  // Construct the Ith alternative with the result of an invocation of `fun`
  // with `args`.
  template
  < std::size_t I, class Fun, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( EmplaceableWithResultWhenContained
      < alternative_type_t< I >, Fun&&, P&&... >
    )
    ()
  >
  explicit constexpr union_
  ( argot::in_place_index_with_result_t< I >, Fun&& fun, P&&... args )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowEmplaceableWithResultWhenContained
        < alternative_type_t< I >, Fun&&, P&&... >
      )
    )//=;
    //<-
    : alternatives
      ( in_place_index_with_result< I >
      , argot::emplace_contained_with_result< alternative_type_t< I > >
      , ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )...
      ) {} //->

  // Construct the Ith alternative using direct non-list initialization.
  template
  < std::size_t I, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( EmplaceableWhenContained< alternative_type_t< I >, P&&... > )
    ()
  >
  explicit constexpr union_( std::in_place_index_t< I >, P&&... args )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowEmplaceableWhenContained< alternative_type_t< I >, P&&... > )
    )//=;
  //<-
   : alternatives
      ( in_place_index_with_result< I >
      , argot::emplace_contained< alternative_type_t< I > >
      , ARGOT_FORWARD( P )( args )...
      ) {} //->

  // Construct the Ith alternative using direct non-list initialization.
  template
  < std::size_t I, class U, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( EmplaceableWhenContained
      < alternative_type_t< I >, std::initializer_list< U >&, P&&... >
    )
    ()
  >
  explicit constexpr union_
  ( std::in_place_index_t< I >, std::initializer_list< U > ilist, P&&... args )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowEmplaceableWhenContained
        < alternative_type_t< I >, std::initializer_list< U >&, P&&... >
      )
    )//=;
    //<-
    : alternatives
      ( in_place_index_with_result< I >
      , argot::emplace_contained< alternative_type_t< I > >
      , ilist, ARGOT_FORWARD( P )( args )...
      ) {} //->

  // Emplace the Ith alternative with the result of the invocation of `fun` with
  // `args`.
  // Precondition: *this has no active alternative.
  template
  < std::size_t I, class Fun, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( EmplaceableWithResultWhenContained
      < alternative_type_t< I >, Fun&&, P&&... >
    )
    ()
  >
  constexpr auto& emplace_with_result( Fun&& fun, P&&... args )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowEmplaceableWithResultWhenContained
        < alternative_type_t< I >, Fun&&, P&&... >
      )
    )//=;
  //<-
  {
    using alt_t = alternative_type_t< I >;

    laundered_alternatives().~impl_type();

    // TODO(mattcalabrese) Do this without try/catch
    try
    {
      if constexpr( std::is_same_v< alt_t, contained< alt_t > > )
        ::new( static_cast< void* >( std::addressof( alternatives ) ) )
        impl_type
        ( in_place_index_with_result< I >
        , ARGOT_FORWARD( Fun )( fun )
        , ARGOT_FORWARD( P )( args )...
        );
      else
        ::new( static_cast< void* >( std::addressof( alternatives ) ) )
        impl_type
        ( in_place_index_with_result< I >
        , emplace_contained_with_result< alt_t >
        , ARGOT_FORWARD( Fun )( fun )
        , ARGOT_FORWARD( P )( args )...
        );

      if constexpr
      ( std::is_same_v< alt_t, contained< alt_t > > )
        return detail_union::union_impl< sizeof...( T ), I >
        ::template get< alt_t >( laundered_alternatives() );
      else
        return argot::access_contained
        ( detail_union::union_impl< sizeof...( T ), I >
          ::template get< contained< alt_t > >( pure().alternatives )
        );
    }
    catch( ... )
    {
      ::new( static_cast< void* >( std::addressof( alternatives ) ) )
      impl_type;

      throw;
    }
  } //->

  // Emplace the Ith alternative with the `args` using direct non-list
  // initialization.
  // Precondition: *this has no active alternative.
  template
  < std::size_t I, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( EmplaceableWhenContained< alternative_type_t< I >, P&&... > )
    ()
  >
  constexpr auto& emplace( P&&... args )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowEmplaceableWhenContained< alternative_type_t< I >, P&&... > )
    )//=;
  //<-
  {
    using alt_t = alternative_type_t< I >;

    laundered_alternatives().~impl_type();

    // TODO(mattcalabrese) Do this without try/catch
    try
    {
      if constexpr( std::is_same_v< alt_t, contained< alt_t > > )
        ::new( static_cast< void* >( std::addressof( alternatives ) ) )
        impl_type
        ( std::in_place_index< I >
        , ARGOT_FORWARD( P )( args )...
        );
      else
        ::new( static_cast< void* >( std::addressof( alternatives ) ) )
        impl_type
        ( in_place_index_with_result< I >
        , emplace_contained< alt_t >
        , ARGOT_FORWARD( P )( args )...
        );

      if constexpr
      ( std::is_same_v< alt_t, contained< alt_t > > )
        return detail_union::union_impl< sizeof...( T ), I >
        ::template get< alt_t >( laundered_alternatives() );
      else
        return argot::access_contained
        ( detail_union::union_impl< sizeof...( T ), I >
          ::template get< contained< alt_t > >( pure().alternatives )
        );
    }
    catch( ... )
    {
      ::new( static_cast< void* >( std::addressof( alternatives ) ) )
      impl_type;

      throw;
    }
  } //->

  // Emplace the Ith alternative with the `ilist` and `args..` using direct
  // non-list initialization.
  // Precondition: *this has no active alternative.
  template
  < std::size_t I, class U, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( EmplaceableWhenContained
      < alternative_type_t< I >, std::initializer_list< U >&, P&&... >
    )
    ()
  >
  constexpr auto& emplace( std::initializer_list< U > ilist, P&&... args )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowEmplaceableWhenContained
        < alternative_type_t< I >, std::initializer_list< U >&, P&&... >
      )
    )//=;
  //<-
  {
    using alt_t = alternative_type_t< I >;

    laundered_alternatives().~impl_type();

    // TODO(mattcalabrese) Do this without try/catch
    try
    {
      if constexpr( std::is_same_v< alt_t, contained< alt_t > > )
        ::new( static_cast< void* >( std::addressof( alternatives ) ) )
        impl_type
        ( std::in_place_index< I >
        , ilist, ARGOT_FORWARD( P )( args )...
        );
      else
        ::new( static_cast< void* >( std::addressof( alternatives ) ) )
        impl_type
        ( in_place_index_with_result< I >
        , emplace_contained< alt_t >
        , ilist, ARGOT_FORWARD( P )( args )...
        );

      if constexpr
      ( std::is_same_v< alt_t, contained< alt_t > > )
        return detail_union::union_impl< sizeof...( T ), I >
        ::template get< alt_t >( laundered_alternatives() );
      else
        return argot::access_contained
        ( detail_union::union_impl< sizeof...( T ), I >
          ::template get< contained< alt_t > >( pure().alternatives )
        );
    }
    catch( ... )
    {
      ::new( static_cast< void* >( std::addressof( alternatives ) ) )
      impl_type;

      throw;
    }
  } //->

  // Assign `arg` to the Ith alternative.
  // Precondition: The Ith alternative is active.
  template
  < std::size_t I, class P
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( AssignableWhenContained< alternative_type_t< I >, P&& > )
    ()
  >
  constexpr auto& assign( P&& arg )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowAssignableWhenContained< alternative_type_t< I >, P&& > )
    )//=;
  //<-
  {
    using alt_t = alternative_type_t< I >;

    return argot::assign_contained< alt_t >
    ( detail_union::union_impl< sizeof...( T ), I >
      ::template get< contained< alt_t > >( pure().alternatives )
    , ARGOT_FORWARD( P )( arg )
    );
  } //->

  // Assign `ilist` to the Ith alternative.
  // Precondition: The Ith alternative is active.
  template
  < std::size_t I, class U
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( AssignableWhenContained
      < alternative_type_t< I >, std::initializer_list< U >& >
    )
    ()
  >
  constexpr auto& assign( std::initializer_list< U > ilist )
    noexcept
    ( ARGOT_IS_MODELED
      ( NothrowAssignableWhenContained
        < alternative_type_t< I >, std::initializer_list< U >& >
      )
    )//=;
  //<-
  {
    using alt_t = alternative_type_t< I >;

    return argot::assign_contained< alt_t >
    ( detail_union::union_impl< sizeof...( T ), I >
      ::template get< contained< alt_t > >( pure().alternatives )
    , ilist
    );
  } //->

  // Destroy the Ith alternative.
  // Precondition: The Ith alternative is active.
  template
  < std::size_t I
  , ARGOT_REQUIRES
    ( UnionIndex< union_, I > )
    ( Destructible< contained< alternative_type_t< I > > > )
    ()
  >
  constexpr void destroy()
    noexcept
    ( std::is_nothrow_destructible_v
      < contained< alternative_type_t< I > > >
    )//=;
  //<-
  {
    detail_union::union_impl< sizeof...( T ), I >
    ::destroy( pure().alternatives );
  } //->

  // Retrieve a reference to this object, but as though it were the type
  // argot::union_< argot::contained< T >... >.
  constexpr pure_type& pure() & noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return *std::launder( this );
    else
      return laundered_alternatives();
  } //->
  constexpr pure_type const& pure() const& noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return *std::launder( this );
    else
      return laundered_alternatives();
  } //->
  constexpr pure_type&& pure() && noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *std::launder( this ) );
    else
      return ARGOT_MOVE( laundered_alternatives() );
  } //->
  constexpr pure_type const&& pure() const && noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *std::launder( this ) );
    else
      return ARGOT_MOVE( laundered_alternatives() );
  } //->
 private:
  //<-
  constexpr impl_type& laundered_alternatives() & noexcept
  {
    return *std::launder( std::addressof( alternatives ) );
  }

  constexpr impl_type const& laundered_alternatives() const& noexcept
  {
    return *std::launder( std::addressof( alternatives ) );
  }

  constexpr impl_type&& laundered_alternatives() && noexcept
  {
    return ARGOT_MOVE( *std::launder( std::addressof( alternatives ) ) );
  }

  constexpr impl_type const&& laundered_alternatives() const && noexcept
  {
    return ARGOT_MOVE( *std::launder( std::addressof( alternatives ) ) );
  }
  //->
  //=union { /*...*/ } state; // Exposition only
  //<-
  ARGOT_NO_UNIQUE_ADDRESS impl_type alternatives;
  //->
};

} // namespace argot

//]

namespace argot {

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
    = detail_argot::variadic_at
      < Index, detail_forward::direct_identity_t
      , T...
      >;

  template< index_type Index, class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    using alt_t = alternative_type_t< Index >;

    // TODO(mattcalabrese) Use intrinsic
    if constexpr
    ( std::is_same_v< alt_t, contained< alt_t > > )
      return detail_union::union_impl< sizeof...( T ), Index >
      ::template get< alt_t >
      ( ARGOT_FORWARD( Self )( self ).laundered_alternatives() );
    else
      return argot::access_contained
      ( detail_union::union_impl< sizeof...( T ), Index >
        ::template get< contained< alt_t > >
        ( ARGOT_FORWARD( Self )( self ).pure().alternatives )
      );
  }
};

} // namespace argot

#endif  // ARGOT_UNION_HPP_
