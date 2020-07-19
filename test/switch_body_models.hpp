/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_SWITCH_BODY_MODELS_HPP_
#define ARGOT_TEST_SWITCH_BODY_MODELS_HPP_

#include <argot/case/case_range.hpp>
#include <argot/case/case_set.hpp>
#include <argot/case/detail/provided.hpp>
#include <argot/concepts/case_labels.hpp>
#include <argot/concepts/persistent_switch_body_case.hpp>
#include <argot/concepts/persistent_switch_body_default_for_type.hpp>
#include <argot/concepts/persistent_switch_body_for_type.hpp>
#include <argot/concepts/same_type.hpp>
#include <argot/concepts/same_value.hpp>
#include <argot/concepts/switch_body.hpp>
#include <argot/concepts/switch_body_case.hpp>
#include <argot/concepts/switch_body_default.hpp>
#include <argot/concepts/switch_body_default_for_type.hpp>
#include <argot/concepts/switch_body_for_type.hpp>
#include <argot/concepts/true.hpp>
#include <argot/discriminated_union.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/requires.hpp>
#include <argot/impossible.hpp>
#include <argot/prov/switch_/detail/config.hpp>
#include <argot/receiver_traits/argument_list_kinds.hpp>
#include <argot/receiver_traits/argument_types.hpp>
#include <argot/struct_.hpp>
#include <argot/value_list.hpp>
#include <argot/zipper.hpp>

#include <type_traits>
#include <utility>

namespace {

template< class Indices >
struct value_list_of_size_impl;

template< int... Indices >
struct value_list_of_size_impl< std::integer_sequence< int, Indices... > >
{
  using type = argot::value_list_t< Indices... >;
};

template< int Size >
using value_list_of_size_t
  = typename value_list_of_size_impl< std::make_integer_sequence< int, Size > >
    ::type;

template< template< auto... > class Template, class Indices >
struct expand_values_of_size_impl;

template< template< auto... > class Template, int... Indices >
struct expand_values_of_size_impl
< Template, std::integer_sequence< int, Indices... > >
{
  using type = Template< Indices... >;
};

template< template< auto... > class Template, int Size >
using expand_values_of_size_t
  = typename expand_values_of_size_impl
    < Template, std::make_integer_sequence< int, Size > >::type;

template< class Indices >
struct argument_types_of_size_impl;

template< int... Indices >
struct argument_types_of_size_impl< std::integer_sequence< int, Indices... > >
{
  using type
    = argot::receiver_traits::argument_list_kinds_t
      < argot::receiver_traits::argument_types_t
        < std::integral_constant< int, Indices >&& >...
      >;
};

template< int Size >
using argument_types_of_size_t
  = typename argument_types_of_size_impl
    < std::make_integer_sequence< int, Size > >::type;

template< class Indices >
struct variant_of_argument_references_of_size_impl;

template< int... Indices >
struct variant_of_argument_references_of_size_impl
< std::integer_sequence< int, Indices... > >
{
  using type
    = argot::discriminated_union
      < argot::struct_< std::integral_constant< int, Indices >&& >... >;
};

template< int Size >
using variant_of_argument_references_of_size_t
  = typename variant_of_argument_references_of_size_impl
    < std::make_integer_sequence< int, Size > >::type;

template< class Indices >
struct variant_of_argument_references_of_size_persistent_impl;

template< int... Indices >
struct variant_of_argument_references_of_size_persistent_impl
< std::integer_sequence< int, Indices... > >
{
  using type
    = argot::discriminated_union
      < argot::struct_< std::integral_constant< int, Indices > const& >... >;
};

template< int Size >
using variant_of_argument_references_of_size_persistent_t
  = typename variant_of_argument_references_of_size_persistent_impl
    < std::make_integer_sequence< int, Size > >::type;

template< class Indices >
struct argument_types_of_size_persistent_impl;

template< int... Indices >
struct argument_types_of_size_persistent_impl
< std::integer_sequence< int, Indices... > >
{
  using type
    = argot::receiver_traits::argument_list_kinds_t
      < argot::receiver_traits::argument_types_t
        < std::integral_constant< int, Indices > const& >...
      >;
};

template< int Size >
using argument_types_of_size_persistent_t
  = typename argument_types_of_size_persistent_impl
    < std::make_integer_sequence< int, Size > >::type;

template< int V >
std::integral_constant< int, V > integral_constant_v{};

struct body_value_default_t { int value; };
struct persistent_body_value_default_t { int value; };

struct body_no_cases {};
struct body_0_to_3 {};
struct body_3_to_8 {};
struct body_8_to_10 {};
struct body_default {};
struct body_unreachable_case_10 {};

struct body_0_to_max {};
struct body_0_to_supmax {};
struct body_0_to_2max {};
struct body_0_to_sup2max {};

}  // namespace

