/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_GIVE_QUALIFIERS_TO_HPP_
#define ARGOT_DETAIL_GIVE_QUALIFIERS_TO_HPP_

namespace argot {
namespace call_detail {

template< class Source, class Target >
struct give_qualifiers_to
{
  using type = Target;
};

#define ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( qual_kind )                      \
template< class Source, class Target >                                         \
struct give_qualifiers_to< Source qual_kind, Target >                          \
{                                                                              \
  using type = Target qual_kind;                                               \
};

ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( & )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( && )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( const )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( const & )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( const && )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( volatile )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( volatile & )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( volatile && )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( volatile const )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( volatile const & )
ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL( volatile const && )

#undef ARGOT_DETAIL_GIVE_QUALIFIERS_TO_IMPL

template< class Source, class Target >
using give_qualifiers_to_t
  = typename give_qualifiers_to< Source, Target >::type;

} // namespace argot::call_detail
} // namespace argot

#endif  // ARGOT_DETAIL_GIVE_QUALIFIERS_TO_HPP_
