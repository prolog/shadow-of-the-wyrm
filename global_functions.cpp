#include <sstream>
#include "buildinfo.hpp"
#include "global_prototypes.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"

using namespace std;

/*
 ******************************************************************

 	Get the current version of Savage Lands

 ******************************************************************/
string get_version()
{
	stringstream ss;
	ss << MAJOR_VERSION << "." << MINOR_VERSION << "." << REVISION;
	string version = ss.str();
	return version;
}

/*
 *******************************************************************

  Get the current version's code name.

 *******************************************************************/
string get_code_name()
{
  return "\"Knut\"";
}

/*
 *******************************************************************

  Get a game version synopsis: Name version "codename"

 *******************************************************************/
string get_game_version_synopsis()
{
  string game_name = StringTable::get(TextKeys::SL_TITLE);
  string version = get_version();
  string code_name = get_code_name();

  return game_name + " " + version + " " + code_name;
}

// Get the poem for the title screen.
string get_title_poem()
{
  string title_poem = StringTable::get(TextKeys::SL_TITLE_POEM);
  return title_poem;
}
