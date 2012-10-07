#include <boost/make_shared.hpp>
#include "KeyboardCommandMapFactory.hpp"
#include "EquipmentKeyboardCommandMap.hpp"
#include "InventoryKeyboardCommandMap.hpp"
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

  KeyboardCommandMapPtr kb_com_map  = boost::make_shared<KeyboardCommandMap>();
  KeyboardCommandMapPtr eq_com_map  = boost::make_shared<EquipmentKeyboardCommandMap>();
  KeyboardCommandMapPtr inv_com_map = boost::make_shared<InventoryKeyboardCommandMap>();
  KeyboardCommandMapPtr ts_com_map  = boost::make_shared<TileSelectionKeyboardCommandMap>();

  kb_map.insert(make_pair(CLASS_ID_KEYBOARD_COMMAND_MAP, kb_com_map));
  kb_map.insert(make_pair(CLASS_ID_EQUIPMENT_KEYBOARD_COMMAND_MAP, eq_com_map));
  kb_map.insert(make_pair(CLASS_ID_INVENTORY_KEYBOARD_COMMAND_MAP, inv_com_map));
  kb_map.insert(make_pair(CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP, ts_com_map));
}