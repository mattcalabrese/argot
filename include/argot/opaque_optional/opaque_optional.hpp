/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_OPAQUE_OPTIONAL_OPAQUE_OPTIONAL_HPP_
#define ARGOT_OPAQUE_OPTIONAL_OPAQUE_OPTIONAL_HPP_

#include <argot/concepts/decayed_type.hpp>
#include <argot/concepts/default_constructible.hpp>
#include <argot/concepts/nothrow_destructible.hpp>
#include <argot/concepts/emplaceable_when_contained.hpp>
#include <argot/concepts/emplaceable_with_result_when_contained.hpp>
#include <argot/concepts/optional_like.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires.hpp>
#include <argot/in_place_default_init.hpp>
#include <argot/in_place_with_result.hpp>
#include <argot/opaque_optional/detail/opaque_base.hpp>

#include <boost/assert.hpp>

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <utility>

namespace argot {

// TODO(mattcalabrese) Allocator support
template< class T >
class opaque_optional
  : detail_opaque::opaque_base< opaque_optional, T >
{
    ARGOT_CONCEPT_ASSERT( DecayedType< T > );

    friend class detail_opaque::opaque_base< opaque_optional, T >;
 public:
  using element_type = T;

  constexpr opaque_optional() noexcept : target( nullptr ) {}

  template< class... P
          , ARGOT_REQUIRES( EmplaceableWhenContained< T, P&&... > )()
          >
  explicit opaque_optional( std::in_place_t, P&&... args )
    : target( ::new T( ARGOT_FORWARD( P )( args )...) ) {}

  template
  < class U, class... P
  , ARGOT_REQUIRES
    ( EmplaceableWhenContained< T, std::initializer_list< U >&, P&&... > )()
  >
  explicit opaque_optional( std::in_place_t
                          , std::initializer_list< U > ilist, P&&... args
                          )
    : target( ::new T( ilist, ARGOT_FORWARD( P )( args )...) ) {}

  template< class Fun, class... P
          , ARGOT_REQUIRES
            ( EmplaceableWithResultWhenContained< T, Fun&&, P&&... > )()
          >
  explicit opaque_optional( in_place_with_result_t, Fun&& fun, P&&... args )
    : target
      ( ::new T( argot_detail::constexpr_invoke
                 ( ARGOT_FORWARD( Fun )( fun )
                 , ARGOT_FORWARD( P )( args )...
                 )
               )
      ) {}

  template< class LazyT = T
          , ARGOT_REQUIRES( DefaultConstructible< LazyT > )()
          >
  explicit opaque_optional( in_place_default_init_t ) : target( ::new T ) {}

  constexpr opaque_optional( opaque_optional&& other ) noexcept
    : target( other.target )
  {
    other.target = nullptr;
  }

  opaque_optional( opaque_optional const& ) = delete;

  constexpr opaque_optional& operator=( opaque_optional&& rhs ) noexcept
  {
    return this->detail_move_assign( *this, ARGOT_MOVE( rhs ) );
  }

  opaque_optional& operator=( opaque_optional const& ) = delete;

  ~opaque_optional() noexcept
  {
    ARGOT_CONCEPT_ASSERT( NothrowDestructible< T > );

    static_assert
    ( sizeof( T ) != 0
    , "T must be complete when instantiating the destructor."
    );

    delete target;
  }

  using detail_opaque::opaque_base< opaque_optional, T >::has_value;
  using detail_opaque::opaque_base< opaque_optional, T >::reset;
  using detail_opaque::opaque_base< opaque_optional, T >::assign;
  using detail_opaque::opaque_base< opaque_optional, T >::emplace;
  using detail_opaque::opaque_base< opaque_optional, T >::emplace_default_init;
  using detail_opaque::opaque_base< opaque_optional, T >::emplace_with_result;
  using detail_opaque::opaque_base< opaque_optional, T >::operator *;
  using detail_opaque::opaque_base< opaque_optional, T >::operator ->;
  using detail_opaque::opaque_base< opaque_optional, T >::swap;
 private:
  T* target;
};

template< class T
        , ARGOT_REQUIRES
          ( DecayedType< T > )              
          ( DefaultConstructible< T > )
          ()
        >
opaque_optional< T > make_opaque_optional_default_init()
{
  return opaque_optional< T >( in_place_default_init );
}

template< std::nullptr_t = nullptr
        , class T
        , ARGOT_REQUIRES( EmplaceableWhenContained< std::decay_t< T >, T&& > )()
        >
opaque_optional< std::decay_t< T > > make_opaque_optional( T&& value )
{
  return opaque_optional< std::decay_t< T > >
         ( std::in_place, ARGOT_FORWARD( T )( value ) );
}

template< class T, class... P
        , ARGOT_REQUIRES( DecayedType< T > )
                        ( EmplaceableWhenContained< T, P&&... > )
                        ()
        >
opaque_optional< T > make_opaque_optional( P&&... args )
{
  return opaque_optional< T >( std::in_place, ARGOT_FORWARD( P )( args )... );
}

template< class T, class U, class... P
        , ARGOT_REQUIRES
          ( DecayedType< T > )              
          ( EmplaceableWhenContained< T, std::initializer_list< U >&, P&&... > )
          ()
        >
opaque_optional< T >
make_opaque_optional( std::initializer_list< U > ilist, P&&... args )
{
  return opaque_optional< T >
  ( std::in_place, ilist, ARGOT_FORWARD( P )( args )... );
}

template< std::nullptr_t = nullptr
        , class Fun, class... P
        , ARGOT_REQUIRES
          ( InvocableWith< Fun&&, P&&... > )
          ( DecayedType
            < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
          )
          ( EmplaceableWithResultWhenContained
            < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... >
            , Fun&&, P&&...
            >
          )
          ()
        >
auto make_opaque_optional_with_result( Fun&& fun, P&&... args )
{
  return opaque_optional
  < argot_detail::result_of_constexpr_invoke_t< Fun&&, P&&... > >
  ( in_place_with_result
  , ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )...
  );
}

template< class T, class Fun, class... P
        , ARGOT_REQUIRES
          ( DecayedType< T > )
          ( EmplaceableWithResultWhenContained< T, Fun&&, P&&... > )
          ()
        >
opaque_optional< T > make_opaque_optional_with_result( Fun&& fun, P&&... args )
{
  return opaque_optional< T >
  ( in_place_with_result
  , ARGOT_FORWARD( Fun )( fun ), ARGOT_FORWARD( P )( args )...
  );
}

template< class T >
struct make_concept_map< OptionalLike< opaque_optional< T > > >
{
  using element_type_t = T;

  static constexpr bool has_value( opaque_optional< T > const& opt ) noexcept
  {
    return opt.has_value();
  }

  template< class Self >
  static constexpr
  typename call_detail::give_qualifiers_to_t< Self&&, element_type_t >
  get( Self&& opt ) noexcept
  {
    BOOST_ASSERT( opt.has_value() );
    return *ARGOT_FORWARD( Self )( opt );
  }
};

} // namespace argot

template< class T >
struct std::hash< ::argot::opaque_optional< T > >
  : ::argot::detail_opaque::hash_base< ::argot::opaque_optional< T > > {};

#endif // ARGOT_OPAQUE_OPTIONAL_OPAQUE_OPTIONAL_HPP_
