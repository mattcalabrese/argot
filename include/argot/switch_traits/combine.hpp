/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_SWITCH_TRAITS_COMBINE_HPP_
#define ARGOT_SWITCH_TRAITS_COMBINE_HPP_

#include <argot/basic_result_of.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/detail/declval.hpp>
#include <argot/empty_switch_body.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/prov_traits/provide.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_destructive.hpp>
#include <argot/switch_traits/argument_list_kinds_of_body_persistent.hpp>
#include <argot/switch_traits/case_values.hpp>
#include <argot/switch_traits/destructive_provide_isolated_case.hpp>
#include <argot/switch_traits/destructive_provide_isolated_default.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_default_destructive.hpp>
#include <argot/switch_traits/leading_argument_list_kinds_of_default_persistent.hpp>
#include <argot/switch_traits/persistent_provide_isolated_case.hpp>
#include <argot/switch_traits/persistent_provide_isolated_default.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_destructive.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_case_persistent.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_default_destructive.hpp>
#include <argot/switch_traits/trailing_argument_list_kinds_of_default_persistent.hpp>
#include <argot/detail/remove_cvref.hpp>

#include <type_traits>

namespace argot {
namespace switch_traits {

struct combine_t
{
  template< class... Bodies >
  struct impl;
 private:
  template< class HeadBody, class... TailBodies >
  struct impl_of
  {
    using type = impl< HeadBody, TailBodies... >;
  };

  template< class HeadBody, class... TailBodies >
  using impl_of_t = typename impl_of< HeadBody, TailBodies... >::type;
 public:
  template< class HeadBody, class NextBody, class... TailBodies >
  struct impl< HeadBody, NextBody, TailBodies... >
  {
    // TODO(mattcalabrese) Assert requirements.

    HeadBody head_body;
    impl_of_t< NextBody, TailBodies... > tail_bodies;
  };
 private:
  template< class Body >
  struct impl_of< Body >
  {
    using type = Body;
  };

  template< class Body >
  static constexpr detail_argot::remove_cvref_t< Body > make_impl( Body&& body )
  {
    return ARGOT_FORWARD( Body )( body );
  }

  template< class HeadBody, class NextBody, class... TailBodies >
  static constexpr impl
  < detail_argot::remove_cvref_t< HeadBody >, detail_argot::remove_cvref_t< NextBody >
  , detail_argot::remove_cvref_t< TailBodies >...
  >
  make_impl( HeadBody&& head, NextBody&& next, TailBodies&&... tail )
  {
    return
    { ARGOT_FORWARD( HeadBody )( head )
    , make_impl
      ( ARGOT_FORWARD( NextBody )( next )
      , ARGOT_FORWARD( TailBodies )( tail )...
      )
    };
  }
 public:
  // TODO(mattcalabrese) Constraints: no overlapping values or defaults, sinkable, etc.
  template< class... Bodies
          , ARGOT_REQUIRES( SwitchBody< detail_argot::remove_cvref_t< Bodies > >... )()
          >
  constexpr auto operator()( Bodies&&... bodies ) const
  {
    if constexpr( sizeof...( Bodies ) == 0 )
      return empty_switch_body;
    else
      return make_impl( call_detail::forward_and_sink< Bodies >( bodies )... );
    // TODO(mattcalabrese) Construct the concatenation.
  }
} inline constexpr combine{};

template< class... Bodies >
using result_of_combine = basic_result_of< combine_t const&, Bodies&&... >;

template< class... Bodies >
using result_of_combine_t = basic_result_of_t< combine_t const&, Bodies&&... >;

namespace combine_detail {

template< class... Bodies >
struct body_list_t;

template< class Bodies, class ValueType >
struct concatenated_argument_list_kinds_of_destructive;

template< class... Bodies, class ValueType >
struct concatenated_argument_list_kinds_of_destructive
< body_list_t< Bodies... >, ValueType >
{
  using type
    = call_detail::concatenate_t
      < argument_list_kinds_of_body_destructive_t< Bodies, ValueType >... >;
};

template< class Bodies, class ValueType >
using concatenated_argument_list_kinds_of_destructive_t
  = typename concatenated_argument_list_kinds_of_destructive
    < Bodies, ValueType >::type;

template< class Bodies, class ValueType >
struct concatenated_argument_list_kinds_of_persistent;

template< class... Bodies, class ValueType >
struct concatenated_argument_list_kinds_of_persistent
< body_list_t< Bodies... >, ValueType >
{
  using type
    = call_detail::concatenate_t
      < argument_list_kinds_of_body_persistent_t< Bodies, ValueType >... >;
};

template< class Bodies, class ValueType >
using concatenated_argument_list_kinds_of_persistent_t
  = typename concatenated_argument_list_kinds_of_persistent
    < Bodies, ValueType >::type;

template< class Leading, class Body, class Trailing >
struct body_cursor_t
{
  using leading_bodies_t = Leading;
  using body_t = Body;
  using trailing_bodies_t = Trailing;

