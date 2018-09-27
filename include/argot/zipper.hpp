/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_ZIPPER_HPP_
#define ARGOT_ZIPPER_HPP_

#include <cstddef>
#include <type_traits>

namespace argot {

template< class Leading, class Elem, class Trailing >
struct zipper {};

template< template< class... > class Template
        , class... Leading, class Elem, class... Trailing
        >
struct zipper
< Template< Leading... >
, Elem
, Template< Trailing... >
>
{
  using all_t = Template< Leading..., Elem, Trailing... >;
  using index_t = std::integral_constant< std::size_t, sizeof...( Leading ) >;
  using leading_t = Template< Leading... >;
  using element_t = Elem;
  using trailing_t = Template< Trailing... >;

  static leading_t constexpr leading{};
  static trailing_t constexpr trailing{};
  static bool constexpr is_end = false;
};

// TODO(mattcalabrese) This should fail substitution, not be undefined.
template< class Zipper >
struct zipper_end_t;

template< template< class... > class Template, class... Zipper >
struct zipper_end_t< Template< Zipper... > >
{
  using all_t = Template< Zipper... >;
  using index_t
    = std::integral_constant< std::size_t, sizeof...( Zipper ) >;
  static bool constexpr is_end = true;
};

template< class Zipper >
struct zipper_end {};

template< template< class... > class Template, class... Zipper >
struct zipper_end< Template< Zipper... > >
{
  using type = zipper_end_t< Template< Zipper... > >;
};

template< class Zipper >
struct zipper_begin {};

template< template< class... > class Template
        , class Head, class... Tail
        >
struct zipper_begin< Template< Head, Tail... > >
{
  using type
    = zipper< Template<>, Head, Template< Tail... > >;
};

template< template< class... > class Template >
struct zipper_begin< Template<> >
{
  using type = zipper_end_t< Template<> >;
};

template< class Zipper >
using zipper_begin_t
  = typename zipper_begin< Zipper >::type;

template< class Partition >
struct zipper_next {};

template< template< class... > class Template
        , class... Leading, class Elem
        , class HeadTrailing, class... TailTrailing
        >
struct zipper_next
< zipper
  < Template< Leading... >
  , Elem
  , Template< HeadTrailing, TailTrailing... >
  >
>
{
  using type
    = zipper
      < Template< Leading..., Elem >
      , HeadTrailing
      , Template< TailTrailing... >
      >;
};

template< template< class... > class Template, class... Leading, class Elem >
struct zipper_next
< zipper< Template< Leading... >, Elem, Template<> >
>
{
  using type = zipper_end_t< Template< Leading..., Elem > >;
};

template< class Partition >
using zipper_next_t
  = typename zipper_next< Partition >::type;

template< class Zipper, std::size_t I >
struct zipper_at {};

template< template< class... > class Template, class... Zipper >
struct zipper_at< Template< Zipper... >, 0 >
{
  using type
    = typename zipper_begin< Template< Zipper... > >::type;
};

// TODO(mattcalabrese) SFINAE
template< template< class... > class Template
        , class... Zipper, std::size_t I
        >
struct zipper_at< Template< Zipper... >, I >
{
  using type
    = typename zipper_next
      < typename zipper_at
        < Template< Zipper... >, I - 1 >::type
      >::type;
};

template< class Zipper, std::size_t I >
using zipper_at_t
  = typename zipper_at< Zipper, I >::type;

// TODO(mattcalabrese) SFINAE
template< class Partition, std::ptrdiff_t Offset >
struct zipper_advance
{
  using type
    = zipper_at_t
      < typename Partition::all_t
      , Partition::index_t::value + Offset
      >;
};

template< class Partition, std::ptrdiff_t Offset >
using zipper_advance_t
  = typename zipper_advance< Partition, Offset >::type;

template< class Partition >
struct zipper_previous {};

// TODO(mattcalabrese) Specialize the end case
template< template< class... > class Template
        , class HeadLeading, class... TailLeading, class Elem
        , class... Trailing
        >
struct zipper_previous
< zipper
  < Template< HeadLeading, TailLeading... >, Elem, Template< Trailing... > >
>
{
  using type
    = zipper_at_t
      < Template
        < HeadLeading, TailLeading..., Elem
        , Trailing...
        >
      , sizeof...( TailLeading )
      >;
};

template< class Zipper >
using zipper_previous_t = typename zipper_previous< Zipper >::type;

} // namespace argot

#endif  // ARGOT_ZIPPER_HPP_
