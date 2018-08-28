/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DISCRIMINATED_UNION_HPP_
#define ARGOT_DISCRIMINATED_UNION_HPP_

#include <argot/call/call.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/comparable.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/equality_comparable.hpp>
#include <argot/concepts/equatable.hpp>
#include <argot/concepts/greater_equal_comparable.hpp>
#include <argot/concepts/greater_than_comparable.hpp>
#include <argot/concepts/inequality_comparable.hpp>
#include <argot/concepts/less_equal_comparable.hpp>
#include <argot/concepts/less_than_comparable.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/nothrow_destructible.hpp>
#include <argot/concepts/nothrow_equality_comparable.hpp>
#include <argot/concepts/nothrow_greater_equal_comparable.hpp>
#include <argot/concepts/nothrow_greater_than_comparable.hpp>
#include <argot/concepts/nothrow_hashable.hpp>
#include <argot/concepts/nothrow_inequality_comparable.hpp>
#include <argot/concepts/nothrow_less_equal_comparable.hpp>
#include <argot/concepts/nothrow_less_than_comparable.hpp>
#include <argot/concepts/nothrow_move_constructible.hpp>
#include <argot/concepts/nothrow_swappable.hpp>
#include <argot/concepts/swappable.hpp>
#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/declval.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_swap.hpp>
#include <argot/detail/holder.hpp>
#include <argot/detail/regular_bases.hpp>
#include <argot/discriminated_union/detail/discriminated_union_base.hpp>
#include <argot/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/index_of.hpp>
#include <argot/prov/union_index.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/state_traits/equal_to.hpp>
#include <argot/state_traits/greater_equal.hpp>
#include <argot/state_traits/greater_than.hpp>
#include <argot/state_traits/hash_combine.hpp>
#include <argot/state_traits/less_equal.hpp>
#include <argot/state_traits/less_than.hpp>
#include <argot/state_traits/not_equal_to.hpp>
#include <argot/union_traits/alternative_type.hpp>
#include <argot/union_traits/index_type.hpp>
#include <argot/union_traits/get.hpp>
#include <argot/variant_traits/index_of.hpp>
#include <argot/void_.hpp>

