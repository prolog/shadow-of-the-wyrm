#include <string>
#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "AutomaticMovementAction.hpp"
#include "BestiaryAction.hpp"
#include "CharacterAction.hpp"
#include "ChatAction.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "CurrencyAction.hpp"
#include "DateTimeAction.hpp"
#include "DropAction.hpp"
#include "EquipmentManager.hpp"
#include "ExitGameAction.hpp"
#include "ExperienceAction.hpp"
#include "EvokeAction.hpp"
#include "FeatureAction.hpp"
#include "FileWriter.hpp"
#include "FoodAction.hpp"
#include "Game.hpp"
#include "GameEnvTextKeys.hpp"
#include "ItemFilterFactory.hpp"
#include "InventoryManager.hpp"
#include "KickAction.hpp"
#include "LatestMessagesAction.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementTextKeys.hpp"
#include "OfferAction.hpp"
#include "PickupAction.hpp"
#include "PietyAction.hpp"
#include "PrayerAction.hpp"
#include "PromptTextKeys.hpp"
#include "QuestListAction.hpp"
#include "ReadAction.hpp"
#include "SearchAction.hpp"
#include "ShowConductsAction.hpp"
#include "ShowResistancesAction.hpp"
#include "SkinAction.hpp"
#include "SpellcastingAction.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "VersionAction.hpp"
#include "WeaponInfoAction.hpp"
#include "Log.hpp"

using namespace std;

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

bool ActionManager::operator==(const ActionManager& am) const
{
  bool result = true;

  result = result && (combat_manager == am.combat_manager);
  result = result && (movement_action == am.movement_action);
  result = result && (item_manager == am.item_manager);
  result = result && (tile_selection_action == am.tile_selection_action);
  result = result && (ranged_combat_action == am.ranged_combat_action);
  result = result && (quaff_action == am.quaff_action);

  return result;
}

ActionCost ActionManager::version(CreaturePtr creature)
{
  VersionAction va;
  return get_action_cost(creature, va.version());
}

ActionCost ActionManager::date_and_time(CreaturePtr creature)
{
  DateTimeAction dt;
  return get_action_cost(creature, dt.date_and_time());
}

ActionCost ActionManager::display_character(CreaturePtr creature)
{
  CharacterAction ca;
  return get_action_cost(creature, ca.display_character(creature));
}

ActionCost ActionManager::dump_character(CreaturePtr creature)
{
  CharacterAction ca;
  return get_action_cost(creature, ca.dump_character(creature));
}

ActionCost ActionManager::search(CreaturePtr creature)
{
  SearchAction sa;
  return get_action_cost(creature, sa.search(creature));
}

ActionCost ActionManager::move(CreaturePtr creature, const Direction direction)
{
  return get_action_cost(creature, movement_action.move(creature, direction));
}

ActionCost ActionManager::automatic_movement(CreaturePtr creature)
{
  AutomaticMovementAction ama;
  return get_action_cost(creature, ama.automatic_movement(creature));
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
    
  if (map_type == MapType::MAP_TYPE_WORLD && creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);
    string search_message = StringTable::get(MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP);

    manager.add_new_message(search_message);
    manager.send();
      
    return get_action_cost(creature, 0);
  } 
    
  ActionCostValue acv = movement_action.ascend(creature);
  
  return get_action_cost(creature, acv);
}

// Move down a level
ActionCost ActionManager::descend(CreaturePtr creature)
{
  return get_action_cost(creature, movement_action.descend(creature));
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
      list<IItemFilterPtr> total_filter(worn_filter);

      // JCD FIXME: Refactor this to return a list of filters on a per-slot
      // basis.
      //
      // If the creature is wielding an item, or holding it in its off-hand,
      // then we need to check to see if there are enough hands available
      // for this.  Don't check for other slots (rings, head, etc).
      if (worn_location == EquipmentWornLocation::EQUIPMENT_WORN_WIELDED || worn_location == EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND)
      {
        list<IItemFilterPtr> hands_filter = ItemFilterFactory::create_hands_required_filter(creature->get_hands_available());
        total_filter.insert(total_filter.end(), hands_filter.begin(), hands_filter.end());
      }

      ItemPtr item_in_slot = inventory(creature, creature->get_inventory(), total_filter, {}, false);
      
      // This is null if no item was selected.
      if (item_in_slot)
      {        
        ActionCostValue item_equipped = handle_item(creature, ItemAction::ITEM_ACTION_EQUIP, item_in_slot, worn_location);
        
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
    case ItemAction::ITEM_ACTION_EQUIP:
      if (loc != EquipmentWornLocation::EQUIPMENT_WORN_NONE) item_manager.equip(creature, item, loc);
      else item_manager.equip(creature, item);
      break;
    case ItemAction::ITEM_ACTION_PICK_UP:
      item_manager.pick_up(creature, item);
      break;
    case ItemAction::ITEM_ACTION_DROP:
      item_manager.drop(creature, item);
      break;
    default:
      Log::instance().log("ActionManager::handle_item - Error: Unhandled item action!");
      action_cost_value = 0;
      break;
  }
  
  return action_cost_value;
}

