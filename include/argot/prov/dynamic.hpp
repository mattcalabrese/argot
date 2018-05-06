/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_TO_DYNAMIC_HPP_
#define ARGOT_PROV_TO_DYNAMIC_HPP_

#include <argot/declval.hpp>
#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/prov/access_variant.hpp>
#include <argot/prov/bind_call.hpp>
#include <argot/prov/constant_variant_index_of.hpp>
#include <argot/prov/reference_to.hpp>

#include <algorithm>
#include <array>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot {
namespace prov {
namespace dynamic_cast_detail {

template< class Target, class Source >
using dynamic_cast_type_t
  = decltype( dynamic_cast< Target* >( ARGOT_DECLVAL( Source* ) ) );

template< class Target, class Source >
using can_dynamic_cast
  = call_detail::is_detected< dynamic_cast_type_t, Target, Source >;

template< class Target, class Source >
bool constexpr can_dynamic_cast_v
  = call_detail::is_detected_v< dynamic_cast_type_t, Target, Source >;

template< class T, class Deleter, class... PossibleChildren >
struct dynamic_cast_shared_ptr_impl
{
  std::shared_ptr< T, Deleter > ptr;
};

template< class T, class... PossibleChildren >
struct dynamic_cast_ptr_impl
{
  T* ptr;
};

template< class T, class... PossibleChildren >
struct dynamic_cast_impl
{
  std::remove_reference_t< T >* obj;
};

template< class T >
alignas( T ) inline char raw_storage_for_flat_map[ sizeof( T ) ];

template< class IndexType >
struct index_pair
{
  std::type_index t_index;
  IndexType t_list_index;
};

template< class... PossibleChildren >
struct type_index_flat_map
{
  static std::size_t constexpr num_elements = sizeof...( PossibleChildren );
  using type_list_index_type
    = typename boost::uint_value_t< num_elements >::least;

  using type_list_index_array_type
    = std::array< type_list_index_type, num_elements >;

  using it = typename type_list_index_array_type::const_iterator;

  it operator[]( std::type_info const& info ) const
  {
    auto const type_index_it
      = std::lower_bound( type_index_array.begin()
                        , type_index_array.end()
                        , std::type_index( info )
                        );

    return   type_list_index_array.begin()
           + ( type_index_it - type_index_array.begin() );
  }

  bool type_was_found( it it_ ) const
  {
    return it_ != type_list_index_array.end();
  }

  std::array< std::type_index, num_elements > type_index_array;
  type_list_index_array_type type_list_index_array;
};

template< class... PossibleChildren >
struct type_index_array_tag;

template< class... PossibleChildren >
struct type_list_index_array_tag;

template< class... PossibleChildren
        , class IndexType
        , IndexType... Indices
        >
type_index_flat_map< PossibleChildren... > const&
type_index_map_init( std::integer_sequence< IndexType, Indices... > )
{
  std::array< std::type_index, num_elements > type_index_array
   = { { index_pair< IndexType >
         { std::type_index( typeid( PossibleChildren ) ), Indices }...
       }
     };

  std::sort( type_index_array.begin(), type_index_array.end() );

  type_index_flat_map< PossibleChildren... >& type_indices
    = *new( &dynamic_cast_detail::raw_storage_for_flat_map
            < type_index_flat_map< PossibleChildren... > >
          );

  std::transform
  ( type_index_array.begin(), type_index_array.end()
  , type_indices.type_index_array.begin()
  , []( index_pair< IndexType > const& source )
    {
      return source.t_index;
    }
  );

  std::transform
  ( type_index_array.begin(), type_index_array.end()
  , type_indices.type_list_index_array.begin()
  , []( index_pair< IndexType > const& source )
    {
      return source.t_list_index;
    }
  );

  return type_indices;
}

}  // namespace argot::prov::dynamic_cast_detail

template< class... PossibleChildren >
struct dynamic_fn
{
  static_assert
  ( (    (    is_unqualified_v< PossibleChildren >
           && std::is_polymorphic< PossibleChildren >::value
         )
      && ...
    )
  , "Type arguments to prov::dynamic_cast_ must all be "
    "unqualified, polymorphic types."
  );

 private:

  using type_index_array_t
    = std::array< index_pair, sizeof...( PossibleChildren ) >;

  static dynamic_detail::type_index_flat_map< PossibleChildren... > const&
  type_index_map()
  {
    using index_type
      = typename boost::uint_value_t< sizeof...( PossibleChildren ) >::least;

    static dynamic_detail::type_index_flat_map< PossibleChildren... > const& result
      = dynamic_detail::type_index_array_init< PossibleChildren... >
        ( std::make_integer_sequence< index_type, sizeof...( PossibleChildren ) >() );

    return result;
  }

  struct ptr_cast
  {
    template< class PolymorphicType
            , class Default = /*Possibly not cast for default*/
            >
    static constexpr std::enable_if_t  // TODO(mattcalabrese) Require default to be modeled
    < (    dynamic_cast_detail::can_dynamic_cast_v
           < PossibleChildren, remove_cvref_t< PolymorphicType > >
        && ...
      )
    , dynamic_cast_ptr_impl< PolymorphicType, PossibleChildren... >
    >
    run( PolymorphicType* obj ) const
    {
      return { obj };
    }
  };

  struct ref_cast
  {
    template< class PolymorphicType
            , class Default = /*Possibly not cast for default*/
            >
    static constexpr std::enable_if_t  // TODO(mattcalabrese) Require default to be modeled
    < (    dynamic_cast_detail::can_dynamic_cast_v
           < PossibleChildren, remove_cvref_t< PolymorphicType > >
        && ...
      )
    , dynamic_cast_ref_impl< PolymorphicType, PossibleChildren... >
    >
    static run( PolymorphicType&& obj ) const
    {
      return { std::addressof( obj ) };
    }
  };
 public:
  template< class PolymorphicType
          , class Default = /*Possibly not cast for default*/
          >
  operator ()( PolymorphicType&& obj ) const
  {
    return bind
    ( value_of( access_variant )
    , reference_to( std::forward< Variant >( variant_like ) )
    , constant_variant_index_of( variant_like )
    );
  }
};

// TODO(mattcalabrese) Result of calculators

}  // namespace argot::prov
}  // namespace argot

#endif  // ARGOT_PROV_TO_DYNAMIC_HPP_
