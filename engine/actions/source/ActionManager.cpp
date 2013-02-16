#include <string>
#include <boost/make_shared.hpp>
#include "ActionManager.hpp"
#include "CharacterDumpManager.hpp"
#include "ChatManager.hpp"
#include "Conversion.hpp"
#include "CurrencyManager.hpp"
#include "DateTimeManager.hpp"
#include "DropManager.hpp"
#include "EquipmentManager.hpp"
#include "FeatureManager.hpp"
#include "FileWriter.hpp"
#include "FoodManager.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "InventoryManager.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "PickupManager.hpp"
#include "PrayerManager.hpp"
#include "QuestListManager.hpp"
#include "ReadManager.hpp"
#include "SearchActionManager.hpp"
#include "Serialization.hpp"
#include "VersionActionManager.hpp"
#include "WeaponInfoManager.hpp"
#include "Log.hpp"

using namespace std;

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

bool ActionManager::operator==(const ActionManager& am)
{
  bool result = true;

  result = result && (combat_manager == am.combat_manager);
  result = result && (movement_manager == am.movement_manager);
  result = result && (item_manager == am.item_manager);
  result = result && (tile_selection_manager == am.tile_selection_manager);
  result = result && (ranged_combat_manager == am.ranged_combat_manager);
  result = result && (quaff_manager == am.quaff_manager);

  return result;
}

ActionCost ActionManager::version(CreaturePtr creature)
{
  VersionActionManager vam;
  return get_action_cost(creature, vam.version());
}

ActionCost ActionManager::date_and_time(CreaturePtr creature)
{
  DateTimeManager dtm;
  return get_action_cost(creature, dtm.date_and_time());
}

ActionCost ActionManager::dump_character(CreaturePtr creature)
{
  CharacterDumpManager cdm;
  return get_action_cost(creature, cdm.dump_character(creature));
}

ActionCost ActionManager::search(CreaturePtr creature)
{
  SearchActionManager sam;
  return get_action_cost(creature, sam.search(creature));
}

ActionCost ActionManager::move(CreaturePtr creature, const Direction direction)
{
  return get_action_cost(creature, movement_manager.move(creature, direction));
}

ActionCost ActionManager::attack(CreaturePtr creature, const Direction direction)
{
  ActionCostValue action_cost_value = combat_manager.attack(creature, direction);
  return get_action_cost(creature, action_cost_value);
}

// Move up a level
ActionCost ActionManager::ascend(CreaturePtr creature)
{
  Game& game = Game::instance();
  
  // If we're on the world map, send a message about not being able to ascend further.
  MapPtr current_map = game.get_current_map();
  MapType map_type = current_map->get_map_type();
    
  if (map_type == MAP_TYPE_WORLD && creature && creature->get_is_player())
  {
    MessageManager& manager = MessageManager::instance();
    string search_message = StringTable::get(MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP);

    manager.add_new_message(search_message);
    manager.send();
      
    return get_action_cost(creature, 0);
  } 
    
  movement_manager.ascend(creature);
  
  return get_action_cost(creature, 1); // JCD FIXME
}

// Move down a level
ActionCost ActionManager::descend(CreaturePtr creature)
{
  return get_action_cost(creature, movement_manager.descend(creature));
}

// Remove an item from a particular slot.
// Advance the turn if there was an item in the slot.
// Do not advance if there was no item in the slot.
ActionCostValue ActionManager::remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location)
{
  if (creature)
  {
    ItemPtr item_in_slot = creature->get_equipment().get_item(worn_location);
    
    if (item_in_slot)
    {
      item_manager.remove(creature, worn_location);
      return 1;
    }
  }
  
  return 0;
}

// Wear or remove a particular item from the worn equipment by adding/removing the item from a slot.
ActionCostValue ActionManager::wear_or_remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location)
{
  ActionCostValue action_cost = 0;
  
  if (creature)
  {
    ActionCostValue item_removed = remove_item(creature, worn_location);
    action_cost = item_removed;
    
    if (!item_removed) // Wear an item - select something.
    {
      list<EquipmentWornLocation> worn_list;
      worn_list.push_back(worn_location);
      
      list<IItemFilterPtr> worn_filter = ItemFilterFactory::create_equipment_filter(worn_list);
      ItemPtr item_in_slot = inventory(creature, creature->get_inventory(), worn_filter, false);
      
      // This is null if no item was selected.
      if (item_in_slot)
      {        
        ActionCostValue item_equipped = handle_item(creature, ITEM_ACTION_EQUIP, item_in_slot, worn_location);
        
        // If the item was successfully equipped, remove it from the
        // inventory.
        if (item_equipped)
        {
          action_cost = 1;
        }
      }
    }
  }
  
  return action_cost;
}

// Do something with an item:
// - Equip it, or
// - Pick it up from the ground, or
// - Drop it on to the ground.
// 
// This function assumes everything is ok - it doesn't check for the overland map, any
// special terrain types, etc.
ActionCostValue ActionManager::handle_item(CreaturePtr creature, const ItemAction item_action, ItemPtr item, const EquipmentWornLocation loc)
{
  ActionCostValue action_cost_value = 1;
  
  switch(item_action)
  {
    case ITEM_ACTION_EQUIP:
      if (loc != EQUIPMENT_WORN_NONE) item_manager.equip(creature, item, loc);
      else item_manager.equip(creature, item);
      break;
    case ITEM_ACTION_PICK_UP:
      item_manager.pick_up(creature, item);
      break;
    case ITEM_ACTION_DROP:
      item_manager.drop(creature, item);
      break;
    default:
      Log::instance().log("Error: Unhandled item action!");
      action_cost_value = 0;
      break;
  }
  
  return action_cost_value;
}

