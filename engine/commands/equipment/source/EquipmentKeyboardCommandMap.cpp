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

void EquipmentKeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{ {Integer::to_string('a'), EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD},
                        {Integer::to_string('A'), EquipmentCommandKeys::WEAR_OR_REMOVE_HEAD},
                        {Integer::to_string('b'), EquipmentCommandKeys::WEAR_OR_REMOVE_NECK},
                        {Integer::to_string('B'), EquipmentCommandKeys::WEAR_OR_REMOVE_NECK},
                        {Integer::to_string('c'), EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER},
                        {Integer::to_string('C'), EquipmentCommandKeys::WEAR_OR_REMOVE_RIGHT_FINGER},
                        {Integer::to_string('d'), EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER},
                        {Integer::to_string('D'), EquipmentCommandKeys::WEAR_OR_REMOVE_LEFT_FINGER},
                        {Integer::to_string('e'), EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED},
                        {Integer::to_string('E'), EquipmentCommandKeys::WEAR_OR_REMOVE_WIELDED},
                        {Integer::to_string('f'), EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND},
                        {Integer::to_string('F'), EquipmentCommandKeys::WEAR_OR_REMOVE_OFF_HAND},
                        {Integer::to_string('g'), EquipmentCommandKeys::WEAR_OR_REMOVE_BODY},
                        {Integer::to_string('G'), EquipmentCommandKeys::WEAR_OR_REMOVE_BODY},
                        {Integer::to_string('h'), EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY},
                        {Integer::to_string('H'), EquipmentCommandKeys::WEAR_OR_REMOVE_ABOUT_BODY},
                        {Integer::to_string('i'), EquipmentCommandKeys::WEAR_OR_REMOVE_FEET},
                        {Integer::to_string('I'), EquipmentCommandKeys::WEAR_OR_REMOVE_FEET},
                        {Integer::to_string('j'), EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED},
                        {Integer::to_string('J'), EquipmentCommandKeys::WEAR_OR_REMOVE_RANGED},
                        {Integer::to_string('k'), EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION},
                        {Integer::to_string('K'), EquipmentCommandKeys::WEAR_OR_REMOVE_AMMUNITION},
                        {Integer::to_string('y'), EquipmentCommandKeys::YOUR_ITEMS},
                        {Integer::to_string('Y'), EquipmentCommandKeys::YOUR_ITEMS},
                        {Integer::to_string('z'), EquipmentCommandKeys::EXIT_EQUIPMENT},
                        {Integer::to_string('Z'), EquipmentCommandKeys::EXIT_EQUIPMENT}};
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