// "q"uaff a potion
ActionCost ActionManager::quaff(CreaturePtr creature)
{
  return get_action_cost(creature, quaff_action.quaff(creature, this));
}

// 'r'ead a scroll or spellbook
ActionCost ActionManager::read(CreaturePtr creature)
{
  ReadAction ra;
  return get_action_cost(creature, ra.read(creature, this));
}

// '$': check how much currency is held (free action)
ActionCost ActionManager::check_currency(CreaturePtr creature)
{
  CurrencyAction ca;
  return get_action_cost(creature, ca.count_currency(creature));
}

// 'e'at something
ActionCost ActionManager::eat(CreaturePtr creature)
{
  FoodAction fa;
  return get_action_cost(creature, fa.eat(creature, this));
}

// Chat with some (hopefully) friendly critter
ActionCost ActionManager::chat(CreaturePtr creature)
{
  ChatAction ca;
  return get_action_cost(creature, ca.chat(creature));
}

// Apply/handle a terrain feature
ActionCost ActionManager::apply(CreaturePtr creature)
{
  FeatureAction fa;
  return get_action_cost(creature, fa.apply(creature));
}

// Show the list of quests.
ActionCost ActionManager::quest_list(CreaturePtr creature)
{
  QuestListAction qla;
  return get_action_cost(creature, qla.quest_list());
}

void ActionManager::reload_scripts_and_sids()
{
  CreaturePtr nullcr;
  reload_scripts_and_sids(nullcr);
}

// Clear the Lua state so scripts can be reloaded.
// Reload the ini settings.
// Reload the strings.
ActionCost ActionManager::reload_scripts_and_sids(CreaturePtr creature)
{
  Game& game = Game::instance();
  ScriptEngine& se = game.get_script_engine_ref();
  se.clear_state();

  Settings settings(true);
  game.set_settings(settings);

  StringTable::load(game.get_sid_ini_filename());

  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  manager.add_new_message(StringTable::get(GameEnvTextKeys::GAME_ENV_LUA_STATE_CLEARED));
  manager.send();

  return get_action_cost(creature, 0);
}

ActionCost ActionManager::run_script_command(CreaturePtr creature)
{
  Game& game = Game::instance();
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  ScriptEngine& se = game.get_script_engine_ref();
  string command = manager.add_new_message_with_prompt(StringTable::get(PromptTextKeys::PROMPT_RUN_SCRIPT));

  // If the player didn't enter anything, use the last command.
  // Otherwise, save the current command for next time.
  if (command.empty())
  {
    command = se.get_last_executed();
  }
  else
  {
    se.set_last_executed(command);
  }

  se.run_command(command);

  return get_action_cost(creature, 0);
}

ActionCost ActionManager::cast_spell(CreaturePtr creature, const string& spell_id, const Direction direction)
{
  SpellcastingAction sa;
  ActionCost ac;

  if (spell_id.empty())
  {
    ac = get_action_cost(creature, sa.cast_spell(creature));
  }
  else
  {
    ac = get_action_cost(creature, sa.cast_spell(creature, spell_id, direction));
  }

  return ac;
}

ActionCost ActionManager::bestiary(CreaturePtr creature)
{
  string no_search_text;
  return bestiary(creature, no_search_text);
}

ActionCost ActionManager::bestiary(CreaturePtr creature, const string& creature_search_text)
{
  BestiaryAction bestiary;

  return get_action_cost(creature, bestiary.display_creature_information(creature, creature_search_text));
}

ActionCost ActionManager::evoke(CreaturePtr creature)
{
  EvokeAction ea;

  return get_action_cost(creature, ea.evoke(creature, this));
}

ActionCost ActionManager::show_resistances(CreaturePtr creature)
{
  ShowResistancesAction sra;

  return get_action_cost(creature, sra.show_resistances(creature));
}

ActionCost ActionManager::show_conducts(CreaturePtr creature)
{
  ShowConductsAction sca;

  return get_action_cost(creature, sca.show_conducts(creature));
}

ActionCost ActionManager::latest_messages(CreaturePtr creature)
{
  LatestMessagesAction lma;

  return get_action_cost(creature, lma.latest_messages(creature));
}

ActionCost ActionManager::kick(CreaturePtr creature)
{
  KickAction ka;

  return get_action_cost(creature, ka.kick(creature));
}

