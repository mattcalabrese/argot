/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_CONCEPTS_FUT_FUTURE_HPP_
#define ARGOT_CONCEPTS_FUT_FUTURE_HPP_

#if 0

#include <argot/concepts/future.hpp>
#include <argot/concepts/invocable_object_with.hpp>
#include <argot/concepts/move_constructible.hpp>
#include <argot/concepts/reference_to_const_object.hpp>
#include <argot/concepts/unqualified_object.hpp>
#include <argot/contained.hpp>
#include <argot/detail/conditional.hpp>
#include <argot/detail/constexpr_invoke.hpp>
#include <argot/forward.hpp>
#include <argot/gen/concept_assert.hpp>
#include <argot/gen/make_concept_map.hpp>
#include <argot/gen/or.hpp>
#include <argot/gen/requires.hpp>
#include <argot/move.hpp>
#include <argot/no_unique_address.hpp>
#include <argot/remove_cvref.hpp>
#include <argot/void_.hpp>

#include <atomic>
#include <cstddef>
#include <cstring>
#include <memory>
#include <new>
#include <type_traits>

namespace argot {
namespace fut {

template< class T >
class destructive_future;

template< class T >
class persistent_future;

// TODO(mattcalabrese)
//   Check requirements on T and also allow reference types and void types.
template< class T >
using future_type_of_t
  = typename argot_detail::conditional< std::is_copy_constructible_v< T > >
    ::template meta_apply< destructive_future, persistent_future, T >;

template< class T >
using future_type_of = call_detail::lazy_expand< future_type_of_t, T >;

namespace future_detail {

template< class T >
struct destructive_shared_state;

template< class T >
struct persistent_shared_state;

template< class T >
using shared_state_of_t
  = typename argot_detail::conditional< std::is_copy_constructible_v< T > >
    ::template meta_apply
    < persistent_shared_state, destructive_shared_state, T >;

template< class P >
class moveonly_continuation_type
{
 private:
  using param_type = std::remove_reference_t< P >*;
  using fun_ptr_type = void ( * )( void*, operation, param_type ) noexcept;
 public:
  ~moveonly_continuation_type()
  {
    if( dispatch )
      dispatch( &storage, operation::destroy, nullptr );
  }

  explicit operator bool() noexcept const { return dispatch; }

  void operator ()() && noexcept { dispatch( &storage, operation::call ); }

  // TODO(mattcalabrese) Require function call to be noexcept
  // TODO(mattcalabrese) Require destructor to be noexcept
  template< class FunParam
          , ARGOT_REQUIRES
            ( Or< UnqualifiedObject< FunParam >
                , ReferenceToConstObject< FunParam >
                >
            )  // TODO(mattcalabrese) Make a concept for this
            ( NothrowInvocableObjectWith< remove_cvref_t< FunParam > > )
            ()
          >
  void store( FunParam&& fun )
  {
    using fun_type = remove_cvref_t< FunParam >;

    if constexpr( is_inlinable< fun_type >() )
      ::new( static_cast< void* >( &storage ) )
        fun_type( ARGOT_FORWARD( FunParam )( fun ) );
    else
    {
      fun_type* const function_ptr
        = new fun_type( ARGOT_FORWARD( FunParam )( fun ) );
      std::memcpy( &storage, &function_ptr, sizeof( function_ptr ) );
    }

    dispatch = dispatch_function< fun_type >;
  }
 private:
  static constexpr std::size_t storage_alignment = alignof( void* );
  static constexpr std::size_t storage_size = sizeof( void* ) * 3;

  // Necessary for the implementation to store the pointer there if not inlined.
  static_assert( storage_size >= sizeof( void* ) );

  // TODO(mattcalabrese) Allow over-aligned types to use inline storage.
  template< class Fun >
  static constexpr bool is_inlinable()
  {
    return alignof( Fun ) <= storage_alignment && sizeof( Fun ) <= storage_size;
  }

  enum class operation : bool { call, destroy };

  template< class Fun >
  static void dispatch_function
  ( void* const storage, operation const op, param_type const value_ptr )
  noexcept
  {
    ARGOT_CONCEPT_ASSERT( NothrowInvocableObjectWith< Fun > );

    Fun* const fun_ptr = static_cast< Fun* >( storage );

    // TODO(mattcalabrese) Figure out what to do if an exception is thrown.
    // TODO(mattcalabrese) Don't use constexpr_invoke (function should already be wrapped so a direct function call works)
    if( op == operation::call )
      call_detail::constexpr_invoke
      ( ARGOT_MOVE( *fun ), ARGOT_FORWARD( P )( *value_ptr ) );
    else
      if constexpr( is_inlinable< Fun >() )
        fun_ptr->~Fun();
      else
        delete fun_ptr;
  }

  alignas( alignment ) char storage[ sizeof( void* ) * 3 ];
  fun_ptr_type dispatch = nullptr;
};

template< class T >
struct destructive_shared_state
{
  using contained_type = contained< T >;

