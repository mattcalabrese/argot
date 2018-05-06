/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/concepts/can_default_to_reference_to.hpp>
#include <argot/gen/not.hpp>
#include <argot/gen/concept_ensure.hpp>
#include <argot/prov/reference_to.hpp>
#include <argot/prov/value_of.hpp>

#include <type_traits>

using argot::CanDefaultToReferenceTo;
using argot::Not;

struct basic
{
  basic( basic&& ) = default;
  basic( basic const& ) = default;

  basic( basic& ) = delete;
  basic( basic volatile& ) = delete;
  basic( basic volatile const& ) = delete;

  basic( basic const&& ) = delete;
  basic( basic volatile&& ) = delete;
  basic( basic volatile const&& ) = delete;
};

struct mv_only
{
  mv_only( mv_only&& ) = default;

  mv_only( mv_only& ) = delete;
  mv_only( mv_only const& ) = delete;
  mv_only( mv_only volatile& ) = delete;
  mv_only( mv_only volatile const& ) = delete;

  mv_only( mv_only const&& ) = delete;
  mv_only( mv_only volatile&& ) = delete;
  mv_only( mv_only volatile const&& ) = delete;
};

struct cp_only
{
  cp_only( cp_only const& ) = default;

  cp_only( cp_only& ) = delete;
  cp_only( cp_only volatile& ) = delete;
  cp_only( cp_only volatile const& ) = delete;

  cp_only( cp_only&& ) = delete;
  cp_only( cp_only const&& ) = delete;
  cp_only( cp_only volatile&& ) = delete;
  cp_only( cp_only volatile const&& ) = delete;
};

template< class T >
using r_ = argot::prov::result_of_reference_to_t< T >;

template< class T >
using v_ = argot::prov::result_of_value_of_t< T >;

/////////////////////////////
// Not an ArgumentProvider //
/////////////////////////////

// basic
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic const& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic volatile& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic volatile const& > );

ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic const&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic volatile&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic volatile const&& > );

ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic const > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic volatile > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< basic volatile const > );

// mv_only
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only const& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only volatile& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only volatile const& > );

ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only const&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only volatile&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only volatile const&& > );

ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only const > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only volatile > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< mv_only volatile const > );

// cp_only
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only const& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only volatile& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only volatile const& > );

ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only const&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only volatile&& > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only volatile const&& > );

ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only const > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only volatile > );
ARGOT_CONCEPT_ENSURE( CanDefaultToReferenceTo< cp_only volatile const > );

//////////////////
// reference_to //
//////////////////

// r_< basic cv_ref > const&
ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic& > const& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic const& > const& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic volatile& > const& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic volatile const& > const& > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< r_< basic&& > const& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< r_< basic const&& > const& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< r_< basic volatile&& > const& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< r_< basic volatile const&& > const& > > );

// r_< basic cv_ref >&&
ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic& >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic const& >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic volatile& >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic volatile const& >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic&& >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic const&& >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic volatile&& >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< r_< basic volatile const&& >&& > );

//////////////
// value_of //
//////////////

// basic
ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< basic >& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< basic > const& > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< basic > volatile& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< basic > volatile const& > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< basic >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< basic > const&& > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< basic > volatile&& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< basic > volatile const&& > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< basic > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< basic > const > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< basic > volatile > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< basic > volatile const > > );

// mv_only
ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only >& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > const& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > volatile& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > volatile const& > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< mv_only >&& > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > const&& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > volatile&& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > volatile const&& > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< mv_only > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > const > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > volatile > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< mv_only > volatile const > > );

// cp_only
ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< cp_only >& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< cp_only > const& > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< cp_only > volatile& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< cp_only > volatile const& > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< cp_only >&& > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< cp_only > const&& > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< cp_only > volatile&& > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< cp_only > volatile const&& > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< cp_only > > );

ARGOT_CONCEPT_ENSURE
( CanDefaultToReferenceTo< v_< cp_only > const > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< cp_only > volatile > > );

ARGOT_CONCEPT_ENSURE
( Not< CanDefaultToReferenceTo< v_< cp_only > volatile const > > );
