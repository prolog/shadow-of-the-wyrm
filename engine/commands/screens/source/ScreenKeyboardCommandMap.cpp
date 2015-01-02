#include "Conversion.hpp"
#include "ScreenCommandKeys.hpp"
#include "ScreenKeyboardCommandMap.hpp"

using namespace std;

ScreenKeyboardCommandMap::ScreenKeyboardCommandMap()
{
}

ScreenKeyboardCommandMap::~ScreenKeyboardCommandMap()
{
}

void ScreenKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Fail silently.
  }
}

// The Screen command map only contains the commands necessary for each and every
// Screen - moving back and forth between pages, if they exist.
//
// Settings currently does nothing here.
void ScreenKeyboardCommandMap::initialize_command_mapping(const Settings& settings)
{
  command_mapping.clear();

  command_mapping.insert(make_pair(",", ScreenCommandKeys::PREVIOUS_PAGE));
  command_mapping.insert(make_pair(".", ScreenCommandKeys::NEXT_PAGE));
}

KeyboardCommandMap* ScreenKeyboardCommandMap::clone()
{
  return new ScreenKeyboardCommandMap(*this);
}

string ScreenKeyboardCommandMap::get_settings_prefix() const
{
  return "key_scr_";
}

ClassIdentifier ScreenKeyboardCommandMap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCREEN_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScreenKeyboardCommandMap_test.cpp"
#endif
