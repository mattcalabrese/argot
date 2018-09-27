/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_GEN_REQUIRES_HPP_
#define ARGOT_GEN_REQUIRES_HPP_

//[description
/*`
ARGOT_REQUIRES is a macro that can be used to enable and disable templates via
substitution failures as based on one or more /gen concepts/, or produce a hard
error when expanded elsewhere. 
*/
//]

#include <argot/gen/is_auto_concept.hpp>
#include <argot/gen/is_modeled.hpp>
#include <argot/gen/requires/detail/macro_backend.hpp>
#include <argot/gen/transparent_requirement.hpp>

#ifndef ARGOT_GENERATE_PREPROCESSED_CONCEPTS

#include <argot/detail/conditional.hpp>
#include <argot/detail/identity.hpp>

#include <type_traits>

#endif

namespace argot {

template< class T >
struct Type;

template< class ConceptSpec >
struct FAILED_BECAUSE_THE_FOLLOWING_CONCEPT_IS_NOT_MODELED;

namespace requires_detail {

template< class... ConceptSpec >
struct requires_impl { using type = Type< void >; };

template< bool ConceptIsModeled >
struct requirement_checker_base
{
  template< class... ConceptSpecs >
  using and_
    = FAILED_BECAUSE_THE_FOLLOWING_CONCEPT_IS_NOT_MODELED
      < typename requires_impl< ConceptSpecs... >::type >;

  template< class U = void >
  using result = U;

  template< class U = void >
  using ARGOT_RESULT = U;

  template< class U = void >
  using ARGOT_RESULT_ = U;
};

template<>
struct requirement_checker_base< /*ConceptIsModeled =*/ false > {};

template< class... T >
struct with_trailing_requirements
{
  template< class... ConceptSpecs >
  using apply = requires_impl< ConceptSpecs..., T... >;
};

template< class H, class... T >
struct requires_impl< TransparentRequirement< H >, T... >
  : H::template expand_requirements
    < with_trailing_requirements< T... >::template apply > {};

template< class ConceptSpec >
struct failed_explicit_concept
{
  using type = ConceptSpec;
};

template< class ConceptSpec >
struct failed_auto_concept
{
  using type = typename ConceptSpec::requirements;
};

// TODO(mattcalabrese) Avoid identity declaration instantiation.
template< class H, class... T >
struct requires_impl< H, T... >
  : argot_detail::conditional< is_modeled_v< H > >::template half_meta_apply
    < requires_impl
    , typename argot_detail::conditional< is_auto_concept_v< H > >
      ::template meta_apply< failed_auto_concept, failed_explicit_concept, H >
    , T...
    > {};

struct empty {};

} // namespace argot(::requires_detail)

// TODO(mattcalabrese)
//   Branch based on if it's a Not requirements so that we can produce and error
//   that does not contain a double negative.
// TODO(mattcalabrese)
//   Recurse so that the lowest-level failure is reported.
template< class ConceptSpec >
struct FAILED_BECAUSE_THE_FOLLOWING_CONCEPT_IS_NOT_MODELED
  : requires_detail::requirement_checker_base< is_modeled_v< ConceptSpec > >
  , argot_detail::conditional< is_modeled_v< ConceptSpec > >
    ::template half_meta_apply
    < argot_detail::identity, requires_detail::empty
    , FAILED_BECAUSE_THE_FOLLOWING_CONCEPT_IS_NOT_MODELED< ConceptSpec >
    > {};

template< class... ConceptSpecs >
using requires_
  = FAILED_BECAUSE_THE_FOLLOWING_CONCEPT_IS_NOT_MODELED
    < typename requires_detail::requires_impl< ConceptSpecs... >::type >;

} // namespace argot

#define ARGOT_REQUIRES( ... )                                                  \
typename ::argot::requires_< __VA_ARGS__ >::_::template ARGOT_RESULT

#include <argot/gen/type.hpp>

//[docs
/*`
[synopsis_heading]

```
``#define ARGOT_REQUIRES( ... ) [unspecified_expansion]``
```
*/
//]

#endif  // ARGOT_GEN_REQUIRES_HPP_
