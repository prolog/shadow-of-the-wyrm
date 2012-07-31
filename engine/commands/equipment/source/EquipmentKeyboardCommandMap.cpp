#include "Conversion.hpp"
#include "EquipmentCommandKeys.hpp"
#include "EquipmentKeyboardCommandMap.hpp"

using std::string;

EquipmentKeyboardCommandMap::EquipmentKeyboardCommandMap()
{
}

EquipmentKeyboardCommandMap::~EquipmentKeyboardCommandMap()
{
}

void EquipmentKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Right now, do nothing.
  }
}

void EquipmentKeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();

  // Head
  command_mapping.insert(make_pair(Integer::to_string('a'), EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD));
  command_mapping.insert(make_pair(Integer::to_string('A'), EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD));

  // Neck
  command_mapping.insert(make_pair(Integer::to_string('b'), EquipmentCommandKeys::WEAR_OR_REMOVE_NECK));
  command_mapping.insert(make_pair(Integer::to_string('B'), EquipmentCommandKeys::WEAR_OR_REMOVE_NECK));

  // Right finger
  command_mapping.insert(make_pair(Integer::to_string('c'), EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER));
  command_mapping.insert(make_pair(Integer::to_string('C'), EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER));

  // Left finger
  command_mapping.insert(make_pair(Integer::to_string('d'), EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER));
  command_mapping.insert(make_pair(Integer::to_string('D'), EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER));

  // Right hand
  command_mapping.insert(make_pair(Integer::to_string('e'), EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED));
  command_mapping.insert(make_pair(Integer::to_string('E'), EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED));

  // Left hand
  command_mapping.insert(make_pair(Integer::to_string('f'), EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND));
  command_mapping.insert(make_pair(Integer::to_string('F'), EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND));

  // Body
  command_mapping.insert(make_pair(Integer::to_string('g'), EquipmentCommandKeys::WEAR_OR_REMOVE_BODY));
  command_mapping.insert(make_pair(Integer::to_string('G'), EquipmentCommandKeys::WEAR_OR_REMOVE_BODY));

  // About body
  command_mapping.insert(make_pair(Integer::to_string('h'), EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY));
  command_mapping.insert(make_pair(Integer::to_string('H'), EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY));

  // Feet
  command_mapping.insert(make_pair(Integer::to_string('i'), EquipmentCommandKeys::WEAR_OR_REMOVE_FEET));
  command_mapping.insert(make_pair(Integer::to_string('I'), EquipmentCommandKeys::WEAR_OR_REMOVE_FEET));
  
  // Ranged
  command_mapping.insert(make_pair(Integer::to_string('j'), EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED));
  command_mapping.insert(make_pair(Integer::to_string('J'), EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED));
  
  // Ammunition
  command_mapping.insert(make_pair(Integer::to_string('k'), EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION));
  command_mapping.insert(make_pair(Integer::to_string('K'), EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION));

  // View inventory
  command_mapping.insert(make_pair(Integer::to_string('y'), EquipmentCommandKeys::YOUR_ITEMS));
  command_mapping.insert(make_pair(Integer::to_string('Y'), EquipmentCommandKeys::YOUR_ITEMS));

  // Quit inventory
  command_mapping.insert(make_pair(Integer::to_string('z'), EquipmentCommandKeys::EXIT_EQUIPMENT));
  command_mapping.insert(make_pair(Integer::to_string('Z'), EquipmentCommandKeys::EXIT_EQUIPMENT));
}
