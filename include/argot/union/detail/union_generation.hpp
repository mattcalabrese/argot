#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define ARGOT_DETAIL_UNION_MEMBER( z, n, text )                                \
ARGOT_NO_UNIQUE_ADDRESS call_detail::holder< T ## n > alternative ## n;

#define ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES                               \
BOOST_PP_ITERATION()

namespace detail_union
{

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 1, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES                             \
     , <argot/union/detail/union_emplace_destroy_generation.hpp>               \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

} // namespace argot(::detail_union)

template
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, class T ) >
union union_
< BOOST_PP_ENUM_PARAMS( ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES, T ) >
{
  template<>
  friend
  struct detail_union::union_impl< ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES >;
 public:
  union_() = default;

#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 1, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES                             \
     , <argot/union/detail/union_function_generation.hpp>                      \
     )                                                                         \
)
#include BOOST_PP_ITERATE()

  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class... P
  , ARGOT_REQUIRES
    // TODO(mattcalabrese) Require I < num alts
    ( Constructible< union_traits::alternative_type_t< union_, I >, P&&... > )
    ()
  >
  constexpr auto& emplace( P&&... args )
  {
    return detail_union::union_impl< I >
    ::emplace( *this, ARGOT_FORWARD( P )( args )... );
  }

  // TODO(mattcalabrese) noexcept
  template
  < std::size_t I, class U, class... P
  , ARGOT_REQUIRES
    // TODO(mattcalabrese) Require I < num alts
    ( Constructible
      < union_traits::alternative_type_t< union_, I >
      , std::initializer_list< U >&, P&&...
      >
    )
    ()
  >
  constexpr auto& emplace( std::initializer_list< U > ilist, P&&... args )
  {
    return detail_union::union_impl< I >
    ::emplace( *this, ilist, ARGOT_FORWARD( P )( args )... );
  }

  // TODO(mattcalabrese) Better index checking requirement.
  template
  < std::size_t I
  , ARGOT_REQUIRES
    // TODO(mattcalabrese) Require I < num alts
    ( True< ( I < ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES ) > )
    ()
  >
  constexpr void destroy()
  {
    return detail_union::union_impl< I >::destroy( *this );
  }
 private:
#define BOOST_PP_ITERATION_PARAMS_2                                            \
( 3, ( 1, ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES                             \
     , <argot/union/detail/union_alternative_generation.hpp>                   \
     )                                                                         \
)
#include BOOST_PP_ITERATE()
};

#undef ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES
#undef ARGOT_DETAIL_UNION_MEMBER

#endif  // ARGOT_PREPROCESSING_MODE
