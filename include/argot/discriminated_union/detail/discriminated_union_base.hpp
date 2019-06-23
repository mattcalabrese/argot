/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DISCRIMINATED_UNION_DETAIL_DISCRIMINATED_UNION_BASE_HPP_
#define ARGOT_DISCRIMINATED_UNION_DETAIL_DISCRIMINATED_UNION_BASE_HPP_

#include <argot/call/call.hpp>
#include <argot/concepts/basic_callable_with.hpp>
#include <argot/concepts/destructible.hpp>
#include <argot/concepts/union_index.hpp>
#include <argot/concepts/union_like.hpp>
#include <argot/concepts/variant_like.hpp>
#include <argot/contained.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/regular_bases.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/prov/index_of.hpp>
#include <argot/prov_traits/destructive_provide.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/union_.hpp>
#include <argot/union_traits/alternative_type.hpp>
#include <argot/union_traits/get.hpp>

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot::detail_discriminated_union {

template< bool End >
struct index_of_trivial_alternative_impl
{
  template< class I, class H, class... T >
  using apply
    = typename argot_detail::conditional< !std::is_trivial_v< H > >
      ::template half_meta_apply
      < index_of_trivial_alternative_impl< sizeof...( T ) == 0 >
        ::template next_apply
      , I
      , I, T...
      >;

  template< class I, class H, class... T >
  using next_apply
    = apply< std::integral_constant< std::size_t, I::value + 1 >, H, T... >;
};

template<>
struct index_of_trivial_alternative_impl< true >
{
  template< class I >
  using apply = I;

  template< class I >
  using next_apply = std::integral_constant< std::size_t, I::value + 1 >;
};

template< class... T >
inline constexpr std::size_t const& index_of_trivial_alternative_v
  = index_of_trivial_alternative_impl< sizeof...( T ) == 0 >
    ::template apply< std::integral_constant< std::size_t, 0 >, T... >::value;

template< class... T >
struct state_base
{
  using index_type = std::size_t;

  using union_ = argot::union_< T... >;

  template< index_type Index >
  using alternative_type_t = union_traits::alternative_type_t< union_, Index >;

  static constexpr index_type const& alternative_count_v
    = std::integral_constant< index_type, sizeof...( T ) >::value;

  static constexpr index_type const& partially_formed_index_value_v
    = index_of_trivial_alternative_v< T... >;

  static constexpr bool const& has_unique_partially_formed_index_v
    = partially_formed_index_value_v == sizeof...( T );

  constexpr state_base() noexcept
    : index_value( partially_formed_index_value_v ) {}

  template< std::size_t I, class Fun, class... P >
  explicit constexpr state_base
  ( in_place_index_with_result_t< I >, Fun&& fun, P&&... args )
  noexcept( argot_detail::is_nothrow_constexpr_invocable_v< Fun&&, P&&... > )
    : alternatives
      ( in_place_index_with_result< I >
      , ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )...
      )
    , index_value( I ) {}

  static constexpr auto to_const_index( index_type i )
  {
    return prov::value_in_range< index_type, 0, alternative_count_v >( i );
  }

  static constexpr auto to_const_index_and_partially_formed( index_type i )
  {
    return prov::value_in_range< index_type, 0, alternative_count_v + 1 >( i );
  }

  template< bool ResetIndexValue >
  constexpr void to_partially_formed()
  {
    if constexpr( has_unique_partially_formed_index_v )
    {
      if( index_value != partially_formed_index_value_v )
        argot::call
        ( [ this ]( auto index )
          {
            if constexpr( index.value != partially_formed_index_value_v )
              this->alternatives.template destroy< index.value >();
          }
        , to_const_index_and_partially_formed( index_value )
        );
    }
    else
      argot::call
      ( [ this ]( auto const index )
        {
          alternatives.template destroy< index.value >();
        }
      , to_const_index( index_value )
      );

    if constexpr( ResetIndexValue )
      index_value = partially_formed_index_value_v;
  }

  ARGOT_NO_UNIQUE_ADDRESS union_ alternatives;
  ARGOT_NO_UNIQUE_ADDRESS index_type index_value;
};

