#include "Conversion.hpp"
#include "MenuCommandKeys.hpp"
#include "MenuKeyboardCommandMap.hpp"

using namespace std;

MenuKeyboardCommandMap::MenuKeyboardCommandMap()
{
}

MenuKeyboardCommandMap::~MenuKeyboardCommandMap()
{
}

void MenuKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Fail silently.
  }
}

// The menu command map only contains the commands necessary for each and every
// menu - moving back and forth between pages, if they exist.
void MenuKeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{ { Integer::to_string('.'), MenuCommandKeys::NEXT_PAGE },
  { Integer::to_string(','), MenuCommandKeys::PREVIOUS_PAGE }};
}

KeyboardCommandMap* MenuKeyboardCommandMap::clone()
{
  return new MenuKeyboardCommandMap(*this);
}

ClassIdentifier MenuKeyboardCommandMap::internal_class_identifier() const
{
  return CLASS_ID_MENU_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/MenuKeyboardCommandMap_test.cpp"
#endif
