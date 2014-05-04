#include <sstream>
#include "buildinfo.hpp"
#include "CompilationDetails.hpp"
#include "Environment.hpp"
#include "global_prototypes.hpp"
#include "Metadata.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

bool Metadata::operator==(const Metadata& meta) const
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
  // First king of Bernicia (Northumberland)
  return "\"Esa\"";
}

string Metadata::get_game_version_synopsis() const
{
  ostringstream oss;

  string game_name = StringTable::get(TextKeys::SL_TITLE);
  string version = get_version();
  string code_name = get_code_name();

  oss << game_name << " " << version << " " << code_name;

  return oss.str();
}

// Get the game version information with additional platform, compiler,
// and compile-time details.
string Metadata::get_full_game_version_details() const
{
  ostringstream oss;
  CompilationDetails cd;

  oss << get_game_version_synopsis() << " (" << cd.get_compilation_details_string() << ")";

  return oss.str();
}

bool Metadata::serialize(ostream& stream) const
{
  CompilationDetails cd;

  Serialize::write_string(stream, get_user_name());
  Serialize::write_string(stream, get_version());
  Serialize::write_string(stream, cd.get_compilation_details_string());

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

