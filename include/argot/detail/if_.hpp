/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_IF_HPP_
#define ARGOT_DETAIL_IF_HPP_

namespace argot {
namespace detail_if_ {

template< bool C >
struct if_;

template<>
struct if_< true >
{
  struct and_
  {
    template< bool C >
    using _ = if_< C >;
  };

  struct and_apply
  {
    template< template< class... > class Metafunction, class... P >
    using _ = if_< Metafunction< P... >::value >;
  };

  struct or_
  {
    template< bool /*C*/ >
    using _ = if_;
  };

  struct or_apply
  {
    template< template< class... > class /*Metafunction*/, class... /*P*/ >
    using _ = if_;
  };

  struct then
  {
    template< class T >
    using _ = T;
  };

  struct then_apply
  {
    template< template< class... > class Metafunction, class... P >
    using _ = Metafunction< P... >;
  };

  struct then_else
  {
    template< class T, class /*F*/ >
    using _ = T;
  };

  struct then_apply_else
  {
    template< template< class... > class Metafunction, class /*F*/, class... P >
    using _ = Metafunction< P... >;
  };

  struct then_else_apply
  {
    template< class T, template< class... > class /*Metafunction*/
            , class... /*P*/
            >
    using _ = T;
  };

  struct then_else_apply_values
  {
    template< class T, template< auto... > class /*Metafunction*/
            , auto... /*N*/
            >
    using _ = T;
  };

  struct then_apply_else_apply
  {
    template< template< class... > class TMetafunction
            , template< class... > class /*FMetafunction*/, class... P
            >
    using _ = TMetafunction< P... >;
  };
};

template<>
struct if_< false >
{
  struct and_
  {
    template< bool /*C*/ >
    using _ = if_;
  };

  struct and_apply
  {
    template< template< class... > class /*Metafunction*/, class... /*P*/ >
    using _ = if_;
  };

  struct or_
  {
    template< bool C >
    using _ = if_< C >;;
  };

  struct or_apply
  {
    template< template< class... > class Metafunction, class... P >
    using _ = if_< Metafunction< P... >::value >;
  };

  struct else_
  {
    template< class T >
    using _ = T;
  };

  struct else_apply
  {
    template< template< class... > class Metafunction, class... P >
    using _ = Metafunction< P... >;
  };

  struct then_else
  {
    template< class /*T*/, class F >
    using _ = F;
  };

  struct then_apply_else
  {
    template< template< class... > class /*Metafunction*/, class F
            , class... /*P*/
            >
    using _ = F;
  };

  struct then_else_apply
  {
    template< class /*T*/, template< class... > class Metafunction, class... P >
    using _ = Metafunction< P... >;
  };

  struct then_else_apply_values
  {
    template< class /*T*/, template< auto... > class Metafunction
            , auto... V
            >
    using _ = Metafunction< V... >;
  };

  struct then_apply_else_apply
  {
    template< template< class... > class /*TMetafunction*/
            , template< class... > class FMetafunction, class... P
            >
    using _ = FMetafunction< P... >;
  };
};

template< bool C >
struct succeed_if;

template<>
struct succeed_if< true >
{
  using nullptr_t = decltype( nullptr );

  struct and_
  {
    template< bool C >
    using _ = succeed_if< C >;
  };

  struct and_apply
  {
    template< template< class... > class Metafunction, class... P >
    using _ = succeed_if< Metafunction< P... >::value >;
  };

  struct or_
  {
    template< bool /*C*/ >
    using _ = succeed_if;
  };

  struct or_apply
  {
    template< template< class... > class /*Metafunction*/, class... /*P*/ >
    using _ = succeed_if;
  };

  struct result
  {
    template< class T >
    using _ = T;
  };

  struct result_apply
  {
    template< template< class... > class Metafunction, class... P >
    using _ = Metafunction< P... >;
  };
};

template<>
struct succeed_if< false >
{
  struct or_
  {
    template< bool C >
    using _ = succeed_if< C >;;
  };

  struct or_apply
  {
    template< template< class... > class Metafunction, class... P >
    using _ = succeed_if< Metafunction< P... >::value >;
  };
};

} // namespace argot::detail_if_
} // namespace argot

#endif  // ARGOT_DETAIL_IF_HPP_
