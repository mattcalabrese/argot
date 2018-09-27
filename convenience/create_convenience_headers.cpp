/*==============================================================================
  Copyright (c) 2017, 2018, 2019 Matt Calabrese

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>

namespace {

namespace fs = boost::filesystem;

enum class kinds_exposed : unsigned char;

template< class... KindsExposed
        , std::enable_if_t
          < ( std::is_same_v< KindsExposed, kinds_exposed > && ... ) >*
            = nullptr
        >
[[nodiscard]]
constexpr
kinds_exposed and_( KindsExposed const... components )
{
  return static_cast< kinds_exposed >
  ( ( static_cast< unsigned char >( components ) | ... ) );
}

enum class kinds_exposed : unsigned char
{ macro     = 0b0000001
, concept_  = 0b0000010
, natural   = 0b0000100
, _v        = 0b0001000
, _t        = 0b0010000
, _fn       = 0b0100000
, result_of = 0b1000000

, object               = natural | _t
, function             = natural | _fn | result_of
, typed_variable_trait = _t | _v 
};

[[nodiscard]]
constexpr
bool has( kinds_exposed const value, kinds_exposed const component )
{
  return
       (   static_cast< unsigned char >( value )
         & static_cast< unsigned char >( component )
       )
    != 0;
}

[[nodiscard]]
std::string uppercase_to_unicode( std::string const& name )
{
  // NOTE: Capital letters are converted to unicode to prevent macro expansion.
  std::string result;
  for( char const c : name )
    switch( c )
    {
     case 'A': result += "\\u0041"; break;
     case 'B': result += "\\u0042"; break;
     case 'C': result += "\\u0043"; break;
     case 'D': result += "\\u0044"; break;
     case 'E': result += "\\u0045"; break;
     case 'F': result += "\\u0046"; break;
     case 'G': result += "\\u0047"; break;
     case 'H': result += "\\u0048"; break;
     case 'I': result += "\\u0049"; break;
     case 'J': result += "\\u004A"; break;
     case 'K': result += "\\u004B"; break;
     case 'L': result += "\\u004C"; break;
     case 'M': result += "\\u004D"; break;
     case 'N': result += "\\u004E"; break;
     case 'O': result += "\\u004F"; break;
     case 'P': result += "\\u0050"; break;
     case 'Q': result += "\\u0051"; break;
     case 'R': result += "\\u0052"; break;
     case 'S': result += "\\u0053"; break;
     case 'T': result += "\\u0054"; break;
     case 'U': result += "\\u0055"; break;
     case 'V': result += "\\u0056"; break;
     case 'W': result += "\\u0057"; break;
     case 'X': result += "\\u0058"; break;
     case 'Y': result += "\\u0059"; break;
     case 'Z': result += "\\u005A"; break;
     default: result.push_back( c ); break;
    }
  return result;
}

[[nodiscard]]
std::string interpolate_with_emptiness( std::string const& name )
{
  constexpr char emptiness[] = "\\u200B";

  std::string result;
  if( !name.empty() )
  {
    for( char c : name )
    {
      result += c;
      result += "\\u200B";
    }
    result.resize( result.size() - ( sizeof( emptiness ) - 1 ) );
  }
  return result;
}

[[nodiscard]]
std::string snake_case_to_camel_case( std::string const& name )
{
  std::string result;
  result.reserve( name.size() );

  std::for_each
  ( name.begin(), name.end()
  , [ &result, start_of_new_word = true ]( char const character ) mutable
    {
      if( character != '_' )
      {
        if( start_of_new_word )
          result.push_back( std::toupper( character ) );
        else
          result.push_back( character );

        start_of_new_word = false;
      }
      else
        start_of_new_word = true;
    }
  );

  return result;
}

std::string snake_case_to_argot_macro( std::string const& name )
{ 
  // NOTE: 5F is underscore. This is done to prevent macro expansion
  std::string result = "ARGOT\\u005F";
  result.reserve( result.size() + name.size() );

  std::transform
  ( name.begin(), name.end()
  , std::back_inserter( result )
  , []( char const character )
    {
      return static_cast< char >( std::toupper( character ) );
    }
  );

  return result;
}

std::string const section_name_from_path( fs::path const& path_from_include )
{
  // TODO(mattcalabrese) Placement new
  static auto const& suffix_overrides
    = *new std::map< fs::path, kinds_exposed >
      ( { { "argot/basic_result_of.hpp"
          , and_( kinds_exposed::natural, kinds_exposed::_t )
          }
        , { "argot/conc_traits/argument_list_kinds_of.hpp", kinds_exposed::_t }
        , { "argot/conc_traits/argument_list_kinds_of_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/conc_traits/argument_list_kinds_of_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/fut_traits/value_type.hpp", kinds_exposed::_t }
        , { "argot/gen/access_raw_concept_map.hpp", kinds_exposed::natural }
        , { "argot/gen/and.hpp", kinds_exposed::concept_ }
        , { "argot/gen/concept_conditional.hpp", kinds_exposed::natural }
        , { "argot/gen/is_auto_concept.hpp", kinds_exposed::_v }
        , { "argot/gen/is_valid_concept_map.hpp", kinds_exposed::_v }
        , { "argot/gen/make_concept_map.hpp", kinds_exposed::natural }
        , { "argot/gen/transparent_requirement.hpp", kinds_exposed::natural }
        , { "argot/gen/not.hpp", kinds_exposed::concept_ }
        , { "argot/gen/or.hpp", kinds_exposed::concept_ }
        , { "argot/gen/type.hpp", kinds_exposed::concept_ }
        , { "argot/opt_traits/element_type.hpp", kinds_exposed::_t }
        , { "argot/opt_traits/nil_element_type.hpp", kinds_exposed::_t }
        , { "argot/prov_traits/argument_list_kinds_of.hpp", kinds_exposed::_t }
        , { "argot/prov_traits/argument_list_kinds_of_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/prov_traits/argument_list_kinds_of_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/receiver_traits/partitioned_provider_types.hpp"
          , kinds_exposed::_t
          }
        , { "argot/receiver_traits/provider_types.hpp", kinds_exposed::_t }
        , { "argot/reducer_traits/is_homogeneous.hpp", kinds_exposed::_v }
        , { "argot/reducer_traits/return_types_of_call.hpp", kinds_exposed::_t }
        , { "argot/switch_traits/argument_list_kinds_of_body_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/argument_list_kinds_of_body_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/argument_list_kinds_of_case_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/argument_list_kinds_of_case_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/argument_list_kinds_of_default_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/argument_list_kinds_of_default_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/"
            "leading_argument_list_kinds_of_case_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/"
            "leading_argument_list_kinds_of_case_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/"
            "leading_argument_list_kinds_of_default_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/"
            "leading_argument_list_kinds_of_default_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/case_value_for_type_at.hpp"
          , kinds_exposed::_v
          }
        , { "argot/switch_traits/case_values.hpp", kinds_exposed::_t }
        , { "argot/switch_traits/case_values_for_type.hpp", kinds_exposed::_t }
        , { "argot/switch_traits/expand_case_values.hpp", kinds_exposed::_t }
        , { "argot/switch_traits/expand_case_values_for_type.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/num_cases.hpp", kinds_exposed::_v }
        , { "argot/switch_traits/"
            "trailing_argument_list_kinds_of_case_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/"
            "trailing_argument_list_kinds_of_case_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/"
            "trailing_argument_list_kinds_of_default_destructive.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/"
            "trailing_argument_list_kinds_of_default_persistent.hpp"
          , kinds_exposed::_t
          }
        , { "argot/switch_traits/combine.hpp", kinds_exposed::_t }
        , { "argot/tuple_traits/element_type.hpp", kinds_exposed::_t }
        , { "argot/tuple_traits/index_constant.hpp"
          , kinds_exposed::typed_variable_trait
          }
        , { "argot/tuple_traits/index_type.hpp", kinds_exposed::_t }
        , { "argot/tuple_traits/num_elements.hpp", kinds_exposed::_v }
        , { "argot/union_traits/alternative_type.hpp", kinds_exposed::_t }
        , { "argot/union_traits/index_constant.hpp"
          , kinds_exposed::typed_variable_trait
          }
        , { "argot/union_traits/index_type.hpp", kinds_exposed::_t }
        , { "argot/union_traits/num_alternatives.hpp", kinds_exposed::_v }
        , { "argot/variant_traits/alternative_type.hpp", kinds_exposed::_t }
        , { "argot/variant_traits/index_constant.hpp"
          , kinds_exposed::typed_variable_trait
          }
        , { "argot/variant_traits/index_type.hpp", kinds_exposed::_t }
        , { "argot/variant_traits/num_alternatives.hpp", kinds_exposed::_v }
        }
      );

  auto const& subdirectory
    = path_from_include.parent_path().stem().string();

  kinds_exposed const kinds
    = [ &path_from_include, &subdirectory ]
      {

        auto const override_it = suffix_overrides.find( path_from_include );

        return override_it == suffix_overrides.end()
          ?   subdirectory == "concepts"
            ? kinds_exposed::concept_
            :   subdirectory == "gen"
              ? kinds_exposed::macro
              : kinds_exposed::function
          : override_it->second;
      }(); 

  if( has( kinds, kinds_exposed::macro ) )
    return snake_case_to_argot_macro( path_from_include.stem().string() );
  else
    if( has( kinds, kinds_exposed::concept_ ) )
      return uppercase_to_unicode
      ( snake_case_to_camel_case( path_from_include.stem().string() ) );
    else
      if( has( kinds, kinds_exposed::natural ) )
        return    subdirectory == "argot"
               || subdirectory == "gen" || subdirectory == "concepts"
          ? path_from_include.stem().string()
          :   "[namespaced "
            + path_from_include.parent_path().stem().string()
            + ".."
            + path_from_include.stem().string()
            + "]";
      else
        if( has( kinds, kinds_exposed::_v ) )
          return    subdirectory == "argot"
                 || subdirectory == "gen" || subdirectory == "concepts"
            ? path_from_include.stem().string() + "_v"
            :   "[namespaced "
              + path_from_include.parent_path().stem().string()
              + ".."
              + path_from_include.stem().string() + "_v"
              + "]";
        else
          return    subdirectory == "argot"
                 || subdirectory == "gen" || subdirectory == "concepts"
            ? path_from_include.stem().string() + "_t"
            :   "[namespaced "
              + path_from_include.parent_path().stem().string()
              + ".."
              + path_from_include.stem().string() + "_t"
              + "]";
}

using path = fs::path;
using directory_iterator = fs::directory_iterator;
using recursive_directory_iterator = fs::recursive_directory_iterator;

enum class file_kind { quickbook, c_plus_plus };

struct comment_strategy
{
  char const* opener;
  char const* closer;
};

comment_strategy comment_strategy_of( file_kind kind )
{
  switch( kind )
  {
   case file_kind::quickbook:
    return { "[/", "/]" };
   case file_kind::c_plus_plus:
    return { "/*", "*/" };
  }
}

