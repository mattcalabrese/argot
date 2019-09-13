/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_PROV_CHUNK_HPP_
#define ARGOT_PROV_CHUNK_HPP_

//[description
/*`
prov::chunk is a facility that takes value `N` and a series of
ArgumentProviders. It produces a HigherOrderArgumentProvider where each of its
provided arguments is a corresponding, subrange of length `N`. If there number
of total represented arguments is not evenly divisible by `N`, then the length
of the final subrange is the remainder.

[global_function_object_designator]
*/
//]

#include <argot/basic_result_of.hpp>
#include <argot/concepts/argument_provider.hpp>
#include <argot/concepts/convertible_to_type_or_constant.hpp>
#include <argot/concepts/sinkable.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/max_argument_list_length.hpp>
#include <argot/detail/remove_cvref.hpp>
#include <argot/detail/variadic_chunk.hpp>
#include <argot/gen/requires.hpp>
#include <argot/prov/bind_call.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/value_in_range.hpp>
#include <argot/prov/value_of.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

//[docs
/*`
[synopsis_heading]
*/

namespace argot::prov {
//<-
namespace detail_chunk {

// TODO(mattcalabrese) Use implementation detail defined elsewhere
template< class T >
constexpr bool is_integral_constant_v = false;

template< class T, T V >
constexpr bool is_integral_constant_v< std::integral_constant< T, V > > = true;

template< std::size_t MaxArgumentListSize, class SizeT >
constexpr auto clamped_chunk_size( SizeT&& size )
{
  using raw_size_type = detail_argot::remove_cvref_t< SizeT >;

  if constexpr( is_integral_constant_v< raw_size_type > )
    return std::integral_constant
    < std::size_t
    ,   ( MaxArgumentListSize < raw_size_type::value )
      ? MaxArgumentListSize : raw_size_type::value
    >();
  else
  {
    std::size_t const requested_chunk_size
      = static_cast< std::size_t >( ARGOT_FORWARD( SizeT )( size ) );

    return   ( MaxArgumentListSize < requested_chunk_size )
           ? MaxArgumentListSize : requested_chunk_size;
  }
}

} // namespace argot::prov(::detail_chunk)
//->

struct chunk_fn
{
  //<-
  struct impl
  {
    template< std::size_t ChunkSize, class... P >
    constexpr auto operator()
    ( std::integral_constant< std::size_t, ChunkSize >, P&&... args ) const
    {
      return detail_argot::variadic_chunk_impl
      < std::make_index_sequence< sizeof...( P ) / ChunkSize >
      , /*HasIncompleteFinalChunk =*/ sizeof...( P ) % ChunkSize != 0
      >::template run< ChunkSize >
      ( prov::reference_to
      , prov::value_of
      , ARGOT_FORWARD( P )( args )...
      );
    }
  };
  //->
  template
  < class SizeT, class... Providers
  , ARGOT_REQUIRES
    ( ConvertibleToTypeOrConstant< SizeT, std::size_t > )
    ( ArgumentProvider< detail_argot::remove_cvref_t< Providers >... > )
    ( Sinkable< Providers&& >... )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( SizeT&& i, Providers&&... provs ) const//=;
  //<-
  {
    constexpr std::size_t max_argument_list_length
      = (   detail_argot::max_argument_list_length_v
            < prov_traits::argument_list_kinds_of_t< Providers&& > >
          + ...
        );

    constexpr std::size_t max_clamped_chunk_size
      = max_argument_list_length == 0 ? 1 : max_argument_list_length;

    return prov::bind_call
    ( impl()
    , prov::value_in_range< std::size_t, 1, max_clamped_chunk_size + 1 >
      ( detail_chunk::clamped_chunk_size< max_clamped_chunk_size >
        ( ARGOT_FORWARD( SizeT )( i ) )
      )
    , ARGOT_FORWARD( Providers )( provs )...
    );
  } //->
} inline constexpr chunk{};

template< std::size_t ChunkSize >
struct chunk_v_fn
{
  //<-
  static_assert( ChunkSize != 0 );

  struct impl
  {
    template< class... P >
    constexpr auto operator()( P&&... args ) const
    {
      return detail_argot::variadic_chunk_impl
      < std::make_index_sequence< sizeof...( P ) / ChunkSize >
      , /*HasIncompleteFinalChunk =*/ sizeof...( P ) % ChunkSize != 0
      >::template run< ChunkSize >
      ( prov::reference_to
      , prov::value_of
      , ARGOT_FORWARD( P )( args )...
      );
    }
  };
  //->
  template
  < class... Providers
  , ARGOT_REQUIRES
    ( ArgumentProvider< detail_argot::remove_cvref_t< Providers >... > )
    ( Sinkable< Providers&& >... )
    ()
  >
  [[nodiscard]]
  constexpr auto operator ()( Providers&&... provs ) const//=;
  //<-
  {
    return prov::bind_call( impl(), ARGOT_FORWARD( Providers )( provs )... );
  } //->
};

template< std::size_t ChunkSize >
constexpr chunk_v_fn< ChunkSize > chunk_{}; 

template< class SizeT, class... Providers >
using result_of_chunk_t//= = ``[see_prologue_result_of]``;
//<-
  = basic_result_of_t< chunk_fn const&, SizeT, Providers... >; //->

} // namespace (argot::prov)

//]

#endif // ARGOT_PROV_CHUNK_HPP_
