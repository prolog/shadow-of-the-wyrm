#include <ctype.h>
#include "Conversion.hpp"
#include "InventoryCommandKeys.hpp"
#include "InventoryKeyboardCommandMap.hpp"

using std::string;

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

void InventoryKeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();

  // Selection commands.
  // 'z'/'Z' is reserved for exit.
  for (int i = 'a'; i <= 'y'; i++)
  {
    command_mapping.insert(make_pair(Integer::to_string(i), InventoryCommandKeys::SELECT_ITEM));
    command_mapping.insert(make_pair(Integer::to_string(toupper(i)), InventoryCommandKeys::SELECT_ITEM));
  }
  
  // Exit
  command_mapping.insert(make_pair(Integer::to_string('z'), InventoryCommandKeys::EXIT_INVENTORY));
  command_mapping.insert(make_pair(Integer::to_string('Z'), InventoryCommandKeys::EXIT_INVENTORY));

  // Clear the filter - display all applicable
  command_mapping.insert(make_pair(Integer::to_string('/'), InventoryCommandKeys::CLEAR_FILTER));

  // Apply a filter
  // JCD FIXME DO THIS LATER

  // Next page
  command_mapping.insert(make_pair(Integer::to_string('.'), InventoryCommandKeys::NEXT_PAGE));

  // Previous page
  command_mapping.insert(make_pair(Integer::to_string(','), InventoryCommandKeys::PREVIOUS_PAGE));
}

KeyboardCommandMap* InventoryKeyboardCommandMap::clone()
{
  return new InventoryKeyboardCommandMap(*this);
}

ClassIdentifier InventoryKeyboardCommandMap::internal_class_identifier() const
{
  return CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/InventoryKeyboardCommandMap_test.cpp"
#endif

