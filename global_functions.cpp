#include <sstream>
#include <boost/algorithm/string/replace.hpp>
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
  // First king of Sussex
  return "\"Aelle\"";
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

// Convert a colour to an HTML colour string - used by the map tester.
// Convert a colour to an HTML hex code.
std::string convert_colour_to_hex_code(const Colours colour)
{
  std::string hex_code;
  
  switch (colour)
  {
    case COLOUR_UNDEFINED:
    case COLOUR_BLACK:
      hex_code = "#000000";
      break;
    case COLOUR_RED:
      hex_code = "#8B0000";
      break;
    case COLOUR_GREEN:
      hex_code = "#008000";
      break;
    case COLOUR_YELLOW:
      hex_code = "#B8860B";
      break;
    case COLOUR_BLUE:
      hex_code = "#00008B";
      break;
    case COLOUR_MAGENTA:
      hex_code = "#8B008B";
      break;
    case COLOUR_CYAN:
      hex_code = "#00FFFF";
      break;
    case COLOUR_WHITE:
      hex_code = "#DCDCDC";
      break;
    case COLOUR_BOLD_BLACK:
      hex_code = "#696969";
      break;
    case COLOUR_BOLD_RED:
      hex_code = "#FF0000";
      break;
    case COLOUR_BOLD_GREEN:
      hex_code = "#7CFC00";
      break;
    case COLOUR_BOLD_YELLOW:
      hex_code = "#FFFF00";
      break;
    case COLOUR_BOLD_BLUE:
      hex_code = "#0000FF";
      break;
    case COLOUR_BOLD_MAGENTA:
      hex_code = "#FF00FF";
      break;
    case COLOUR_BOLD_CYAN:
      hex_code = "#E0FFFF";
      break;
    case COLOUR_BOLD_WHITE:
      hex_code = "#F8FFFF";
      break;
    default:
      break;
  }
  
  return hex_code;
}

// HTML encode a string
std::string html_encode(const std::string& str)
{
  string replace = str;
  
  using boost::algorithm::replace_all;
  replace_all(replace, "&",  "&amp;");
  replace_all(replace, "\"", "&quot;");
  replace_all(replace, "\'", "&apos;");
  replace_all(replace, "<",  "&lt;");
  replace_all(replace, ">",  "&gt;");
  
  return replace;
}
