/*==============================================================================
  Copyright (c) 2017 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/filesystem.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <sstream>
#include <utility>
#include <vector>

namespace {

namespace fs = boost::filesystem;

using path = fs::path;
using directory_iterator = fs::directory_iterator;

std::string header_guard_from_path( path const& subdirectory )
{
  std::ostringstream os;

  std::for_each
  ( subdirectory.begin(), subdirectory.end()
  , [ &os ]( path const& part )
    {
      auto const str = part.string();

      std::for_each
      ( str.begin(), str.end()
      , [ &os ]( char const c )
        {
          os << static_cast< char >( std::toupper( c ) );
        }
      );

      os << '_';
    }
  );

  os << "HPP_";

  return std::move( os ).str();
}

std::vector< path > headers_in_path( path const& directory )
{
  std::vector< path > result;

  std::copy_if
  ( directory_iterator( directory ), directory_iterator()
  , std::back_inserter( result )
  , []( path const& curr_path )
    {
      return fs::is_regular_file( curr_path ) && curr_path.has_stem();
    }
  );

  std::sort( result.begin(), result.end() );

  return result;
}

void create_convenience_header
( path const& include_root, path const& subdirectory )
{
  std::ostringstream os;

  os << "/*===================================================================="
        "==========\n"
     <<
R"(  Copyright (c) 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

)";

  std::string const header_guard
    = header_guard_from_path( subdirectory );

  os << "#ifndef " << header_guard << "\n"
        "#define " << header_guard << "\n"
        "\n";

  {
    auto const headers = headers_in_path( include_root / subdirectory );

    std::for_each
    ( headers.begin(), headers.end()
    , [ &os, &subdirectory ]( path const& curr_path )
      {
        if( fs::is_regular_file( curr_path ) && curr_path.has_stem() )
          os << "#include <" << subdirectory.string() << '/'
             << curr_path.filename().string() << ">\n";
      }
    );
  }

  os << "\n"
        "#endif  // " << header_guard << '\n';

  path const convenience_header_path
    = [ full_subdirectory = include_root / subdirectory ]() mutable
      {
        full_subdirectory.replace_extension( path( ".hpp" ) );
        return std::move( full_subdirectory );
      }();

  std::ofstream file( convenience_header_path.string() );
  file << std::move( os ).str();
}

}  // namespace

int main()
{
  path const include_root( "../include" );

  // TODO(mattcalabrese)
  // Automatically calculate these lists based on nested directories that are
  // not "detail". Recurse and populate from leaves first. Make sure to not
  // delete things like switch_.hpp (move switch_.hpp to switch_/switch_.hpp).

  create_convenience_header( include_root, path( "argot/async_call" ) );
  create_convenience_header( include_root, path( "argot/call" ) );
  create_convenience_header( include_root, path( "argot/case" ) );
  create_convenience_header( include_root, path( "argot/conc/expand" ) );
  create_convenience_header( include_root, path( "argot/conc" ) );
  create_convenience_header( include_root, path( "argot/conc_traits" ) );
  create_convenience_header( include_root, path( "argot/concepts" ) );
  create_convenience_header( include_root, path( "argot/executor" ) );
  create_convenience_header( include_root, path( "argot/executor_traits" ) );
  create_convenience_header( include_root, path( "argot/fut" ) );
  create_convenience_header( include_root, path( "argot/fut_traits" ) );
  create_convenience_header( include_root, path( "argot/gen" ) );
  create_convenience_header( include_root, path( "argot/packager" ) );
  create_convenience_header( include_root, path( "argot/opaque_optional" ) );
  create_convenience_header( include_root, path( "argot/opt_traits" ) );
  create_convenience_header( include_root, path( "argot/packager_traits" ) );

  create_convenience_header( include_root
                           , path( "argot/prov/bind_transform" )
                           );
  create_convenience_header( include_root, path( "argot/prov/expand" ) );

  create_convenience_header( include_root, path( "argot/prov" ) );
  create_convenience_header( include_root, path( "argot/prov_traits" ) );
  create_convenience_header( include_root, path( "argot/receiver" ) );
  create_convenience_header( include_root, path( "argot/receiver_traits" ) );
  create_convenience_header( include_root, path( "argot/reducer" ) );
  create_convenience_header( include_root, path( "argot/reducer_traits" ) );
  create_convenience_header( include_root, path( "argot/state_traits" ) );
  create_convenience_header( include_root, path( "argot/switch_traits" ) );
  create_convenience_header( include_root, path( "argot/tuple_traits" ) );
  create_convenience_header( include_root, path( "argot/union_traits" ) );
  create_convenience_header( include_root, path( "argot/variant_traits" ) );

  create_convenience_header( include_root, path( "argot" ) );
}
