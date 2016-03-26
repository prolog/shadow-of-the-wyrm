#include "CursesConstants.hpp"
#include "HelpCommandKeys.hpp"
#include "HelpKeyboardCommandMap.hpp"

using namespace std;

HelpKeyboardCommandMap::HelpKeyboardCommandMap()
{
}

HelpKeyboardCommandMap::~HelpKeyboardCommandMap()
{
}

void HelpKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Fail silently.
  }
}

// Settings currently does nothing here.
void HelpKeyboardCommandMap::initialize_command_mapping(const Settings& settings)
{
  string esc_key;
  esc_key = NC_ESCAPE_KEY;

  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{ { std::to_string('a'), HelpCommandKeys::INTRODUCTION_ROGUELIKES },
  { std::to_string('b'), HelpCommandKeys::SOTW_HISTORY },
  { std::to_string('c'), HelpCommandKeys::STRATEGY_BASICS },
  { std::to_string('d'), HelpCommandKeys::KEYBINDINGS },
  { std::to_string('z'), HelpCommandKeys::EXIT_HELP },
  { std::to_string('Z'), HelpCommandKeys::EXIT_HELP },
  { std::to_string(NC_ESCAPE_KEY), HelpCommandKeys::EXIT_HELP },
  { esc_key, HelpCommandKeys::EXIT_HELP } };

}

KeyboardCommandMap* HelpKeyboardCommandMap::clone()
{
  return new HelpKeyboardCommandMap(*this);
}

string HelpKeyboardCommandMap::get_settings_prefix() const
{
  return "key_help_";
}

ClassIdentifier HelpKeyboardCommandMap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HELP_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/HelpKeyboardCommandMap_test.cpp"
#endif
