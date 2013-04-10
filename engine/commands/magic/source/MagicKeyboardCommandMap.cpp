#include "Conversion.hpp"
#include "MagicCommandKeys.hpp"
#include "MagicKeyboardCommandMap.hpp"

using namespace std;

MagicKeyboardCommandMap::MagicKeyboardCommandMap()
{
}

MagicKeyboardCommandMap::~MagicKeyboardCommandMap()
{
}

void MagicKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Fail silently.
  }
}

void MagicKeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();

  // Select a spell
  for (char c = 'a'; c < 'z'; c++)
  {
    // a - y should select a spell (or do nothing, if there are not that many spells in the list).
    command_mapping.insert(make_pair(Integer::to_string(c), MagicCommandKeys::SELECT_SPELL));
  }

  // Next page
  command_mapping.insert(make_pair(Integer::to_string('+'), MagicCommandKeys::NEXT_PAGE));

  // Previous page
  command_mapping.insert(make_pair(Integer::to_string('-'), MagicCommandKeys::PREVIOUS_PAGE));

  // Exit
  command_mapping.insert(make_pair(Integer::to_string('z'), MagicCommandKeys::EXIT_MAGIC));
  command_mapping.insert(make_pair(Integer::to_string('Z'), MagicCommandKeys::EXIT_MAGIC));
}

KeyboardCommandMap* MagicKeyboardCommandMap::clone()
{
  return new MagicKeyboardCommandMap(*this);
}

ClassIdentifier MagicKeyboardCommandMap::internal_class_identifier() const
{
  return CLASS_ID_MAGIC_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicKeyboardCommandMap_test.cpp"
#endif
