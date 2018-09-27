/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_AS_HPP_
#define ARGOT_PROV_AS_HPP_

//[description
/*`
prov::as is a facility for binding arguments into an ArgumentProvider, along
with the requirement for the user to explicitly specify how the arguments are to
be bound (whether by value, by lvalue reference, or by rvalue reference). For
bindings that are intended to capture all argument by value, prefer
prov::value_of, and for bindings that are intended to capture all arguments by
reference, prefer prov::reference_to.

[global_function_object_template_designator]
*/
//]

#include <argot/concepts/convertible.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/contained.hpp>
#include <argot/detail/argument_pack.hpp>
#include <argot/detail/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/detail/as_impl.hpp>
#include <argot/prov/nothing.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/receiver_traits/receive.hpp>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {

template< class... AsP >
struct as_fn
{
  //<-
  ARGOT_CONCEPT_ASSERT( MoveConstructible< argot::contained< AsP > >... );
 private:
  template< class HeadP, class... TailP >
  [[nodiscard]]
  constexpr auto impl( HeadP&& head, TailP&&... tail ) const//=;
  {
    return as_detail::as_impl< AsP... >
    { { call_detail::make_argument_pack< AsP const... >
        ( ARGOT_FORWARD( HeadP )( head ), ARGOT_FORWARD( TailP )( tail )... )
      }
    };
  }
 public:
  //->
  template< class... P
          , ARGOT_REQUIRES
            ( SameType
              < detail_argot::remove_cvref_t< AsP >
              , detail_argot::remove_cvref_t< P >
              >...
            )
            ( Convertible< P&&, AsP >... )
            ()
          >
  [[nodiscard]]
  constexpr auto operator ()( P&&... args ) const//=;
  //<-
  {
    if constexpr( sizeof...( P ) == 0 )
      return prov::nothing;
    else
      return impl( ARGOT_FORWARD( AsP )( args )... );
  }//->
};

// TODO(mattcalabrese) Make a concept for this constraint
template< class... AsP >
ARGOT_REQUIRES( MoveConstructible< argot::contained< AsP > >... )
< as_fn< AsP... > > constexpr as{};
//<-
#if 0
// TODO(mattcalabrese) Make result_of calculators

namespace detail_as {

template< class As, class... P >
using as_application_t
  = basic_result_of_t< As const&, P... >;

template< class... HeadE >
struct quoted_as
{
  template< class... TailE >
  struct bind_more = quoted_as< HeadE..., TailE... >;

  template< class... TailE >
  struct apply = as_fn< HeadE..., TailE... >;
};

template< bool IsEven, std::size_t SizeOverTwo >
struct result_of_as_t_impl {};

template<>
struct result_of_as_t_impl< /*IsEven =*/ true, 0 >
{
  using _ = result_of_as_t_impl;

  template< template< class... > AsFormer, class... P >
  using apply
    = decltype( AsFormer<>{}( argot_detail::exact_declval< P&& >()... ) );
};

template<>
struct result_of_as_t_impl< /*IsEven =*/ true, 1 >
{
  using _ = result_of_as_t_impl;

  template< template< class... > AsFormer, class E0, class... P >
  using apply
    = decltype( AsFormer< E0 >( argot_detail::exact_declval< P&& >() ) );
};

template<>
struct result_of_as_t_impl< /*IsEven =*/ true, 2 >
{
  using _ = result_of_as_t_impl;

  template< template< class... > AsFormer, class E0, class E1, class... P >
  using apply
    = decltype
      ( AsFormer< E0, E1 >( argot_detail::exact_declval< P&& >()... ) );
};

template<>
struct result_of_as_t_impl< /*IsEven =*/ true, 3 >
{
  using _ = result_of_as_t_impl;

  template< template< class... > AsFormer, class E0, class E1, class E2, class P0, class... P >
  using apply
    = decltype
      ( AsFormer< E0, E1, E2 >( argot_detail::exact_declval< P&& >()... ) );
};

template<>
struct result_of_as_t_impl< /*IsEven =*/ true, 4 >
{
  using _ = result_of_as_t_impl;