  ~destructive_shared_state()
  {
    if( is_set )
      result_state.value.~contained_type();
  }

  std::mutex mutex;
  union result_state_type
  {
    result_state_type() noexcept : empty() {}
    ~result_state_type() {}

    ARGOT_NO_UNIQUE_ADDRESS void_ empty;
    ARGOT_NO_UNIQUE_ADDRESS contained_type value;
  };

  ARGOT_NO_UNIQUE_ADDRESS result_state_type result_state;
  moveonly_continuation_type continuation;
  std::atomic< int > num_owners = 2;
  bool is_set = false;  // TODO(mattcalabrese) Possibly sneak this into num_owners

  // TODO(mattcalabrese) Assert function object type.
  template< class Fun >
  struct function_fulfilling_promise
  {
    void operator ()() && noexcept
    {
      using raw_result_type = argot_detail::constexpr_invoke_result_t< Fun >;

      auto& state = *promise.state_ptr;

      if constexpr( std::is_void_v< raw_result_type > )
        call_detail::constexpr_invoke( ARGOT_MOVE( fun ) );
      else
        if constexpr( std::is_reference_v< raw_result_type > )
        {
          // TODO(mattcalabrese) Make contained
        }
        else  // TODO(mattcalabrese) Placement-new the contained type not the raw type
          ::new
          ( static_cast< void* >( std::addressof( state.result_state.value ) ) )
          raw_result_type( call_detail::constexpr_invoke( ARGOT_MOVE( fun ) ) );

      // Execute the attached continuation if one exists.
      if( std::lock_guard< std::mutex > lock( state.mutex );
          state.continuation
        )
      {
        // NOTE: It is okay to execute the continuation behind a lock because if
        // the continuation is set, then the corresponding future cannot lock
        // this mutex again.
        ARGOT_MOVE( state.continuation )();
        state.is_set = true;
      }
      else
        state.is_set = true;
    }

    promise_type_of_t< argot_detail::constexpr_invoke_result_t< Fun > > promise;
    ARGOT_NO_UNIQUE_ADDRESS Fun fun;
  };

  // TODO(mattcalabrese) Make sure continuation was not already set
  // TODO(mattcalabrese) Constraints
  template< class Fun >
  future_type_of_t
  < argot_detail::constexpr_invoke_result_t< std::decay_t< Fun > > >
  destructive_then( Fun&& fun )
  {
    using raw_result_type
      = argot_detail::constexpr_invoke_result_t< std::decay_t< Fun > >;

    using result_shared_state_t = shared_state_of_t< raw_result_type >;

    promise_type_of_t< result_shared_state_t >
    promise{ new result_shared_state_t };

    future_type_of_t< result_shared_state_t > result{ promise.state_ptr };

    function_fulfilling_promise< std::decay_t< Fun > > actual_function
    { call_detail::forward_and_decay_sink< Fun >( fun )
    , ARGOT_MOVE( promise )
    };

    // TODO(mattcalabrese) Assert not set
    // Note: Assumes the copy/move of Fun doesn't set_value, or call then, etc.
    {
      std::lock_guard< std::mutex > lock( mutex );
      continuation.store( ARGOT_MOVE( actual_function ) );
    }

    return result;
  }

  template< class T >
  void execute_continuation_if_exists()
  {

  }

  void set_value( T&& value )
  {
    emplace_value( ARGOT_FORWARD( T )( value ) );
  }

  void set_value( T const& value )
  {
    emplace_value( value );
  }
};

template< class T >
struct shared_state_ptr_deleter
{
  void operator ()( T* const this_ ) const
  {
    // Prefer post-decrement rather than pre-decrement for atomics.
    if( this_->num_owners-- == 1 )
      delete this_;
  }
};

template< class T >
struct shared_state_ptr
{
 public:
  explicit shared_state_ptr( T* ptr ) noexcept : ptr( ptr ) {}
  T* operator ->() const noexcept { return ptr.operator ->(); }
  T& operator *() const noexcept { return *ptr; }
 private:
  std::unique_ptr< T, shared_state_ptr_deleter< T > > ptr;
};

} // namespace argot::fut(::future_detail)

  // TODO(mattcalabrese) Support custom allocation mechanism.
template< class T >
class destructive_future
{
  ARGOT_CONCEPT_ASSERT( MoveConstructible< T > );
 private:
  future_detail::shared_state_ptr< destructive_shared_state > state_;

  friend struct argot::make_concept_map< Future< future > >;
};

} // namespace argot(::fut)

template< class T >
struct make_concept_map< Future< fut::destructive_future< T > > >
{
  template< class Fun >
  static auto destructive_then( fut::destructive_future< T >&& self, Fun&& fun )
  {
    return fut::future_type_of_t
    < argot_detail::constexpr_invoke_result_t< Fun&& > >
    ( self.state_->destructive_then( ARGOT_FORWARD( Fun )( fun ) ) );
  }
};

} // namespace argot

#endif

#endif  // ARGOT_CONCEPTS_FUT_FUTURE_HPP_
