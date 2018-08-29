#ifndef ARGOT_PREPROCESSING_MODE
/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#endif // ARGOT_PREPROCESSING_MODE

// Make the includes appear directly so that rebuilds still take place when
// dependencies change.
#if 0
#include <argot/union_/detail/generation/union_constructor_generation.hpp>
#include <argot/union_/detail/generation/union_member_generation.hpp>
#include <argot/union_/detail/generation/union_member_typedef_generation.hpp>
#endif

#define ARGOT_DETAIL_UNION_CURR_NUM_ALTERNATIVES                               \
BOOST_PP_ITERATION()

#define ARGOT_DETAIL_UNION_CURR_IMPL_INDEX                                     \
BOOST_PP_DEC( BOOST_PP_ITERATION() )

template<>
struct union_impl_preprocessed< ARGOT_DETAIL_UNION_CURR_IMPL_INDEX >
{
  template< class... T >
  using alternative_type_t
    = typename raw_struct< T... >
      ::BOOST_PP_CAT( alternative_type, ARGOT_DETAIL_UNION_CURR_IMPL_INDEX );

  template< class Self >
  static constexpr auto&& get( Self&& self ) noexcept
  {
    using qualified_alt
      = call_detail::give_qualifiers_to_t
        < Self&&
        , typename access_raw_concept_map< UnionLike< remove_cvref_t< Self > > >
          ::template alternative_type_t< ARGOT_DETAIL_UNION_CURR_IMPL_INDEX >
        >;

    return static_cast< qualified_alt >
    ( * //std::launder // TODO(mattcalabrese) Uncomment when launder exists.
       ( std::addressof
         ( self.alternatives
           .BOOST_PP_CAT( alternative, ARGOT_DETAIL_UNION_CURR_IMPL_INDEX )
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