  body_t* body;
};

template< class Leading, class Body, class Trailing >
struct const_body_cursor_t
{
  using leading_bodies_t = Leading;
  using body_t = Body;
  using trailing_bodies_t = Trailing;

  body_t const* body;
};

template< class LeadingBody, class... Leading, class Body, class Trailing >
constexpr
body_cursor_t< body_list_t< LeadingBody, Leading... >, Body, Trailing >
prepend_to_cursor
( body_cursor_t< body_list_t< Leading... >, Body, Trailing > cursor ) noexcept
{
  return { cursor.body };
}

template< class LeadingBody, class... Leading, class Body, class Trailing >
constexpr
const_body_cursor_t< body_list_t< LeadingBody, Leading... >, Body, Trailing >
prepend_to_const_cursor
( const_body_cursor_t< body_list_t< Leading... >, Body, Trailing > cursor )
noexcept
{
  return { cursor.body };
}

template< auto Value >
struct destructive_body_for_case_t
{
  // TODO(mattcalabrese) Assert that the case is represented

  template< class HeadBody, class NextBody, class... TailBodies >
  constexpr auto operator ()
  ( combine_t::impl< HeadBody, NextBody, TailBodies... >&& impl ) const
  {
    if constexpr( is_modeled_v< SwitchBodyCase< HeadBody, Value > > )
      return body_cursor_t
      < body_list_t<>, HeadBody, body_list_t< NextBody, TailBodies... > >
      { std::addressof( impl.head_body ) };
    else
      if constexpr( sizeof...( TailBodies ) == 0 )
        return body_cursor_t< body_list_t< HeadBody >, NextBody, body_list_t<> >
        { std::addressof( impl.tail_bodies ) };
      else
        return ( prepend_to_cursor< HeadBody > )
        ( ( *this )( ARGOT_MOVE( impl.tail_bodies ) ) );
  }
};

template< auto Value >
destructive_body_for_case_t< Value > constexpr destructive_body_for_case{};

template< auto Value >
struct persistent_body_for_case_t
{
  // TODO(mattcalabrese) Assert that the case is represented

  template< class HeadBody, class NextBody, class... TailBodies >
  constexpr auto operator ()
  ( combine_t::impl< HeadBody, NextBody, TailBodies... > const& impl ) const
  {
    if constexpr( is_modeled_v< PersistentSwitchBodyCase< HeadBody, Value > > )
      return const_body_cursor_t
      < body_list_t<>, HeadBody, body_list_t< NextBody, TailBodies... > >
      { std::addressof( impl.head_body ) };
    else
      if constexpr( sizeof...( TailBodies ) == 0 )
        return const_body_cursor_t
        < body_list_t< HeadBody >, NextBody, body_list_t<> >
        { std::addressof( impl.tail_bodies ) };
      else
        return ( prepend_to_const_cursor< HeadBody > )
        ( ( *this )( impl.tail_bodies ) );
  }
};

template< auto Value >
persistent_body_for_case_t< Value > constexpr persistent_body_for_case{};

template< class ValueType >
struct destructive_body_for_default_t
{
  // TODO(mattcalabrese) Assert that there is a default

  template< class HeadBody, class NextBody, class... TailBodies >
  constexpr auto operator ()
  ( combine_t::impl< HeadBody, NextBody, TailBodies... >&& impl ) const
  {
    if constexpr
    ( is_modeled_v< SwitchBodyDefaultForType< HeadBody, ValueType > > )
      return body_cursor_t
      < body_list_t<>, HeadBody, body_list_t< NextBody, TailBodies... > >
      { std::addressof( impl.head_body ) };
    else
      if constexpr( sizeof...( TailBodies ) == 0 )
        return body_cursor_t< body_list_t< HeadBody >, NextBody, body_list_t<> >
        { std::addressof( impl.tail_bodies ) };
      else
        return ( prepend_to_cursor< HeadBody > )
        ( ( *this )( ARGOT_MOVE( impl.tail_bodies ) ) );
  }
};

template< class ValueType >
destructive_body_for_default_t< ValueType > constexpr
destructive_body_for_default{};

template< class ValueType >
struct persistent_body_for_default_t
{
  // TODO(mattcalabrese) Assert that there is a default

