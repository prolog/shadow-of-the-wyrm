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

  KeyboardCommandMapPtr kb_com_map  = std::make_unique<KeyboardCommandMap>();
  KeyboardCommandMapPtr eq_com_map  = std::make_unique<EquipmentKeyboardCommandMap>();
  KeyboardCommandMapPtr inv_com_map = std::make_unique<InventoryKeyboardCommandMap>();
  KeyboardCommandMapPtr ts_com_map  = std::make_unique<TileSelectionKeyboardCommandMap>();
  KeyboardCommandMapPtr hp_com_map  = std::make_unique<HelpKeyboardCommandMap>();
  KeyboardCommandMapPtr sk_com_map  = std::make_unique<SkillsKeyboardCommandMap>();
  KeyboardCommandMapPtr scr_com_map = std::make_unique<ScreenKeyboardCommandMap>();

  kb_map.insert(make_pair(ClassIdentifier::CLASS_ID_KEYBOARD_COMMAND_MAP, std::move(kb_com_map)));
  kb_map.insert(make_pair(ClassIdentifier::CLASS_ID_EQUIPMENT_KEYBOARD_COMMAND_MAP, std::move(eq_com_map)));
  kb_map.insert(make_pair(ClassIdentifier::CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP, std::move(inv_com_map)));
  kb_map.insert(make_pair(ClassIdentifier::CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP, std::move(ts_com_map)));
  kb_map.insert(make_pair(ClassIdentifier::CLASS_ID_SCREEN_KEYBOARD_COMMAND_MAP, std::move(scr_com_map)));
  kb_map.insert(make_pair(ClassIdentifier::CLASS_ID_HELP_KEYBOARD_COMMAND_MAP, std::move(hp_com_map)));
  kb_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILLS_KEYBOARD_COMMAND_MAP, std::move(sk_com_map)));
}