/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/sinkable.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>

#include <type_traits>

using argot::Sinkable;
using argot::Not;

struct basic_copyable_movable {};

struct copyable_movable
{
  copyable_movable( copyable_movable&& ) = default;
  copyable_movable( copyable_movable const& ) = default;

  copyable_movable( copyable_movable& ) = delete;
  copyable_movable( copyable_movable volatile& ) = delete;
  copyable_movable( copyable_movable volatile const& ) = delete;

  copyable_movable( copyable_movable const&& ) = delete;
  copyable_movable( copyable_movable volatile&& ) = delete;
  copyable_movable( copyable_movable volatile const&& ) = delete;
};

struct move_only
{
  move_only( move_only&& ) = default;

  move_only( move_only& ) = delete;
  move_only( move_only const& ) = delete;
  move_only( move_only volatile& ) = delete;
  move_only( move_only volatile const& ) = delete;

  move_only( move_only const&& ) = delete;
  move_only( move_only volatile&& ) = delete;
  move_only( move_only volatile const&& ) = delete;
};

struct copy_only
{
  copy_only( copy_only const& ) = default;

  copy_only( copy_only& ) = delete;
  copy_only( copy_only volatile& ) = delete;
  copy_only( copy_only volatile const& ) = delete;

  copy_only( copy_only&& ) = delete;
  copy_only( copy_only const&& ) = delete;
  copy_only( copy_only volatile&& ) = delete;
  copy_only( copy_only volatile const&& ) = delete;
};

// basic_copyable_movable
ARGOT_CONCEPT_ENSURE( Sinkable< basic_copyable_movable& > );
ARGOT_CONCEPT_ENSURE( Sinkable< basic_copyable_movable const& > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< basic_copyable_movable volatile& > > );
ARGOT_CONCEPT_ENSURE
( Not< Sinkable< basic_copyable_movable volatile const& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< basic_copyable_movable&& > );
ARGOT_CONCEPT_ENSURE( Sinkable< basic_copyable_movable const&& > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< basic_copyable_movable volatile&& > > );
ARGOT_CONCEPT_ENSURE
( Not< Sinkable< basic_copyable_movable volatile const&& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< basic_copyable_movable > );
ARGOT_CONCEPT_ENSURE( Sinkable< basic_copyable_movable const > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< basic_copyable_movable volatile > > );
ARGOT_CONCEPT_ENSURE
( Not< Sinkable< basic_copyable_movable volatile const > > );

// copyable_movable
ARGOT_CONCEPT_ENSURE( Sinkable< copyable_movable& > );
ARGOT_CONCEPT_ENSURE( Sinkable< copyable_movable const& > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copyable_movable volatile& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copyable_movable volatile const& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< copyable_movable&& > );
ARGOT_CONCEPT_ENSURE( Sinkable< copyable_movable const&& > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copyable_movable volatile&& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copyable_movable volatile const&& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< copyable_movable > );
ARGOT_CONCEPT_ENSURE( Sinkable< copyable_movable const > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copyable_movable volatile > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copyable_movable volatile const > > );

// move_only
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only const& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only volatile& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only volatile const& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< move_only&& > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only const&& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only volatile&& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only volatile const&& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< move_only > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only const > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only volatile > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< move_only volatile const > > );

// copy_only
ARGOT_CONCEPT_ENSURE( Sinkable< copy_only& > );
ARGOT_CONCEPT_ENSURE( Sinkable< copy_only const& > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copy_only volatile& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copy_only volatile const& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< copy_only&& > );
ARGOT_CONCEPT_ENSURE( Sinkable< copy_only const&& > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copy_only volatile&& > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copy_only volatile const&& > > );

ARGOT_CONCEPT_ENSURE( Sinkable< copy_only > );
ARGOT_CONCEPT_ENSURE( Sinkable< copy_only const > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copy_only volatile > > );
ARGOT_CONCEPT_ENSURE( Not< Sinkable< copy_only volatile const > > );
