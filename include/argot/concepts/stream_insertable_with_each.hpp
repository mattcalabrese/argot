/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_EACH_HPP_
#define ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_EACH_HPP_

//[description
/*`
StreamInsertableWithEach is an [argot_gen_concept] that is satisfied if
each of the argument types represented in the specified `argument_types`
specializations is StreamInsertable with the specified type.
*/
//]

#include <argot/concepts/argument_types.hpp>
#include <argot/concepts/invocable_with.hpp>
#include <argot/concepts/stream_insertable.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/receiver_traits/argument_types.hpp>

#endif  // ARGOT_GENERATE_PREPROCESSED_CONCEPTS

namespace argot {
namespace detail_stream_insertable_with_each {

template< class Stream, class ArgumentTypes >
struct stream_insertable_with_argument_types {};

template< class Stream, class... P >
struct stream_insertable_with_argument_types
< Stream
, receiver_traits::argument_types_t< P... >
>
{
  template< template< class... > class Req >
  using expand_requirements = Req< StreamInsertable< Stream, P >... >;
};

template< class Stream, class... ArgumentListKinds >
struct stream_insertable_with_each_impl
{
  template< template< class... > class Req >
  using expand_requirements
    = Req
      < ArgumentTypes< ArgumentListKinds >...
      , TransparentRequirement
        < stream_insertable_with_argument_types
          < Stream, ArgumentListKinds >
        >...
      >;
};

} // namespace argot(::detail_stream_insertable_with_each)

template< class Stream, class... ArgumentListKinds >
using StreamInsertableWithEach
  = TransparentRequirement
    < detail_stream_insertable_with_each::stream_insertable_with_each_impl
      < Stream, ArgumentListKinds... >
    >;

} // namespace argot

#endif  // ARGOT_CONCEPTS_STREAM_INSERTABLE_WITH_EACH_HPP_
