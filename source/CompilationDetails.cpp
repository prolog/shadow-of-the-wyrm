#include <sstream>
#include "CompilationDetails.hpp"

using namespace std;

// Get a list of strings, each of which represents a compilation detail,
// such as:
// - target platform
// - compiler
// - additional compile time options (debug, unit tests, etc)
vector<string> CompilationDetails::get_compilation_details() const
{
  vector<string> comp_details;

  comp_details.push_back(get_platform());
  comp_details.push_back(get_compiler());

  vector<string> compile_options = get_compile_time_options();
  comp_details.insert(comp_details.end(), compile_options.begin(), compile_options.end());

  return comp_details;
}

// Get the compilation details as a comma-separated string.
string CompilationDetails::get_compilation_details_string() const
{
  ostringstream oss;

  vector<string> comp_details = get_compilation_details();
  size_t cd_size = comp_details.size();

  for (size_t i = 0; i < cd_size; i++)
  {
    oss << comp_details.at(i);

    if (i < (cd_size - 1))
    {
      oss << ", ";
    }
  }

  return oss.str();
}

// Get the OS/platform used to compile the binary.
string CompilationDetails::get_platform() const
{
  ostringstream oss;

  #ifdef _WIN64
  oss << "Win64";
  #elif defined(_WIN32)
  oss << "Win32";
  #else
  // This needs to be filled in when porting to Linux/FreeBSD/MacOS/etc.
  static_assert(false, "Platform not recognized");
  #endif

  return oss.str();
}

// Get the compiler used to compile the binary.
string CompilationDetails::get_compiler() const
{
  ostringstream compiler_details;

  #ifdef _MSC_VER
  compiler_details << "MSVC " << _MSC_VER;
  #else
  // This needs to be filled in when porting to use gcc/etc
  static_assert(false, "Unrecognized compiler.");
  #endif

  return compiler_details.str();
}

// Get any specific compile-time options.
vector<string> CompilationDetails::get_compile_time_options() const
{
  vector<string> ct_options;

  #ifdef _DEBUG
  ct_options.push_back("debug");
  #endif

  #ifdef UNIT_TESTS
  ct_options.push_back("unit tests");
  #endif
  
  return ct_options;
}

