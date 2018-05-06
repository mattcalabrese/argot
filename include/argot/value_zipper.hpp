/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_VALUE_ZIPPER_HPP_
#define ARGOT_VALUE_ZIPPER_HPP_

#include <cstddef>
#include <type_traits>

namespace argot {

template< class Leading, auto Elem, class Trailing >
struct value_zipper {};

template< template< auto... > class Template
        , auto... Leading, auto Elem, auto... Trailing
        >
struct value_zipper
< Template< Leading... >
, Elem
, Template< Trailing... >
>
{
  // TODO(mattcalabrese) Make this private
  static value_zipper find_impl( value_list_t< Elem > );

  using all_t = Template< Leading..., Elem, Trailing... >;
  using index_t = std::integral_constant< std::size_t, sizeof...( Leading ) >;
  using leading_t = Template< Leading... >;
  using value_type = decltype( Elem );
  static constexpr value_type value = Elem;
  using trailing_t = Template< Trailing... >;

  static leading_t constexpr leading{};
  static trailing_t constexpr trailing{};
  static bool constexpr is_end = false;
};

// TODO(mattcalabrese) This should fail substitution, not be undefined.
template< class Zipper >
struct value_zipper_end_t;

template< template< auto... > class Template, auto... Zipper >
struct value_zipper_end_t< Template< Zipper... > >
{
  using all_t = Template< Zipper... >;
  using index_t
    = std::integral_constant< std::size_t, sizeof...( Zipper ) >;
  static bool constexpr is_end = true;
};

template< class Zipper >
struct value_zipper_end {};

template< template< auto... > class Template, auto... Zipper >
struct value_zipper_end< Template< Zipper... > >
{
  using type = value_zipper_end_t< Template< Zipper... > >;
};

template< class Zipper >
struct value_zipper_begin {};

template< template< auto... > class Template
        , auto Head, auto... Tail
        >
struct value_zipper_begin< Template< Head, Tail... > >
{
  using type
    = value_zipper< Template<>, Head, Template< Tail... > >;
};

template< template< auto... > class Template >
struct value_zipper_begin< Template<> >
{
  using type = value_zipper_end_t< Template<> >;
};

template< class Zipper >
using value_zipper_begin_t
  = typename value_zipper_begin< Zipper >::type;

template< class Partition >
struct value_zipper_next {};

template< template< auto... > class Template
        , auto... Leading, auto Elem
        , auto HeadTrailing, auto... TailTrailing
        >
struct value_zipper_next
< value_zipper
  < Template< Leading... >
  , Elem
  , Template< HeadTrailing, TailTrailing... >
  >
>
{
  using type
    = value_zipper
      < Template< Leading..., Elem >
      , HeadTrailing
      , Template< TailTrailing... >
      >;
};

template< template< auto... > class Template, auto... Leading, auto Elem >
struct value_zipper_next
< value_zipper< Template< Leading... >, Elem, Template<> >
>
{
  using type = value_zipper_end_t< Template< Leading..., Elem > >;
};

template< class Partition >
using value_zipper_next_t
  = typename value_zipper_next< Partition >::type;

template< class Zipper, std::size_t I >
struct value_zipper_at {};

template< template< auto... > class Template, auto... Zipper >
struct value_zipper_at< Template< Zipper... >, 0 >
{
  using type
    = typename value_zipper_begin< Template< Zipper... > >::type;
};

// TODO(mattcalabrese) SFINAE
template< template< auto... > class Template
        , auto... Zipper, std::size_t I
        >
struct value_zipper_at< Template< Zipper... >, I >
{
  using type
    = typename value_zipper_next
      < typename value_zipper_at
        < Template< Zipper... >, I - 1 >::type
      >::type;
};

template< class Zipper, std::size_t I >
using value_zipper_at_t
  = typename value_zipper_at< Zipper, I >::type;

// TODO(mattcalabrese) SFINAE
template< class Partition, std::ptrdiff_t Offset >
struct value_zipper_advance
{
  using type
    = value_zipper_at_t
      < typename Partition::all_t
      , Partition::index_t::value + Offset
      >;
};

template< class Partition, std::ptrdiff_t Offset >
using value_zipper_advance_t
  = typename value_zipper_advance< Partition, Offset >::type;

template< class Partition >
struct value_zipper_previous {};

// TODO(mattcalabrese) Specialize the end case
template< template< auto... > class Template
        , auto HeadLeading, auto... TailLeading, auto Elem
        , auto... Trailing
        >
struct value_zipper_previous
< value_zipper
  < Template< HeadLeading, TailLeading... >, Elem, Template< Trailing... > >
>
{
  using type
    = value_zipper_at_t
      < Template
        < HeadLeading, TailLeading..., Elem
        , Trailing...
        >
      , sizeof...( TailLeading )
      >;
};

template< class Zipper >
using value_zipper_previous_t = typename value_zipper_previous< Zipper >::type;

namespace value_zipper_detail {

template< class Indices, class Values >
struct value_zipper_find_impl;

template< std::size_t... Indices, class Values >
struct value_zipper_find_impl< std::index_sequence< Indices... >, Values >
  : value_zipper_at_t< Values, Indices >...
{
  using value_zipper_at_t< Values, Indices >::find_impl...;

  template< auto NotFound >
  static value_zipper_end_t< Values > find_impl( value_list_t< NotFound > );
};

}  // namespace argot(::value_zipper_detail)

template< class Values, auto Value >
struct value_zipper_find;

template
< template< auto... Values > class Template, auto... Values, auto Value >
struct value_zipper_find< Template< Values... >, Value >
{
  using type
    = decltype
      ( value_zipper_detail::value_zipper_find_impl
        < std::make_index_sequence< sizeof...( Values ) >
        , Template< Values... >
        >::find_impl( value_list_t< Value >() )
      );
};

template< class Values, auto Value >
using value_zipper_find_t = typename value_zipper_find< Values, Value >::type;

template< class Values, auto Value >
bool constexpr value_zipper_contains_v
  = !std::is_same_v
    < value_zipper_find_t< Values, Value >, value_zipper_end_t< Values > >;

template< class Values, auto Value >
struct value_zipper_contains
  : std::bool_constant< value_zipper_contains_v< Values, Value > > {};

}  // namespace argot

#endif  // ARGOT_VALUE_ZIPPER_HPP_
