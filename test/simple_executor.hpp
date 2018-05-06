/*==============================================================================
  Copyright (c) 2018 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ARGOT_TEST_SIMPLE_EXECUTOR_HPP_
#define ARGOT_TEST_SIMPLE_EXECUTOR_HPP_

#include <argot/concepts/executor.hpp>
#include <argot/gen/make_concept_map.hpp>

#include <algorithm>
#include <deque>
#include <functional>
#include <mutex>
#include <optional>
#include <utility>

namespace argot_test {

class simple_executor_context
{
 public:
  using fun_type = std::function< void() >;
  using container_type = std::deque< fun_type >;

  struct executor_t
  {
    simple_executor_context* context;
  };

  executor_t executor() { return executor_t{ this }; }
 public:
  bool run_one()
  {
    std::optional< fun_type > fun;

    {
      std::lock_guard< std::mutex > const lock( mut );
      if( !funs.empty() )
      {
        fun.emplace( std::move( funs.front() ) );
        fun.pop_front();
      }
    }

    if( fun )
      (*fun)();
  }

  bool run()
  {
    container_type funs_to_run;
    bool result = false;

    do
    {
      {
        std::lock_guard< std::mutex > const lock( mut );
        funs_to_run = std::move( funs );
        funs.clear();
      }

      if( funs_to_run.empty() )
        return result;

      std::for_each
      ( funs_to_run.begin(), funs_to_run.end()
      , []( fun_type& fun ) { fun(); }
      );

      result = true;
    }
    while( true );
  }
 private:
  mutable std::mutex mut;
  std::deque< fun_type > funs;

  friend struct ::argot::make_concept_map< argot::Executor< executor_t > >;
};

} // namespace argot_test

namespace argot {

template<>
struct make_concept_map
< Executor< argot_test::simple_executor_context::executor_t > >
{
 private:
  template< class Fun >
  struct fun_type
  {
    void operator ()()
    {
      (void)std::move( fun )();
    }

    Fun fun;
  };
 public:
  template< class Fun >
  static constexpr void execute
  ( argot_test::simple_executor_context::executor_t self
  , Fun&& fun
  )
  {
    argot_test::simple_executor_context::fun_type fun
    ( fun_type< argot::remove_cvref_t< Fun > >{ std::forward< Fun >( fun ) } );

    argot_test::simple_executor_context& context = *self.context;
    std::lock_guard< std::mutex > const lock( context.mut );
    context.funs.push_back( std::move( fun ) );
  }
};

} // namespace argot

#endif  // ARGOT_TEST_SIMPLE_EXECUTOR_HPP_