ActionCost ActionManager::offer(CreaturePtr creature)
{
  OfferAction oa;

  return get_action_cost(creature, oa.offer(creature, this));
}

ActionCost ActionManager::skin(CreaturePtr creature)
{
  SkinAction sa;

  return get_action_cost(creature, sa.skin(creature, this));
}

ActionCost ActionManager::piety(CreaturePtr creature)
{
  PietyAction pa;
  return get_action_cost(creature, pa.piety(creature, this));
}

ActionCost ActionManager::experience(CreaturePtr creature)
{
  ExperienceAction ea;

  return get_action_cost(creature, ea.experience(creature));
}

// Pick up an item, doing any necessary checks first.
ActionCost ActionManager::pick_up(CreaturePtr creature)
{
  PickupAction pa;
  return get_action_cost(creature, pa.pick_up(creature, this));
}

// Drop an item, doing any necessary checks first.
ActionCost ActionManager::drop(CreaturePtr creature)
{
  DropAction da;
  return get_action_cost(creature, da.drop(creature, this));
}

// Display the inventory; potentially select something.
ItemPtr ActionManager::inventory(CreaturePtr creature, IInventoryPtr inv, const list<IItemFilterPtr>& base_display_filter_list, const list<IItemFilterPtr>& additional_display_filter_list, const bool inventory_is_read_only)
{
  ItemPtr selected_item;
  
  Game& game = Game::instance();
  
  if (creature)
  {
    DisplayPtr game_display = game.get_display();
    InventoryManager inv_manager(game_display, creature);

    selected_item = inv_manager.manage_inventory(inv, base_display_filter_list, additional_display_filter_list, inventory_is_read_only);
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
    PrayerAction prayer_action;
    action_cost_value = prayer_action.pray(creature);
  }

  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::weapon_info(CreaturePtr creature, const WeaponStyle weapon_style)
{
  WeaponInfoAction wa;
  return get_action_cost(creature, wa.weapon_info(creature, weapon_style));
}

ActionCost ActionManager::select_tile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  CurrentCreatureAbilities cca;

  if (creature && cca.can_see(creature, true))
  {
    action_cost_value = tile_selection_action.select_tile(creature, ActionTextKeys::ACTION_LOOK, TileReset::TILE_RESET_ON_CREATURE);
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCostValue ActionManager::select_tile(CreaturePtr creature, const SelectCreatureType sct, TileSelectionAction* const tsa)
{
  ActionCostValue action_cost_value = 0;

  if (creature)
  {
    // Ensure that we use the passed-in tile selection manager, as it may have certain properties
    // set (to exclude parts of the overall tile description, etc).
    if (tsa)
    {
      action_cost_value = tsa->select_tile(creature, sct);
    }
  }

  return action_cost_value;
}

ActionCostValue ActionManager::select_tile(CreaturePtr creature, const Direction d, TileSelectionAction* const tsa)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    // Ensure that we use the passed-in tile selection manager, as it may have certain properties
    // set (to exclude parts of the overall tile description, etc).
    if (tsa)
    {
      action_cost_value = tsa->select_tile(creature, d);
    }
  }
  
  return action_cost_value;
}

ActionCost ActionManager::fire_missile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  CurrentCreatureAbilities cca;
  
  if (creature && cca.can_see(creature))
  {
    action_cost_value = ranged_combat_action.fire_missile(creature);
  }
  else
  {
    if (creature && creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance(creature, true);
      string combat_message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_BLIND_RANGED_COMBAT);

      manager.add_new_message(combat_message);
      manager.send();

    }
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::rest(CreaturePtr creature)
{
  Game& game = Game::instance();
  Settings& settings = game.get_settings_ref();
  int rest_turns = String::to_int(settings.get_setting("rest_turns"));
  creature->get_automatic_movement_ref().set_turns(rest_turns);

  AutomaticMovementAction ama;
  return get_action_cost(creature, ama.rest(creature));
}

ActionCost ActionManager::save(CreaturePtr creature)
{
  ExitGameAction ega;
  return get_action_cost(creature, ega.save(creature));
}

ActionCost ActionManager::quit(CreaturePtr creature)
{
  ExitGameAction ega;
  return get_action_cost(creature, ega.quit(creature, true));
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

bool ActionManager::serialize(std::ostream& stream) const
{
  tile_selection_action.serialize(stream);

  return true;
}

bool ActionManager::deserialize(std::istream& stream)
{
  tile_selection_action.deserialize(stream);

  return true;
}

ClassIdentifier ActionManager::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ACTION_MANAGER;
}

#ifdef UNIT_TESTS
#include "unit_tests/ActionManager_test.cpp"
#endif

