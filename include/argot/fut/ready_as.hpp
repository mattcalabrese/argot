/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_READY_AS_HPP_
#define ARGOT_FUT_READY_AS_HPP_

#if 0

namespace argot {
namespace fut {
namespace ready_detail {

template< class T >
struct impl
{
  // TODO(mattcalabrese) Use holder.
  ARGOT_NO_UNIQUE_ADDRESS T value;
};

template< class Fun, class... P >
constexpr impl< basic_result_of_t< Fun&&, P&&... > >
make_from_result( Fun&& fun, P&&... args )
{
  return { ARGOT_MOVE( fun )( ARGOT_FORWARD( P )( args )... ) };
}

template< class Fun, class T >
struct immediate_function
{
  // TODO(mattcalabrese) Concept assert that fun and arg are references.

  constexpr basic_result_of_t< Fun&&, P&&... > operator ()() &&
  {
    return ARGOT_FORWARD( Fun )( fun )( ARGOT_FORWARD( T )( arg ) );
  }

  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  ARGOT_NO_UNIQUE_ADDRESS T arg;
};

} // namespace argot::fut(::ready_detail)

template< class T >
struct ready_fn
{
  template< class U
          , ARGOT_REQUIRES( Convertible< U&&, T > )()
          >
  [[nodiscard]] constexpr auto operator ()( U&& source ) const
  {
    // TODO(mattcalabrese) Don't use forward and sink, allow conversions.
    return ready_detail::impl< T >
    { call_detail::forward_and_sink< U >( source ) };
  }

};

template< class T >
constexpr ready_fn ready{};

} // namespace argot(::fut)

template< class T >
struct make_concept_map< Future< fut::ready_detail::impl< T > > >
{
  using value_type_t = T;

  template< class Fun >
  static constexpr decltype( auto )
  forgetful_then( fut::ready_detail::impl< T >&& self, Fun&& fun )
  {
    // TODO(mattcalabrese) Execute only const& or && overloads of Fun.
    (void)ARGOT_FORWARD( Fun )( fun )( ARGOT_FORWARD( T )( self.value ) );
  }
};

template< class T, class FutPackager, class Exec >
struct make_concept_map
< Thenable< fut::ready_detail::impl< T >, packager::ready, Exec >
, ARGOT_REQUIRES( ImmediateExecutor< Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class Exec, class Fun >
  static constexpr auto
  then( stlab::future< T >&& self, Exec&& exec, Fun&& fun )
  {
    return fut::ready_detail::impl< basic_result_of_t< Fun&&, T&& > >
    { executor_traits::execute_immediately
      ( ARGOT_FORWARD( Exec )( exec )
      , fut::ready_detail::immediate_function< Fun&&, T&& >
        { ARGOT_FORWARD( Fun )
        , ARGOT_FORWARD( T )( self.value )
        }
      )
    };
  }
};

} // namespace argot

#endif

#endif  // ARGOT_FUT_READY_AS_HPP_
