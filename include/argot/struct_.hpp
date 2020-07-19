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
#include <argot/detail/addressof.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_swap.hpp>
#include <argot/detail/construct.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/is_same.hpp>
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
#include <argot/referential_identity.hpp>
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
#include <argot/tuple_traits/apply.hpp>

#include <boost/container_hash/hash.hpp>

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <tuple>
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
      return tuple_traits::apply
      ( hash_combiner< contained< T >... >()
      , self.pure()
      );
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

struct perform_referential_identity
{
  template< class T >
  static constexpr T&& run( T&& arg ) noexcept
  {
    return ARGOT_SIMPLE_FORWARD( arg );
  }
};

// TODO(mattcalabrese) Avoid this type instantiation
template< class T >
struct perform_emplace_contained_with_result
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

// TODO(mattcalabrese) Avoid this type instantiation
template< class T >
struct perform_make_contained
{
  template< class P >
  static constexpr auto run( P&& arg )
  {
    return [ & ]
    {
      return make_contained< T >( ARGOT_SIMPLE_FORWARD( arg ) );
    };
  }
};

template< class Fun, bool... IsNaturallyContained >
struct unpack_possibly_contained_fn
{
  // TODO(mattcalabrese) Conditional noexcept
  template< class... P >
  constexpr decltype( auto ) operator ()( P&&... args ) &&
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( *fun )
    , typename detail_if_::if_< IsNaturallyContained >
      ::then_else
      ::template _< referential_identity_fn, access_contained_fn >()
      ( ARGOT_FORWARD( P )( args ) )...
    );
  }

  std::remove_reference_t< Fun >* fun;
};

} // namespace argot(::detail_struct)

