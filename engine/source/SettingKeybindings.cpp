#include <boost/algorithm/string.hpp>
#include "SettingKeybindings.hpp"

using namespace std;

vector<string> SettingKeybindings::get_keybindings(const string& setting) const
{
  vector<string> keybindings;

  if (!setting.empty())
  {
    boost::split(keybindings, setting, boost::is_any_of("|"));
  }

  return keybindings;
}

#ifdef UNIT_TESTS
#include "unit_tests/SettingKeybindings_test.cpp"
#endif