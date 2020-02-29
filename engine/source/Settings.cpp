#include <boost/algorithm/string/predicate.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include "Conversion.hpp"
#include "Environment.hpp"
#include "Serialize.hpp"
#include "Settings.hpp"

using namespace std;

const string Settings::SETTINGS_FILENAME = "swyrm.ini";
const string Settings::KEYBINDING_PREFIX = "key_";

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
        throw std::runtime_error("Could not find a copy of swyrm.ini");
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

void Settings::set_setting(const string& name, const string& val)
{
  settings_tree.put(name, val);
}

void Settings::set_settings(const map<string, string>& addl_settings)
{
  for (const auto& s_pair : addl_settings)
  {
    settings_tree.put(s_pair.first, s_pair.second);
  }
}

// Get all the keybindings.  Keybindings are the settings that start with 
// "key_".
map<string, string> Settings::get_keybindings() const
{
  map<string, string> keybindings;

  for (boost::property_tree::ptree::const_iterator iter = settings_tree.begin(); iter != settings_tree.end(); iter++)
  {
    string key = iter->first;

    if (boost::starts_with(key, KEYBINDING_PREFIX))
    {
      keybindings[iter->first] = iter->second.data();
    }
  }

  return keybindings;
}

bool Settings::get_setting_as_bool(const string& key, const bool default_val) const
{
  string setting = get_setting(key);
  bool settingb = default_val;

  if (!setting.empty())
  {
    settingb = String::to_bool(get_setting(key));
  }

  return settingb;  
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
