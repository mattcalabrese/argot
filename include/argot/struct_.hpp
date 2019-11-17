/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_STRUCT_HPP_
#define ARGOT_STRUCT_HPP_

#include <argot/concepts/assignable_when_contained.hpp>
#include <argot/concepts/comparable.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/emplaceable_when_contained.hpp>
#include <argot/concepts/emplaceable_with_result_when_contained.hpp>
#include <argot/concepts/equatable.hpp>
#include <argot/concepts/move_assignable.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/nothrow_assignable_when_contained.hpp>
#include <argot/concepts/nothrow_decay_sinkable.hpp>
#include <argot/concepts/nothrow_emplaceable_when_contained.hpp>
#include <argot/concepts/nothrow_emplaceable_with_result_when_contained.hpp>
#include <argot/concepts/nothrow_swappable.hpp>
#include <argot/concepts/swappable.hpp>
#include <argot/concepts/tuple_index.hpp>
#include <argot/concepts/tuple_like.hpp>
#include <argot/contained.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_swap.hpp>
#include <argot/detail/construct.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/regular_bases.hpp>
#include <argot/detail/variadic_at.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/in_place_with_result.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/drop_while.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/receiver/forgetful_invoke.hpp>
#include <argot/receiver/reduced_invoke.hpp>
#include <argot/reducer/to.hpp>
#include <argot/side_effect.hpp>
#include <argot/state_traits/equal_to.hpp>
#include <argot/state_traits/greater_equal.hpp>
#include <argot/state_traits/greater_than.hpp>
#include <argot/state_traits/hash_combine.hpp>
#include <argot/state_traits/less_equal.hpp>
#include <argot/state_traits/less_than.hpp>
#include <argot/state_traits/not_equal_to.hpp>
#include <argot/struct_/detail/config.hpp>
#include <argot/struct_/detail/generate_struct_backend.hpp>

