/*==============================================================================
  Copyright (c) 2018, 2020 Matt Calabrese

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
#include <argot/detail/addressof.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/construct.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/is_const.hpp>
#include <argot/detail/is_rvalue_reference.hpp>
#include <argot/detail/is_same.hpp>
#include <argot/detail/launder.hpp>
#include <argot/detail/rethrow.hpp>
#include <argot/detail/variadic_at.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/union_/detail/config.hpp>
#include <argot/union_/detail/union_backend.hpp>

#include <boost/predef.h>
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

//<-

// GCC doesn't do "guaranteed elision" here...
#if BOOST_COMP_GNUC
#define ARGOT_DETAIL_NO_DATAMEMBER_GUARANTEED_ELISION 1
#else
#define ARGOT_DETAIL_NO_DATAMEMBER_GUARANTEED_ELISION 0
#endif

//->

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

//->
template< class... T >
class union_
//<-
  : detail_union_adl::adl_base< union_< T... > > //->
{
  //<-
  // TODO(mattcalabrese) Don't do this here. Avoid substituting in nonpure.
  using union_tree
    = detail_argot::form_tree< detail_union::union_impl, contained< T >... >;

  using raw_concept_map = access_raw_concept_map< UnionLike< union_ > >;

  static constexpr std::size_t tree_depth_v
    = detail_argot::tree_depth_from_amount( sizeof...( T ) );

  static constexpr std::size_t amount_per_group_v
    = detail_argot::amount_per_group_at_depth( tree_depth_v );

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
    = ARGOT_IS_SAME( contained< alternative_type_t< Index > >
                   , alternative_type_t< Index >
                   );

  static constexpr bool is_pure_v
    = ARGOT_IS_SAME
      ( argot::union_< contained< T >... >
      , union_
      );

  using impl_type
    = typename argot_detail::conditional< is_pure_v >::template meta_apply
      < detail_union::form_union_tree
      , detail_union::form_pure_union
      , T...
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
// GCC doesn't do "guaranteed elision" here.
#if ARGOT_DETAIL_NO_DATAMEMBER_GUARANTEED_ELISION
    : union_
      ( make_in_place_with_result_tag< I >()
      , ARGOT_SIMPLE_FORWARD( fun ), ARGOT_SIMPLE_FORWARD( args )...
      ) {} //->
#else
    : alternatives
      ( make_in_place_with_result< I >
        ( ARGOT_SIMPLE_FORWARD( fun ), ARGOT_SIMPLE_FORWARD( args )... )
      ) {}
#endif //->

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
// GCC doesn't do "guaranteed elision" here.
#if ARGOT_DETAIL_NO_DATAMEMBER_GUARANTEED_ELISION
   : union_
     ( make_in_place_tag< I >()
     , ARGOT_SIMPLE_FORWARD( args )...
     ) {}
#else
   : alternatives
     ( make_in_place< I >( ARGOT_SIMPLE_FORWARD( args )... ) ) {}
#endif //->

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
// GCC doesn't do "guaranteed elision" here.
#if ARGOT_DETAIL_NO_DATAMEMBER_GUARANTEED_ELISION
   : union_
     ( make_in_place_tag< I >()
     , ilist, ARGOT_SIMPLE_FORWARD( args )...
     ) {}
#else
   : alternatives
     ( make_in_place< I >( ilist, ARGOT_SIMPLE_FORWARD( args )... ) ) {}
#endif // ->

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
    if constexpr( !is_pure_v )
      ARGOT_LAUNDER_DIRECT( alternatives.alternatives ).~union_tree();

    ARGOT_LAUNDER_DIRECT( alternatives ).~impl_type();

    // TODO(mattcalabrese) Do this without try/catch
    try
    {
      ::new( static_cast< void* >( ARGOT_ADDRESSOF( alternatives ) ) )
      impl_type
      ( make_in_place_with_result< I >
        ( ARGOT_SIMPLE_FORWARD( fun ), ARGOT_SIMPLE_FORWARD( args )... )
      );

      // TODO(mattcalabrese) Don't use get -- get element via construction
      auto& element = raw_concept_map::template get< I >( *this );

      using alt_t = alternative_type_t< I >;

      if constexpr( ARGOT_IS_SAME( alt_t, contained< alt_t > ) )
        return element;
      else
        return argot::access_contained( element );
    }
    catch( ... )
    {
      ::new( static_cast< void* >( ARGOT_ADDRESSOF( alternatives ) ) )
        impl_type;
      detail_argot::rethrow();
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
    if constexpr( !is_pure_v )
      ARGOT_LAUNDER_DIRECT( alternatives.alternatives ).~union_tree();

    ARGOT_LAUNDER_DIRECT( alternatives ).~impl_type();

    // TODO(mattcalabrese) Do this without try/catch
    try
    {
      ::new( static_cast< void* >( ARGOT_ADDRESSOF( alternatives ) ) )
      impl_type
      ( make_in_place< I >( ARGOT_SIMPLE_FORWARD( args )... ) );

      // TODO(mattcalabrese) Don't use get -- get element via construction
      auto& element = raw_concept_map::template get< I >( *this );

      using alt_t = alternative_type_t< I >;

      if constexpr( ARGOT_IS_SAME( alt_t, contained< alt_t > ) )
        return element;
      else
        return argot::access_contained( element );
    }
    catch( ... )
    {
      ::new( static_cast< void* >( ARGOT_ADDRESSOF( alternatives ) ) )
        impl_type;
      detail_argot::rethrow();
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
    if constexpr( !is_pure_v )
      ARGOT_LAUNDER_DIRECT( alternatives.alternatives ).~union_tree();

    ARGOT_LAUNDER_DIRECT( alternatives ).~impl_type();

    // TODO(mattcalabrese) Do this without try/catch
    try
    {
      ::new( static_cast< void* >( ARGOT_ADDRESSOF( alternatives ) ) )
      impl_type
      ( make_in_place< I >( ilist, ARGOT_SIMPLE_FORWARD( args )... ) );

      // TODO(mattcalabrese) Don't use get -- get element via construction
      auto& element = raw_concept_map::template get< I >( *this );

      using alt_t = alternative_type_t< I >;

      if constexpr( ARGOT_IS_SAME( alt_t, contained< alt_t > ) )
        return element;
      else
        return argot::access_contained( element );
    }
    catch( ... )
    {
      ::new( static_cast< void* >( ARGOT_ADDRESSOF( alternatives ) ) )
        impl_type;
      detail_argot::rethrow();
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

    if constexpr( ARGOT_IS_SAME( contained< alt_t >, alt_t ) )
    {
      auto& element = raw_concept_map::template get< I >( *this );
      element = ARGOT_SIMPLE_FORWARD( arg );
      return element;
    }
    else
      return argot::assign_contained< alt_t >
      ( access_raw_concept_map< UnionLike< impl_type > >
        ::template get< I >( alternatives )
      , ARGOT_SIMPLE_FORWARD( arg )
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

    if constexpr( ARGOT_IS_SAME( contained< alt_t >, alt_t ) )
    {
      auto& element = raw_concept_map::template get< I >( *this );
      element = ilist;
      return element;
    }
    else
      return argot::assign_contained< alt_t >
      ( access_raw_concept_map< UnionLike< impl_type > >
        ::template get< I >( alternatives )
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
    // TODO(mattcalabrese) Do this in a more compile-time efficient way
    if constexpr( is_pure_v )
    {
      auto& elem = raw_concept_map::template get< I >( *this );
      using alt_t = std::remove_reference_t< decltype( elem ) >;
      elem.~alt_t();
    }
    else
      alternatives.template destroy< I >();
  } //->

  // Retrieve a reference to this object, but as though it were the type
  // argot::union_< argot::contained< T >... >.
  constexpr pure_type& pure() & noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return *ARGOT_LAUNDER( this );
    else
      return ARGOT_LAUNDER( this )->alternatives;
  } //->
  constexpr pure_type const& pure() const& noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return *ARGOT_LAUNDER( this );
    else
      return ARGOT_LAUNDER( this )->alternatives;
  } //->
  constexpr pure_type&& pure() && noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *ARGOT_LAUNDER( this ) );
    else
      return ARGOT_MOVE( ARGOT_LAUNDER( this )->alternatives );
  } //->
  constexpr pure_type const&& pure() const && noexcept//=;
  //<-
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *ARGOT_LAUNDER( this ) );
    else
      return ARGOT_MOVE( ARGOT_LAUNDER( this )->alternatives );
  } //->
 private:
  //<-
  // TODO(calabrese) noexcept
  template< std::size_t I, class F, class... U >
  static constexpr auto make_in_place_with_result( F&& f, U&&... args )
  {
    if constexpr( is_pure_v )
      return union_tree
      ( in_place_index_with_result< tree_depth_v - 1 >
      , std::in_place_index< I / amount_per_group_v >
      , std::in_place_index< I % amount_per_group_v >
      , ARGOT_SIMPLE_FORWARD( f ), ARGOT_SIMPLE_FORWARD( args )...
      );
    else
      if constexpr( alternative_is_pure_v< I > )
        return pure_type
        ( in_place_index_with_result< I >
        , ARGOT_SIMPLE_FORWARD( f )
        , ARGOT_SIMPLE_FORWARD( args )...
        );
      else
        return pure_type
        ( in_place_index_with_result< I >
        , []( F&& f_fwd, U&&... args_fwd ) -> decltype( auto ) // TODO(calabrese) noexcept
          {
            return emplace_contained_with_result< alternative_type_t< I > >
            ( ARGOT_SIMPLE_FORWARD( f_fwd )
            , ARGOT_SIMPLE_FORWARD( args_fwd )...
            );
          }
        , ARGOT_SIMPLE_FORWARD( f )
        , ARGOT_SIMPLE_FORWARD( args )...
        );
  }

  // TODO(calabrese) noexcept
  template< std::size_t I, class... U >
  static constexpr auto make_in_place( U&&... args )
  {
    if constexpr( is_pure_v )
      return union_tree
      ( std::in_place_index< tree_depth_v - 1 >
      , std::in_place_index< I / amount_per_group_v >
      , std::in_place_index< I % amount_per_group_v >
      , ARGOT_SIMPLE_FORWARD( args )...
      );
    else
      if constexpr( alternative_is_pure_v< I > )
        return pure_type
        ( std::in_place_index< I >
        , ARGOT_SIMPLE_FORWARD( args )...
        );
      else
        return pure_type
        ( in_place_index_with_result< I >
        , []( U&&... args_fwd ) -> decltype( auto ) // TODO(calabrese) noexcept
          {
            return make_contained< alternative_type_t< I > >
            ( ARGOT_SIMPLE_FORWARD( args_fwd )... );
          }
        , ARGOT_SIMPLE_FORWARD( args )...
        );
  }

#if ARGOT_DETAIL_NO_DATAMEMBER_GUARANTEED_ELISION
  template< std::size_t I >
  struct fully_pure_make_in_place_with_result_tag {};

  template< std::size_t I >
  struct impure_make_in_place_with_result_tag {};

  template< std::size_t I >
  struct partially_pure_make_in_place_with_result_tag {};

  template< std::size_t I >
  using make_impure_in_place_with_result_tag
    = typename detail_if_::if_< alternative_is_pure_v< I > >
      ::then_apply_else_apply_values::template _
      < partially_pure_make_in_place_with_result_tag
      , impure_make_in_place_with_result_tag
      , I
      >;

  template< std::size_t I >
  using make_in_place_with_result_tag
    = typename detail_if_::if_< is_pure_v >
      ::then_apply_else_apply_values::template _
      < fully_pure_make_in_place_with_result_tag
      , make_impure_in_place_with_result_tag
      , I
      >;

  template< std::size_t I >
  struct fully_pure_make_in_place_tag {};

  template< std::size_t I >
  struct impure_make_in_place_tag {};

  template< std::size_t I >
  struct partially_pure_make_in_place_tag {};

  template< std::size_t I >
  using make_impure_in_place_tag
    = typename detail_if_::if_< alternative_is_pure_v< I > >
      ::then_apply_else_apply_values::template _
      < partially_pure_make_in_place_tag
      , impure_make_in_place_tag
      , I
      >;

  template< std::size_t I >
  using make_in_place_tag
    = typename detail_if_::if_< is_pure_v >
      ::then_apply_else_apply_values::template _
      < fully_pure_make_in_place_tag
      , make_impure_in_place_tag
      , I
      >;

  template< std::size_t I, class Fun, class... P >
  explicit constexpr union_
  ( fully_pure_make_in_place_with_result_tag< I >, Fun&& fun, P&&... args )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowEmplaceableWithResultWhenContained
      < alternative_type_t< I >, Fun&&, P&&... >
    )
  ) : alternatives
      ( in_place_index_with_result< tree_depth_v - 1 >
      , std::in_place_index< I / amount_per_group_v >
      , std::in_place_index< I % amount_per_group_v >
      , ARGOT_SIMPLE_FORWARD( fun ), ARGOT_SIMPLE_FORWARD( args )...
      ) {}

  template< std::size_t I, class Fun, class... P >
  explicit constexpr union_
  ( partially_pure_make_in_place_with_result_tag< I >, Fun&& fun, P&&... args )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowEmplaceableWithResultWhenContained
      < alternative_type_t< I >, Fun&&, P&&... >
    )
  ) : alternatives
      ( in_place_index_with_result< I >
      , ARGOT_SIMPLE_FORWARD( fun )
      , ARGOT_SIMPLE_FORWARD( args )...
      ) {}

  template< std::size_t I, class F, class... P >
  explicit constexpr union_
  ( impure_make_in_place_with_result_tag< I >, F&& fun, P&&... args )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowEmplaceableWithResultWhenContained
      < alternative_type_t< I >, F&&, P&&... >
    )
  ) : alternatives
      ( in_place_index_with_result< I >
      , []( F&& f_fwd, P&&... args_fwd ) -> decltype( auto ) // TODO(calabrese) noexcept
        {
          return emplace_contained_with_result< alternative_type_t< I > >
          ( ARGOT_SIMPLE_FORWARD( f_fwd )
          , ARGOT_SIMPLE_FORWARD( args_fwd )...
          );
        }
      , ARGOT_SIMPLE_FORWARD( fun )
      , ARGOT_SIMPLE_FORWARD( args )...
      ) {}

  template< std::size_t I, class... P >
  explicit constexpr union_( fully_pure_make_in_place_tag< I >, P&&... args )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowEmplaceableWhenContained< alternative_type_t< I >, P&&... > )
  ) : alternatives
      ( std::in_place_index< tree_depth_v - 1 >
      , std::in_place_index< I / amount_per_group_v >
      , std::in_place_index< I % amount_per_group_v >
      , ARGOT_SIMPLE_FORWARD( args )...
      ) {}

  template< std::size_t I, class... P >
  explicit constexpr union_( partially_pure_make_in_place_tag< I >, P&&... args )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowEmplaceableWhenContained< alternative_type_t< I >, P&&... > )
  ) : alternatives
      ( std::in_place_index< I >
      , ARGOT_SIMPLE_FORWARD( args )...
      ) {}

  template< std::size_t I, class... P >
  explicit constexpr union_( impure_make_in_place_tag< I >, P&&... args )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowEmplaceableWhenContained< alternative_type_t< I >, P&&... > )
  ) : alternatives
      ( in_place_index_with_result< I >
      , []( P&&... args_fwd ) -> decltype( auto ) // TODO(calabrese) noexcept
        {
          return make_contained< alternative_type_t< I > >
          ( ARGOT_SIMPLE_FORWARD( args_fwd )... );
        }
      , ARGOT_SIMPLE_FORWARD( args )...
      ) {}
#endif
  //->
  //=union { /*...*/ } state; // Exposition only
  //<-
  ARGOT_NO_UNIQUE_ADDRESS impl_type alternatives;
  //->
};

} // namespace argot