#include <boost/container_hash/hash.hpp>

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot {

template< class... T >
class discriminated_union;

namespace detail_discriminated_union {

struct discriminated_union_core_access;

} // namespace argot(::detail_discriminated_union)


namespace detail_discriminated_union_adl {

template< class Child >
struct adl_base {};

}  // namespace argot(::detail_discriminated_union_adl)

// TODO(mattcalabrese) Possibly optimize the nullary and unary cases.

// TODO(mattcalabrese) Make explicit "destroy" functions (with an without index)
// TODO(mattcalabrese) Make emplace function that's aware of the current index
template< class... T >
class discriminated_union
  : argot_detail::conditional
    < std::is_same_v
      < argot::discriminated_union< call_detail::holder< T >... >
      , argot::discriminated_union< T... >
      >
    >::template meta_apply
    < detail_discriminated_union::discriminated_union_base
    , discriminated_union
    , call_detail::holder< T >...
    >
  , detail_discriminated_union_adl::adl_base< discriminated_union< T... > >
{
  template< class... >
  friend class discriminated_union;

  friend struct detail_discriminated_union::discriminated_union_core_access;
  friend struct std::hash< discriminated_union >;

  friend struct make_concept_map< UnionLike< discriminated_union > >;
  friend struct make_concept_map< VariantLike< discriminated_union > >;
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
      < argot::discriminated_union< call_detail::holder< T >... >
      , discriminated_union
      >;

  using base_t
    = typename argot_detail::conditional< is_pure_v >::template meta_apply
      < detail_discriminated_union::discriminated_union_base
      , discriminated_union
      , call_detail::holder< T >...
      >;

  using typename base_t::index_type;
 public:
  using pure_type
    = typename argot::discriminated_union< call_detail::holder< T >... >;

  discriminated_union() = default;

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  template
  < std::size_t I, class Fun, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_with_result_fn< alternative_type_t< I > >
          const&
      , Fun&&, P&&...
      >
    )
    ()
  >
  explicit constexpr discriminated_union
  ( in_place_index_with_result_t< I > const /*in_place_index_with_result*/
  , Fun&& fun, P&&... args
  ) noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
    : base_t
      ( in_place_index_with_result< I >
      , call_detail::emplace_holder_with_result< alternative_type_t< I > >
      , ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )...
      ) {}

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) Make sure noexcept works with holder
  template
  < index_type I, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , P&&...
      >
    )
    ()
  >
  explicit constexpr discriminated_union
  ( std::in_place_index_t< I > const /*in_place_index*/, P&&... args )
  noexcept( std::is_nothrow_constructible_v< alternative_type_t< I >, P&&... > )
    : base_t
      ( in_place_index_with_result< I >
      , call_detail::emplace_holder< alternative_type_t< I > >
      , ARGOT_FORWARD( P )( args )...
      ) {}

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) Make sure noexcept works with holder
  template
  < index_type I, class U, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , std::initializer_list< U >&, P&&...
      >
    )
    ()
  >
  explicit constexpr discriminated_union
  ( std::in_place_index_t< I > const /*in_place_index*/
  , std::initializer_list< U > ilist, P&&... args
  )
  noexcept
  ( std::is_nothrow_constructible_v
    < alternative_type_t< I >, std::initializer_list< U >&, P&&... >
  ) : base_t
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
    ( UnionIndex< discriminated_union, I > )
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
    auto& pure_alternative
      = *::new
         ( static_cast< void* >( std::addressof( alternatives ) ) )
         call_detail::holder< alternative_type_t< I > >
         ( call_detail::emplace_holder_with_result_fn< alternative_type_t< I > >
           ( ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )... )
         );

    index_value = I;

    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( pure_alternative );
  }

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < index_type I, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , P&&...
      >
    )
    ()
  >
  constexpr auto& emplace( P&&... args )
  {
    this->template to_partially_formed
    < !std::is_nothrow_constructible_v< alternative_type_t< I >, P&&...> >();

    auto& pure_alternative
      = *::new
         ( static_cast< void* >( std::addressof( alternatives ) ) )
         call_detail::holder< alternative_type_t< I > >
         ( call_detail::emplace_holder< alternative_type_t< I > >
           ( ARGOT_FORWARD( P )( args )... )
         );

    index_value = I;

    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( pure_alternative );
  }

  // TODO(mattcalabrese)
  //   Branch to Constructible for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < index_type I, class U, class... P
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , std::initializer_list< U >&, P&&...
      >
    )
    ()
  >
  constexpr auto& emplace( std::initializer_list< U > ilist, P&&... args )
  {
    this->template to_partially_formed
    < !std::is_nothrow_constructible_v
      < alternative_type_t< I >, std::initializer_list< U >&, P&&...>
    >();

    auto& pure_alternative
      = *::new
         ( static_cast< void* >( std::addressof( alternatives ) ) )
         call_detail::holder< alternative_type_t< I > >
         ( call_detail::emplace_holder< alternative_type_t< I > >
           ( ilist, ARGOT_FORWARD( P )( args )... )
         );

    index_value = I;

    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( pure_alternative );
  }

  // TODO(mattcalabrese)
  //   Branch to Assignable for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < index_type I, class P
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )/*
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , P&&
      >
    )*/
    ()
  >
  constexpr auto& assign( P&& arg )
  {
    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( alternatives.template assign< I >( ARGOT_FORWARD( P )( arg ) ) );
  }

  // TODO(mattcalabrese)
  //   Branch to Assignable for better errors when non-const/non-ref/non-void
  // TODO(mattcalabrese) noexcept
  template
  < index_type I, class U
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )/*
    ( BasicCallableWith
      < call_detail::emplace_holder_fn< alternative_type_t< I > > const&
      , std::initializer_list< U >&, P&&...
      >
    )*/
    ()
  >
  constexpr auto& assign( std::initializer_list< U > ilist )
  {
    return call_detail::access_holder_if< !alternative_is_pure_v< I > >
    ( alternatives.template assign< I >( ilist ) );
  }

  // TODO(mattcalabrese) Branch on const so there is a better error.
  // TODO(mattcalabrese) Make sure this is constexpr if trivially destructible.
  template
  < std::size_t I
  , ARGOT_REQUIRES
    ( UnionIndex< discriminated_union, I > )
    ( Destructible< call_detail::holder< alternative_type_t< I > > > )
    ()
  >
  constexpr void destroy()
  noexcept
  ( std::is_nothrow_destructible_v
    < call_detail::holder< alternative_type_t< I > > >
  )
  {
    alternatives.template destroy< I >();

    if constexpr( I != partially_formed_index_value_v )
      index_value = partially_formed_index_value_v;
  }

  // TODO(mattcalabrese) Make a way to set to partially formed, from any state?

  constexpr pure_type& pure() & noexcept
  {
    return *this;
  }

  constexpr pure_type const& pure() const& noexcept
  {
    return *this;
  }

  constexpr pure_type&& pure() && noexcept
  {
    return ARGOT_MOVE( *this );
  }

  constexpr pure_type const&& pure() const && noexcept
  {
    return ARGOT_MOVE( *this );
  }
 private:
  using base_t::partially_formed_index_value_v;
  using base_t::alternatives;
  using base_t::index_value;

  friend detail_regular_bases::regular_core_access;
};

