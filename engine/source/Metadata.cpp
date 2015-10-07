#include <sstream>
#include "buildinfo.hpp"
#include "CompilationDetails.hpp"
#include "CreatureDescriber.hpp"
#include "Environment.hpp"
#include "global_prototypes.hpp"
#include "Metadata.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

Metadata::Metadata(CreaturePtr creature)
: player(creature)
{
}

Metadata::Metadata()
{
}

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
  // Italian guitarist and composer of the classical period.
  return "\"Carcassi\"";
}

string Metadata::get_game_version_synopsis() const
{
  ostringstream oss;

  string game_name = StringTable::get(TextKeys::SW_TITLE);
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

  CreatureDescriber cdesc(player, player);
  Serialize::write_string(stream, cdesc.describe_for_save_file());

  return true;
}

bool Metadata::deserialize(istream& stream)
{
  // The metadata has no actual state, so just consume the values
  // and forget them.
  Serialize::consume_string(stream); // user name
  Serialize::consume_string(stream); // version
  Serialize::consume_string(stream); // compilation details
  Serialize::consume_string(stream); // character synopsis

  return true;
}

ClassIdentifier Metadata::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_METADATA;
}

#ifdef UNIT_TESTS
#include "unit_tests/Metadata_test.cpp"
#endif

