/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_FUT_AUGMENT_HPP_
#define ARGOT_FUT_AUGMENT_HPP_

#include <argot/concepts/decay_sinkable.hpp>
#include <argot/concepts/forgetful_thenable.hpp>
#include <argot/concepts/future.hpp>
#include <argot/concepts/intrinsic_persistent_thenable.hpp>
#include <argot/concepts/intrinsic_thenable.hpp>
#include <argot/concepts/persistent_forgetful_thenable.hpp>
#include <argot/concepts/persistent_future.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/sink.hpp>
#include <argot/executor/immediate.hpp>
#include <argot/gen/access_raw_concept_map.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/requires.hpp>
#include <argot/detail/move.hpp>
#include <argot/detail/forward.hpp>
#include <argot/fut_traits/value_type.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/detail/remove_cvref.hpp>

namespace argot {
namespace fut {
namespace augment_detail {

template< class Fut, class Augmentation >
struct impl
{
  // TODO(mattcalabrese) Concept assert
  ARGOT_CONCEPT_ASSERT( Future< Fut > );
  ARGOT_CONCEPT_ASSERT
  ( InvocableObjectWith< Augmentation, fut_traits::value_type_t< Fut > > );

  ARGOT_NO_UNIQUE_ADDRESS Fut fut;
  ARGOT_NO_UNIQUE_ADDRESS Augmentation augmentation;
};

template< class Augmentation, class Fun >
struct continuation
{
  template< class Value >
  constexpr decltype( auto ) operator ()( Value&& value ) &&
  {
    return ARGOT_MOVE( fun )
    ( argot_detail::constexpr_invoke
      ( ARGOT_MOVE( augmentation )
      , ARGOT_FORWARD( Value )( value )
      )
    );
  }

  ARGOT_NO_UNIQUE_ADDRESS Augmentation augmentation;
  ARGOT_NO_UNIQUE_ADDRESS Fun fun;
};

}  // namespace argot(::fut::augment_detail)

struct augment_t
{
  template< class Fut, class Augmentation
          , ARGOT_REQUIRES
            ( Future< Fut > )
            ( InvocableObjectWith  // TODO(mattcalabrese) Fix constraint
              < std::decay_t< Augmentation >
              , fut_traits::value_type_t< detail_argot::remove_cvref_t< Fut > >
              >
            )
            ( Sinkable< Fut&& > )
            ( DecaySinkable< Augmentation&& > )
            ()
          >
  [[nodiscard]]
  constexpr auto operator()( Fut&& fut, Augmentation&& augmentation ) const
  {
    return augment_detail::impl
    < detail_argot::remove_cvref_t< Fut >, std::decay_t< Augmentation > >
    { call_detail::forward_and_sink< Fut >( fut )
    , call_detail::forward_and_decay_sink< Augmentation >( augmentation )
    };
  }
} inline constexpr augment{};

// TODO(mattcalabrese) result calculators

}  // namespace argot(::fut)

template< class Fut, class Augmentation >
struct make_concept_map
< Future< fut::augment_detail::impl< Fut, Augmentation > > >
{
  // TODO(mattcalabrese) Fix argument type
  using value_type_t
    = argot_detail::result_of_constexpr_invoke_t
      < Augmentation&&, fut_traits::value_type_t< Fut > >;
};

template< class Fut, class Augmentation, class Exec >
struct make_concept_map
< ForgetfulThenable< fut::augment_detail::impl< Fut, Augmentation >, Exec >
, ARGOT_REQUIRES( ForgetfulThenable< Fut, Exec > )<>
>
{
  // TODO(mattcalabrese) Constrain
  template< class ExecP, class Fun >
  static constexpr void forgetful_then
  ( fut::augment_detail::impl< Fut, Augmentation >&& self
  , ExecP&& exec, Fun&& fun
  )
  {
    access_raw_concept_map< ForgetfulThenable< Fut, Exec > >::forgetful_then
    ( ARGOT_MOVE( self.fut )
    , ARGOT_FORWARD( ExecP )( exec )
    , fut::augment_detail::continuation
      < Augmentation, detail_argot::remove_cvref_t< Fun > >
      { ARGOT_MOVE( self.augmentation ), ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

template< class Fut, class Augmentation >
struct make_concept_map
< PersistentFuture< fut::augment_detail::impl< Fut, Augmentation > >
, ARGOT_REQUIRES( PersistentFuture< Fut > )<>
>
{
};

template< class Fut, class Augmentation, class Exec >
struct make_concept_map
< PersistentForgetfulThenable
  < fut::augment_detail::impl< Fut, Augmentation >, Exec >
, ARGOT_REQUIRES( PersistentForgetfulThenable< Fut, Exec > )<>
>
{
  template< class ExecP, class Fun >
  static constexpr void forgetful_then
  ( fut::augment_detail::impl< Fut, Augmentation > const& self
  , ExecP&& exec, Fun&& fun
  )
  {
    access_raw_concept_map< PersistentForgetfulThenable< Fut, Exec > >
    ::forgetful_then
    ( self.fut
    , ARGOT_FORWARD( ExecP )( exec )
    , fut::augment_detail::continuation
      < Augmentation, detail_argot::remove_cvref_t< Fun > >
      { ARGOT_MOVE( self.augmentation ), ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

template< class Fut, class Augmentation, class FPackager, class Exec >
struct make_concept_map
< IntrinsicThenable
  < fut::augment_detail::impl< Fut, Augmentation >, FPackager, Exec >
, ARGOT_REQUIRES( IntrinsicThenable< Fut, FPackager, Exec > )<>
>
{
  template< class ExecP, class Fun >
  static constexpr auto
  then( fut::augment_detail::impl< Fut, Augmentation >&& self
      , ExecP&& exec, Fun&& fun
      )
  {
    return access_raw_concept_map< IntrinsicThenable< Fut, FPackager, Exec > >
    ::then
    ( ARGOT_MOVE( self.fut )
    , ARGOT_FORWARD( ExecP )( exec )
    , fut::augment_detail::continuation
      < Augmentation, detail_argot::remove_cvref_t< Fun > >
      { ARGOT_MOVE( self.augmentation ), ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

template< class Fut, class Augmentation, class FPackager, class Exec >
struct make_concept_map
< IntrinsicPersistentThenable
  < fut::augment_detail::impl< Fut, Augmentation >, FPackager, Exec >
, ARGOT_REQUIRES( IntrinsicPersistentThenable< Fut, FPackager, Exec > )<>
>
{
  template< class ExecP, class Fun >
  static constexpr auto
  then( fut::augment_detail::impl< Fut, Augmentation > const& self
      , ExecP&& exec, Fun&& fun
      )
  {
    return access_raw_concept_map
    < IntrinsicPersistentThenable< Fut, FPackager, Exec > >::then
    ( self.fut
    , ARGOT_FORWARD( ExecP )( exec )
    , fut::augment_detail::continuation
      < Augmentation, detail_argot::remove_cvref_t< Fun > >
      { ARGOT_MOVE( self.augmentation ), ARGOT_FORWARD( Fun )( fun ) }
    );
  }
};

}  // namespace argot

#endif  // ARGOT_FUT_AUGMENT_HPP_
