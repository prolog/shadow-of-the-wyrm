#include <sstream>
#include "buildinfo.hpp"
#include "Environment.hpp"
#include "global_prototypes.hpp"
#include "Metadata.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"

using namespace std;

bool Metadata::operator==(const Metadata& meta)
{
  bool result = true;

  return result;
}

string Metadata::get_user_name() const
{
  return Environment::get_user_name();
}

string Metadata::get_version() const
{
	stringstream ss;
	ss << MAJOR_VERSION << "." << MINOR_VERSION << "." << REVISION;
	string version = ss.str();
	return version;
}

string Metadata::get_code_name() const
{
  // "Son" of Aelle, disputedly.  Second king of Sussex, also disputedly.
  return "\"Cissa\"";
}

string Metadata::get_game_version_synopsis() const
{
  string game_name = StringTable::get(TextKeys::SL_TITLE);
  string version = get_version();
  string code_name = get_code_name();

  return game_name + " " + version + " " + code_name;
}

string Metadata::get_compiler_details() const
{
  ostringstream compiler_details;

  #ifdef _MSC_VER
  compiler_details << "MSVC " << _MSC_VER;

    #ifdef _M_IX86
    compiler_details << " x86 ";
    #endif

    #ifdef _M_IA64
    compiler_details << " IA64 ";
    #endif

    #ifdef _M_X64
    compiler_details << " x64 ";
    #endif
  #else
  // This needs to be filled in when porting to use gcc/etc
  BOOST_STATIC_ASSERT( false );
  #endif

  return compiler_details.str();
}


bool Metadata::serialize(ostream& stream)
{
  Serialize::write_string(stream, get_user_name());
  Serialize::write_string(stream, get_version());
  Serialize::write_string(stream, get_compiler_details());

  return true;
}

bool Metadata::deserialize(istream& stream)
{
  // The metadata has no actual state, so just consume the values
  // and forget them.
  Serialize::consume_string(stream);
  Serialize::consume_string(stream);
  Serialize::consume_string(stream);

  return true;
}

ClassIdentifier Metadata::internal_class_identifier() const
{
  return CLASS_ID_METADATA;
}

#ifdef UNIT_TESTS
#include "unit_tests/Metadata_test.cpp"
#endif