namespace argot {

template<>
struct make_concept_map< SwitchBody< body_no_cases > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t = value_list_t<>;

  template< template< auto... > class Template >
  using expand_case_values_t = Template<>;
};

template<>
struct make_concept_map< SwitchBody< body_0_to_3 > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t = value_list_t< 0, 1, 2 >;

  template< template< auto... > class Template >
  using expand_case_values_t = Template< 0, 1, 2 >;
};

template<>
struct make_concept_map< SwitchBody< body_3_to_8 > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t = value_list_t< 3, 4, 5, 6, 7 >;

  template< template< auto... > class Template >
  using expand_case_values_t = Template< 3, 4, 5, 6, 7 >;
};

template<>
struct make_concept_map< SwitchBody< body_8_to_10 > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t = value_list_t< 8, 9 >;

  template< template< auto... > class Template >
  using expand_case_values_t = Template< 8, 9 >;
};

template<>
struct make_concept_map< SwitchBody< body_default > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t = value_list_t<>;

  template< template< auto... > class Template >
  using expand_case_values_t = Template<>;
};

template<>
struct make_concept_map< SwitchBody< body_unreachable_case_10 > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t = value_list_t< 10 >;

  template< template< auto... > class Template >
  using expand_case_values_t = Template< 10 >;
};

template<>
struct make_concept_map< SwitchBody< body_0_to_max > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t
    = value_list_of_size_t< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >;

  template< template< auto... > class Template >
  using expand_case_values_t
    = expand_values_of_size_t< Template, ARGOT_MAX_PREPROCESSED_SWITCH_CASES >;
};

template<>
struct make_concept_map< SwitchBody< body_0_to_supmax > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t
    = value_list_of_size_t< ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >;

  template< template< auto... > class Template >
  using expand_case_values_t
    = expand_values_of_size_t
      < Template, ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1>;
};

template<>
struct make_concept_map< SwitchBody< body_0_to_2max > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t
    = value_list_of_size_t< ARGOT_MAX_PREPROCESSED_SWITCH_CASES * 2 >;

  template< template< auto... > class Template >
  using expand_case_values_t
    = expand_values_of_size_t
      < Template, ARGOT_MAX_PREPROCESSED_SWITCH_CASES * 2 >;
};

template<>
struct make_concept_map< SwitchBody< body_0_to_sup2max > >
{
  // TODO(mattcalabrese) Remove
  using case_values_t
    = value_list_of_size_t< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >;

  template< template< auto... > class Template >
  using expand_case_values_t
    = expand_values_of_size_t
      < Template, 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1>;
};

template<>
struct make_concept_map< SwitchBodyCase< body_0_to_3, 0 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 1 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 2 >&& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_3&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 0 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_0_to_3, 0 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 1 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 2 > const& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_3 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 0 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_0_to_3, 1 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 0 >&& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 2 >&& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_3&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::move( integral_constant_v< 1 > )
    );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_0_to_3, 1 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 0 > const& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 2 > const& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_3 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 1 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_0_to_3, 2 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 0 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 1 >&& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_3&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 2 > ) );
  }
};

