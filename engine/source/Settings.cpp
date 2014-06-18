#include <boost/property_tree/ini_parser.hpp>
#include "Environment.hpp"
#include "Settings.hpp"

using namespace std;

// Find the ini file (first check the user's home directory, then the
// game directory).  Parse it into the boost::ptree so that it can be
// later queried for languages, keybindings, etc.
Settings::Settings()
{
  string home_dir = Environment::get_user_home_directory();
}

