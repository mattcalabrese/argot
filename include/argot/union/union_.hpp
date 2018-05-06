/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_UNION_UNION_HPP_
#define ARGOT_UNION_UNION_HPP_

#include <argot/detail/conditional.hpp>
#include <argot/detail/variadic_at.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/union/detail/config.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace argot {
namespace detail_union {

// Precondition: num_elements != 0
constexpr std::size_t log( std::size_t num_elements ) noexcept
{
  std::size_t result = 0;

  for( std::size_t curr_value
         = num_elements / ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES
     ; curr_value != 0
     ; curr_value /= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES
     )
    ++result;

  return result;
}

template< std::size_t RemainingTiers >
struct push_back_alternative_chunk_impl;

template< std::size_t RemainingTiers >
struct alternatives_type_impl;

template<>
struct alternatives_type_impl< /*RemainingTiers =*/ 0 >
{
  template
  < std::size_t NumPreceedingAlternatives
  , BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, class T )
  , class... U
  >
  using apply
    = union_
      < BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, T ) >;
};

template< std::size_t RemainingTiers >
struct alternatives_type_impl
{
  using next = alternatives_type_impl< RemainingTiers - 1 >;

  template< BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, T )
          , class... U
          >
  using apply
    = union_
      < typename next::template
        < BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, T ) >
      , /*push back until the max is hit*/
      >
};

template< std::size_t Index >
struct union_impl_preprocessed;

template< std::size_t Index >
struct union_impl_variadic;

template< std::size_t Size, std::size_t Index >
using least_nested_union
  = typename argot_detail::conditional
    < ( Size <= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES ) >
    ::template apply< union_impl_preprocessed< Index >
                    , union_impl_variadic
                      < Size / ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES // TODO(mattcalabrese) Fix this calculation
                      , Index
                      >
                    >;

template
< BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, class T )
, class... U
>
using leading_group
  = union_
    < BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, T ) >;

template
< BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, class T )
, class... U
>
using trailing_after_group
  = union_
    < BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, T ) >;

template< class... LeadingAlts >
struct group_alternatives
{
  template< class... T >
  using f
  = typename argot_detail::conditional
    < ( sizeof...( T ) <= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES ) >
    ::template apply< leading_group< Index >
                    , union_impl_variadic
                      < Size / ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES // TODO(mattcalabrese) Fix this calculation
                      , Index
                      >
                    >;
};

template< class... T >
using grouped_alternatives
  = typename argot_detail::conditional
    < ( sizeof...( T ) <= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES ) >
    ::template apply< union_impl_preprocessed< Index >
                    , union_impl_variadic
                      < Size / ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES // TODO(mattcalabrese) Fix this calculation
                      , Index
                      >
                    >;

template< std::size_t Chunks, std::size_t Index >
struct union_impl_variadic
{
  template
  < BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, class T )
  , class... U
  >
  using alternative_type_t
    = typename argot_detail::conditional
      < ( Index <= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES ) >
      ::template apply
      < least_nested_union< ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, Index >
      , union_impl_variadic
        < Chunks - 1
        , ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES - Index // TODO(mattcalabrese) Fix this calculation (and also make sure we instantiate the exact same nested union)
        >
      >
      ::template alternative_type_t< U... >;

  template< class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    if constexpr( Index < ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES )
      return least_nested_union< Index >::get
      ( least_nested_union< 0 >::get
        ( ARGOT_FORWARD( Self )( self ).alternatives )
      );
    else
      return least_nested_union
      < Index - ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES + 1 >
      ::get( ARGOT_FORWARD( Self )( self ).alternatives );
  }
};

}  // namespace argot(::detail_union)

template< class... T >
union union_;

template<>
union union_<>
{
 private:
  ARGOT_NO_UNIQUE_ADDRESS impossible no_alternatives;
};

template< class... T >
struct make_concept_map< Union< union_< T... > > >
{
  using index_type = std::size_t;  // TODO(mattcalabrese) Calculate

