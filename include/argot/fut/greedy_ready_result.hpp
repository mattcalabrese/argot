/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_GREEDY_READY_RESULT_HPP_
#define ARGOT_FUT_GREEDY_READY_RESULT_HPP_

namespace argot {
namespace fut {

// TODO(mattcalabrese) Allow reducer to be specified
struct greedy_ready_result_fn
{
  // TODO(mattcalabrese) Include leading and trailing argument list kinds.
  template< class Result >
  struct impl
  {
    Result result;
  };

  // TODO(mattcalabrese) Possible default_to_reference_to or don't take providers
  template< class Fun, class... Providers >
  constexpr // TODO(mattcalabrese) SFINAE
  auto operator()( Fun&&, Providers&&... providers ) const
  {
    return impl< result_type >
    { prov_traits::provide( prov::group( providers )
                          , receiver::reduced_invoke( /*fun, reducer*/ )
                          )
    };
  }
} inline constexpr greedy_ready_result{};

} // namespace argot(::fut)

template< class Fun, class Provider >
struct make_concept_map< Future< fut::greedy_ready_result_fn::impl< Fun, Provider > > >
{
  template< class Fun >
  static constexpr auto
  then( fut::greedy_ready_result_fn::impl< Fun, Provider >&& self, Fun&& fun )
  {
    using direct_result_type
      = decltype
        ( prov_traits::provide( ARGOT_MOVE( self.fun ), /*function caller*/ ) );

    return fut::ready< direct_result_type >
    ( prov_traits::provide( ARGOT_MOVE( self.fun ), /*function caller*/ )
    , /* TODO(mattcalabrese) Call constructor that is RVO friendly */
    );
  }
};

} // namespace argot

#endif  // ARGOT_FUT_GREEDY_READY_RESULT_HPP_
