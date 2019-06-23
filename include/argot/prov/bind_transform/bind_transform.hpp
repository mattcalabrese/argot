/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_BIND_TRANSFORM_BIND_TRANSFORM_HPP_
#define ARGOT_PROV_BIND_TRANSFORM_BIND_TRANSFORM_HPP_

#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/decay_sinkable.hpp>
#include <argot/basic_result_of.hpp>
#include <argot/detail/sink.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/lift_transform.hpp>
#include <argot/prov/squash.hpp>
#include <argot/concepts/sinkable.hpp>

#include <type_traits>

namespace argot::prov {

struct bind_transform_t
{
 private:
  template< class Provider >
  static constexpr auto make_impl( Provider&& provider )
  {
    return call_detail::forward_and_sink< Provider >( provider );
  }

  template< class Provider
          , class HeadTransformation, class... TailTransformations
          >
  static constexpr auto make_impl
  ( Provider&& provider
  , HeadTransformation&& head_transformation
  , TailTransformations&&... tail_transformations
  )
  {
    if constexpr( sizeof...( TailTransformations ) == 0 )
      return prov::squash
      ( prov::lift_transform
        ( call_detail::forward_and_sink< Provider >( provider )
        , call_detail::forward_and_decay_sink< HeadTransformation >
          ( head_transformation )
        )
      );
    else
      return make_impl
      ( make_impl
        ( call_detail::forward_and_sink< Provider >( provider )
        , call_detail::forward_and_decay_sink< HeadTransformation >
          ( head_transformation )
        )
      , call_detail::forward_and_decay_sink< TailTransformations >
        ( tail_transformations )...
      );
  }
 public:
  // TODO(mattcalabrese) Constrain to the result being higher order
  template
  < class Provider, class... Transformations
  , ARGOT_REQUIRES
    ( ComposableWithProvision
      < detail_argot::remove_cvref_t< Provider >
      , std::decay_t< Transformations >...
      >
    )
    //( HigherOrderArgumentProvider
    //  < typename ComposableWithProvision
    //    < Provider, std::decay_t< Transformations >... >::result_type
    //  >
    //)
    ( Sinkable< Provider&& > )
    ( DecaySinkable< Transformations&& >... )
    ()
  >
  [[nodiscard]] constexpr auto
  operator ()( Provider&& provider, Transformations&&... transformations ) const
  {
    return make_impl
    ( call_detail::forward_and_sink< Provider >( provider )
    , call_detail::forward_and_decay_sink< Transformations >
      ( transformations )...
    );
  }
} inline constexpr bind_transform{};

template< class Provider, class... Transformations >
using result_of_bind_transform
  = basic_result_of< bind_transform_t const&, Provider, Transformations... >;

template< class Provider, class... Transformations >
using result_of_bind_transform_t
  = basic_result_of_t< bind_transform_t const&, Provider, Transformations... >;

}  // namespace (argot::prov)

#endif  // ARGOT_PROV_BIND_TRANSFORM_BIND_TRANSFORM_HPP_
