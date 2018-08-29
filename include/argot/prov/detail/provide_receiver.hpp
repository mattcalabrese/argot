/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_DETAIL_PROVIDE_RECEIVER_HPP_
#define ARGOT_PROV_DETAIL_PROVIDE_RECEIVER_HPP_

#include <argot/forward.hpp>
#include <argot/receiver_traits/receive.hpp>

namespace argot::prov::prov_detail {

// IMPORTANT:
//   This directly contains a reference instead of being in a contained
//   because it is never assigned-to. This saves template instantiations.
// TODO(mattcalabrese) Possibly change this to use the contained or a pointer.
template< class Receiver >
struct provide_receiver
{
  Receiver&& rec;

  // TODO(mattcalabrese) Constrain
  template< class... P >
  constexpr receiver_traits::result_of_receive_t< Receiver, P... >
  operator()( P&&... args ) &&
  {
    return receiver_traits::receive( ARGOT_FORWARD( Receiver )( rec )
                                   , ARGOT_FORWARD( P )( args )...
                                   );
  }
};

}  // namespace (argot::prov::prov_detail)

#endif  // ARGOT_PROV_DETAIL_PROVIDE_RECEIVER_HPP_
