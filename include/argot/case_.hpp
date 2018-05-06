/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CASE_HPP_
#define ARGOT_CASE_HPP_

#include <argot/case/case_.hpp>
#include <argot/case/case_range.hpp>
#include <argot/case/case_set.hpp>
//#include <argot/case/disjoint_case_range.hpp>
//#include <argot/case/disjoint_case_set.hpp>

// TODO(mattcalabrese)
//   Allow the argument provider generator to generate references to argument
//   providers.
#if 0
namespace argot {
namespace case_detail {

template< class Values >
struct values_to_integral_constant_argument_list_kinds;

template< auto... Values >
struct values_to_integral_constant_argument_list_kinds
< value_list_t< Values... > >
{
  using type
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < call_detail::constant< Values > >...
      >;
};

template< class Values >
using values_to_integral_constant_argument_list_kinds_t
  = typename values_to_integral_constant_argument_list_kinds< Values >::type;

template< class Values, class Generator >
struct values_to_destructive_generated_argument_list_kinds;

template< auto... Values, class Generator >
struct values_to_destructive_generated_argument_list_kinds
< value_list_t< Values... >, Generator >
{
  using type
    = call_detail::concatenate_t
      < prov_traits::argument_list_kinds_of_destructive_t
        < std::invoke_result_t
          < Generator&&
          , call_detail::constant< Values >&&
          >
        >...
      >;
};

template< class Values, class Generator >
using values_to_destructive_generated_argument_list_kinds_t
  = typename values_to_destructive_generated_argument_list_kinds
    < Values, Generator >::type;

template< class Values, class Generator >
struct values_to_persistent_generated_argument_list_kinds;

template< auto... Values, class Generator >
struct values_to_persistent_generated_argument_list_kinds
< value_list_t< Values... >, Generator >
{
  using type
    = call_detail::concatenate_t
      < prov_traits::argument_list_kinds_of_destructive_t
        < std::invoke_result_t
          < Generator const&
          , call_detail::constant< Values >&&
          >
        >...
      >;
};

template< class Values, class Generator >
using values_to_persistent_generated_argument_list_kinds_t
  = typename values_to_persistent_generated_argument_list_kinds
    < Values, Generator >::type;

}  // namespace argot(::case_detail)

// TODO(mattcalabrese) Make constructors.
template< class Values, class Provider >
struct bound_case;

template< auto... Values, class Provider >
struct bound_case< value_list_t< Values... >, Provider >
{
  ARGOT_CONCEPT_ASSERT( ArgumentProvider< Provider > );

  // TODO(mattcalabrese) Assert valid values

  using provider_type = Provider;

  provider_type provider;
};

template< class Values, class Generator >
struct bound_generator_case;

template< auto... Values, class Generator >
struct bound_generator_case
< value_list_t< Values... >, Generator >
{
  Generator generator;
};

template< auto... Values >
struct bound_to_constant_case {};

template< auto... Values >
struct unreachable_case_t {};

// TODO(mattcalabrese) Verify that they are valid case values
template< auto... Values >
unreachable_case_t< Values... > constexpr unreachable_case{};

// TODO(mattcalabrese) Only enable if no duplicate cases
template< auto... Values >
struct case_t
{
  // TODO(mattcalabrese) Make disjoint form of what operator() does.
  // TODO(mattcalabrese) Make a version of the generator that doesn't take a
  //                     std::integral_constant (and makes a single branch).

  template< class Provider >
  constexpr ARGOT_REQUIRES
  ( ArgumentProvider< remove_cvref_t< Provider > > )
  ( Sinkable< Provider&& > )
  < bound_case
    < value_list_t< Values... >
    , remove_cvref_t< Provider >
    >
  >
  operator ()( Provider&& provider ) const
  {
    return
    { ARGOT_FORWARD( Provider )( provider ) };
  }

  static constexpr unreachable_case_t< Values... > unreachable() noexcept
  {
    return {};
  }