  template< class HeadBody, class NextBody, class... TailBodies >
  constexpr auto operator ()
  ( combine_t::impl< HeadBody, NextBody, TailBodies... > const& impl ) const
  {
    if constexpr
    ( is_modeled_v
      < PersistentSwitchBodyDefaultForType< HeadBody, ValueType > >
    )
      return const_body_cursor_t
      < body_list_t<>, HeadBody, body_list_t< NextBody, TailBodies... > >
      { std::addressof( impl.head_body ) };
    else
      if constexpr( sizeof...( TailBodies ) == 0 )
        return const_body_cursor_t
        < body_list_t< HeadBody >, NextBody, body_list_t<> >
        { std::addressof( impl.tail_bodies ) };
      else
        return ( prepend_to_const_cursor< HeadBody > )
        ( ( *this )( impl.tail_bodies ) );
  }
};

template< class ValueType >
persistent_body_for_default_t< ValueType > constexpr
persistent_body_for_default{};

} // namespace argot::switch_traits(::combine_detail)
} // namespace argot(::switch_traits)

// TODO(mattcalabrese) Properly constrain
template< class... Bodies >
struct make_concept_map
< SwitchBody< switch_traits::combine_t::impl< Bodies... > > >
{
  using case_values_t
    = concatenate_value_lists_t< switch_traits::case_values_t< Bodies >... >;

    // TODO(mattcalabrese) Define expander
};

// TODO(mattcalabrese) Properly constrain
template< class... Bodies >
struct make_concept_map
< SwitchBodyDefault< switch_traits::combine_t::impl< Bodies... > >
, ARGOT_REQUIRES( Or< SwitchBodyDefault< Bodies >... > )<>
>
{
  using case_values_t
    = concatenate_value_lists_t< switch_traits::case_values_t< Bodies >... >;

    // TODO(mattcalabrese) Define expander
};

// TODO(mattcalabrese) Properly constrain
template< class... Bodies, auto Value >
struct make_concept_map
< SwitchBodyCase< switch_traits::combine_t::impl< Bodies... >, Value >
, ARGOT_REQUIRES( Or< SwitchBodyCase< Bodies, Value >... > )<>
>
{
 private:
  using cursor
    = decltype
      ( switch_traits::combine_detail::destructive_body_for_case< Value >
        ( ARGOT_DECLVAL( switch_traits::combine_t::impl< Bodies... >&& ) )
      );
 public:
  // TODO(mattcalabrese) Rewrite this to maximize memoization.
  //                     (Possibly make a zipper)
  using leading_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_destructive_t
        < typename cursor::leading_bodies_t, decltype( Value ) >
      , switch_traits::leading_argument_list_kinds_of_case_destructive_t
        < typename cursor::body_t, Value >
      >;

  using trailing_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::trailing_argument_list_kinds_of_case_destructive_t
        < typename cursor::body_t, Value >
      , switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_destructive_t
        < typename cursor::trailing_bodies_t, decltype( Value ) >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_case
  ( switch_traits::combine_t::impl< Bodies... >&& self, Receiver&& rec )
  {
    return switch_traits::destructive_provide_isolated_case< Value >
    ( ARGOT_MOVE
      ( *switch_traits::combine_detail::destructive_body_for_case< Value >
        ( ARGOT_MOVE( self ) ).body
      )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

// TODO(mattcalabrese) Properly constrain
template< class... Bodies, auto Value >
struct make_concept_map
< PersistentSwitchBodyCase
  < switch_traits::combine_t::impl< Bodies... >, Value >
, ARGOT_REQUIRES
  ( SwitchBodyCase< switch_traits::combine_t::impl< Bodies... >, Value > )<>
>
{
 private:
  using cursor
    = decltype
      ( switch_traits::combine_detail::persistent_body_for_case< Value >
        ( ARGOT_DECLVAL( switch_traits::combine_t::impl< Bodies... > const& ) )
      );
 public:
  // TODO(mattcalabrese) Rewrite this to maximize memoization.
  //                     (Possibly make a zipper)
  using leading_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_persistent_t
        < typename cursor::leading_bodies_t, decltype( Value ) >
      , switch_traits::leading_argument_list_kinds_of_case_persistent_t
        < typename cursor::body_t, Value >
      >;

  using trailing_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::trailing_argument_list_kinds_of_case_persistent_t
        < typename cursor::body_t, Value >
      , switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_persistent_t
        < typename cursor::trailing_bodies_t, decltype( Value ) >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_case
  ( switch_traits::combine_t::impl< Bodies... > const& self, Receiver&& rec )
  {
    return switch_traits::persistent_provide_isolated_case< Value >
    ( *switch_traits::combine_detail::persistent_body_for_case< Value >( self )
       .body
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

// TODO(mattcalabrese) Properly constrain with value type
template< class... Bodies, class ValueType >
struct make_concept_map
< SwitchBodyDefaultForType
  < switch_traits::combine_t::impl< Bodies... >, ValueType >
, ARGOT_REQUIRES( Or< SwitchBodyDefaultForType< Bodies, ValueType >... > )<>
>
{
 private:
  using cursor
    = decltype
      ( switch_traits::combine_detail::destructive_body_for_default< ValueType >
        ( ARGOT_DECLVAL( switch_traits::combine_t::impl< Bodies... >&& ) )
      );
 public:
  // TODO(mattcalabrese) Rewrite this to maximize memoization.
  //                     (Possibly make a zipper)
  using leading_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_destructive_t
        < typename cursor::leading_bodies_t, ValueType >
      , switch_traits::leading_argument_list_kinds_of_default_destructive_t
        < typename cursor::body_t, ValueType >
      >;

  using trailing_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::trailing_argument_list_kinds_of_default_destructive_t
        < typename cursor::body_t, ValueType >
      , switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_destructive_t
        < typename cursor::trailing_bodies_t, ValueType >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_default
  ( switch_traits::combine_t::impl< Bodies... >&& self
  , ValueType value, Receiver&& rec
  )
  {
    return switch_traits::destructive_provide_isolated_default
    ( ARGOT_MOVE
      ( *switch_traits::combine_detail::destructive_body_for_default
         < ValueType >( ARGOT_MOVE( self ) ).body
      )
    , ARGOT_MOVE( value ), ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

// TODO(mattcalabrese) Properly constrain with value type
template< class... Bodies, class ValueType >
struct make_concept_map
< PersistentSwitchBodyDefaultForType
  < switch_traits::combine_t::impl< Bodies... >, ValueType >
, ARGOT_REQUIRES
  ( SwitchBodyDefaultForType
    < switch_traits::combine_t::impl< Bodies... >, ValueType >
  )
  ( Or< PersistentSwitchBodyDefaultForType< Bodies, ValueType >... > )
  <>
>
{
 private:
  using cursor
    = decltype
      ( switch_traits::combine_detail::persistent_body_for_default< ValueType >
        ( ARGOT_DECLVAL( switch_traits::combine_t::impl< Bodies... > const& ) )
      );
 public:
  // TODO(mattcalabrese) Rewrite this to maximize memoization.
  //                     (Possibly make a zipper)
  using leading_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_persistent_t
        < typename cursor::leading_bodies_t, ValueType >
      , switch_traits::leading_argument_list_kinds_of_default_persistent_t
        < typename cursor::body_t, ValueType >
      >;

  using trailing_argument_list_kinds_t
    = call_detail::concatenate_t
      < switch_traits::trailing_argument_list_kinds_of_default_persistent_t
        < typename cursor::body_t, ValueType >
      , switch_traits::combine_detail
        ::concatenated_argument_list_kinds_of_persistent_t
        < typename cursor::trailing_bodies_t, ValueType >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_default
  ( switch_traits::combine_t::impl< Bodies... > const& self
  , ValueType value, Receiver&& rec
  )
  {
    return switch_traits::persistent_provide_isolated_default
    ( *switch_traits::combine_detail::persistent_body_for_default< ValueType >
      ( self ).body
    , ARGOT_MOVE( value ), ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

} // namespace argot

#endif  // ARGOT_SWITCH_TRAITS_COMBINE_HPP_
