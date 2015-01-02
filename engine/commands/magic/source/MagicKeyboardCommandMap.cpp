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

// Settings currently does nothing here.
void MagicKeyboardCommandMap::initialize_command_mapping(const Settings& settings)
{
  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{{Integer::to_string('.'), MagicCommandKeys::NEXT_PAGE},
                                              {Integer::to_string(','), MagicCommandKeys::PREVIOUS_PAGE},
                                              {Integer::to_string('z'), MagicCommandKeys::EXIT_MAGIC},
                                              {Integer::to_string('Z'), MagicCommandKeys::EXIT_MAGIC}};

  // Select a spell
  for (char c = 'a'; c < 'z'; c++)
  {
    // a - y should select a spell (or do nothing, if there are not that many spells in the list).
    command_mapping.insert(make_pair(Integer::to_string(c), MagicCommandKeys::SELECT_SPELL));
  }
}

KeyboardCommandMap* MagicKeyboardCommandMap::clone()
{
  return new MagicKeyboardCommandMap(*this);
}

string MagicKeyboardCommandMap::get_settings_prefix() const
{
  return "key_mag_";
}

ClassIdentifier MagicKeyboardCommandMap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAGIC_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicKeyboardCommandMap_test.cpp"
#endif