namespace detail_discriminated_union {

struct discriminated_union_core_access
{
  template< class... T >
  static constexpr void swap_impl( discriminated_union< T... >& lhs
                                 , discriminated_union< T... >& rhs
                                 )
  noexcept
  ( (    (    ARGOT_IS_MODELED( NothrowSwappable< call_detail::holder< T > > )
           && ARGOT_IS_MODELED
              ( NothrowMoveConstructible< call_detail::holder< T > > )
           && ARGOT_IS_MODELED
              ( NothrowDestructible< call_detail::holder< T > > )
         )
      && ...
    )
  )
  {
    // If the underlying union is swappable then we can avoid all branching.
    if constexpr
    ( ARGOT_IS_MODELED( Swappable< union_< call_detail::holder< T >... > > ) )
      detail_argot_swap::constexpr_swap( lhs.alternatives, rhs.alternatives );
    else
      argot::call
      ( [ &lhs, &rhs ]( auto const index )
        {
          // If the same index is active in each operand...
          if( lhs.index == rhs.index_value )
          {
            detail_argot_swap::constexpr_swap
            ( union_traits::get< index.value >( lhs.alternatives )
            , union_traits::get< index.value >( rhs.alternatives )
            );
          }
          else // Otherwise, a different index is active for each operand...
          {
            using pure_type = typename discriminated_union< T... >::pure_type;
            constexpr auto partially_formed_index_value_v
              = discriminated_union< T... >::partially_formed_index_value_v;

            // Temporary backup of the current state.
            auto old_left
              = ARGOT_MOVE
                ( union_traits::get< index.value >( lhs.alternatives ) );

            // If destroy fails, it's okay since the indices haven't changed.
            lhs.alternatives.template destroy< index >();

            // Perform the part of the swap dependent on the rhs index value.
            argot::call
            ( [ &lhs, &rhs, index ]( auto const rhs_index )
              {
                // Flag the index as partially formed only if move can fail.
                // Note: This operand's state was already destroyed.
                if constexpr
                ( !std::is_nothrow_move_constructible_v
                   < typename pure_type::template alternative_type_t
                     < rhs_index.value >
                   >
                )
                  lhs.index_value = partially_formed_index_value_v;

                // Update the lhs to hold the old rhs state.
                // If failure here, lhs is safely in a partially-formed state.
                lhs.alternatives.template emplace< rhs_index.value >
                ( ARGOT_MOVE
                  ( union_traits::get< index.value >( rhs.alternatives ) )
                );

                // Since updating the lhs succeeded, update the index.
                lhs.index_value = rhs_index.value;

                // If failure here, that's okay because both indices are proper.
                rhs.alternatives.template destroy< rhs_index.value >();
              }
            , prov::index_of( rhs )
            );

            // Flag the index value as partially-formed only if move can fail.
            // Note: This operand's state was already destroyed.
            if constexpr
            ( !std::is_nothrow_move_constructible_v
               < typename pure_type::template alternative_type_t< index > >
            )
              rhs.index_value = partially_formed_index_value_v;

            // Update the rhs to hold the old lhs state.
            rhs.alternatives.template emplace< index >
            ( ARGOT_MOVE( old_left ) );

            // Now that the rhs was successfully updated, update its index.
            // If this fails, rhs is properly in a partially-formed state.
            rhs.index_value = index;
          }
        }
      , prov::index_of( lhs )
      );
  }
};

template< class... T >
struct hash_base
{
  constexpr
  std::size_t operator()( discriminated_union< T... > const& self ) const
  noexcept
  (    ARGOT_IS_MODELED
       ( NothrowHashable
         < union_traits::index_type_t< discriminated_union< T... > > >
       )
    && (    ARGOT_IS_MODELED( NothrowHashable< call_detail::holder< T > > )
         && ...
       )
  )
  {
    return argot::call
    ( [ &self
      , result
          = std::hash
            < union_traits::index_type_t< discriminated_union< T... > > >()
            ( variant_traits::index_of( self ) )
      ]( auto const index ) mutable
      {
        state_traits::hash_combine
        < union_traits::alternative_type_t
          < discriminated_union< T... >, index.value >
        >
        ( result
        , union_traits::get< index.value >( self )
        );

        return result;
      }
    , prov::index_of( self )
    );
  }
};

} // namespace argot(::detail_discriminated_union)

