#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif

struct union_impl_preprocessed< BOOST_PP_ITERATE() >
{
  template< class Self, class... P >
  static constexpr auto& emplace( Self& self, P&&... args )
  noexcept
  ( std::is_nothrow_constructible_v
    < typename Self::BOOST_PP_CAT( alternative_type, BOOST_PP_ITERATE() )
    , P&&...
    >
  )
  {
    // TODO(mattcalabrese) std::launder
    return *::new( static_cast< void* >( &self ) )
    BOOST_PP_CAT( T, BOOST_PP_ITERATE() )( ARGOT_FORWARD( P )( args )... );
  }

  // TODO(mattcalabrese) Possibly noexcept
  template< class T, class Self >
  static constexpr void destroy( Self& self )
  noexcept
  ( std::is_nothrow_destructible_v
    < typename Self::BOOST_PP_CAT( alternative_type, BOOST_PP_ITERATE() )
    , P&&...
    >
  )
  {
    // TODO(mattcalabrese) Use holder's destroy (does nothing if trivial)
    std::destroy_at
    ( std::addressof( BOOST_PP_CAT( self.alternative, BOOST_PP_ITERATE() ) ) );
  }

  template< class... T >
  using alternative_type_t
    = typename union_< T... >
      ::BOOST_PP_CAT( alternative_type, BOOST_PP_ITERATE() );

  template< class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    return call_detail::access_holder
    ( ARGOT_FORWARD( Self )( self )
      .BOOST_PP_CAT( alternative, BOOST_PP_ITERATE() )
    );
  }
}

#endif  // ARGOT_PREPROCESSING_MODE
