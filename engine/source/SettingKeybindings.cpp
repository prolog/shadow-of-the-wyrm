#include <boost/algorithm/string.hpp>
#include "SettingKeybindings.hpp"

using namespace std;

vector<string> SettingKeybindings::get_keybindings(const string& setting) const
{
  vector<string> keybindings;
  size_t pos = setting.find("=");

  if (pos != string::npos && pos != setting.size()-1)
  {
    string val = setting.substr(pos+1, string::npos);
    boost::split(keybindings, val, boost::is_any_of("|"));
  }

  return keybindings;
}

#ifdef UNIT_TESTS
#include "unit_tests/SettingKeybindings_test.cpp"
#endif