  template< template< class... > AsFormer
          , class E0, class E1, class E2, class E3
          , class... T
          >
  using partial_apply
    = quoted_as< >


  template< template< class... > AsFormer
          , class E0, class E1, class E2, class E3, class... P
          >
  using apply
    = decltype
      ( AsFormer< E0, E1, E2, E3 >( argot_detail::exact_declval< P&& >()... ) );
};

template< std::size_t Size >
struct partition_impl;

template<>
struct partition_impl< 0 >
{
  template< template< class Part, class... Tail > class Result
          , template< class... > class Template, class... P
          >
  using apply = Result< Template<>, P... >; 
};

template<>
struct partition_impl< 1 >
{
  template< template< class Part, class... Tail > class Result
          , template< class... > class Template, class P0, class... P
          >
  using apply = Result< Template< P0 >, P... >; 
};


template<>
struct partition_impl< 2 >
{
  template< template< class Part, class... Tail > class Result
          , template< class... > class Template, class P0, class P1, class... P
          >
  using apply = Result< Template< P0, P1 >, P... >; 
};


template<>
struct partition_impl< 3 >
{
  template< template< class Part, class... Tail > class Result
          , template< class... > class Template
          , class P0, class P1, class P2, class... P
          >
  using apply = Result< Template< P0, P1, P2 >, P... >; 
};


template<>
struct partition_impl< 4 >
{
  template< template< class Part, class... Tail > class Result
          , template< class... > class Template
          , class P0, class P1, class P2, class P3, class... P
          >
  using apply = Result< Template< P0, P1, P2, P3 >, P... >; 
};

inline std::size_t unrolled_size = 4;

template< template< class... > class Template, class... P >
using quote
{
  template< class... U >
  using apply = Template< P..., U... >
};

template< std::size_t Size
        , template< class... > class Result
        , template< class... > class Template
        , class... P
        >
using partition
  = typename call_detail::if_< Size <= unrolled_size >
    ::template meta_apply_value
    < partition_impl
    , partial_partition_impl
    >::template apply< Result, Template, P... >;

template< std::size_t >
using partial_partition_impl = partial_partition_impl_;

struct partial_partition_impl_
{
  template< std::size_t Size
          , template< class... > class Result
          , template< class... > class Template
          , class P0, class P1, class P2, class P3
          , class... P
          >
  using apply
    = partition< Size - unrolled_size
               , quote< Result, P0, P1, P2, P3 >::template apply
               , Template
               , P...
               >;
};

template< std::size_t Size
        , template< class... > class Template
        , class... P
        >
using partition_as
  = partition< Size, as_fn, result_of_as_impl_t, P... >;

} // namespace argot(::detail_as)

template< class... P >
using result_of_as
  = basic_result_of< as_t const&, P&&... >;

template< class... P >
using result_of_as_t
  = basic_result_of_t< as_t const&, P&&... >;
#endif
//->

} // namespace (argot::prov)

/*`
[table Explicit Template Parameters
 [[Parameter][Requirement][Description]]
 [[`class... AsP`]
  [Each type of `AsP...` is a ParameterType]
  [The type of each entity to be captured]
 ]
]

[table Function Parameters
 [[Parameter][Requirement][Description]]
 [[`P&&... args`]
  [Each type of `std::remove_cvref_t< P >...` is the same as the corresponding
   type of `std::remove_cvref_t< AsP >...`, and each type of `P...` is
   convertible to the corresponding type of `AsP...`]
  [The entities to be captured]
 ]
]

[provider_properties_heading]

[table Resultant Provider
 [[Property][Description]]
 [[Logical Provision]
  [A reference to each captured entity]
 ]
 [[Possible Argument Types of Destructive Provision]
  [[itemized_list [```( AsP&&... )```]]]
 ]
 [[Possible Argument Types of Persistent Provision]
  [[itemized_list [```( AsP const&... )```]]]
 ]
]
*/

//]

#endif  // ARGOT_PROV_AS_HPP_
