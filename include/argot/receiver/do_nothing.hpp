/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_RECEIVER_DO_NOTHING_HPP_
#define ARGOT_RECEIVER_DO_NOTHING_HPP_

//[description
/*`
receiver::do_nothing is an ArgumentReceiver that can receive any arguments, but
does nothing with those arguments. It is useful when exploiting an
ArgumentProvider for its side-effects.

[note This is a low-level facility. If you wish to exploit an ArgumentProvider
      for its side-effects and do not want to deal with an ArgumentReceiver
      directly, the argot::side_effect facility is a higher-level facility that
      can be used for similar overall behavior.
]
*/
//]

#include <argot/concepts/argument_receiver.hpp>
#include <argot/gen/make_concept_map.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::receiver {

struct do_nothing_fn
{
  //<-
  struct impl {};
  //->
  constexpr auto operator()() const noexcept//=;
  //<-
  {
    return impl{};
  } //->
} inline constexpr do_nothing{};

} // namespace (argot::receiver)

//]

namespace argot {

template<>
struct make_concept_map< ArgumentReceiver< receiver::do_nothing_fn::impl > >
{
  template< class LeadingArgLists, class TrailingArgLists, class... P >
  static constexpr void
  receive_branch
  ( receiver::do_nothing_fn::impl
  , LeadingArgLists, TrailingArgLists, P&&...
  ) noexcept
  {
  }
};

} // namespace argot

#endif // ARGOT_RECEIVER_DO_NOTHING_HPP_