template<>
struct make_concept_map
< PersistentSwitchBodyCase< body_0_to_3, 2 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 0 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 1 > const& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_3 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 2 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_3_to_8, 3 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 4 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 5 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 6 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 7 >&& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 3 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_3_to_8, 3 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 4 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 5 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 6 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 7 > const& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 3 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_3_to_8, 4 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 >&& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 5 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 6 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 7 >&& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 4 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_3_to_8, 4 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 > const& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 5 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 6 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 7 > const& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 4 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_3_to_8, 5 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 4 >&& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 6 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 7 >&& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 5 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_3_to_8, 5 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 4 > const& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 6 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 7 > const& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 5 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_3_to_8, 6 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 4 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 5 >&& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 7 >&& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 6 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_3_to_8, 6 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 4 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 5 > const& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 7 > const& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 6 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_3_to_8, 7 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 4 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 5 >&& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 6 >&& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 7 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_3_to_8, 7 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 3 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 4 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 5 > const& >
      , receiver_traits::argument_types_t
        < std::integral_constant< int, 6 > const& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_3_to_8 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 7 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_8_to_10, 8 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 9 >&& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_8_to_10&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 8 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_8_to_10, 8 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 9 > const& >
      >;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_8_to_10 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 8 > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyCase< body_8_to_10, 9 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 8 >&& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_8_to_10&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), std::move( integral_constant_v< 9 > ) );
  }
};

template<>
struct make_concept_map< PersistentSwitchBodyCase< body_8_to_10, 9 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t
      < receiver_traits::argument_types_t
        < std::integral_constant< int, 8 > const& >
      >;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_8_to_10 const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< 9 > )
    );
  }
};

template<>
struct make_concept_map
< SwitchBodyCase< body_unreachable_case_10, 10 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static impossible
  provide_isolated_case( body_unreachable_case_10&&, Receiver&& rec )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template<>
struct make_concept_map
< PersistentSwitchBodyCase< body_unreachable_case_10, 10 > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static impossible
  provide_isolated_case( body_unreachable_case_10 const&, Receiver&& rec )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }
};

template< int Value >
struct make_concept_map
< SwitchBodyCase< body_0_to_max, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value < ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_max&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::move( integral_constant_v< Value > )
    );
  }
};

template< int Value >
struct make_concept_map
< PersistentSwitchBodyCase< body_0_to_max, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value < ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_max const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< Value > )
    );
  }
};

template< int Value >
struct make_concept_map
< SwitchBodyCase< body_0_to_supmax, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value <= ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_supmax&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::move( integral_constant_v< Value > )
    );
  }
};

template< int Value >
struct make_concept_map
< PersistentSwitchBodyCase< body_0_to_supmax, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value <= ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_supmax const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< Value > )
    );
  }
};

template< int Value >
struct make_concept_map
< SwitchBodyCase< body_0_to_2max, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_2max&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::move( integral_constant_v< Value > )
    );
  }
};

template< int Value >
struct make_concept_map
< PersistentSwitchBodyCase< body_0_to_2max, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_2max const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< Value > )
    );
  }
};

template< int Value >
struct make_concept_map
< SwitchBodyCase< body_0_to_sup2max, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value <= 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_t< 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_sup2max&&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::move( integral_constant_v< Value > )
    );
  }
};

template< int Value >
struct make_concept_map
< PersistentSwitchBodyCase< body_0_to_sup2max, Value >
, ARGOT_REQUIRES
  ( argot::True
    < ( Value >= 0 && Value <= 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES ) >
  )
  <>
>
{
  using leading_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::leading_t;

  using trailing_argument_list_kinds_t
    = typename argot::zipper_at_t
      < argument_types_of_size_persistent_t
        < 2 * ARGOT_MAX_PREPROCESSED_SWITCH_CASES + 1 >
      , Value
      >::trailing_t;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_case( body_0_to_sup2max const&, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , std::as_const( integral_constant_v< Value > )
    );
  }
};

template<>
struct make_concept_map< SwitchBodyDefault< body_default > > {};

