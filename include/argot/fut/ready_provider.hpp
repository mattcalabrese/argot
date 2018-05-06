/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_READY_PROVIDER_HPP_
#define ARGOT_FUT_READY_PROVIDER_HPP_

namespace argot {
namespace fut {

struct ready_provider_fn
{
  template< class Provider >
  struct impl
  {
    ARGOT_CONCEPT_ASSERT( ArgumentProvider< Provider > );

    Provider provider;
  };

  template< class Provider
          , ARGOT_REQUIRES( ArgumentProvider< remove_cvreft_t< Provider > > )
                          ( Sinkable< Provider&& > )
                          ()
          >
  [[nodiscard]] constexpr auto operator ()( Provider&& provider ) const
  {
    return impl< remove_cvref_t< Provider > >
    { call_detail::forward_and_sink< Provider >( provider ) };
  }

} inline constexpr ready_provider{};

} // namespace argot(::fut)

template< class Provider >
struct make_concept_map< fut::ready_provider_fn::impl< Provider > >
{
  template< class Fun >
  static constexpr decltype( auto )
  then( fut::ready_provider_fn::impl< Provider >&& self, Fun&& fun )
  {
    return fut::ready_result( );
  }
};

} // namespace argot

#endif  // ARGOT_FUT_READY_PROVIDER_HPP_
