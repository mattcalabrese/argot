/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_DYNAMIC_CAST_HPP_
#define ARGOT_PROV_DYNAMIC_CAST_HPP_

#include <argot/declval.hpp>
#include <argot/detail/give_qualifiers_to.hpp>
#include <argot/detail/unreachable.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/value_of.hpp>
#include <argot/receiver_traits/partitioned_provider_types.hpp>
#include <argot/type_list.hpp>
#include <argot/remove_cvref.hpp>

#include <memory>
#include <type_traits>
#include <utility>

namespace argot {
namespace prov {
namespace dynamic_cast_detail {

template< class Target, class Source >
using dynamic_cast_fnype_t
  = decltype( dynamic_cast< Target* >( ARGOT_DECLVAL( Source* ) ) );

template< class Target, class Source >
using can_dynamic_cast
  = call_detail::is_detected< dynamic_cast_fnype_t, Target, Source >;

template< class Target, class Source >
bool constexpr can_dynamic_cast_v
  = call_detail::is_detected_v< dynamic_cast_fnype_t, Target, Source >;

template< class T, class... PossibleChildren >
struct dynamic_cast_shared_ptr_impl
{
  std::shared_ptr< T > ptr;
};

template< class T, class... PossibleChildren >
struct dynamic_cast_ptr_impl
{
  T* ptr;
};

template< class T, class... PossibleChildren >
struct dynamic_cast_ref_impl
{
  std::remove_reference_t< T >* ptr;
};

}  // namespace argot::prov::dynamic_cast_detail

template< class PossibleChildrenList >
struct dynamic_cast_fn;

template< class... PossibleChildren >
struct dynamic_cast_fn< type_list< PossibleChildren... > >
{
  static_assert
  ( (    (    is_unqualified_v< PossibleChildren >
           && std::is_polymorphic< PossibleChildren >::value
         )
      && ...
    )
  , "Type arguments to prov::dynamic_cast_ must all be "
    "unqualified, polymorphic types."
  );
 private:
  struct shared_ptr_cast
  {
    // TODO(mattcalabrese) Don't allow volatile shared_ptr
    template< class PolymorphicSharedPtr >
    static constexpr std::enable_if_t
    < (    dynamic_cast_detail::can_dynamic_cast_v
           < PossibleChildren
           , std::remove_cv_t
             < typename std::remove_reference_t< PolymorphicSharedPtr >
               ::element_type
             >
           >
        && ...
      )
    , dynamic_cast_detail::dynamic_cast_shared_ptr_impl
      < typename std::remove_reference_t< PolymorphicSharedPtr >::element_type
      , PossibleChildren...
      >
    >
    run( PolymorphicSharedPtr&& obj )
    {
      return { obj };
    }
  };

  struct ptr_cast
  {
    template< class PolymorphicType >
    static constexpr std::enable_if_t
    < (    dynamic_cast_detail::can_dynamic_cast_v
           < PossibleChildren, remove_cvref_t< PolymorphicType > >
        && ...
      )
    , dynamic_cast_detail::dynamic_cast_ptr_impl
      < PolymorphicType, PossibleChildren... >
    >
    run( PolymorphicType* obj )
    {
      return { obj };
    }
  };

  struct ref_cast
  {
    template< class PolymorphicType >
    static constexpr std::enable_if_t
    < (    dynamic_cast_detail::can_dynamic_cast_v
           < PossibleChildren, remove_cvref_t< PolymorphicType > >
        && ...
      )
    , dynamic_cast_detail::dynamic_cast_ref_impl
      < PolymorphicType, PossibleChildren... >
    >
    run( PolymorphicType&& obj )
    {
      return { std::addressof( obj ) };
    }
  };

  template< class UnqualifiedT >
  struct cast_kind_impl
  {
    using type = ref_cast;
  };

  template< class UnqualifiedT >
  struct cast_kind_impl< UnqualifiedT* >
  {
    using type = ptr_cast;
  };