//]

namespace argot {

template< class... T >
struct make_concept_map< UnionLike< union_< T... > > >
{
 private:
  using un_t = union_< T... >;

  using depth_indices_t
    = std::make_index_sequence
      < detail_argot::tree_depth_from_amount( sizeof...( T ) ) >;
 public:
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
    static_assert( Index < sizeof...( T ) );

    using alt_t = alternative_type_t< Index >;

    auto& raw_un = const_cast< un_t& >( self );

    // Alternative type with const if the union is const
    using c_alt
      = typename detail_if_::if_
        < ARGOT_IS_CONST( std::remove_reference_t< Self > ) >
        ::then_else::template _< const alt_t, alt_t >;

    // Qualified alternative type with appropriate reference qualifier
    using qual_alt
      = typename detail_if_::if_< ARGOT_IS_RVALUE_REFERENCE( Self&& ) >
        ::then_else::template _< c_alt&&, c_alt& >;

    // TODO(mattcalabrese) Use intrinsics
    if constexpr
    ( ARGOT_IS_SAME( alt_t, contained< alt_t > ) )
      if constexpr( un_t::is_pure_v )
        return static_cast< qual_alt >
        ( detail_union::access_tree< Index >
          ( ARGOT_LAUNDER_DIRECT( raw_un.alternatives )
          , depth_indices_t()
          )
        );
      else
        return static_cast< qual_alt >
        ( detail_union::access_tree< Index >
          ( ARGOT_LAUNDER_DIRECT( raw_un.alternatives.alternatives )
          , depth_indices_t()
          )
        );
    else
      if constexpr( un_t::is_pure_v )
        return static_cast< qual_alt >
        ( argot::access_contained
          ( detail_union::access_tree< Index >
            ( ARGOT_LAUNDER_DIRECT( raw_un.alternatives )
            , depth_indices_t()
            )
          )
        );
      else
        return static_cast< qual_alt >
        ( argot::access_contained
          ( detail_union::access_tree< Index >
            ( ARGOT_LAUNDER_DIRECT( raw_un.alternatives.alternatives )
            , depth_indices_t()
            )
          )
        );
  }
};

} // namespace argot

#endif  // ARGOT_UNION_HPP_