template<>
struct make_concept_map< SwitchBodyDefaultForType< body_default, int > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_default( body_default&&, int value, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec ), body_value_default_t{ value } );
  }
};

template<>
struct make_concept_map
< PersistentSwitchBodyDefaultForType< body_default, int > >
{
  using leading_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  using trailing_argument_list_kinds_t
    = receiver_traits::argument_list_kinds_t<>;

  // TODO(mattcalabrese) Constrain
  template< class Receiver >
  static constexpr decltype( auto )
  provide_isolated_default( body_default const&, int value, Receiver&& rec )
  {
    return receiver_traits::receive
    ( std::forward< Receiver >( rec )
    , persistent_body_value_default_t{ value }
    );
  }
};

ARGOT_CONCEPT_ENSURE( SwitchBody< body_0_to_3 > );
ARGOT_CONCEPT_ENSURE( SwitchBody< body_3_to_8 > );
ARGOT_CONCEPT_ENSURE( SwitchBody< body_8_to_10 > );
ARGOT_CONCEPT_ENSURE( SwitchBody< body_default > );

ARGOT_CONCEPT_ENSURE( SwitchBodyDefault< body_default > );
ARGOT_CONCEPT_ENSURE( SwitchBodyDefaultForType< body_default, int > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyDefaultForType< body_default, int > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyDefaultForType< body_default, long > > );

ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_0_to_3, -1 > > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_0_to_3, 0 > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_0_to_3, 1 > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_0_to_3, 2 > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_0_to_3, 3 > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_3_to_8, 2 > > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_3_to_8, 3 > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_3_to_8, 4 > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_3_to_8, 5 > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_3_to_8, 6 > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_3_to_8, 7 > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_3_to_8, 8 > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_8_to_10, 7 > > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_8_to_10, 8 > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_8_to_10, 9 > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_8_to_10, 10 > > );
ARGOT_CONCEPT_ENSURE( SwitchBodyCase< body_unreachable_case_10, 10 > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_unreachable_case_10, 11 > > );

ARGOT_CONCEPT_ENSURE( Not< PersistentSwitchBodyCase< body_0_to_3, -1 > > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_0_to_3, 0 > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_0_to_3, 1 > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_0_to_3, 2 > );
ARGOT_CONCEPT_ENSURE( Not< PersistentSwitchBodyCase< body_0_to_3, 3 > > );
ARGOT_CONCEPT_ENSURE( Not< PersistentSwitchBodyCase< body_3_to_8, 2 > > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_3_to_8, 3 > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_3_to_8, 4 > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_3_to_8, 5 > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_3_to_8, 6 > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_3_to_8, 7 > );
ARGOT_CONCEPT_ENSURE( Not< PersistentSwitchBodyCase< body_3_to_8, 8 > > );
ARGOT_CONCEPT_ENSURE( Not< PersistentSwitchBodyCase< body_8_to_10, 7 > > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_8_to_10, 8 > );
ARGOT_CONCEPT_ENSURE( PersistentSwitchBodyCase< body_8_to_10, 9 > );
ARGOT_CONCEPT_ENSURE( Not< PersistentSwitchBodyCase< body_8_to_10, 10 > > );
ARGOT_CONCEPT_ENSURE
( PersistentSwitchBodyCase< body_unreachable_case_10, 10 > );
ARGOT_CONCEPT_ENSURE
( Not< PersistentSwitchBodyCase< body_unreachable_case_10, 11 > > );

ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_0_to_3, 0l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_0_to_3, 1l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_0_to_3, 2l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_3_to_8, 3l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_3_to_8, 4l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_3_to_8, 5l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_3_to_8, 6l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_3_to_8, 7l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_8_to_10, 8l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_8_to_10, 9l > > );
ARGOT_CONCEPT_ENSURE( Not< SwitchBodyCase< body_unreachable_case_10, 10l > > );

}  // namespace argot

#endif  // ARGOT_TEST_SWITCH_BODY_MODELS_HPP_