  static index_type constexpr num_alternatives = sizeof...( T );

  template< index_type Index >
  using alternative_type_t
    = typename detail_union::union_impl< Index >
      ::template alternative_type_t< T... >;

  template< index_type Index, class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    return detail_union::union_impl< Index >
    ::get( ARGOT_FORWARD( Self )( self ) );
  }
};

#define BOOST_PP_ITERATION_PARAMS_1                                            \
( 3, ( 1, ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES                            \
     , <argot/union/detail/union_generation.hpp>                               \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

template
< BOOST_PP_ENUM_PARAMS( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, class T )
, class TN, class... U
>
union union_
{
 private:
  template< std::size_t I >
  static std::size_t constexpr primary_index_v
    =   I < ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES
      ? std::size_t( 0 )
      : std::size_t( I - ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES );

  template< std::size_t I >
  static std::size_t constexpr secondary_index_v
    =   I < ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES
      ? I
      : std::size_t( I - ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES );
 public:
  union_() = default;

  // TODO(mattcalabrese) handle refernce types and const.
  template< std::size_t I, class... P
          , ARGOT_REQUIRES  // TODO(mattcalabrese) <=?
            ( True< ( I < ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES ) > )
            ( Constructible
              < union_traits::alternative_type_t< I, union_ >
              , P&&...
              >
            )
            ()
          >
  explicit constexpr union_( std::in_place_index_t< I >, P&&... args )
  noexcept
  ( std::is_nothrow_constructible_v
    < union_traits::alternative_type_t< I, union_ >, P&&... >
  ) : alternatives( std::in_place_index< 0 >
                  , std::in_place_index< I >
                  , ARGOT_FORWARD( P )( args )
                  ) {}

  template< std::size_t I, class... P
          , ARGOT_REQUIRES  // TODO(mattcalabrese) <=?
            ( True< ( I >= ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES ) > )
            ( Constructible
              < union_traits::alternative_type_t< I, union_ >
              , P&&...
              >
            )
            ()
          >
  explicit constexpr union_( std::in_place_index_t< I >, P&&... args )
  noexcept
  ( std::is_nothrow_constructible_v
    < union_traits::alternative_type_t< I, union_ >, P&&... >
  ) : alternatives
      ( std::in_place_index< 1 >
      , std::in_place_index< I - ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES + 1 >
      , ARGOT_FORWARD( P )( args )
      ) {}

  // TODO(mattcalabrese) handle refernce types and const.
  template
  < std::size_t I, class U, class... P
  , ARGOT_REQUIRES
    ( True< ( I < ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES ) > )
    ( Constructible
      < union_traits::alternative_type_t< I, union_ >
      , std::initializer_list< U >& P&&...
      >
    )()
  >
  explicit constexpr union_
  ( std::in_place_index_t< I >
  , std::initializer_list< U > ilist, P&&... args
  )
  noexcept
  ( std::is_nothrow_constructible_v
    < union_traits::alternative_type_t< I, union_ >
    , std::initializer_list< U >&, P&&... >
    >
  ) : alternatives( std::in_place_index< 0 >
                  , std::in_place_index< I >
                  , ilist
                  , ARGOT_FORWARD( P )( args )
                  ) {}

  // TODO(mattcalabrese) Make emplace and destroy functions.

 private:
  // TODO(mattcalabrese)
  //   Change to make this a tree of unions where each subunion has at most
  //   ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES alternatives. Minimize depth.

  using alternatives_type
    = ARGOT_NO_UNIQUE_ADDRESS union_
      < union_
        < BOOST_PP_ENUM_PARAMS
          ( ARGOT_MAX_PREPROCESSED_UNION_ALTERNATIVES, class T )
        >
      , TN, U...
      >;

  ARGOT_NO_UNIQUE_ADDRESS alternatives_type alternatives;
};

}  // namespace argot

#endif  // ARGOT_UNION_UNION_HPP_