template< class... T >
struct nontrivial_destructor
  : protected state_base< T... >
{
  using base_t = state_base< T... >;
  using base_t::base_t;

  nontrivial_destructor() = default;

  ~nontrivial_destructor()
  noexcept
  ( ( std::is_nothrow_destructible_v< contained< T > > && ... ) )
  {
    this->template to_partially_formed< /*ResetIndexValue =*/ false >();
  }

  nontrivial_destructor( nontrivial_destructor&& ) = default;
  nontrivial_destructor( nontrivial_destructor const& ) = default;

  nontrivial_destructor& operator =( nontrivial_destructor&& ) = default;
  nontrivial_destructor& operator =( nontrivial_destructor const& ) = default;
};

template< class... T >
using destructor
  = typename argot_detail::conditional
    < std::is_trivially_destructible_v< union_< T... > > >
    ::template meta_apply< state_base, nontrivial_destructor, T... >;

template< class... T >
struct nontrivial_move_constructor
  : protected destructor< T... >
{
  using base_t = destructor< T... >;
  using base_t::base_t;

  nontrivial_move_constructor() = default;
  ~nontrivial_move_constructor() = default;

  constexpr nontrivial_move_constructor( nontrivial_move_constructor&& other )
  noexcept
  ( (    std::is_nothrow_move_constructible_v< contained< T > >
      && ...
    )
  )
  {
    // TODO(mattcalabrese) Use lower-level primitive than call.
    argot::call
    ( [ this, &other ]( auto other_index )
      {
        using alt_t
          = typename base_t::template alternative_type_t< other_index.value >;

        this->alternatives.template emplace< other_index.value >
        ( ARGOT_FORWARD( alt_t )
          ( union_traits::get< other_index.value >( other.alternatives ) )
        );
      }
    , other.to_const_index( other.index_value )
    );

    this->index_value = other.index_value;
  }

  nontrivial_move_constructor( nontrivial_move_constructor const& ) = default;

  nontrivial_move_constructor& operator =( nontrivial_move_constructor&& )
    = default;

  nontrivial_move_constructor& operator =( nontrivial_move_constructor const& )
    = default;
};

template< class... T >
using move_constructor
  = typename argot_detail::conditional
    <    std::is_move_constructible_v< union_< T... > >
      || !( std::is_move_constructible_v< T > && ... ) // TODO(mattcalabrese) Do lazily
    >::template meta_apply< destructor, nontrivial_move_constructor, T... >;

template< class... T >
struct nontrivial_copy_constructor
  : protected move_constructor< T... >
{
  using base_t = move_constructor< T... >;
  using base_t::base_t;

  nontrivial_copy_constructor() = default;
  ~nontrivial_copy_constructor() = default;

  nontrivial_copy_constructor( nontrivial_copy_constructor&& ) = default;

  constexpr nontrivial_copy_constructor
  ( nontrivial_copy_constructor const& other )
  noexcept
  ( (    std::is_nothrow_copy_constructible_v< contained< T > >
      && ...
    )
  )
  {
    // TODO(mattcalabrese) Use lower-level primitive than call.
    argot::call
    ( [ this, &other ]( auto other_index )
      {
        this->alternatives.template emplace< other_index.value >
        ( union_traits::get< other_index.value >( other.alternatives ) );
      }
    , other.to_const_index( other.index_value )
    );

    this->index_value = other.index_value;
  }

  nontrivial_copy_constructor& operator =( nontrivial_copy_constructor&& )
    = default;

  nontrivial_copy_constructor& operator =( nontrivial_copy_constructor const& )
    = default;
};

