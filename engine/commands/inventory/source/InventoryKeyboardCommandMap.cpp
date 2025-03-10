#include <ctype.h>
#include "Conversion.hpp"
#include "CursesConstants.hpp"
#include "InventoryCommandKeys.hpp"
#include "InventoryKeyboardCommandMap.hpp"

using namespace std;

const string InventoryKeyboardCommandMap::FILTER_UNPAID = "~";
const string InventoryKeyboardCommandMap::SELECT_ALL = "*";

InventoryKeyboardCommandMap::InventoryKeyboardCommandMap()
{
}

InventoryKeyboardCommandMap::~InventoryKeyboardCommandMap()
{
}

// Fail silently - no msg buffer on inventory screen.
void InventoryKeyboardCommandMap::command_not_found(const std::string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Do nothing.
  }
}

// Settings currently does nothing here.
void InventoryKeyboardCommandMap::initialize_command_mapping(const Settings& /*settings*/)
{
  string esc_key;
  esc_key = NC_ESCAPE_KEY;

  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{{"z", InventoryCommandKeys::EXIT_INVENTORY},
                                              {"Z", InventoryCommandKeys::EXIT_INVENTORY},
                                              {esc_key, InventoryCommandKeys::EXIT_INVENTORY},
                                              {"*", InventoryCommandKeys::SELECT_ITEM},
                                              {"`", InventoryCommandKeys::CLEAR_FILTER},
                                              {"~", InventoryCommandKeys::FILTER_VIEW},
                                              {"]", InventoryCommandKeys::FILTER_VIEW},
                                              {")", InventoryCommandKeys::FILTER_VIEW},
                                              {"[", InventoryCommandKeys::FILTER_VIEW},
                                              {"!", InventoryCommandKeys::FILTER_VIEW},
                                              {"\"", InventoryCommandKeys::FILTER_VIEW},
                                              {"?", InventoryCommandKeys::FILTER_VIEW},
                                              {"\\", InventoryCommandKeys::FILTER_VIEW},
                                              {"|", InventoryCommandKeys::FILTER_VIEW},
                                              {"=", InventoryCommandKeys::FILTER_VIEW},
                                              {"+", InventoryCommandKeys::FILTER_VIEW},
                                              {"%", InventoryCommandKeys::FILTER_VIEW},
                                              {"/", InventoryCommandKeys::FILTER_VIEW},
                                              {"#", InventoryCommandKeys::FILTER_VIEW},
                                              {"&", InventoryCommandKeys::FILTER_VIEW},
                                              {"$", InventoryCommandKeys::FILTER_VIEW},
                                              {"(", InventoryCommandKeys::FILTER_VIEW},
                                              };

  // Selection and codex commands.
  // 'z'/'Z' is reserved for exit.
  for (char i = 'a'; i <= 'y'; i++)
  {
    command_mapping.insert(make_pair(string(1, i), InventoryCommandKeys::SELECT_ITEM));
    command_mapping.insert(make_pair(string(1, static_cast<char>(toupper(i))), InventoryCommandKeys::CODEX));
  }
}

KeyboardCommandMap* InventoryKeyboardCommandMap::clone()
{
  return new InventoryKeyboardCommandMap(*this);
}

string InventoryKeyboardCommandMap::get_settings_prefix() const
{
  return "key_inv_";
}

ClassIdentifier InventoryKeyboardCommandMap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/InventoryKeyboardCommandMap_test.cpp"
#endif

