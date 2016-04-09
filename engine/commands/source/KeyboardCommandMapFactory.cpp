#include "KeyboardCommandMapFactory.hpp"
#include "EquipmentKeyboardCommandMap.hpp"
#include "HelpKeyboardCommandMap.hpp"
#include "InventoryKeyboardCommandMap.hpp"
#include "ScreenKeyboardCommandMap.hpp"
#include "SkillsKeyboardCommandMap.hpp"
#include "TileSelectionKeyboardCommandMap.hpp"

using namespace std;

KeyboardCommandMapSerializationMap KeyboardCommandMapFactory::kb_map;

KeyboardCommandMapPtr KeyboardCommandMapFactory::create_keyboard_command_map(const ClassIdentifier ci)
{
  KeyboardCommandMapPtr kb;

  // Initialize on first use
  if (kb_map.empty())
  {
    initialize_command_map_map();
  }

  KeyboardCommandMapSerializationMap::iterator k_it = kb_map.find(ci);

  if (k_it != kb_map.end())
  {
    kb = KeyboardCommandMapPtr(k_it->second->clone());
  }

  return kb;
}

void KeyboardCommandMapFactory::initialize_command_map_map()
{
  kb_map.clear();

  KeyboardCommandMapPtr kb_com_map  = std::make_shared<KeyboardCommandMap>();
  KeyboardCommandMapPtr eq_com_map  = std::make_shared<EquipmentKeyboardCommandMap>();
  KeyboardCommandMapPtr inv_com_map = std::make_shared<InventoryKeyboardCommandMap>();
  KeyboardCommandMapPtr ts_com_map  = std::make_shared<TileSelectionKeyboardCommandMap>();
  KeyboardCommandMapPtr hp_com_map  = std::make_shared<HelpKeyboardCommandMap>();
  KeyboardCommandMapPtr sk_com_map  = std::make_shared<SkillsKeyboardCommandMap>();
  KeyboardCommandMapPtr scr_com_map = std::make_shared<ScreenKeyboardCommandMap>();

  kb_map = KeyboardCommandMapSerializationMap{{ClassIdentifier::CLASS_ID_KEYBOARD_COMMAND_MAP, kb_com_map},
                                              {ClassIdentifier::CLASS_ID_EQUIPMENT_KEYBOARD_COMMAND_MAP, eq_com_map},
                                              {ClassIdentifier::CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP, inv_com_map},
                                              {ClassIdentifier::CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP, ts_com_map},
                                              {ClassIdentifier::CLASS_ID_SCREEN_KEYBOARD_COMMAND_MAP, scr_com_map},
                                              {ClassIdentifier::CLASS_ID_HELP_KEYBOARD_COMMAND_MAP, hp_com_map},
                                              {ClassIdentifier::CLASS_ID_SKILLS_KEYBOARD_COMMAND_MAP, sk_com_map}};
}