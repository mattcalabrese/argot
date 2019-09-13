/*==============================================================================
  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_DETAIL_VARIADIC_CHUNK_HPP_
#define ARGOT_DETAIL_VARIADIC_CHUNK_HPP_

#include <argot/detail/constexpr_invoke.hpp>
#include <argot/detail/forward.hpp>
#include <argot/detail/variadic_drop.hpp>
#include <argot/detail/variadic_range.hpp>
#include <argot/detail/variadic_take.hpp>

#include <cstddef>
#include <utility>

namespace argot::detail_argot {

template< class CompleteChunkIndices, bool HasIncompleteFinalChunk >
struct variadic_chunk_impl;

template< std::size_t... ChunkIndices >
struct variadic_chunk_impl
< std::index_sequence< ChunkIndices... >
, /*HasIncompleteFinalChunk =*/ false
>
{
  template< std::size_t AmountPerChunk
          , class Chunker
          , class Fun, class... P
          >
  static constexpr decltype( auto )
  run( Chunker const& chunker, Fun&& fun, P&&... args )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun )
    , variadic_drop_impl< ChunkIndices * AmountPerChunk >::run
      ( ( bind_variadic_take_run< AmountPerChunk > )( chunker )
      , ARGOT_FORWARD( P )( args )...
      )...
    );
  }

  template< std::size_t AmountPerChunk
          , template< class... > class Chunker
          , template< class... > class Result
          , class... P
          >
  using apply
    = Result
      < variadic_sized_range
        < AmountPerChunk * ChunkIndices, AmountPerChunk, Chunker, P... >...
      >;
};

template< std::size_t... ChunkIndices >
struct variadic_chunk_impl
< std::index_sequence< ChunkIndices... >
, /*HasIncompleteFinalChunk =*/ true
>
{
  template< std::size_t AmountPerChunk
          , class Chunker
          , class Fun, class... P
          >
  static constexpr decltype( auto )
  run( Chunker const& chunker, Fun&& fun, P&&... args )
  {
    return argot_detail::constexpr_invoke
    ( ARGOT_FORWARD( Fun )( fun )
    , variadic_drop_impl< ChunkIndices * AmountPerChunk >::run
      ( ( bind_variadic_take_run< AmountPerChunk > )( chunker )
      , ARGOT_FORWARD( P )( args )...
      )...
    , variadic_drop_impl< sizeof...( ChunkIndices ) * AmountPerChunk >
      ::run( chunker, ARGOT_FORWARD( P )( args )... )
    );
  }

  template< std::size_t AmountPerChunk
          , template< class... > class Chunker
          , template< class... > class Result
          , class... P
          >
  using apply
    = Result
      < variadic_sized_range
        < AmountPerChunk * ChunkIndices, AmountPerChunk, Chunker, P... >...
      , variadic_drop
        < AmountPerChunk * sizeof...( ChunkIndices )
        , Chunker, P...
        >
      >;
};

template< std::size_t AmountPerChunk
        , template< class... > class Chunker
        , template< class... > class Result
        , class... P
        >
using variadic_chunk
  = typename variadic_chunk_impl
    < std::make_index_sequence< sizeof...( P ) / AmountPerChunk >
    , sizeof...( P ) % AmountPerChunk != 0
    >::template apply< AmountPerChunk, Chunker, Result, P... >;

} // namespace (argot::detail_argot)

#endif // ARGOT_DETAIL_VARIADIC_CHUNK_HPP_