void create_license_comment( std::ostringstream& os, file_kind kind )
{
  auto const year = boost::gregorian::day_clock::local_day().year();
  auto const [ opener, closer ] = comment_strategy_of( kind );

  os << opener;
  os << "===================================================================="
        "==========\n"
     << "  Copyright (c) " << year << " Matt Calabrese\n"
     <<
R"(
  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================)";

  os
    << '=' << closer << "\n"
       "\n"
    << opener
    << "***********************************************************************"
       "*****"
    << closer
    << '\n'
    << opener
    << "******* "
       "THIS FILE IS AUTOMATICALLY GENERATED. DO NOT MODIFY BY HAND."
       " *******"
    << closer
    << '\n'
    << opener
    << "***********************************************************************"
       "*****"
    << closer
    << '\n';
}

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
      return    fs::is_regular_file( curr_path ) && curr_path.has_stem()
             && curr_path.extension() == ".hpp";
    }
  );

  std::sort( result.begin(), result.end() );

  return result;
}

bool file_should_be_documented( path const& location )
{
  return    location.extension() == ".hpp"
         && std::find_if
            ( location.begin(), location.end()
            , []( path const& path_part )
              {
                return path_part == "detail";
              }
            ) == location.end();
}

std::vector< path > recursive_headers_in_path( path const& directory )
{
  std::vector< path > result;

  std::copy_if
  ( recursive_directory_iterator( directory ), recursive_directory_iterator()
  , std::back_inserter( result )
  , []( path const& curr_path )
    {
      return    fs::is_regular_file( curr_path ) && curr_path.has_stem()
             && file_should_be_documented( curr_path );
    }
  );

  std::sort( result.begin(), result.end() );

  return result;
}