// Note:
//   The default definition is used only up to the preprocessed maximum.
template< class... T >
class struct_
  : detail_struct::adl_base< struct_< T... > >
{
  // TODO(mattcalabrese) Don't do this here. Avoid substituting in nonpure.
  using struct_tree
    = detail_argot::form_tree< detail_struct::struct_impl, contained< T >... >;

  using raw_concept_map = access_raw_concept_map< TupleLike< struct_ > >;

  static constexpr std::size_t tree_depth_v
    = detail_argot::tree_depth_from_amount( sizeof...( T ) );

  static constexpr std::size_t amount_per_group_v
    = detail_argot::amount_per_group_at_depth( tree_depth_v );

  using depth_indices_t = std::make_index_sequence< tree_depth_v >;

  // TODO(mattcalabrese) Remove this hack and access through core_access
  template< class, class >
  friend struct make_concept_map;

  template< class... >
  friend class struct_;

  friend detail_struct::struct_core_access;
 private:
  template< std::size_t Index >
  using element_type_t
    = detail_argot::variadic_at
      < Index, detail_forward::direct_identity_t
      , T...
      >;

  template< std::size_t Index >
  static constexpr bool element_is_pure_v
    = ARGOT_IS_SAME( contained< element_type_t< Index > >
                   , element_type_t< Index >
                   );

  static constexpr bool is_pure_v
    = ARGOT_IS_SAME
      ( argot::struct_< contained< T >... >
      , struct_
      );

  using impl_type
    = typename argot_detail::conditional< is_pure_v >::template meta_apply
      < detail_struct::form_struct_tree
      , detail_struct::form_pure_struct
      , T...
      >;
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
      ( make_in_place( std::make_index_sequence< sizeof...( T ) >()
                     , ARGOT_SIMPLE_FORWARD( args )...
                     )
      ) {}

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
      ( make_in_place_with_result
        ( std::make_index_sequence< sizeof...( T ) >()
        , ARGOT_SIMPLE_FORWARD( funs )...
        )
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
    if constexpr( is_pure_v )
    {
      auto& element = get< I >();
      element = ARGOT_SIMPLE_FORWARD( arg );
      return element;
    }
    else
    {
      using elem_t = element_type_t< I >;

      if constexpr( ARGOT_IS_SAME( contained< elem_t >, elem_t ) )
      {
        auto& element = elements.template get< I >();
        element = ARGOT_SIMPLE_FORWARD( arg );
        return element;
      }
      else
        return argot::assign_contained< elem_t >
        ( elements.template get< I >()
        , ARGOT_SIMPLE_FORWARD( arg )
        );
    }
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
    if constexpr( is_pure_v )
    {
      auto& element = get< I >();
      element = ilist;
      return element;
    }
    else
    {
      using elem_t = element_type_t< I >;

      if constexpr( ARGOT_IS_SAME( contained< elem_t >, elem_t ) )
      {
        auto& element = elements.template get< I >();
        element = ilist;
        return element;
      }
      else
        return argot::assign_contained< elem_t >
        ( elements.template get< I >()
        , ilist
        );
    }
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

  template< std::size_t Index
          , std::enable_if_t< ( Index < sizeof...( T ) ) >* = nullptr
          >
  constexpr auto&& get() & noexcept
  {
    using elem_t = element_type_t< Index >;
    using qual_elem = elem_t&;

    if constexpr( is_pure_v )
      return static_cast< qual_elem >
      ( detail_struct::access_tree< Index >
        ( elements
        , depth_indices_t()
        )
      );
    else
      if constexpr( ARGOT_IS_SAME( elem_t, contained< elem_t > ) )
        return static_cast< qual_elem >
        ( detail_struct::access_tree< Index >
          ( elements.elements
          , depth_indices_t()
          )
        );
      else
        return static_cast< qual_elem >
        ( argot::access_contained
          ( detail_struct::access_tree< Index >
            ( elements.elements
            , depth_indices_t()
            )
          )
        );
  }

  template< std::size_t Index
          , std::enable_if_t< ( Index < sizeof...( T ) ) >* = nullptr
          >
  constexpr auto&& get() const& noexcept
  {
    using elem_t = element_type_t< Index >;
    using qual_elem = elem_t const&;

    if constexpr( is_pure_v )
      return static_cast< qual_elem >
      ( detail_struct::access_tree< Index >
        ( elements
        , depth_indices_t()
        )
      );
    else
      if constexpr( ARGOT_IS_SAME( elem_t, contained< elem_t > ) )
        return static_cast< qual_elem >
        ( detail_struct::access_tree< Index >
          ( elements.elements
          , depth_indices_t()
          )
        );
      else
        return static_cast< qual_elem >
        ( argot::access_contained
          ( detail_struct::access_tree< Index >
            ( elements.elements
            , depth_indices_t()
            )
          )
        );
  }

  template< std::size_t Index
          , std::enable_if_t< ( Index < sizeof...( T ) ) >* = nullptr
          >
  constexpr auto&& get() && noexcept
  {
    using elem_t = element_type_t< Index >;
    using qual_elem = elem_t&&;

    if constexpr( is_pure_v )
      return static_cast< qual_elem >
      ( detail_struct::access_tree< Index >
        ( elements
        , depth_indices_t()
        )
      );
    else
      if constexpr( ARGOT_IS_SAME( elem_t, contained< elem_t > ) )
        return static_cast< qual_elem >
        ( detail_struct::access_tree< Index >
          ( elements.elements
          , depth_indices_t()
          )
        );
      else
        return static_cast< qual_elem >
        ( argot::access_contained
          ( detail_struct::access_tree< Index >
            ( elements.elements
            , depth_indices_t()
            )
          )
        );
  }

  template< std::size_t Index
          , std::enable_if_t< ( Index < sizeof...( T ) ) >* = nullptr
          >
  constexpr auto&& get() const&& noexcept
  {
    using elem_t = element_type_t< Index >;
    using qual_elem = elem_t const&&;

    if constexpr( is_pure_v )
      return static_cast< qual_elem >
      ( detail_struct::access_tree< Index >
        ( elements
        , depth_indices_t()
        )
      );
    else
      if constexpr( ARGOT_IS_SAME( elem_t, contained< elem_t > ) )
        return static_cast< qual_elem >
        ( detail_struct::access_tree< Index >
          ( elements.elements
          , depth_indices_t()
          )
        );
      else
        return static_cast< qual_elem >
        ( argot::access_contained
          ( detail_struct::access_tree< Index >
            ( elements.elements
            , depth_indices_t()
            )
          )
        );
  }
 private:
  template< std::size_t I >
  using perform_emplace_contained_with_result_from_index
    = detail_struct::perform_emplace_contained_with_result
      < element_type_t< I > >;

  // TODO(calabrese) noexcept
  template< std::size_t... Indices, class... F >
  static constexpr auto
  make_in_place_with_result( std::index_sequence< Indices... >, F&&... f )
  {
    if constexpr( is_pure_v )
      return struct_tree
      ( in_place_index_with_result< tree_depth_v - 1 >
      , ARGOT_SIMPLE_FORWARD( f )...
      );
    else
      return pure_type
      ( in_place_with_result
      , detail_if_::if_< element_is_pure_v< Indices > >
        ::then_else_apply_values::template _
        < detail_struct::perform_referential_identity
        , perform_emplace_contained_with_result_from_index
        , Indices
        >::run( ARGOT_SIMPLE_FORWARD( f ) )...
      );
  }

  template< std::size_t I >
  using perform_make_contained_from_index
    = detail_struct::perform_make_contained< element_type_t< I > >;

  // TODO(calabrese) noexcept
  template< std::size_t... Indices, class... U >
  static constexpr auto
  make_in_place( std::index_sequence< Indices... >, U&&... args )
  {
    if constexpr( is_pure_v )
      return struct_tree
      ( std::in_place_index< tree_depth_v - 1 >
      , ARGOT_SIMPLE_FORWARD( args )...
      );
    else
      return pure_type
      ( in_place_with_result
      , detail_if_::if_< element_is_pure_v< Indices > >
        ::then_else_apply_values::template _
        < detail_struct::perform_referential_identity
        , perform_make_contained_from_index
        , Indices
        >::run( ARGOT_SIMPLE_FORWARD( args ) )...
      );
  }
 private:
  ARGOT_NO_UNIQUE_ADDRESS impl_type elements;
};

template< class... T >
struct make_concept_map< IntrinsicUnpackable< struct_< T... > > >
{
  template< template< class... > class Result >
  using expand_element_types_t = Result< T... >;

  // TODO(mattcalabrese) Conditional noexcept
  template< class Fun, class Self >
  static constexpr decltype( auto ) apply( Fun&& fun, Self&& self )
  {
    if constexpr( sizeof...( T ) <= ARGOT_DETAIL_PRIMARY_UNROLL_DEPTH() )
      if constexpr( std::remove_reference_t< Self >::is_pure_v )
        return self.elements.unpack_this_level
        ( ARGOT_SIMPLE_FORWARD( fun ), ARGOT_SIMPLE_FORWARD( self ).elements );
      else
        return self.elements.elements.unpack_this_level
        ( detail_struct::unpack_possibly_contained_fn
          < Fun&&, ARGOT_IS_SAME( T, contained< T > )... >
          { ARGOT_ADDRESSOF( fun ) }
        , ARGOT_SIMPLE_FORWARD( self ).elements.elements
        );
    else
      return detail_struct::variadic_unpack
      ( ARGOT_FORWARD( Fun)( fun )
      , ARGOT_FORWARD( Self )( self )
      , std::make_index_sequence< sizeof...( T ) >()
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

template< class... T >
struct tuple_size< ::argot::struct_< T... > >
  : std::integral_constant< std::size_t, sizeof...( T ) > {};

template< std::size_t Index, class... T >
struct tuple_element< Index, ::argot::struct_< T... > >
{
  using type
    = ::argot::detail_argot::variadic_at
      < Index, ::argot::detail_forward::direct_identity_t
      , T...
      >;
};

} // namespace std

#endif // ARGOT_STRUCT_HPP_
