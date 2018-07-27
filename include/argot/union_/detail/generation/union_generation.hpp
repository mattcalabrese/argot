#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

#define ARGOT_DETAIL_UNION_MEMBER( z, n, text )                                \
ARGOT_NO_UNIQUE_ADDRESS call_detail::holder< T ## n > alternative ## n;

#define ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES                               \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_UNION_CURR_IMPL_INDEX                                     \
BOOST_PP_DEC( BOOST_PP_ITERATION() )

// TODO(mattcalabrese) Remove destroy and emplace (only need get here)
//                     Doing the above requires exposing holder typedef as well.
template<>
struct union_impl_preprocessed< ARGOT_DETAIL_UNION_CURR_IMPL_INDEX >
{
  template< class... T >
  using alternative_type_t
    = typename raw_struct< T... >
      ::BOOST_PP_CAT( alternative_type, ARGOT_DETAIL_UNION_CURR_IMPL_INDEX );

  template< class... T, class P >
  static constexpr auto& assign( union_< T... >& self, P&& arg )
  {
    // TODO(mattcalabrese) Branch on whether or not it is a holder_type
    BOOST_PP_CAT( self.alternatives.alternative
                , ARGOT_DETAIL_UNION_CURR_IMPL_INDEX
                )
      = ARGOT_FORWARD( P )( arg );

    return call_detail::access_holder
    ( BOOST_PP_CAT( self.alternatives.alternative
                  , ARGOT_DETAIL_UNION_CURR_IMPL_INDEX
                  )
    );
  }

  // TODO(mattcalabrese) noexcept
  template< class... T, class... P >
  static constexpr auto& emplace( union_< T... >& self, P&&... args )/*
  noexcept
  ( std::is_nothrow_constructible_v  // TODO(mattcalabrese) change to emplace
    < alternative_type_t< T... >
    , P&&...
    >
  )*/
  {
    // TODO(mattcalabrese) std::launder
    return call_detail::access_holder
    ( *::new( static_cast< void* >( &self ) )
      call_detail::holder< alternative_type_t< T... > >
      ( call_detail::emplace_holder< alternative_type_t< T... > >
        ( ARGOT_FORWARD( P )( args )... )
      )
    );
  }

  template< class... T >
  static constexpr void destroy( union_< T... >& self )
  noexcept
  ( std::is_nothrow_destructible_v
    < call_detail::holder< alternative_type_t< T... > > >
  )
  {
    if constexpr
    ( !std::is_trivially_destructible_v
      < call_detail::holder< alternative_type_t< T... > > >
    )
      std::destroy_at
      ( //std::launder // TODO(mattcalabrese) launder
        ( std::addressof
          ( BOOST_PP_CAT( self.alternatives.alternative
                        , ARGOT_DETAIL_UNION_CURR_IMPL_INDEX
                        )
          )
        )
      );
  }

  template< class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    // TODO(mattcalabrese) Get alternative type in a simpler manner?
    using qual_holder
      = call_detail::give_qualifiers_to_t
        < Self&&
        , call_detail::holder
          < typename access_raw_concept_map
            < UnionLike< remove_cvref_t< Self > > >
            ::template alternative_type_t< ARGOT_DETAIL_UNION_CURR_IMPL_INDEX >
          >
        >;

    return call_detail::access_holder
    ( static_cast< qual_holder >
      ( * //std::launder // TODO(mattcalabrese) launder
        ( std::addressof
          ( self.alternatives
            .BOOST_PP_CAT( alternative, ARGOT_DETAIL_UNION_CURR_IMPL_INDEX )
          )
        )
      )
    );
  }
};

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, class T ) >
struct raw_struct
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, T ) >
{
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_member_typedef_generation.hpp>    \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_member_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
};

namespace no_default_no_destructor {

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, class T ) >
struct union_base
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, T ) >
{
  constexpr union_base() noexcept {}
  ~union_base() noexcept {}

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_constructor_generation.hpp>       \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

  union
  {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_member_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
  };
};

} // namespace argot::detail_union(::no_default_no_destructor)

namespace no_default_has_destructor {

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, class T ) >
struct union_base
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, T ) >
{
  constexpr union_base() noexcept {}
  ~union_base() = default;

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_constructor_generation.hpp>       \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

  union
  {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_member_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
  };
};

} // namespace argot::detail_union(::no_default_has_destructor)

// TODO(mattcalabrese)
//   Possibly make a base for union_base and add the default constructor in the
//   child. This would unfortunately instantiate more types.

namespace has_default_no_destructor {

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, class T ) >
struct union_base
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, T ) >
{
  union_base() = default;
  ~union_base() noexcept {}

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_constructor_generation.hpp>       \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

  union
  {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_member_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
  };
};

} // namespace argot::detail_union(::has_default_no_destructor)

namespace has_default_has_destructor {

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, class T ) >
struct union_base
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, T ) >
{
  union_base() = default;
  ~union_base() = default;

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_constructor_generation.hpp>       \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

  union
  {
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 0, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES - 1                         \
     , <argot/union_/detail/generation/union_member_generation.hpp>            \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
  };
};

} // namespace argot::detail_union(::has_default_has_destructor)

#undef ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES
#undef ARGOT_DETAIL_UNION_MEMBER