void create_convenience_header
( path const& include_root, path const& subdirectory )
{
  std::ostringstream os;

  create_license_comment( os, file_kind::c_plus_plus );

  os << '\n';

  std::string const header_guard
    = header_guard_from_path( subdirectory );

  os << "#ifndef " << header_guard << "\n"
        "#define " << header_guard << "\n"
        "\n";

  os << R"(//[description"
/*`
This header includes all of the facilities of the `)"
     << subdirectory.stem().string()
     << R"(` directory.
*/
//]

//[docs
//]

)";

  {
    auto const headers = headers_in_path( include_root / subdirectory );

    std::for_each
    ( headers.begin(), headers.end()
    , [ &os, &subdirectory ]( path const& curr_path )
      {
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

void create_quickbook_macro
( std::ostringstream& os, std::string_view name, std::string_view expansion)
{
  os << "[def " << name << ' ' << expansion << ']';
}

bool is_namespace_convenience_header( path const& curr_path )
{
  auto const stem = curr_path.stem();

  auto const directory_of_convenience
    = curr_path.parent_path() / stem;

  return    fs::is_directory( directory_of_convenience )
         && !headers_in_path( directory_of_convenience ).empty()
         && (    stem == "argot"
              || stem == "prov"
              || stem == "prov_traits"
              || stem == "receiver"
              || stem == "receiver_traits"
              || stem == "concepts"
              || stem == "conc"
              || stem == "conc_traits"
              || stem == "executor"
              || stem == "executor_traits"
              || stem == "fut"
              || stem == "fut_traits"
              || stem == "gen"
              || stem == "opt_traits"
              || stem == "packager"
              || stem == "packager_traits"
              || stem == "reducer"
              || stem == "reducer_traits"
              || stem == "state_traits"
              || stem == "switch_traits"
              || stem == "tuple_traits"
              || stem == "union_traits"
              || stem == "variant_traits"
            );
}

bool is_convenience_header( path const& curr_path )
{
  auto const directory_of_convenience
    = curr_path.parent_path() / curr_path.stem();

  return    fs::is_directory( directory_of_convenience )
         && !headers_in_path( directory_of_convenience ).empty();
}

void create_quickbook_links
( std::ostringstream& os
, path const& include_root, path const& subdirectory
, std::string const namespace_
)
{
  auto const headers = headers_in_path( include_root / subdirectory );

  std::for_each
  ( headers.begin(), headers.end()
  , [ &os, &namespace_ ]( path const& curr_path )
    {
      // Skip namespace convenience headers (for now)
      if( is_namespace_convenience_header( curr_path ) )
        return;

      std::string const namespace_part
        = namespace_ == "argot" ? std::string("argot.")
                                : namespace_ + ".";

      // What to put immediately before the `t` or `v` or `fn` of a facility.
      // This is usually `_`, but if the facility already ends in `_`, do not
      // add another one.
      char const* const suffix_separator
        =      !curr_path.stem().string().empty()
            && curr_path.stem().string().back() == '_'
          ? + ""
          : + "_";

      os << '\n';

      // The macro that expands to the name (without linking to the facility)
      create_quickbook_macro
      ( os
      , namespace_ + '_' + curr_path.stem().string()
      , namespace_ + "::" + curr_path.stem().string()
      );

      os << '\n';

      // The macro that links to the facility
      create_quickbook_macro
      ( os
      , namespace_ + "::" + curr_path.stem().string() + suffix_separator + "fn"
      ,   "[link argot.ref." + namespace_part
        + curr_path.stem().string() + " `" + namespace_ + "::"
        + curr_path.stem().string() + suffix_separator + "fn`]"
      );

      os << '\n';

      os << "[def " << namespace_ << "::"
         << curr_path.stem().string() << suffix_separator
         << "t [link argot.ref." << namespace_part
         << curr_path.stem().string() << " `" << namespace_ << "::"
         << curr_path.stem().string() << suffix_separator << "t`]]\n"

            "[def " << namespace_ << "::"
         << curr_path.stem().string() << suffix_separator
         << "v [link argot.ref." << namespace_part
         << curr_path.stem().string() << " `" << namespace_ << "::"
         << curr_path.stem().string() << suffix_separator << "v`]]\n"

            "[def " << namespace_ << "::" << curr_path.stem().string()
         << " [link argot.ref." << namespace_part
         << curr_path.stem().string() << " `" << namespace_ << "::"
         << curr_path.stem().string() << "`]]\n"

            "[def " << namespace_ << "::result_of_" << curr_path.stem().string()
         << suffix_separator << "t [link argot.ref." << namespace_part
         << curr_path.stem().string() << " `" << namespace_
         << "::result_of_" << curr_path.stem().string() << suffix_separator
         << "t`]]\n"

            "[def " << namespace_ << "::result_of_" << curr_path.stem().string()
         << " [link argot.ref." << namespace_part
         << curr_path.stem().string() << " `" << namespace_ << "::result_of_"
         << curr_path.stem().string() << "`]]\n";
    }
  );
}

void create_concept_quickbook_links
( std::ostringstream& os
, path const& include_root, path const& subdirectory
)
{
  auto const headers = headers_in_path( include_root / subdirectory );

  std::for_each
  ( headers.begin(), headers.end()
  , [ &os ]( path const& curr_path )
    {
      std::string const snake_case_name = curr_path.stem().string();

      std::string const camel_case_name
        = snake_case_to_camel_case( snake_case_name );

      if( fs::is_regular_file( curr_path ) && curr_path.has_stem() )
        os << "\n[def concepts_" << snake_case_name << " `"
                                 << camel_case_name << "`]"
              "\n[def _" << camel_case_name << "_ " << camel_case_name << "]"
              "\n[def _" << camel_case_name << " `" << camel_case_name
           << "`]\n[def " << camel_case_name
           << " [link argot.ref.concepts."
           << curr_path.stem().string() << " `" << camel_case_name << "`]]\n";
    }
  );
}

void create_header_quickbook_links
( std::ostringstream& os, path const& include_root, path const& /*doc_root*/ )
{
  auto const headers = recursive_headers_in_path( include_root );

  std::for_each
  ( headers.begin(), headers.end()
  , [ &os, &include_root ]( path const& curr_path )
    {
      fs::path const header = fs::relative( curr_path, include_root );

      os << "\n[def " << header.string() << " [link argot.ref";

      os << '.' << header.parent_path().stem().string()
         << '.' << header.stem().string()
         << " `" << header.string() << "`]]\n";
    }
  );
}

void create_reference_section_group
( std::ostringstream& reference_chapter_os
, path const& include_root, path const& doc_root, path const& subdirectory
, std::string_view group_name
)
{
  fs::path const reference_root = doc_root / "reference";
  fs::path const header_directory_path
    = include_root / "argot" / subdirectory;
  fs::path const group_root = reference_root / subdirectory;
  fs::path const filename
    =   subdirectory == "./"
      ? fs::path( "_.qbk" )
      : fs::path( "_" + subdirectory.string() ).replace_extension( "qbk" );
  std::string const id
    =   subdirectory == "./"
      ? std::string( "argot" )
      : std::string( subdirectory.string() );
  fs::path const group_qbk_file
    =   group_root.parent_path()
      / filename;

  std::ostringstream os;

  create_license_comment( os, file_kind::quickbook );

  os
    << "\n"
       "[section:" << id << ' ' << group_name << "]\n"
       "\n";

  auto const headers = headers_in_path( header_directory_path );

  std::for_each
  ( headers.begin(), headers.end()
  , [ &os, &subdirectory ]( path const& curr_path )
    {
      // Skip namespace convenience headers (for now)
      if( is_namespace_convenience_header( curr_path ) )
        return;

      fs::path const qbk_file
        =   subdirectory
          / fs::path( curr_path.filename() ).replace_extension( "qbk" );

      os << "[include " << qbk_file.string() << "]\n";
    }
  );

  os << "\n[endsect:" << id << "]\n";

  fs::create_directories( group_qbk_file.parent_path() );
  std::ofstream file( group_qbk_file.string() );
  file << std::move( os ).str();

  reference_chapter_os
    << "[include ../reference/" << filename.string() << "]\n"; 
}

void create_reference_section_files
( path const& include_root, path const& doc_root, path const& example_root )
{
  auto const headers = recursive_headers_in_path( include_root / "argot" );

  fs::path const reference_root = doc_root / "reference";

  std::for_each
  ( headers.begin(), headers.end()
  , [ &include_root, &reference_root, &example_root ]( path const& curr_path )
    {
      std::ostringstream os;

      fs::path const header = fs::relative( curr_path, include_root );
      fs::path const qbk_file
        =   reference_root
          / fs::relative( curr_path, include_root / "argot" )
            .replace_extension( "qbk" );
      fs::path const example_file
        =   example_root
          / fs::relative( curr_path, include_root )
            .replace_extension( "cpp" );
      fs::path const target
        = fs::relative( curr_path, qbk_file.parent_path() );
      std::string const component = qbk_file.stem().string();

      bool const is_top_level
        = qbk_file.parent_path().stem().string() == "reference";

      std::string const group_name
        =   is_top_level
          ? std::string( "argot" )
          : qbk_file.parent_path().stem().string();

      std::string const elaborate_component
        = section_name_from_path( header );

      bool const has_example_file = fs::is_regular_file( example_file );

      // Skip namespace convenience headers (for now)
      if( is_namespace_convenience_header( curr_path ) )
        return;

      create_license_comment( os, file_kind::quickbook );

      os
        << "\n"
           "[section:" << component << ' ' << elaborate_component << "]\n"
           "\n"
           "[import " << target.string() << "]\n";

      if( has_example_file )
        os << "[import " << example_file.string() << "]\n";

      os
        << "[description_heading]\n"
           "[description]\n";

      if( is_top_level )
        os << "[top_header_spec " << component << "]\n";
      else
        os << "[header_spec " << group_name << ".." << component << "]\n";

      os << "[docs]\n";

      if( has_example_file ) 
        os << "[example_usage_heading]\n"
              "[example]\n";

      os
        << "\n"
           "[endsect:" << component << "]\n";

      fs::create_directories( qbk_file.parent_path() );
      std::ofstream file( qbk_file.string() );
      file << std::move( os ).str();
    }
  );
}

void create_reference_section
( path const& include_root, path const& doc_root, path const& example_root )
{
  std::ostringstream os;

  create_license_comment( os, file_kind::quickbook );

  create_reference_section_files( include_root, doc_root, example_root );

  os << "\n"
        "[chapter _Reference_\n"
        "  [quickbook 1.7]\n"
        "  [id argot.ref]\n"
        "]\n"
        "\n";

  create_reference_section_group
  ( os, include_root, doc_root
  , "gen", "Argot.Gen"
  );

  create_reference_section_group
  ( os, include_root, doc_root
  , "concepts", "Concepts"
  );

  create_reference_section_group
  ( os, include_root, doc_root
  , "./", "Top-Level Facilities"
  );

  create_reference_section_group
  ( os, include_root, doc_root, "prov", "Argument Providers" );

  create_reference_section_group
  ( os, include_root, doc_root, "prov_traits", "Argument Provider Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "receiver", "Argument Receivers" );

  create_reference_section_group
  ( os, include_root, doc_root, "receiver_traits", "Argument Receiver Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "conc", "Concurrent Argument Providers" );

  create_reference_section_group
  ( os, include_root, doc_root
  , "conc_traits", "Concurrent Argument Provider Traits"
  );

  create_reference_section_group
  ( os, include_root, doc_root, "executor", "Executors" );

  create_reference_section_group
  ( os, include_root, doc_root, "executor_traits", "_Executor_ Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "fut", "Futures" );

  create_reference_section_group
  ( os, include_root, doc_root, "fut_traits", "_Future_ Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "opt_traits", "_OptionalLike_ Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "packager", "_Future_ Packagers" );

  create_reference_section_group
  ( os, include_root, doc_root, "packager_traits", "_Future_ Packager Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "reducer", "Return Value Reducers" );

  create_reference_section_group
  ( os, include_root, doc_root
  , "reducer_traits", "Return Value Reducer Traits"
  );

  create_reference_section_group
  ( os, include_root, doc_root, "state_traits", "State Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "switch_traits", "_SwitchBody_ Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "tuple_traits", "_TupleLike_ Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "union_traits", "_UnionLike_ Traits" );

  create_reference_section_group
  ( os, include_root, doc_root, "variant_traits", "_VariantLike_ Traits" );

  fs::path const argot_doc_root = doc_root / "argot";
  fs::create_directories( argot_doc_root );
  std::ofstream file( ( argot_doc_root / "reference.qbk" ).string() );
  file << std::move( os ).str();
}

}  // namespace

int main()
{
  // TODO(mattcalabrese) Delete all reference headers before-hand.

  path const include_root( "../include" );
  path const doc_root( "../doc" );
  path const example_root( "../example" );

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

  {
    std::ostringstream os;

    create_license_comment( os, file_kind::quickbook );

    create_quickbook_links
    ( os, include_root, path( "argot" ), "argot" );

    create_quickbook_links
    ( os, include_root, path( "argot/conc" ), "conc" );

    create_quickbook_links
    ( os, include_root, path( "argot/conc_traits" ), "conc_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/executor" ), "executor" );

    create_quickbook_links
    ( os, include_root, path( "argot/executor_traits" ), "executor_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/fut" ), "fut" );

    create_quickbook_links
    ( os, include_root, path( "argot/fut_traits" ), "fut_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/opt_traits" ), "opt_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/packager" ), "packager" );

    create_quickbook_links
    ( os, include_root, path( "argot/packager_traits" ), "packager_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/prov" ), "prov" );

    create_quickbook_links
    ( os, include_root, path( "argot/prov_traits" ), "prov_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/receiver" ), "receiver" );

    create_quickbook_links
    ( os, include_root, path( "argot/receiver_traits" ), "receiver_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/reducer" ), "reducer" );

    create_quickbook_links
    ( os, include_root, path( "argot/reducer_traits" ), "reducer_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/state_traits" ), "state_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/switch_traits" ), "switch_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/tuple_traits" ), "tuple_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/union_traits" ), "union_traits" );

    create_quickbook_links
    ( os, include_root, path( "argot/variant_traits" ), "variant_traits" );

    create_concept_quickbook_links
    ( os, include_root, path( "argot/concepts" ) );

    create_header_quickbook_links( os, include_root, doc_root );

    create_reference_section( include_root, doc_root, example_root );

    path const quickbook_links_path = doc_root / "quickbook_links.qbk";

    std::ofstream file( quickbook_links_path.string() );
    file << std::move( os ).str();
  }
}
