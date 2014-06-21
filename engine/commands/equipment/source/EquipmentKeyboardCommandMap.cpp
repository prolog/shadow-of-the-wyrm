#include "Conversion.hpp"
#include "EquipmentCommandKeys.hpp"
#include "EquipmentKeyboardCommandMap.hpp"

using namespace std;

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

// Settings currently does nothing here.
void EquipmentKeyboardCommandMap::initialize_command_mapping(const Settings& settings)
{
  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{ {"a", EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD},
                        {"A", EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD},
                        {"b", EquipmentCommandKeys::WEAR_OR_REMOVE_NECK},
                        {"B", EquipmentCommandKeys::WEAR_OR_REMOVE_NECK},
                        {"c", EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER},
                        {"C", EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER},
                        {"d", EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER},
                        {"D", EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER},
                        {"e", EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED},
                        {"E", EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED},
                        {"f", EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND},
                        {"F", EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND},
                        {"g", EquipmentCommandKeys::WEAR_OR_REMOVE_BODY},
                        {"G", EquipmentCommandKeys::WEAR_OR_REMOVE_BODY},
                        {"h", EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY},
                        {"H", EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY},
                        {"i", EquipmentCommandKeys::WEAR_OR_REMOVE_FEET},
                        {"I", EquipmentCommandKeys::WEAR_OR_REMOVE_FEET},
                        {"j", EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED},
                        {"J", EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED},
                        {"k", EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION},
                        {"K", EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION},
                        {"y", EquipmentCommandKeys::YOUR_ITEMS},
                        {"Y", EquipmentCommandKeys::YOUR_ITEMS},
                        {"z", EquipmentCommandKeys::EXIT_EQUIPMENT},
                        {"Z", EquipmentCommandKeys::EXIT_EQUIPMENT}};
}

string EquipmentKeyboardCommandMap::get_settings_prefix() const
{
  return "key_eq_";
}

KeyboardCommandMap* EquipmentKeyboardCommandMap::clone()
{
  return new EquipmentKeyboardCommandMap(*this);
}

ClassIdentifier EquipmentKeyboardCommandMap::internal_class_identifier() const
{
  return CLASS_ID_EQUIPMENT_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/EquipmentKeyboardCommandMap_test.cpp"
#endif
