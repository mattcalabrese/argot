/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_BIND_TRANSFORM_OPERATOR_PIPE_HPP_
#define ARGOT_PROV_BIND_TRANSFORM_OPERATOR_PIPE_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/composable_with_provision.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/bind_transform/bind_transform.hpp>

#include <type_traits>

namespace argot {
namespace prov::bind_transform_pipe {

template< class Provider, class Transformation
        , ARGOT_REQUIRES
          ( ComposableWithProvision
            < detail_argot::remove_cvref_t< Provider >
            , std::decay_t< Transformation >
            >
          )
          //( HigherOrderArgumentProvider
          //  < typename ComposableWithProvision
          //    < Provider, std::decay_t< Transformations >... >::result_type
          //  >
          //)
          ( Sinkable< Provider&& > )
          ( DecaySinkable< Transformation&& > )
          ()
        >
[[nodiscard]] constexpr auto operator |
( Provider&& provider, Transformation&& transformation )//=;
//<-
{
  return prov::bind_transform
  ( call_detail::forward_and_sink< Provider >( provider )
  , call_detail::forward_and_decay_sink< Transformation >( transformation )
  );
} //->

} // namespace argot(::prov::bind_transform_pipe)

namespace operators {

using prov::bind_transform_pipe::operator |;

} // namespace argot(::operators)
} // namespace argot

#endif  // ARGOT_PROV_BIND_TRANSFORM_OPERATOR_PIPE_HPP_