// "q"uaff a potion
ActionCost ActionManager::quaff(CreaturePtr creature)
{
  return get_action_cost(creature, quaff_manager.quaff(creature, this));
}

// 'r'ead a scroll or spellbook
ActionCost ActionManager::read(CreaturePtr creature)
{
  ReadManager rm;
  return get_action_cost(creature, rm.read(creature, this));
}

// '$': check how much currency is held (free action)
ActionCost ActionManager::check_currency(CreaturePtr creature)
{
  CurrencyManager cm;
  return get_action_cost(creature, cm.count_currency(creature));
}

// 'e'at something
ActionCost ActionManager::eat(CreaturePtr creature)
{
  FoodManager fm;
  return get_action_cost(creature, fm.eat(creature, this));
}

// Chat with some (hopefully) friendly critter
ActionCost ActionManager::chat(CreaturePtr creature)
{
  ChatManager cm;
  return get_action_cost(creature, cm.chat(creature));
}

// Apply/handle a terrain feature
ActionCost ActionManager::apply(CreaturePtr creature)
{
  FeatureManager fm;
  return get_action_cost(creature, fm.apply(creature));
}

// Show the list of quests.
ActionCost ActionManager::quest_list(CreaturePtr creature)
{
  QuestListManager qlm;
  return get_action_cost(creature, qlm.quest_list());
}

// Pick up an item, doing any necessary checks first.
ActionCost ActionManager::pick_up(CreaturePtr creature)
{
  PickupManager pm;
  return get_action_cost(creature, pm.pick_up(creature, this));
}

// Drop an item, doing any necessary checks first.
ActionCost ActionManager::drop(CreaturePtr creature)
{
  DropManager dm;
  return get_action_cost(creature, dm.drop(creature, this));
}

// Display the inventory; potentially select something.
ItemPtr ActionManager::inventory(CreaturePtr creature, Inventory& inv, const list<IItemFilterPtr>& display_filter_list, const bool inventory_is_read_only)
{
  ItemPtr selected_item;
  
  Game& game = Game::instance();
  
  if (creature)
  {
    DisplayPtr game_display = game.get_display();
    InventoryManager inv_manager(game_display, creature);

    selected_item = inv_manager.manage_inventory(inv, display_filter_list, inventory_is_read_only);
  }
  
  return selected_item;
}

// Wear/unwear equipment
ActionCost ActionManager::equipment(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  Game& game = Game::instance();
  
  if (creature)
  {
    DisplayPtr game_display = game.get_display();
    
    EquipmentManager equipment_manager(game_display, creature);
    action_cost_value = equipment_manager.manage_equipment();
  }

  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::pray(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    PrayerManager prayer_manager;
    action_cost_value = prayer_manager.pray(creature);
  }

  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::weapon_info(CreaturePtr creature, const WeaponStyle weapon_style)
{
  WeaponInfoManager wm;
  return get_action_cost(creature, wm.weapon_info(creature, weapon_style));
}

ActionCost ActionManager::select_tile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    action_cost_value = tile_selection_manager.select_tile(creature, ActionTextKeys::ACTION_LOOK);
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCostValue ActionManager::select_tile(CreaturePtr creature, const Direction d, TileSelectionManager* const tsm)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    // Ensure that we use the passed-in tile selection manager, as it may have certain properties
    // set (to exclude parts of the overall tile description, etc).
    if (tsm)
    {
      action_cost_value = tsm->select_tile(creature, d);
    }
  }
  
  return action_cost_value;
}

ActionCost ActionManager::fire_missile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    action_cost_value = ranged_combat_manager.fire_missile(creature);
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::save(CreaturePtr creature)
{
  Serialization::save(creature);
  quit(creature);
  
  return get_action_cost(creature, 1);
}

ActionCost ActionManager::quit(CreaturePtr creature)
{
  Game& game = Game::instance();
  
  game.stop_playing();
  
  return get_action_cost(creature, 1);
}

// Create an ActionCost based on the ActionCostValue already generated
ActionCost ActionManager::get_action_cost(CreaturePtr creature, const ActionCostValue action_cost_value)
{
  ActionCostValue total_action_cost_value = 0;
  
  if (creature && (action_cost_value > 0))
  {
    total_action_cost_value = creature->get_speed().get_current() + action_cost_value;
  }
  
  ActionCost ac(total_action_cost_value);
  return ac;
}

bool ActionManager::serialize(std::ostream& stream)
{
  tile_selection_manager.serialize(stream);

  return true;
}

bool ActionManager::deserialize(std::istream& stream)
{
  tile_selection_manager.deserialize(stream);

  return true;
}

ClassIdentifier ActionManager::internal_class_identifier() const
{
  return CLASS_ID_ACTION_MANAGER;
}

#ifdef UNIT_TESTS
#include "unit_tests/ActionManager_test.cpp"
#endif

