/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_KINDS_HPP_
#define ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_KINDS_HPP_

//[description
/*`
StreamInsertableWithKinds is an [argot_gen_concept] that is satisfied if
each of the argument types represented in the specified `argument_list_kinds`
specialization is StreamInsertable with the specified type.
*/
//]

#include <argot/concepts/argument_list_kinds.hpp>
#include <argot/concepts/stream_insertable_with_each.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_list_kinds.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detatil_stream_insertable_with_kinds {

template< class Stream, class Kinds >
struct stream_insertable_with_kinds_impl_impl {};

template< class Stream, class... Kinds >
struct stream_insertable_with_kinds_impl_impl
< Stream
, receiver_traits::argument_list_kinds_t< Kinds... >
>
{
  template< template< class... > class Req >
  using expand_requirements
    = Req< StreamInsertableWithEach< Stream, Kinds... > >;
};

template< class Stream, class Kinds >
struct stream_insertable_with_kinds_impl
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ArgumentListKinds< Kinds >
      , TransparentRequirement
        < stream_insertable_with_kinds_impl_impl< Stream, Kinds > >
      >;
};

} // namespace argot(::detatil_stream_insertable_with_kinds)

template< class Stream, class Kinds >
using StreamInsertableWithKinds
  = TransparentRequirement
    < detatil_stream_insertable_with_kinds
      ::stream_insertable_with_kinds_impl< Stream, Kinds >
    >;

} // namespace argot

#endif  // ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_KINDS_HPP_