  // TODO(mattcalabrese) Constrain
  template< class Generator >
  static constexpr bound_generator_case
  < value_list_t< Values... >, remove_cvref_t< Generator > >
  generate_from_constant( Generator&& generator )
  {
    return
    { call_detail::sink( ARGOT_FORWARD( Generator )( generator ) ) };
  }

  static constexpr bound_to_constant_case< Values... > to_constant() noexcept
  {
    return {};
  }
};

// TODO(mattcalabrese) Constrain to no duplicate cases
template< auto... Values >
case_t< Values... > constexpr case_{};

template< class Provider, auto... Values >
using result_of_case_t
  = basic_result_of_t< case_t< Values... > const&, Provider&& >;

template< class Provider, auto... Values >
using result_of_case
  = basic_result_of< case_t< Values... > const&, Provider&& >;

template< auto... Values >
using result_of_case_to_constant_t
  = decltype( case_< Values... >.to_constant() );

template< auto... Values, class Generator >
struct make_concept_map
< SwitchBody< bound_generator_case< value_list_t< Values... >, Generator > > >
{
  using case_values_t = value_list_t< Values... >;
};

// TODO(mattcalabrese) Constrain callability
template< auto... Values, class Generator, auto Value >
struct make_concept_map
< SwitchBodyCase
  < bound_generator_case< value_list_t< Values... >, Generator >, Value >
, ARGOT_REQUIRES
  ( True
    < value_zipper_contains_v
      < value_list_t< static_cast< decltype( Value ) >( Values )... >
      , Value
      >
    >
  )
  <>
>
{
 private:
  using typed_value_list
    = value_list_t< static_cast< decltype( Value ) >( Values )... >;

  using partition = value_zipper_find_t< typed_value_list, Value >;
 public:
  using leading_argument_list_kinds_t
    = case_detail::values_to_destructive_generated_argument_list_kinds_t
      < typed_value_list, typename partition::leading_t >;

  using trailing_argument_list_kinds_t
    = case_detail::values_to_destructive_generated_argument_list_kinds_t
      < typed_value_list, typename partition::trailing_t >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case
  ( bound_generator_case< value_list_t< Values... >, Generator >&& self
  , Receiver&& rec
  )
  {
    // TODO(mattcalabrese) Use constexpr_invoke on the generator
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.generator )
      ( std::integral_constant< remove_cvref_t< decltype( Value ) >, Value >() )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

// TODO(mattcalabrese) Constrain
template< auto... Values, class Generator, auto Value >
struct make_concept_map
< PersistentSwitchBodyCase
  < bound_generator_case< value_list_t< Values... >, Generator >, Value >
>
{
 private:
  using typed_value_list
    = value_list_t< static_cast< decltype( Value ) >( Values )... >;

  using partition = value_zipper_find_t< typed_value_list, Value >;
 public:
  using leading_argument_list_kinds_t
    = case_detail::values_to_persistent_generated_argument_list_kinds_t
      < typed_value_list, typename partition::leading_t >;

  using trailing_argument_list_kinds_t
    = case_detail::values_to_persistent_generated_argument_list_kinds_t
      < typed_value_list, typename partition::trailing_t >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case
  ( bound_generator_case< value_list_t< Values... >, Generator >&& self
  , Receiver&& rec
  )
  {
    // TODO(mattcalabrese) Use constexpr_invoke on the generator
    return prov_traits::persistent_provide
    ( self.generator
      ( std::integral_constant< remove_cvref_t< decltype( Value ) >, Value >() )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

template< auto... Values >
struct make_concept_map< SwitchBody< bound_to_constant_case< Values... > > >
{
  using case_values_t = value_list_t< Values... >;
};

// TODO(mattcalabrese) Constrain
template< auto... Values, auto Value >
struct make_concept_map
< SwitchBodyCase< bound_to_constant_case< Values... >, Value >
, ARGOT_REQUIRES
  ( True
    < value_zipper_contains_v
      < value_list_t< static_cast< decltype( Value ) >( Values )... >
      , Value
      >
    >
  )
  <>
>
{
 private:
  using typed_value_list
    = value_list_t< static_cast< decltype( Value ) >( Values )... >;

  using partition = value_zipper_find_t< typed_value_list, Value >;
 public:
  using leading_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::leading_t >;

  using trailing_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::trailing_t >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_case
  ( bound_to_constant_case< Values... > self, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::integral_constant< remove_cvref_t< decltype( Value ) >, Value >() );
  }
};

// TODO(mattcalabrese) Constrain
template< auto... Values, auto Value >
struct make_concept_map
< PersistentSwitchBodyCase
  < bound_to_constant_case< Values... >, Value >
>
{
 private:
  using typed_value_list
    = value_list_t< static_cast< decltype( Value ) >( Values )... >;

  using partition = value_zipper_find_t< typed_value_list, Value >;
 public:
  using leading_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::leading_t >;

  using trailing_argument_list_kinds_t
    = case_detail::values_to_integral_constant_argument_list_kinds_t
      < typename partition::trailing_t >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto ) provide_isolated_case
  ( bound_to_constant_case< Values... > self, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::integral_constant< remove_cvref_t< decltype( Value ) >, Value >() );
  }
};

template< auto... Values, class Provider >
struct make_concept_map
< SwitchBody< bound_case< value_list_t< Values... >, Provider > > >
{
  using case_values_t = value_list_t< Values... >;
};

// TODO(mattcalabrese) Constrain
template< auto... Values, class Provider, auto Value >
struct make_concept_map
< SwitchBodyCase
  < bound_case< value_list_t< Values... >, Provider >, Value >
, ARGOT_REQUIRES
  ( True
    < value_zipper_contains_v
      < value_list_t< static_cast< decltype( Value ) >( Values )... >
      , Value
      >
    >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using bound_case
    = argot::bound_case< value_list_t< Values... >, Provider >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( bound_case&& self, Receiver&& rec )
  {
    return prov_traits::destructive_provide
    ( ARGOT_MOVE( self.provider )
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};

// TODO(mattcalabrese) Constrain
template< auto... Values, class Provider, auto Value >
struct make_concept_map
< PersistentSwitchBodyCase
  < bound_case< value_list_t< Values... >, Provider >, Value >
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using bound_case
    = argot::bound_case< value_list_t< Values... >, Provider >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( bound_case const& self, Receiver&& rec )
  {
    return prov_traits::persistent_provide
    ( self.provider
    , ARGOT_FORWARD( Receiver )( rec )
    );
  }
};


template< auto... Values >
struct make_concept_map< SwitchBody< unreachable_case_t< Values... > > >
{
  using case_values_t = value_list_t< Values... >;
};

// TODO(mattcalabrese) Constrain
template< auto... Values, auto Value >
struct make_concept_map
< SwitchBodyCase< unreachable_case_t< Values... >, Value >
, ARGOT_REQUIRES
  ( True
    < value_zipper_contains_v
      < value_list_t< static_cast< decltype( Value ) >( Values )... >
      , Value
      >
    >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain and possibly push unreachable into default argument
  template< class Receiver >
  static impossible
  provide_isolated_case( unreachable_case_t< Values... > self, Receiver&& rec )
  noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

// TODO(mattcalabrese) Constrain
template< auto... Values, auto Value >
struct make_concept_map
< PersistentSwitchBodyCase
  < unreachable_case_t< Values... >, Value >
>
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain and possibly push unreachable into default argument
  template< class Receiver >
  static impossible
  provide_isolated_case( unreachable_case_t< Values... > self, Receiver&& rec )
  noexcept
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

}  // namespace argot
#endif
#endif  // ARGOT_CASE_HPP_
