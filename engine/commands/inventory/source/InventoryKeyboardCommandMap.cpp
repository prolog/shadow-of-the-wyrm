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