template< class... T >
struct make_concept_map< UnionLike< discriminated_union< T... > > >
{
  using index_type = typename discriminated_union< T... >::index_type;

  static index_type constexpr num_alternatives = sizeof...( T );

  template< index_type Index >
  using alternative_type_t
    = typename detail_union::union_impl< sizeof...( T ), Index >
      ::template alternative_type_t< T... >;

  template< index_type Index, class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    return call_detail::access_holder_if
    < !discriminated_union< T... >::template alternative_is_pure_v< Index > >
    ( union_traits::get< Index >
      ( ARGOT_FORWARD( Self )( self ).alternatives )
    );
  }
};

template< class... T >
struct make_concept_map< VariantLike< discriminated_union< T... > > >
{
  using index_type = typename discriminated_union< T... >::index_type;

  [[nodiscard]] static constexpr index_type
  index_of( discriminated_union< T... > const& self ) noexcept
  {
    return static_cast< index_type >( self.index_value );
  }
};


namespace detail_discriminated_union_adl {

template< class... T
        , ARGOT_REQUIRES
          ( Swappable< call_detail::holder< T > >... )
          ( MoveConstructible< call_detail::holder< T > >... )
          ( Destructible< call_detail::holder< T > >... )
          ()
        >
constexpr void swap( discriminated_union< T... >& lhs
                   , discriminated_union< T... >& rhs
                   )
noexcept
( (    (    ARGOT_IS_MODELED( NothrowSwappable< call_detail::holder< T > > )
         && ARGOT_IS_MODELED
            ( NothrowMoveConstructible< call_detail::holder< T > > )
         && ARGOT_IS_MODELED( NothrowDestructible< call_detail::holder< T > > )
       )
    && ...
  )
)
{
  detail_discriminated_union::discriminated_union_core_access::swap_impl
  ( lhs, rhs );
}

template< class... T
        , ARGOT_REQUIRES( Equatable< T >... )()
        >
constexpr bool operator ==( discriminated_union< T... > const& lhs
                          , discriminated_union< T... > const& rhs
                          )
noexcept
( (    noexcept
       ( state_traits::equal_to< T >
         ( ARGOT_DECLVAL( T const& )
         , ARGOT_DECLVAL( T const& )
         )
       )
    && ...
  )
)
{
  auto const lhs_index = variant_traits::index_of( lhs );
  auto const rhs_index = variant_traits::index_of( rhs );

  return    lhs_index == rhs_index
         && argot::call
            ( [ &lhs, &rhs ]( auto const index ) -> bool
              {
                return state_traits::equal_to
                < union_traits::alternative_type_t
                  < discriminated_union< T... >, index.value >
                >
                ( union_traits::get< index.value >( lhs )
                , union_traits::get< index.value >( rhs )
                );
              }
            , prov::union_index< discriminated_union< T... > >( lhs_index )
            );
}

template< class... T
        , ARGOT_REQUIRES( Equatable< T >... )()
        >
constexpr bool operator !=( discriminated_union< T... > const& lhs
                          , discriminated_union< T... > const& rhs
                          )
noexcept
( (    noexcept
       ( state_traits::not_equal_to< T >
         ( ARGOT_DECLVAL( T const& )
         , ARGOT_DECLVAL( T const& )
         )
       )
    && ...
  )
)
{
  auto const lhs_index = variant_traits::index_of( lhs );
  auto const rhs_index = variant_traits::index_of( rhs );

  return    lhs_index != rhs_index
         || argot::call
            ( [ &lhs, &rhs ]( auto const index ) -> bool
              {
                return state_traits::not_equal_to
                < union_traits::alternative_type_t
                  < discriminated_union< T... >, index.value >
                >
                ( union_traits::get< index.value >( lhs )
                , union_traits::get< index.value >( rhs )
                );
              }
            , prov::union_index< discriminated_union< T... > >( lhs_index )
            );
}

template< class... T
        , ARGOT_REQUIRES( Comparable< T >... )()
        >
constexpr bool operator <( discriminated_union< T... > const& lhs
                         , discriminated_union< T... > const& rhs
                         )
noexcept
( (    noexcept
       ( state_traits::less_than< T >
         ( ARGOT_DECLVAL( T const& )
         , ARGOT_DECLVAL( T const& )
         )
       )
    && ...
  )
)
{
  auto const lhs_index = variant_traits::index_of( lhs );
  auto const rhs_index = variant_traits::index_of( rhs );

  return   lhs_index == rhs_index
         ? argot::call
           ( [ &lhs, &rhs ]( auto const index ) -> bool
             {
                return state_traits::less_than
                < union_traits::alternative_type_t
                  < discriminated_union< T... >, index.value >
                >
                ( union_traits::get< index.value >( lhs )
                , union_traits::get< index.value >( rhs )
                );
             }
           , prov::union_index< discriminated_union< T... > >( lhs_index )
           )
         : lhs_index < rhs_index;
}

template< class... T
        , ARGOT_REQUIRES( Comparable< T >... )()
        >
constexpr bool operator <=( discriminated_union< T... > const& lhs
                          , discriminated_union< T... > const& rhs
                          )
noexcept
( (    noexcept
       ( state_traits::less_equal< T >
         ( ARGOT_DECLVAL( T const& )
         , ARGOT_DECLVAL( T const& )
         )
       )
    && ...
  )
)
{
  auto const lhs_index = variant_traits::index_of( lhs );
  auto const rhs_index = variant_traits::index_of( rhs );

  return   lhs_index == rhs_index
         ? argot::call
           ( [ &lhs, &rhs ]( auto const index ) -> bool
             {
                return state_traits::less_equal
                < union_traits::alternative_type_t
                  < discriminated_union< T... >, index.value >
                >
                ( union_traits::get< index.value >( lhs )
                , union_traits::get< index.value >( rhs )
                );
             }
           , prov::union_index< discriminated_union< T... > >( lhs_index )
           )
         : lhs_index < rhs_index;
}

template< class... T
        , ARGOT_REQUIRES( Comparable< T >... )()
        >
constexpr bool operator >=( discriminated_union< T... > const& lhs
                          , discriminated_union< T... > const& rhs
                          )
noexcept
( (    noexcept
       ( state_traits::greater_equal< T >
         ( ARGOT_DECLVAL( T const& )
         , ARGOT_DECLVAL( T const& )
         )
       )
    && ...
  )
)
{
  auto const lhs_index = variant_traits::index_of( lhs );
  auto const rhs_index = variant_traits::index_of( rhs );

  return   lhs_index == rhs_index
         ? argot::call
           ( [ &lhs, &rhs ]( auto const index ) -> bool
             {
                return state_traits::greater_equal
                < union_traits::alternative_type_t
                  < discriminated_union< T... >, index.value >
                >
                ( union_traits::get< index.value >( lhs )
                , union_traits::get< index.value >( rhs )
                );
             }
           , prov::union_index< discriminated_union< T... > >( lhs_index )
           )
         : lhs_index > rhs_index;
}

template< class... T
        , ARGOT_REQUIRES( Comparable< T >... )()
        >
constexpr bool operator >( discriminated_union< T... > const& lhs
                         , discriminated_union< T... > const& rhs
                         )
noexcept
( (    noexcept
       ( state_traits::greater_than< T >
         ( ARGOT_DECLVAL( T const& )
         , ARGOT_DECLVAL( T const& )
         )
       )
    && ...
  )
)
{
  auto const lhs_index = variant_traits::index_of( lhs );
  auto const rhs_index = variant_traits::index_of( rhs );

  return   lhs_index == rhs_index
         ? argot::call
           ( [ &lhs, &rhs ]( auto const index ) -> bool
             {
                return state_traits::greater_than
                < union_traits::alternative_type_t
                  < discriminated_union< T... >, index.value >
                >
                ( union_traits::get< index.value >( lhs )
                , union_traits::get< index.value >( rhs )
                );
             }
           , prov::union_index< discriminated_union< T... > >( lhs_index )
           )
         : lhs_index > rhs_index;
}

} // namespace argot(::detail_discriminated_union_adl)

} // namespace argot

namespace std {

// TODO(mattcalabrese) Make the calculation more lazy
template< class... T >
struct hash< ::argot::discriminated_union< T... > >
  : ::argot::argot_detail::conditional
    < ( ARGOT_IS_MODELED( ::argot::Hashable< T > ) && ... )
    >::template half_meta_apply
    < ::argot::detail_discriminated_union::hash_base
    , ::argot::detail_regular_bases::tainted_hash
    , T...
    > {};

} // namespace std

#endif  // ARGOT_DISCRIMINATED_UNION_HPP_