template< class... T >
using copy_constructor
  = typename argot_detail::conditional
    <   std::is_copy_constructible_v< union_< T... > >
      || !( std::is_copy_constructible_v< contained< T > > && ... ) // TODO(mattcalabrese) Do lazily
    >::template meta_apply
    < move_constructor, nontrivial_copy_constructor, T... >;

template< class... T >
struct nontrivial_move_assign
  : protected copy_constructor< T... >
{
  using base_t = copy_constructor< T... >;
  using base_t::base_t;

  nontrivial_move_assign() = default;
  ~nontrivial_move_assign() = default;

  nontrivial_move_assign( nontrivial_move_assign&& ) = default;
  nontrivial_move_assign( nontrivial_move_assign const& ) = default;

  constexpr nontrivial_move_assign& operator =( nontrivial_move_assign&& other )
  noexcept
  ( (    (    std::is_nothrow_move_constructible_v
              < contained< T > >
           && std::is_nothrow_destructible_v< contained< T > >
         )
      && ...
    )
  )
  {
    // TODO(mattcalabrese) Use lower-level primitive than call.
    // Then the indices are the same, the implementation is possibly simpler.
    if( this->index_value == other.index_value )
      argot::call
      ( [ this, &other ]( auto const index )
        {
          using alt_t
            = union_traits::alternative_type_t< union_< T... >, index.value >;

          using contained_alt_t = contained< alt_t >;

          // If the type is move-assignable and of a compatible noexcept-ness,
          // then use the move-assign operator as an optimization.
          if constexpr
          (    std::is_move_assignable_v< contained_alt_t >
            && (     !std::is_nothrow_move_constructible_v< contained_alt_t >
                  || std::is_nothrow_move_assignable_v< contained_alt_t >
               )
          )
            union_traits::get< index.value >( this->alternatives )
              = union_traits::get< index.value >
                ( ARGOT_MOVE( other.alternatives ) );
          else // Otherwise, implementation is similar to when indices differ.
          {
            // Self-move must at least yield a valid-but-unspecified state.
            // TODO(mattcalabrese) Investigate solution that won't branch.
            if( this != std::addressof( other ) )
            {
              // Start by destroying the current state.
              this->alternatives.template destroy< index.value >();

              // If move-construction can throw, update to partially-formed.
              static constexpr bool move_may_throw
                = !std::is_nothrow_move_constructible_v< contained_alt_t >;

              if constexpr( move_may_throw )
                this->index_value = this->partially_formed_index_value_v;

              // Actually perform the move-construction.
              this->alternatives.template emplace< index.value >
              ( union_traits::get< index.value >
                ( ARGOT_MOVE( other.alternatives ) )
              );

              // The index only needs to be restored if set to partially-formed.
              if constexpr( move_may_throw )
                this->index_value = index.value;
            }
          }
        }
      , this->to_const_index( this->index_value )
      );
    else
    {
      // TODO(mattcalabrese) Use lower-level primitive than call.
      argot::call
      ( [ this, &other ]( auto const other_index )
        {
          using alt_t
            = union_traits::alternative_type_t
              < union_< T... >, other_index.value >;

          this->template to_partially_formed
          < !std::is_nothrow_move_constructible_v
            < contained< alt_t > >
          >();

          this->alternatives.template emplace< other_index.value >
          ( union_traits::get< other_index.value >
            ( ARGOT_MOVE( other.alternatives ) )
          );
        }
      , other.to_const_index( other.index_value )
      );

      this->index_value = other.index_value;
    }

    return *this;
  }

  nontrivial_move_assign& operator =( nontrivial_move_assign const& ) = default;
};

// TODO(mattcalabrese) Make the checks more lazy.
template< class... T >
using move_assign
  = typename argot_detail::conditional
    <    (     std::is_move_constructible_v< union_< T... > >
            && std::is_move_assignable_v< union_< T... > >
            && std::is_trivially_destructible_v< union_< T... > >
         )
      || !(    (    std::is_move_constructible_v< contained< T > >
                 && std::is_destructible_v< contained< T > >
               )
            && ...
          )
    >::template meta_apply< copy_constructor, nontrivial_move_assign, T... >;

