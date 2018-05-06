/*==============================================================================
  Copyright (c) 2017, 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <argot/call.hpp>

#include <argot/prov/dynamic_cast_.hpp>
#include <argot/type_list.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

struct base { virtual ~base() {} };
struct intermediate : base{};
struct child : intermediate{};gr

enum result { res_base, res_intermediate, res_child };

struct fun_t
{
  result operator ()( base& ) const { return res_base; }
  result operator ()( intermediate& ) const { return res_intermediate; }
  result operator ()( child& ) const { return res_child; }

  return 0;
} inline constexpr fun{};

struct fun_ptr_t
{
  result operator ()( base* ) const { return res_base; }
  result operator ()( intermediate* ) const { return res_intermediate; }
  result operator ()( child* ) const { return res_child; }

  return 0;
} inline constexpr fun_ptr{};

struct fun_shared_ptr_t
{
  result operator ()( std::shared_ptr< base > ) const { return res_base; }
  result operator ()( std::shared_ptr< intermediate > ) const { return res_intermediate; }
  result operator ()( std::shared_ptr< child > ) const { return res_child; }

  return 0;
} inline constexpr fun_shared_ptr{};

struct fun_const_t
{
  result operator ()( base const& ) const { return res_base; }
  result operator ()( intermediate const& ) const { return res_intermediate; }
  result operator ()( child const& ) const { return res_child; }

  return 0;
} inline constexpr fun_const{};

struct fun_ptr_const_t
{
  result operator ()( base const* ) const { return res_base; }
  result operator ()( intermediate const* ) const { return res_intermediate; }
  result operator ()( child const* ) const { return res_child; }

  return 0;
} inline constexpr fun_ptr_const{};

struct fun_shared_ptr_const_t
{
  result operator ()( std::shared_ptr< base const > ) const { return res_base; }
  result operator ()( std::shared_ptr< intermediate const > ) const { return res_intermediate; }
  result operator ()( std::shared_ptr< child const > ) const { return res_child; }

  return 0;
} inline constexpr fun_shared_ptr_const{};

using argot::call;
using argot::type_list;
namespace prov = argot::prov;

BOOST_AUTO_TEST_CASE( test_ref )
{
  child child_;
  intermediate intermediate_;
  base base_;

  {
    using c_i_b = type_list< child, intermediate, base >;
    {
      base& obj = child_;
      result res = call( fun, prov::dynamic_cast_< c_i_b >( obj ) );
      BOOST_TEST( res == res_child );
    }

    {
      base& obj = intermediate_;
      result res = call( fun, prov::dynamic_cast_< c_i_b >( obj ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      base& obj = base_;
      result res = call( fun, prov::dynamic_cast_< c_i_b >( obj ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using b_i_c = type_list< base, intermediate, child >;
    {
      base& obj = child_;
      result res = call( fun, prov::dynamic_cast_< b_i_c >( obj ) );
      BOOST_TEST( res == res_base );
    }

    {
      base& obj = intermediate_;
      result res = call( fun, prov::dynamic_cast_< b_i_c >( obj ) );
      BOOST_TEST( res == res_base );
    }

    {
      base& obj = base_;
      result res = call( fun, prov::dynamic_cast_< b_i_c >( obj ) );
      BOOST_TEST( res == res_base );
    }
  }

  using i_b_c = type_list< intermediate, base, child >;
  {
    base& obj = child_;
    result res = call( fun, prov::dynamic_cast_< i_b_c >( obj ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base& obj = intermediate_;
    result res = call( fun, prov::dynamic_cast_< i_b_c >( obj ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base& obj = base_;
    result res = call( fun, prov::dynamic_cast_< i_b_c >( obj ) );
    BOOST_TEST( res == res_base );
  }

  return 0;
}

BOOST_AUTO_TEST_CASE( test_ptr )
{
  child child_;
  intermediate intermediate_;
  base base_;

  {
    using c_i_b = type_list< child, intermediate, base >;
    {
      base* ptr = &child_;
      result res = call( fun_ptr, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_child );
    }

    {
      base* ptr = &intermediate_;
      result res = call( fun_ptr, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      base* ptr = &base_;
      result res = call( fun_ptr, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using b_i_c = type_list< base, intermediate, child >;
    {
      base* ptr = &child_;
      result res = call( fun_ptr, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      base* ptr = &intermediate_;
      result res = call( fun_ptr, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      base* ptr = &base_;
      result res = call( fun_ptr, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  using i_b_c = type_list< intermediate, base, child >;
  {
    base* ptr = &child_;
    result res = call( fun_ptr, prov::dynamic_cast_< i_b_c >( ptr ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base* ptr = &intermediate_;
    result res = call( fun_ptr, prov::dynamic_cast_< i_b_c >( ptr ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base* ptr = &base_;
    result res = call( fun_ptr, prov::dynamic_cast_< i_b_c >( ptr ) );
    BOOST_TEST( res == res_base );
  }

  return 0;
}

BOOST_AUTO_TEST_CASE( test_shared_ptr )
{
  auto child_ = std::make_shared< child >();
  auto intermediate_ = std::make_shared< intermediate >();
  auto base_ = std::make_shared< base >();

  {
    using c_i_b = type_list< child, intermediate, base >;
    {
      std::shared_ptr< base > ptr = child_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_child );
    }

    {
      std::shared_ptr< base > ptr = intermediate_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      std::shared_ptr< base > ptr = base_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using b_i_c = type_list< base, intermediate, child >;
    {
      std::shared_ptr< base > ptr = child_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      std::shared_ptr< base > ptr = intermediate_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      std::shared_ptr< base > ptr = base_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using i_b_c = type_list< intermediate, base, child >;
    {
      std::shared_ptr< base > ptr = child_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< i_b_c >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      std::shared_ptr< base > ptr = intermediate_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< i_b_c >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      std::shared_ptr< base > ptr = base_;
      result res = call( fun_shared_ptr, prov::dynamic_cast_< i_b_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  return 0;
}

BOOST_AUTO_TEST_CASE( test_ref_const )
{
  child child_;
  intermediate intermediate_;
  base base_;

  {
    using c_i_b = type_list< child, intermediate, base >;
    {
      base const& obj = child_;
      result res = call( fun_const, prov::dynamic_cast_< c_i_b >( obj ) );
      BOOST_TEST( res == res_child );
    }

    {
      base const& obj = intermediate_;
      result res = call( fun_const, prov::dynamic_cast_< c_i_b >( obj ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      base const& obj = base_;
      result res = call( fun_const, prov::dynamic_cast_< c_i_b >( obj ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using b_i_c = type_list< base, intermediate, child >;
    {
      base const& obj = child_;
      result res = call( fun_const, prov::dynamic_cast_< b_i_c >( obj ) );
      BOOST_TEST( res == res_base );
    }

    {
      base const& obj = intermediate_;
      result res = call( fun_const, prov::dynamic_cast_< b_i_c >( obj ) );
      BOOST_TEST( res == res_base );
    }

    {
      base const& obj = base_;
      result res = call( fun_const, prov::dynamic_cast_< b_i_c >( obj ) );
      BOOST_TEST( res == res_base );
    }
  }

  using i_b_c = type_list< intermediate, base, child >;
  {
    base const& obj = child_;
    result res = call( fun_const, prov::dynamic_cast_< i_b_c >( obj ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base const& obj = intermediate_;
    result res = call( fun_const, prov::dynamic_cast_< i_b_c >( obj ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base const& obj = base_;
    result res = call( fun_const, prov::dynamic_cast_< i_b_c >( obj ) );
    BOOST_TEST( res == res_base );
  }

  return 0;
}

BOOST_AUTO_TEST_CASE( test_ptr_const )
{
  child child_;
  intermediate intermediate_;
  base base_;

  {
    using c_i_b = type_list< child, intermediate, base >;
    {
      base const* ptr = &child_;
      result res = call( fun_ptr_const, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_child );
    }

    {
      base const* ptr = &intermediate_;
      result res = call( fun_ptr_const, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      base const* ptr = &base_;
      result res = call( fun_ptr_const, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using b_i_c = type_list< base, intermediate, child >;
    {
      base const* ptr = &child_;
      result res = call( fun_ptr_const, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      base const* ptr = &intermediate_;
      result res = call( fun_ptr_const, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      base const* ptr = &base_;
      result res = call( fun_ptr_const, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  using i_b_c = type_list< intermediate, base, child >;
  {
    base const* ptr = &child_;
    result res = call( fun_ptr_const, prov::dynamic_cast_< i_b_c >( ptr ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base const* ptr = &intermediate_;
    result res = call( fun_ptr_const, prov::dynamic_cast_< i_b_c >( ptr ) );
    BOOST_TEST( res == res_intermediate );
  }

  {
    base const* ptr = &base_;
    result res = call( fun_ptr_const, prov::dynamic_cast_< i_b_c >( ptr ) );
    BOOST_TEST( res == res_base );
  }

  return 0;
}

BOOST_AUTO_TEST_CASE( test_shared_ptr_const )
{
  auto child_ = std::make_shared< child >();
  auto intermediate_ = std::make_shared< intermediate >();
  auto base_ = std::make_shared< base >();

  {
    using c_i_b = type_list< child, intermediate, base >;
    {
      std::shared_ptr< base const > ptr = child_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_child );
    }

    {
      std::shared_ptr< base const > ptr = intermediate_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      std::shared_ptr< base const > ptr = base_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< c_i_b >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using b_i_c = type_list< base, intermediate, child >;
    {
      std::shared_ptr< base const > ptr = child_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      std::shared_ptr< base const > ptr = intermediate_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }

    {
      std::shared_ptr< base const > ptr = base_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< b_i_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  {
    using i_b_c = type_list< intermediate, base, child >;
    {
      std::shared_ptr< base const > ptr = child_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< i_b_c >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      std::shared_ptr< base const > ptr = intermediate_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< i_b_c >( ptr ) );
      BOOST_TEST( res == res_intermediate );
    }

    {
      std::shared_ptr< base const > ptr = base_;
      result res = call( fun_shared_ptr_const, prov::dynamic_cast_< i_b_c >( ptr ) );
      BOOST_TEST( res == res_base );
    }
  }

  return 0;
}