#include <boost/container_hash/hash.hpp>

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot {

template< class... T >
class struct_;

namespace detail_struct {

struct struct_core_access
{
  template< class... T
          , ARGOT_REQUIRES( Equatable< contained< T > >... )()
          >
  static
  constexpr bool equal_to_fun( struct_< T... > const& lhs
                             , struct_< T... > const& rhs
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
    return lhs.pure().elements == rhs.pure().elements;
  }

  template< class... T
          , ARGOT_REQUIRES( Comparable< contained< T > >... )()
          >
  static
  constexpr bool less_than_fun( struct_< T... > const& lhs
                              , struct_< T... > const& rhs
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
    return lhs.pure().elements < rhs.pure().elements;
  }

  template< class... T
          , ARGOT_REQUIRES
            ( Swappable< T >... )
            ()
          >
  static
  constexpr void swap_fun( struct_< T... >& lhs, struct_< T... >& rhs )
  noexcept( ( ARGOT_IS_MODELED( NothrowSwappable< contained< T > > ) && ... ) )
  {
    return lhs.pure().elements.swap( rhs.pure().elements );
  };

  // TODO(mattcalabrese) Put this in state_traits.
  template< class... T >
  struct hash_combiner
  {
    template< class... U >
    constexpr std::size_t operator()( U const&... args )
    noexcept
    ( (    ARGOT_IS_MODELED( NothrowHashable< contained< T > > ) && ... ) )
    {
      std::size_t result = 0;

      ( state_traits::hash_combine< T >( result, args ), ... );

      return result;
    }
  };

  template< class... T >
  struct hash_base
  {
    constexpr std::size_t operator()( struct_< T... > const& self ) const
    noexcept
    ( (    ARGOT_IS_MODELED( NothrowHashable< contained< T > > ) && ... ) )
    {
      return self.pure().elements.unpack
      ( hash_combiner< contained< T >... >(), self.pure().elements );
    }
  };
};

template< class Child >
struct adl_base {};

template< class... T
        , ARGOT_REQUIRES
          ( Swappable< T >... )
          ()
        >
constexpr void swap( struct_< T... >& lhs, struct_< T... >& rhs )
noexcept( ( ARGOT_IS_MODELED( NothrowSwappable< contained< T > > ) && ... ) )
{
  return struct_core_access::swap_fun( lhs, rhs );
}

template< class... T
        , ARGOT_REQUIRES( Equatable< contained< T > >... )()
        >
constexpr bool operator ==( struct_< T... > const& lhs
                          , struct_< T... > const& rhs
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
  return struct_core_access::equal_to_fun( lhs, rhs );
}

template< class... T
        , ARGOT_REQUIRES( Equatable< contained< T > >... )()
        >
constexpr bool operator !=( struct_< T... > const& lhs
                          , struct_< T... > const& rhs
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
  return !struct_core_access::equal_to_fun( lhs, rhs );
}

template< class... T
        , ARGOT_REQUIRES( Comparable< contained< T > >... )()
        >
constexpr bool operator <( struct_< T... > const& lhs
                         , struct_< T... > const& rhs
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
  return struct_core_access::less_than_fun( lhs, rhs );
}

template< class... T
        , ARGOT_REQUIRES( Comparable< contained< T > >... )()
        >
constexpr bool operator <=( struct_< T... > const& lhs
                          , struct_< T... > const& rhs
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
  return !struct_core_access::less_than_fun( rhs, lhs );
}

template< class... T
        , ARGOT_REQUIRES( Comparable< contained< T > >... )()
        >
constexpr bool operator >=( struct_< T... > const& lhs
                          , struct_< T... > const& rhs
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
  return !struct_core_access::less_than_fun( lhs, rhs );
}

template< class... T
        , ARGOT_REQUIRES( Comparable< contained< T > >... )()
        >
constexpr bool operator >( struct_< T... > const& lhs
                         , struct_< T... > const& rhs
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
  return struct_core_access::less_than_fun( rhs, lhs );
}

template< class... T >
using pure_struct_of = struct_< contained< T >... >;

struct referential_identity
{
  template< class T >
  static constexpr T&& run( T&& arg ) noexcept
  {
    return ARGOT_FORWARD( T )( arg );
  }
};

template< class T >
struct make_contained_with_result
{
  template< class Fun >
  static constexpr auto run( Fun&& fun ) noexcept
  {
    return [ & ]
    {
      return emplace_contained_with_result< T >( ARGOT_FORWARD( Fun )( fun ) );
    };
  }
};

template< class... T, class... P >
constexpr auto make_elements( P&&... args )
{
  if constexpr( struct_< T... >::is_pure_v )
    return detail_struct::struct_base< T... >
    ( std::in_place
    , ARGOT_FORWARD( P )( args )...
    );
  else
    return struct_< contained< T >... >
    ( in_place_with_result
    , [ & ]() -> decltype( auto )
      {
        return argot::make_contained< T >
               ( ARGOT_FORWARD( P )( args ) );
      }...
    );
}

template< class... T, class... Funs >
constexpr auto make_elements_with_result( Funs&&... funs )
{
  if constexpr( struct_< T... >::is_pure_v )
    return detail_struct::struct_base< T... >
    ( in_place_with_result
    , ARGOT_FORWARD( Funs )( funs )...
    );
  else
    return struct_< contained< T >... >
    ( in_place_with_result
    , // TODO(mattcalabrese) Use is_same intrinsic
      typename argot_detail::conditional
      < !std::is_same_v< T, contained< T > > >
      ::template half_meta_apply
      < make_contained_with_result, referential_identity, T >::run
      ( ARGOT_FORWARD( Funs )( funs ) )...
    );
}

} // namespace argot(::detail_struct)

// Note:
//   The default definition is used only up to the preprocessed maximum.
template< class... T >
class struct_
  : detail_struct::adl_base< struct_< T... > >
{
  template< std::size_t >
  friend struct detail_struct::struct_impl_preprocessed;

  template< std::size_t >
  friend struct detail_struct::struct_impl_variadic;

  friend detail_struct::struct_core_access;

  template< class... >
  friend class struct_;

  // TODO(mattcalabrese) Remove this hack and access through core_access
  template< class, class >
  friend struct make_concept_map;
 private:
  template< std::size_t Index >
  using struct_impl = detail_struct::struct_impl< sizeof...( T ), Index >;

  template< std::size_t Index >
  using element_type_t
    = detail_argot::variadic_at
      < Index, detail_forward::direct_identity_t
      , T...
      >;

  template< std::size_t Index >
  static constexpr bool element_is_pure_v
    = std::is_same_v< contained< element_type_t< Index > >
                    , element_type_t< Index >
                    >;
 public:
  static constexpr bool is_pure_v
    = std::is_same_v
      < argot::struct_< contained< T >... >
      , struct_
      >;
 private:
  using impl_type
    = typename argot_detail::conditional< is_pure_v >::template meta_apply
      < detail_struct::struct_base
      , struct_
      , contained< T >...
      >;

  friend impl_type;
 public:
  using pure_type = typename argot::struct_< contained< T >... >;

  struct_() = default;

  template
  < class... P
  , ARGOT_REQUIRES
    ( EmplaceableWhenContained< T, P&& >... )
    ()
  >
  constexpr struct_( std::in_place_t, P&&... args )
  noexcept
  ( ( ARGOT_IS_MODELED( NothrowEmplaceableWhenContained< T, P&& > ) && ... ) )
    : elements
      ( detail_struct::make_elements< T... >( ARGOT_FORWARD( P )( args )... ) )
  {}

  template
  < class... Funs
  , ARGOT_REQUIRES
    ( InvocableWith< Funs&& >... )
    ( EmplaceableWithResultWhenContained< T, Funs&& >... )
    ()
  >
  constexpr struct_( in_place_with_result_t, Funs&&... funs )
  // TODO(mattcalabrese) noexcept
    : elements
      ( detail_struct::make_elements_with_result< T... >
        ( ARGOT_FORWARD( Funs )( funs )... )
      ) {}

  template
  < std::size_t I, class P
  , ARGOT_REQUIRES
    ( TupleIndex< struct_, I > )
    ( AssignableWhenContained< element_type_t< I >, P&& > )
    ()
  >
  constexpr auto& assign( P&& arg )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowAssignableWhenContained< element_type_t< I >, P&& > )
  )
  {
    return argot::assign_contained< element_type_t< I > >
    ( struct_impl< I >
      ::template get< contained< element_type_t< I > > >( pure().elements )
    , ARGOT_FORWARD( P )( arg )
    );
  }

  template
  < std::size_t I, class U
  , ARGOT_REQUIRES
    ( TupleIndex< struct_, I > )
    ( AssignableWhenContained
      < element_type_t< I >, std::initializer_list< U >& >
    )
    ()
  >
  constexpr auto& assign( std::initializer_list< U > ilist )
  noexcept
  ( ARGOT_IS_MODELED
    ( NothrowAssignableWhenContained
      < element_type_t< I >, std::initializer_list< U >& >
    )
  )
  {
    return argot::assign_contained< element_type_t< I > >
    ( struct_impl< I >::template get< contained< element_type_t< I > > >
      ( pure().elements )
    , ilist
    );
  }

  constexpr pure_type& pure() & noexcept
  {
    if constexpr( is_pure_v )
      return *this;
    else
      return elements;
  }

  constexpr pure_type const& pure() const& noexcept
  {
    if constexpr( is_pure_v )
      return *this;
    else
      return elements;
  }

  constexpr pure_type&& pure() && noexcept
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *this );
    else
      return ARGOT_MOVE( elements );
  }

  constexpr pure_type const&& pure() const && noexcept
  {
    if constexpr( is_pure_v )
      return ARGOT_MOVE( *this );
    else
      return ARGOT_MOVE( elements );
  }
 private:
  ARGOT_NO_UNIQUE_ADDRESS impl_type elements;
};

