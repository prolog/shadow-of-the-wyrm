#include "Conversion.hpp"
#include "CursesConstants.hpp"
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
void EquipmentKeyboardCommandMap::initialize_command_mapping(const Settings& /*settings*/)
{
  command_mapping.clear();
  string esc_str;
  esc_str = NC_ESCAPE_KEY;

  command_mapping = KeyboardCommandMappingMap{ {"a", EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD},
                        {"A", EquipmentCommandKeys::CODEX},
                        {"b", EquipmentCommandKeys::WEAR_OR_REMOVE_NECK},
                        {"B", EquipmentCommandKeys::CODEX},
                        {"c", EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER},
                        {"C", EquipmentCommandKeys::CODEX},
                        {"d", EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER},
                        {"D", EquipmentCommandKeys::CODEX},
                        {"e", EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED},
                        {"E", EquipmentCommandKeys::CODEX},
                        {"f", EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND},
                        {"F", EquipmentCommandKeys::CODEX},
                        {"g", EquipmentCommandKeys::WEAR_OR_REMOVE_BODY},
                        {"G", EquipmentCommandKeys::CODEX},
                        {"h", EquipmentCommandKeys::WEAR_OR_REMOVE_AROUND_BODY},
                        {"H", EquipmentCommandKeys::CODEX},
                        {"i", EquipmentCommandKeys::WEAR_OR_REMOVE_FEET},
                        {"I", EquipmentCommandKeys::CODEX},
                        {"j", EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED},
                        {"J", EquipmentCommandKeys::CODEX},
                        {"k", EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION},
                        {"K", EquipmentCommandKeys::CODEX},
                        {"y", EquipmentCommandKeys::YOUR_ITEMS},
                        {"Y", EquipmentCommandKeys::YOUR_ITEMS},
                        {"z", EquipmentCommandKeys::EXIT_EQUIPMENT},
                        {"Z", EquipmentCommandKeys::EXIT_EQUIPMENT},
                        {esc_str, EquipmentCommandKeys::EXIT_EQUIPMENT}
                        };
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
  return ClassIdentifier::CLASS_ID_EQUIPMENT_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/EquipmentKeyboardCommandMap_test.cpp"
#endif
