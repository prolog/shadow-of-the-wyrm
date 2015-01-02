#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include "Environment.hpp"
#include "Serialize.hpp"
#include "Settings.hpp"

using namespace std;

const string Settings::SETTINGS_FILENAME = "slands.ini";

// Find the ini file (first check the user's home directory, then the
// game directory).  Parse it into the boost::ptree so that it can be
// later queried for languages, keybindings, etc.
Settings::Settings(const bool read_from_disk)
{
  if (read_from_disk)
  {
    string home_dir = Environment::get_user_home_directory();
    string ini_file_loc = home_dir + SETTINGS_FILENAME;

    if (!boost::filesystem::exists(ini_file_loc))
    {
      ini_file_loc = SETTINGS_FILENAME;

      // There was no per-user slands.ini file - use the one in the main game
      // directory.
      if (!boost::filesystem::exists(SETTINGS_FILENAME))
      {
        throw std::runtime_error("Could not find a copy of slands.ini");
      }
    }

    boost::property_tree::ini_parser::read_ini(ini_file_loc, settings_tree);
  }
}

// Look up a setting
string Settings::get_setting(const string& key) const
{
  string setting;

  setting = settings_tree.get<string>(key, "");

  return setting;
}

bool Settings::serialize(ostream& stream) const
{
  stringstream ss;
  boost::property_tree::write_ini(ss, settings_tree);
  string prop_str = ss.str();

  Serialize::write_string(stream, prop_str);

  return true;
}

bool Settings::deserialize(istream& stream)
{
  string prop_str;
  Serialize::read_string(stream, prop_str);
  stringstream ss;
  ss << prop_str;

  boost::property_tree::read_ini(ss, settings_tree);

  return true;
}

ClassIdentifier Settings::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SETTINGS;
}