template< class... T >
struct make_concept_map< TupleLike< struct_< T... > > >
{
  using index_type = std::size_t;  // TODO(mattcalabrese) Calculate minimal type

  static index_type constexpr num_elements = sizeof...( T );

  template< index_type Index >
  using element_type_t
    = detail_argot::variadic_at
      < Index, detail_forward::direct_identity_t
      , T...
      >;

  template< index_type Index, class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    using elem_type = element_type_t< Index >;

    // TODO(mattcalabrese) Use intrinsic
    if constexpr( std::is_same_v< elem_type, contained< elem_type > > )
      return detail_struct::struct_impl< sizeof...( T ), Index >
      ::template get< elem_type >( ARGOT_FORWARD( Self )( self ).elements );
    else
      return argot::access_contained
      ( detail_struct::struct_impl< sizeof...( T ), Index >
        ::template get< contained< elem_type > >
        ( ARGOT_FORWARD( Self )( self ).pure().elements )
      );
  }
};

struct make_struct_fn
{
  template
  < class... T
  , ARGOT_REQUIRES
    ( DecaySinkable< T&& >... )
    ()
  >
  [[nodiscard]]
  constexpr struct_< std::decay_t< T >... > operator ()( T&&... args ) const
  noexcept( ( ARGOT_IS_MODELED( NothrowDecaySinkable< T&& > ) && ... ) )
  {
    return struct_< std::decay_t< T >... >
    ( std::in_place, ARGOT_FORWARD( T )( args )... );
  }
} inline constexpr make_struct{};

struct make_referential_struct_fn
{
  template< class... T >
  [[nodiscard]]
  constexpr struct_< T&&... > operator ()( T&&... args ) const noexcept
  {
    return struct_< T&&... >( std::in_place, ARGOT_FORWARD( T )( args )... );
  }
} inline constexpr make_referential_struct{};

} // namespace argot

namespace std {

// TODO(mattcalabrese) Make the calculation more lazy
template< class... T >
struct hash< ::argot::struct_< T... > >
  : ::argot::argot_detail::conditional
    < ( ARGOT_IS_MODELED( ::argot::Hashable< T > ) && ... )
    >::template half_meta_apply
    < ::argot::detail_struct::struct_core_access::hash_base
    , ::argot::detail_regular_bases::tainted_hash
    , T...
    > {};

} // namespace std

#endif // ARGOT_STRUCT_HPP_