  template< class T >
  struct cast_kind_impl< std::shared_ptr< T > >
  {
    using type = shared_ptr_cast;
  };

  template< class T >
  using cast_kind_t
    = typename cast_kind_impl< T >::type;

  template< class T >
  using result_of_run_t
    = decltype( cast_kind_t< remove_cvref_t< T > >::run( ARGOT_DECLVAL( T ) ) );

 public:
  template< class PolymorphicType >
  [[nodiscard]]
  constexpr result_of_run_t< PolymorphicType >
  operator ()( PolymorphicType&& obj ) const
  {
    return cast_kind_t< remove_cvref_t< PolymorphicType > >::run
    ( std::forward< PolymorphicType >( obj ) );
  }
};

template< class PossibleChildrenList >
inline dynamic_cast_fn< PossibleChildrenList > constexpr dynamic_cast_{};

template< class PossibleChildrenList, class T >
using result_of_dynamic_cast_
  = std::invoke_result< dynamic_cast_fn< PossibleChildrenList > const&, T >;

template< class PossibleChildrenList, class T >
using result_of_dynamic_cast_t
  = std::invoke_result_t< dynamic_cast_fn< PossibleChildrenList > const&, T >;

}  // namespace argot::prov

template< class T, class... PossibleChildren >
struct make_concept_map
< ArgumentProvider
  < prov::dynamic_cast_detail::dynamic_cast_ref_impl
    < T, PossibleChildren... >
  >
>
{
 private:
  using self_t
    = prov::dynamic_cast_detail::dynamic_cast_ref_impl
      < T, PossibleChildren... >;

  using prov_types
    = receiver_traits::provider_types_t
      < prov::result_of_reference_to_t
        < call_detail::give_qualifiers_to_t< T&&, PossibleChildren >
        >...
      >;

  template< class Receiver >
  using result_type_t
    = receiver_traits::result_of_branch_t< Receiver, prov_types >;

  using partition = receiver_traits::partition_begin_t< prov_types >;

  template< class Partition, int Dummy = 0, class Receiver >
  static constexpr result_type_t< Receiver >
  provide_impl( self_t self, Receiver&& receiver )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  template< class Partition, class HeadChild, class... TailChildren
          , class Receiver
          >
  static constexpr result_type_t< Receiver >
  provide_impl( self_t self, Receiver&& receiver )
  {
    using reference_result_t
      = call_detail::give_qualifiers_to_t< T&&, HeadChild >;

    using cast_target
      = std::remove_reference_t< reference_result_t >*;

    if( auto* const ptr = dynamic_cast< cast_target >( self.ptr ) )
    {
      return receiver_traits::branch
      ( std::forward< Receiver >( receiver )
      , partition::head_provider_types
      , prov::reference_to( static_cast< reference_result_t >( *ptr ) )
      , partition::tail_provider_types
      );
    }
    else
    {
      return provide_impl< receiver_traits::partition_next_t< Partition >, TailChildren... >
      ( self, std::forward< Receiver >( receiver ) );
    }

    // Do default behavior
  }
 public:
  template< class Receiver >
  static constexpr result_type_t< Receiver >
  provide( self_t self, Receiver&& receiver )
  {
    return provide_impl< partition, PossibleChildren... >
    ( self, std::forward< Receiver >( receiver ) );
  }
};

template< class T, class... PossibleChildren >
struct make_concept_map
< ArgumentProvider
  < prov::dynamic_cast_detail::dynamic_cast_ptr_impl
    < T, PossibleChildren... >
  >
>
{
 private:
  using self_t
    = prov::dynamic_cast_detail::dynamic_cast_ptr_impl
      < T, PossibleChildren... >;

  using prov_types
    = receiver_traits::provider_types_t
      < prov::result_of_value_of_t
        < std::remove_reference_t
          < call_detail::give_qualifiers_to_t< T&&, PossibleChildren > >*
        >...
      >;

  template< class Receiver >
  using result_type_t
    = receiver_traits::result_of_branch_t< Receiver, prov_types >;

  using partition = receiver_traits::partition_begin_t< prov_types >;

  template< class Partition, int Dummy = 0, class Receiver >
  static constexpr result_type_t< Receiver >
  provide_impl( self_t self, Receiver&& receiver )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  template< class Partition, class HeadChild, class... TailChildren
          , class Receiver
          >
  static constexpr result_type_t< Receiver >
  provide_impl( self_t self, Receiver&& receiver )
  {
    using reference_result_t
      = call_detail::give_qualifiers_to_t< T&&, HeadChild >;

    using cast_target
      = std::remove_reference_t< reference_result_t >*;

    if( auto* const ptr = dynamic_cast< cast_target >( self.ptr ) )
    {
      return receiver_traits::branch
      ( std::forward< Receiver >( receiver )
      , partition::head_provider_types
      , prov::value_of( ptr )
      , partition::tail_provider_types
      );
    }
    else
    {
      return provide_impl< receiver_traits::partition_next_t< Partition >, TailChildren... >
      ( self, std::forward< Receiver >( receiver ) );
    }

    // Do default behavior
  }
 public:
  template< class Receiver >
  static constexpr result_type_t< Receiver >
  provide( self_t self, Receiver&& receiver )
  {
    return provide_impl< partition, PossibleChildren... >
    ( self, std::forward< Receiver >( receiver ) );
  }
};

template< class T, class... PossibleChildren >
struct make_concept_map
< ArgumentProvider
  < prov::dynamic_cast_detail::dynamic_cast_shared_ptr_impl
    < T, PossibleChildren... >
  >
>
{
 private:
  using self_t
    = prov::dynamic_cast_detail::dynamic_cast_shared_ptr_impl
      < T, PossibleChildren... >;

  using prov_types
    = receiver_traits::provider_types_t
      < prov::result_of_value_of_t
        < std::shared_ptr
          < std::remove_reference_t
            < call_detail::give_qualifiers_to_t< T&&, PossibleChildren > >
          >
        >...
      >;

  template< class Receiver >
  using result_type_t
    = receiver_traits::result_of_branch_t< Receiver, prov_types >;

  using partition = receiver_traits::partition_begin_t< prov_types >;

  template< class Partition, int Dummy = 0, class Receiver >
  static constexpr result_type_t< Receiver >
  provide_impl( self_t self, Receiver&& receiver )
  {
    ARGOT_DETAIL_UNREACHABLE();
  }

  template< class Partition, class HeadChild, class... TailChildren
          , class Receiver
          >
  static constexpr result_type_t< Receiver >
  provide_impl( self_t self, Receiver&& receiver )
  {
    using reference_result_t
      = call_detail::give_qualifiers_to_t< T&&, HeadChild >;

    using cast_target
      = std::remove_reference_t< reference_result_t >;

    if( auto ptr = std::dynamic_pointer_cast< cast_target >( self.ptr ) )
    {
      return receiver_traits::branch
      ( std::forward< Receiver >( receiver )
      , partition::head_provider_types
      , prov::value_of( std::move( ptr ) )
      , partition::tail_provider_types
      );
    }
    else
    {
      return provide_impl< receiver_traits::partition_next_t< Partition >, TailChildren... >
      ( self, std::forward< Receiver >( receiver ) );
    }

    // Do default behavior
  }
 public:
  template< class Receiver >
  static constexpr result_type_t< Receiver >
  provide( self_t self, Receiver&& receiver )
  {
    return provide_impl< partition, PossibleChildren... >
    ( self, std::forward< Receiver >( receiver ) );
  }
};

}  // namespace argot

#endif  // ARGOT_PROV_DYNAMIC_CAST_HPP_