template< class... T >
struct nontrivial_copy_assign
  : protected move_assign< T... >
{
  using base_t = move_assign< T... >;
  using base_t::base_t;

  nontrivial_copy_assign() = default;
  ~nontrivial_copy_assign() = default;

  nontrivial_copy_assign( nontrivial_copy_assign&& ) = default;
  nontrivial_copy_assign( nontrivial_copy_assign const& ) = default;

  nontrivial_copy_assign& operator =( nontrivial_copy_assign&& other )
    = default;

  constexpr
  nontrivial_copy_assign& operator =( nontrivial_copy_assign const& other )
  noexcept
  ( (    (    std::is_nothrow_copy_constructible_v
              < contained< T > >
           && std::is_nothrow_destructible_v< contained< T > >
         )
      && ...
    )
  )
  {
    // TODO(mattcalabrese) Use lower-level primitive than call.
    if( this->index_value == other.index_value )
      argot::call
      ( [ this, &other ]( auto const index )
        {
          using alt_t
            = union_traits::alternative_type_t< union_< T... >, index.value >;

          using contained_alt_t = contained< alt_t >;

          // If the type is copy-assignable and of a compatible noexcept-ness,
          // then use the copy-assign operator as an optimization.
          if constexpr
          (    std::is_copy_assignable_v< contained_alt_t >
            && (     !std::is_nothrow_copy_constructible_v< contained_alt_t >
                  || std::is_nothrow_copy_assignable_v< contained_alt_t >
               )
          )
          {
            // The assign member-function works with reference alternatives.
            union_traits::get< index.value >( this->alternatives )
              = union_traits::get< index.value >( other.alternatives );
          }
          else // Otherwise, implementation is similar to when indices differ.
          {
            // Self-assign must work and do nothing.
            if( this != std::addressof( other ) )
            {
              // Start by destroying the current state.
              this->alternatives.template destroy< index.value >();

              // If copy-construction can throw, update to partially-formed.
              static constexpr bool copy_may_throw
                = !std::is_nothrow_copy_constructible_v< contained_alt_t >;

              if constexpr( copy_may_throw )
                this->index_value = this->partially_formed_index_value_v;

              // Actually perform the copy-construction.
              this->alternatives.template emplace< index.value >
              ( union_traits::get< index.value >( other.alternatives ) );

              // The index only needs to be restored if set to partially-formed.
              if constexpr( copy_may_throw )
                this->index_value = index.value;
            }
          }
        }
      , this->to_const_index( this->index_value )
      );
    else
    {
      // TODO(mattcalabrese) Use lower-level primitive than call.
      argot::call
      ( [ this, &other ]( auto const other_index )
        {
          using alt_t
            = union_traits::alternative_type_t
              < union_< T... >, other_index.value >;

          this->template to_partially_formed
          < !std::is_nothrow_copy_constructible_v
            < contained< alt_t > >
          >();

          this->alternatives.template emplace< other_index.value >
          ( union_traits::get< other_index.value >( other.alternatives ) );
        }
      , other.to_const_index( other.index_value )
      );

      this->index_value = other.index_value;
    }

    return *this;
  }
};

// TODO(mattcalabrese) Make the checks more lazy.
template< class... T >
using discriminated_union_base
  = typename argot_detail::conditional
    <    (     std::is_copy_constructible_v< union_< T... > >
            && std::is_copy_assignable_v< union_< T... > >
            && std::is_trivially_destructible_v< union_< T... > >
         )
      || !(    (    std::is_copy_constructible_v< contained< T > >
                 && std::is_destructible_v< contained< T > >
               )
            && ...
          )
    >::template meta_apply< move_assign, nontrivial_copy_assign, T... >;

} // namespace (argot::detail_discriminated_union)

#endif  // ARGOT_DISCRIMINATED_UNION_DETAIL_DISCRIMINATED_UNION_BASE_HPP_
