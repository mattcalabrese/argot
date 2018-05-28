/*==============================================================================
  Copyright (c) 2016, 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/detail/constexpr_test.hpp>
#include <argot/detail/regular_bases.hpp>

#include <type_traits>
#include <utility>

namespace {

using argot::detail_regular_bases::may_be_noexcept;
using argot::detail_regular_bases::may_exist;
using argot::detail_regular_bases::equality_comparable;
using argot::detail_regular_bases::less_than_comparable;
using argot::detail_regular_bases::swappable;

using argot::detail_regular_bases::has_proper_equality_operator_v;
using argot::detail_regular_bases::has_proper_less_than_operator_v;

using argot::detail_regular_bases::is_nothrow_equality_comparable_v;
using argot::detail_regular_bases::is_nothrow_less_than_comparable_v;

using argot::detail_regular_bases::regular_core_access;

struct throwing_bool
{
  explicit operator bool() const;
};

struct throwing_eq
{
  bool operator ==( throwing_eq ) const;
};

struct invalid_eq
{
  void operator ==( invalid_eq ) const;
};

struct dubious_eq
{
  throwing_bool operator ==( dubious_eq ) const noexcept;
};

struct throwing_less
{
  bool operator <( throwing_less ) const;
};

struct invalid_less
{
  void operator <( invalid_less ) const;
};

struct dubious_less
{
  throwing_bool operator <( dubious_less ) const noexcept;
};

struct invalid_swap
{
  friend void swap( invalid_swap&, invalid_swap& ) = delete;
};

struct throwing_swap
{
  throwing_swap( throwing_swap&& );
  throwing_swap& operator=( throwing_swap&& );
};

template< may_be_noexcept MayBeNoexcept, may_exist MayExist, class... Deps >
struct int_eq_
  : equality_comparable< int_eq_< MayBeNoexcept, MayExist, Deps... >
                       , MayBeNoexcept, MayExist, Deps...
                       >
{
  using base_t
    = equality_comparable< int_eq_< MayBeNoexcept, MayExist, Deps... >
                         , MayBeNoexcept, MayExist, Deps...
                         >;

  using base_t::equality_comparable_v;
  using base_t::nothrow_equality_comparable_v;

  constexpr explicit int_eq_( int value ) : value( value ) {}

  int value;
 private:
  constexpr bool detail_argot_equals( int_eq_ const other ) const noexcept
  {
    return value == other.value;
  }

  friend regular_core_access;
};

template< may_be_noexcept MayBeNoexcept, may_exist MayExist, class... Deps >
struct int_less_
  : less_than_comparable< int_less_< MayBeNoexcept, MayExist, Deps... >
                        , MayBeNoexcept, MayExist, Deps...
                        >
{
  using base_t
    = less_than_comparable< int_less_< MayBeNoexcept, MayExist, Deps... >
                          , MayBeNoexcept, MayExist, Deps...
                          >;

  using base_t::less_than_comparable_v;
  using base_t::nothrow_less_than_comparable_v;

  constexpr explicit int_less_( int value ) : value( value ) {}

  int value;
 private:
  constexpr bool detail_argot_less( int_less_ const other ) const noexcept
  {
    return value < other.value;
  }

  friend regular_core_access;
};

template< may_be_noexcept MayBeNoexcept, may_exist MayExist, class... Deps >
struct int_swap_
  : swappable< int_swap_< MayBeNoexcept, MayExist, Deps... >
             , MayBeNoexcept, MayExist, Deps...
             >
{
  using base_t
    = swappable< int_swap_< MayBeNoexcept, MayExist, Deps... >
               , MayBeNoexcept, MayExist, Deps...
               >;

  using base_t::swappable_v;
  using base_t::nothrow_swappable_v;

  constexpr explicit int_swap_( int value ) : value( value ) {}

  int_swap_( int_swap_ const& ) = delete;
  int_swap_& operator =( int_swap_ const& ) = delete;

  int value;
 private:
  constexpr void detail_argot_swap( int_swap_& other ) noexcept
  {
    int const old_value = value;
    value = other.value;
    other.value = old_value;
  }

  friend regular_core_access;
};

template< class... Deps >
using int_eq = int_eq_< may_be_noexcept::no, may_exist::yes, Deps... >;

template< class... Deps >
using int_less = int_less_< may_be_noexcept::no, may_exist::yes, Deps... >;

template< class... Deps >
using int_swap = int_swap_< may_be_noexcept::no, may_exist::yes, Deps... >;

template< class... Deps >
using no_int_eq = int_eq_< may_be_noexcept::no, may_exist::no, Deps... >;

template< class... Deps >
using no_int_less = int_less_< may_be_noexcept::no, may_exist::no, Deps... >;

template< class... Deps >
using no_int_swap = int_swap_< may_be_noexcept::no, may_exist::no, Deps... >;

template< class... Deps >
using int_eq_nothrow = int_eq_< may_be_noexcept::yes, may_exist::yes, Deps... >;

template< class... Deps >
using int_less_nothrow
  = int_less_< may_be_noexcept::yes, may_exist::yes, Deps... >;

template< class... Deps >
using int_swap_nothrow
  = int_swap_< may_be_noexcept::yes, may_exist::yes, Deps... >;

template< class... Deps >
using no_int_eq_nothrow
  = int_eq_< may_be_noexcept::yes, may_exist::no, Deps... >;

template< class... Deps >
using no_int_less_nothrow
  = int_less_< may_be_noexcept::yes, may_exist::no, Deps... >;

template< class... Deps >
using no_int_swap_nothrow
  = int_swap_< may_be_noexcept::yes, may_exist::no, Deps... >;

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable )
{
  using this_t = int_eq<>;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_TRUE( int_4 == int_4 );
  ARGOT_TEST_TRUE( int_4 == other_int_4 );
  ARGOT_TEST_FALSE( int_4 == int_5 );

  ARGOT_TEST_FALSE( int_4 != int_4 );
  ARGOT_TEST_FALSE( int_4 != other_int_4 );
  ARGOT_TEST_TRUE( int_4 != int_5 );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              == std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable_valid_deps )
{
  using this_t = int_eq< int, float, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_TRUE( int_4 == int_4 );
  ARGOT_TEST_TRUE( int_4 == other_int_4 );
  ARGOT_TEST_FALSE( int_4 == int_5 );

  ARGOT_TEST_FALSE( int_4 != int_4 );
  ARGOT_TEST_FALSE( int_4 != other_int_4 );
  ARGOT_TEST_TRUE( int_4 != int_5 );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              == std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable_invalid_deps )
{
  using this_t = int_eq< int, invalid_eq, char >;

  ARGOT_TEST_FALSE( has_proper_equality_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable_nothrow )
{
  using this_t = int_eq_nothrow<>;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_TRUE( int_4 == int_4 );
  ARGOT_TEST_TRUE( int_4 == other_int_4 );
  ARGOT_TEST_FALSE( int_4 == int_5 );

  ARGOT_TEST_FALSE( int_4 != int_4 );
  ARGOT_TEST_FALSE( int_4 != other_int_4 );
  ARGOT_TEST_TRUE( int_4 != int_5 );

  ARGOT_TEST_TRUE
  ( noexcept(    std::declval< this_t const& >()
              == std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::equality_comparable_v );
  ARGOT_TEST_TRUE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable_nothrow_valid_deps )
{
  using this_t = int_eq_nothrow< int, float, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_TRUE( int_4 == int_4 );
  ARGOT_TEST_TRUE( int_4 == other_int_4 );
  ARGOT_TEST_FALSE( int_4 == int_5 );

  ARGOT_TEST_FALSE( int_4 != int_4 );
  ARGOT_TEST_FALSE( int_4 != other_int_4 );
  ARGOT_TEST_TRUE( int_4 != int_5 );

  ARGOT_TEST_TRUE
  ( noexcept(    std::declval< this_t const& >()
              == std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::equality_comparable_v );
  ARGOT_TEST_TRUE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable_nothrow_throwing_deps )
{
  using this_t = int_eq_nothrow< int, throwing_eq, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_TRUE( int_4 == int_4 );
  ARGOT_TEST_TRUE( int_4 == other_int_4 );
  ARGOT_TEST_FALSE( int_4 == int_5 );

  ARGOT_TEST_FALSE( int_4 != int_4 );
  ARGOT_TEST_FALSE( int_4 != other_int_4 );
  ARGOT_TEST_TRUE( int_4 != int_5 );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              == std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable_nothrow_dubious_deps )
{
  using this_t = int_eq_nothrow< int, dubious_eq, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_TRUE( int_4 == int_4 );
  ARGOT_TEST_TRUE( int_4 == other_int_4 );
  ARGOT_TEST_FALSE( int_4 == int_5 );

  ARGOT_TEST_FALSE( int_4 != int_4 );
  ARGOT_TEST_FALSE( int_4 != other_int_4 );
  ARGOT_TEST_TRUE( int_4 != int_5 );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              == std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_equality_comparable_nothrow_invalid_deps )
{
  using this_t = int_eq_nothrow< int, invalid_eq, char >;

  ARGOT_TEST_FALSE( has_proper_equality_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable )
{
  using this_t = int_less<>;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_FALSE( int_4 < int_4 );
  ARGOT_TEST_FALSE( int_4 < other_int_4 );
  ARGOT_TEST_TRUE( int_4 < int_5 );
  ARGOT_TEST_FALSE( int_5 < int_4 );

  ARGOT_TEST_FALSE( int_4 > int_4 );
  ARGOT_TEST_FALSE( int_4 > other_int_4 );
  ARGOT_TEST_FALSE( int_4 > int_5 );
  ARGOT_TEST_TRUE( int_5 > int_4 );

  ARGOT_TEST_TRUE( int_4 <= int_4 );
  ARGOT_TEST_TRUE( int_4 <= other_int_4 );
  ARGOT_TEST_TRUE( int_4 <= int_5 );
  ARGOT_TEST_FALSE( int_5 <= int_4 );

  ARGOT_TEST_TRUE( int_4 >= int_4 );
  ARGOT_TEST_TRUE( int_4 >= other_int_4 );
  ARGOT_TEST_FALSE( int_4 >= int_5 );
  ARGOT_TEST_TRUE( int_5 >= int_4 );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              < std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              <= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              >= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              > std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable_valid_deps )
{
  using this_t = int_less< int, float, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_FALSE( int_4 < int_4 );
  ARGOT_TEST_FALSE( int_4 < other_int_4 );
  ARGOT_TEST_TRUE( int_4 < int_5 );
  ARGOT_TEST_FALSE( int_5 < int_4 );

  ARGOT_TEST_FALSE( int_4 > int_4 );
  ARGOT_TEST_FALSE( int_4 > other_int_4 );
  ARGOT_TEST_FALSE( int_4 > int_5 );
  ARGOT_TEST_TRUE( int_5 > int_4 );

  ARGOT_TEST_TRUE( int_4 <= int_4 );
  ARGOT_TEST_TRUE( int_4 <= other_int_4 );
  ARGOT_TEST_TRUE( int_4 <= int_5 );
  ARGOT_TEST_FALSE( int_5 <= int_4 );

  ARGOT_TEST_TRUE( int_4 >= int_4 );
  ARGOT_TEST_TRUE( int_4 >= other_int_4 );
  ARGOT_TEST_FALSE( int_4 >= int_5 );
  ARGOT_TEST_TRUE( int_5 >= int_4 );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              < std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              <= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              >= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              > std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable_invalid_deps )
{
  using this_t = int_less< int, invalid_less, char >;

  ARGOT_TEST_FALSE( has_proper_less_than_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable_nothrow )
{
  using this_t = int_less_nothrow<>;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_FALSE( int_4 < int_4 );
  ARGOT_TEST_FALSE( int_4 < other_int_4 );
  ARGOT_TEST_TRUE( int_4 < int_5 );
  ARGOT_TEST_FALSE( int_5 < int_4 );

  ARGOT_TEST_FALSE( int_4 > int_4 );
  ARGOT_TEST_FALSE( int_4 > other_int_4 );
  ARGOT_TEST_FALSE( int_4 > int_5 );
  ARGOT_TEST_TRUE( int_5 > int_4 );

  ARGOT_TEST_TRUE( int_4 <= int_4 );
  ARGOT_TEST_TRUE( int_4 <= other_int_4 );
  ARGOT_TEST_TRUE( int_4 <= int_5 );
  ARGOT_TEST_FALSE( int_5 <= int_4 );

  ARGOT_TEST_TRUE( int_4 >= int_4 );
  ARGOT_TEST_TRUE( int_4 >= other_int_4 );
  ARGOT_TEST_FALSE( int_4 >= int_5 );
  ARGOT_TEST_TRUE( int_5 >= int_4 );

  ARGOT_TEST_TRUE
  ( noexcept(   std::declval< this_t const& >()
              < std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE
  ( noexcept(    std::declval< this_t const& >()
              <= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE
  ( noexcept(    std::declval< this_t const& >()
              >= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE
  ( noexcept(   std::declval< this_t const& >()
              > std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::less_than_comparable_v );
  ARGOT_TEST_TRUE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable_nothrow_valid_deps )
{
  using this_t = int_less_nothrow< int, float, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_FALSE( int_4 < int_4 );
  ARGOT_TEST_FALSE( int_4 < other_int_4 );
  ARGOT_TEST_TRUE( int_4 < int_5 );
  ARGOT_TEST_FALSE( int_5 < int_4 );

  ARGOT_TEST_FALSE( int_4 > int_4 );
  ARGOT_TEST_FALSE( int_4 > other_int_4 );
  ARGOT_TEST_FALSE( int_4 > int_5 );
  ARGOT_TEST_TRUE( int_5 > int_4 );

  ARGOT_TEST_TRUE( int_4 <= int_4 );
  ARGOT_TEST_TRUE( int_4 <= other_int_4 );
  ARGOT_TEST_TRUE( int_4 <= int_5 );
  ARGOT_TEST_FALSE( int_5 <= int_4 );

  ARGOT_TEST_TRUE( int_4 >= int_4 );
  ARGOT_TEST_TRUE( int_4 >= other_int_4 );
  ARGOT_TEST_FALSE( int_4 >= int_5 );
  ARGOT_TEST_TRUE( int_5 >= int_4 );

  ARGOT_TEST_TRUE
  ( noexcept(   std::declval< this_t const& >()
              < std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE
  ( noexcept(    std::declval< this_t const& >()
              <= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE
  ( noexcept(    std::declval< this_t const& >()
              >= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE
  ( noexcept(   std::declval< this_t const& >()
              > std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::less_than_comparable_v );
  ARGOT_TEST_TRUE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable_nothrow_throwing_deps )
{
  using this_t = int_less_nothrow< int, throwing_less, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_FALSE( int_4 < int_4 );
  ARGOT_TEST_FALSE( int_4 < other_int_4 );
  ARGOT_TEST_TRUE( int_4 < int_5 );
  ARGOT_TEST_FALSE( int_5 < int_4 );

  ARGOT_TEST_FALSE( int_4 > int_4 );
  ARGOT_TEST_FALSE( int_4 > other_int_4 );
  ARGOT_TEST_FALSE( int_4 > int_5 );
  ARGOT_TEST_TRUE( int_5 > int_4 );

  ARGOT_TEST_TRUE( int_4 <= int_4 );
  ARGOT_TEST_TRUE( int_4 <= other_int_4 );
  ARGOT_TEST_TRUE( int_4 <= int_5 );
  ARGOT_TEST_FALSE( int_5 <= int_4 );

  ARGOT_TEST_TRUE( int_4 >= int_4 );
  ARGOT_TEST_TRUE( int_4 >= other_int_4 );
  ARGOT_TEST_FALSE( int_4 >= int_5 );
  ARGOT_TEST_TRUE( int_5 >= int_4 );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              < std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              <= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              >= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              > std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable_nothrow_dubious_deps )
{
  using this_t = int_less_nothrow< int, dubious_less, char >;

  this_t const int_4( 4 );
  this_t const other_int_4( 4 );
  this_t const int_5( 5 );

  ARGOT_TEST_FALSE( int_4 < int_4 );
  ARGOT_TEST_FALSE( int_4 < other_int_4 );
  ARGOT_TEST_TRUE( int_4 < int_5 );
  ARGOT_TEST_FALSE( int_5 < int_4 );

  ARGOT_TEST_FALSE( int_4 > int_4 );
  ARGOT_TEST_FALSE( int_4 > other_int_4 );
  ARGOT_TEST_FALSE( int_4 > int_5 );
  ARGOT_TEST_TRUE( int_5 > int_4 );

  ARGOT_TEST_TRUE( int_4 <= int_4 );
  ARGOT_TEST_TRUE( int_4 <= other_int_4 );
  ARGOT_TEST_TRUE( int_4 <= int_5 );
  ARGOT_TEST_FALSE( int_5 <= int_4 );

  ARGOT_TEST_TRUE( int_4 >= int_4 );
  ARGOT_TEST_TRUE( int_4 >= other_int_4 );
  ARGOT_TEST_FALSE( int_4 >= int_5 );
  ARGOT_TEST_TRUE( int_5 >= int_4 );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              < std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              <= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(    std::declval< this_t const& >()
              >= std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_FALSE
  ( noexcept(   std::declval< this_t const& >()
              > std::declval< this_t const& >()
            )
  );

  ARGOT_TEST_TRUE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_less_than_comparable_nothrow_invalid_deps )
{
  using this_t = int_less_nothrow< int, invalid_less, char >;

  ARGOT_TEST_FALSE( has_proper_less_than_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_swap )
{
  using this_t = int_swap<>;

  this_t int_4( 4 );
  this_t int_5( 5 );

  swap( int_4, int_5 );

  ARGOT_TEST_EQ( int_4.value, 5 );
  ARGOT_TEST_EQ( int_5.value, 4 );

  ARGOT_TEST_TRUE( std::is_swappable_v< this_t > );
  ARGOT_TEST_FALSE( std::is_nothrow_swappable_v< this_t > );

  ARGOT_TEST_TRUE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_swap_valid_deps )
{
  using this_t = int_swap< int, float, char >;

  this_t int_4( 4 );
  this_t int_5( 5 );

  swap( int_4, int_5 );

  ARGOT_TEST_EQ( int_4.value, 5 );
  ARGOT_TEST_EQ( int_5.value, 4 );

  ARGOT_TEST_TRUE( std::is_swappable_v< this_t > );
  ARGOT_TEST_FALSE( std::is_nothrow_swappable_v< this_t > );

  ARGOT_TEST_TRUE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_swap_invalid_deps )
{
  using this_t = int_swap< int, invalid_swap, char >;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_swap_nothrow )
{
  using this_t = int_swap_nothrow<>;

  this_t int_4( 4 );
  this_t int_5( 5 );

  swap( int_4, int_5 );

  ARGOT_TEST_EQ( int_4.value, 5 );
  ARGOT_TEST_EQ( int_5.value, 4 );

  ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< this_t > );

  ARGOT_TEST_TRUE( this_t::swappable_v );
  ARGOT_TEST_TRUE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_swap_nothrow_valid_deps )
{
  using this_t = int_swap_nothrow< int, float, char >;

  this_t int_4( 4 );
  this_t int_5( 5 );

  swap( int_4, int_5 );

  ARGOT_TEST_EQ( int_4.value, 5 );
  ARGOT_TEST_EQ( int_5.value, 4 );

  ARGOT_TEST_TRUE( std::is_nothrow_swappable_v< this_t > );

  ARGOT_TEST_TRUE( this_t::swappable_v );
  ARGOT_TEST_TRUE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_swap_nothrow_throwing_deps )
{
  using this_t = int_swap_nothrow< int, throwing_swap, char >;

  this_t int_4( 4 );
  this_t int_5( 5 );

  swap( int_4, int_5 );

  ARGOT_TEST_EQ( int_4.value, 5 );
  ARGOT_TEST_EQ( int_5.value, 4 );

  ARGOT_TEST_TRUE( std::is_swappable_v< this_t > );
  ARGOT_TEST_FALSE( std::is_nothrow_swappable_v< this_t > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_swap_nothrow_invalid_deps )
{
  using this_t = int_swap_nothrow< int, invalid_swap, char >;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_equality_comparable )
{
  using this_t = no_int_eq<>;

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_equality_comparable_valid_deps )
{
  using this_t = no_int_eq< int, float, char >;

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_equality_comparable_invalid_deps )
{
  using this_t = no_int_eq< int, invalid_eq, char >;

  ARGOT_TEST_FALSE( has_proper_equality_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_equality_comparable_nothrow )
{
  using this_t = no_int_eq_nothrow<>;

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_equality_comparable_nothrow_valid_deps )
{
  using this_t = no_int_eq_nothrow< int, float, char >;

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_no_equality_comparable_nothrow_throwing_deps )
{
  using this_t = no_int_eq_nothrow< int, throwing_eq, char >;

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_no_equality_comparable_nothrow_dubious_deps )
{
  using this_t = no_int_eq_nothrow< int, dubious_eq, char >;

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_no_equality_comparable_nothrow_invalid_deps )
{
  using this_t = no_int_eq_nothrow< int, invalid_eq, char >;

  ARGOT_TEST_FALSE( has_proper_equality_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::equality_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_equality_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_less_than_comparable )
{
  using this_t = no_int_less<>;

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_less_than_comparable_valid_deps )
{
  using this_t = no_int_less< int, float, char >;

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_less_than_comparable_invalid_deps )
{
  using this_t = no_int_less< int, invalid_less, char >;

  ARGOT_TEST_FALSE( has_proper_less_than_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_less_than_comparable_nothrow )
{
  using this_t = no_int_less_nothrow<>;

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_less_than_comparable_nothrow_valid_deps )
{
  using this_t = no_int_less_nothrow< int, float, char >;

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_no_less_than_comparable_nothrow_throwing_deps )
{
  using this_t = no_int_less_nothrow< int, throwing_less, char >;

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_no_less_than_comparable_nothrow_dubious_deps )
{
  using this_t = no_int_less_nothrow< int, dubious_less, char >;

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST
( test_no_less_than_comparable_nothrow_invalid_deps )
{
  using this_t = no_int_less_nothrow< int, invalid_less, char >;

  ARGOT_TEST_FALSE( has_proper_less_than_operator_v< this_t > );

  ARGOT_TEST_FALSE( this_t::less_than_comparable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_less_than_comparable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_swap )
{
  using this_t = no_int_swap<>;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_swap_valid_deps )
{
  using this_t = no_int_swap< int, float, char >;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_swap_invalid_deps )
{
  using this_t = no_int_swap< int, invalid_swap, char >;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_swap_nothrow )
{
  using this_t = no_int_swap_nothrow<>;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_swap_nothrow_valid_deps )
{
  using this_t = no_int_swap_nothrow< int, float, char >;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_swap_nothrow_throwing_deps )
{
  using this_t = no_int_swap_nothrow< int, throwing_swap, char >;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );
  ARGOT_TEST_FALSE( std::is_nothrow_swappable_v< this_t > );

  return 0;
}

ARGOT_REGISTER_CONSTEXPR_TEST( test_no_swap_nothrow_invalid_deps )
{
  using this_t = no_int_swap_nothrow< int, invalid_swap, char >;

  ARGOT_TEST_FALSE( std::is_swappable_v< this_t > );

  ARGOT_TEST_FALSE( this_t::swappable_v );
  ARGOT_TEST_FALSE( this_t::nothrow_swappable_v );

  return 0;
}

ARGOT_EXECUTE_TESTS();

} // namespace
