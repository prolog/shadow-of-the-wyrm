#include <string>
#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "AutomaticActionsAction.hpp"
#include "AutomaticMovementAction.hpp"
#include "BestiaryAction.hpp"
#include "BreedAction.hpp"
#include "CharacterAction.hpp"
#include "ChatAction.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "CurrencyAction.hpp"
#include "DateTimeWeatherAction.hpp"
#include "DisplayProperties.hpp"
#include "DropAction.hpp"
#include "EquipmentManager.hpp"
#include "ExitGameAction.hpp"
#include "ExperienceAction.hpp"
#include "EvokeAction.hpp"
#include "FeatureAction.hpp"
#include "FileWriter.hpp"
#include "FoodAction.hpp"
#include "ItemCodexAction.hpp"
#include "Game.hpp"
#include "GameEnvTextKeys.hpp"
#include "HelpAction.hpp"
#include "InscribeAction.hpp"
#include "ItemFilterFactory.hpp"
#include "InventoryManager.hpp"
#include "KickAction.hpp"
#include "LatestMessagesAction.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementTextKeys.hpp"
#include "OfferAction.hpp"
#include "OrderAction.hpp"
#include "PickupAction.hpp"
#include "PietyAction.hpp"
#include "PrayerAction.hpp"
#include "PromptTextKeys.hpp"
#include "QuestListAction.hpp"
#include "ReadAction.hpp"
#include "SearchAction.hpp"
#include "Setting.hpp"
#include "ShowConductsAction.hpp"
#include "ShowResistancesAction.hpp"
#include "SkinAction.hpp"
#include "SoundSettingsAction.hpp"
#include "SpellcastingAction.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "TerrainSpeedMultiplierCalculator.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
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
  result = result && (skills_action == am.skills_action);

  return result;
}

ActionCost ActionManager::version(CreaturePtr creature)
{
  VersionAction va;
  return get_action_cost(creature, va.version());
}

ActionCost ActionManager::date_and_time(CreaturePtr creature)
{
  DateTimeWeatherAction dtw;
  return get_action_cost(creature, dtw.date_and_time_and_weather());
}

ActionCost ActionManager::display_character(CreaturePtr creature)
{
  CharacterAction ca;
  return get_action_cost(creature, ca.display_character(creature));
}

ActionCost ActionManager::dump_character(CreaturePtr creature)
{
  CharacterAction ca;
  return get_action_cost(creature, ca.dump_character(creature, CharacterDumpType::CHARACTER_DUMP_USER_INITIATED, false));
}

ActionCost ActionManager::search(CreaturePtr creature)
{
  SearchAction sa;
  return get_action_cost(creature, sa.search(creature, true));
}

ActionCost ActionManager::move(CreaturePtr creature, const Direction direction, const bool confirm_if_dangerous)
{
  TerrainSpeedMultiplierCalculator tsmc;
  MapPtr map = Game::instance().get_current_map();
  float total_mult = tsmc.calculate(creature, map);

  return get_action_cost(creature, movement_action.move(creature, direction, confirm_if_dangerous), total_mult);
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
    IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, true);

    string ascend_message = StringTable::get(MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP);

    if (!game.do_deities_exist())
    {
      ascend_message = StringTable::get(MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP_NO_GODS);
    }

    manager.add_new_message(ascend_message);
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
  ActionCostValue action_cost = ActionCostConstants::NO_ACTION;
  
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
        list<IItemFilterPtr> hands_filter = ItemFilterFactory::create_hands_required_filter(worn_location, creature->get_hands_available());
        total_filter.insert(total_filter.end(), hands_filter.begin(), hands_filter.end());
      }

      ItemPtr item_in_slot = inventory(creature, creature->get_inventory(), total_filter, {}, false, false);
      
      // This is null if no item was selected.
      if (item_in_slot)
      {        
        ActionCostValue item_equipped = handle_item(creature, ItemAction::ITEM_ACTION_EQUIP, item_in_slot, worn_location);
        
        // If the item was successfully equipped, remove it from the
        // inventory.
        if (item_equipped)
        {
          action_cost = ActionCostConstants::DEFAULT;
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
  ActionCostValue action_cost_value = ActionCostConstants::DEFAULT;
  
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
ActionCost ActionManager::read(CreaturePtr creature, const std::string& item_id)
{
  ReadAction ra;

  if (item_id.empty())
  {
    return get_action_cost(creature, ra.read(creature, this));
  }
  else
  {
    return get_action_cost(creature, ra.read(creature, item_id));
  }
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

void ActionManager::reload_scripts_assets_and_sids()
{
  CreaturePtr nullcr;
  reload_scripts_assets_and_sids(nullcr);
}

// Clear the Lua state so scripts can be reloaded.
// Reload the strings.
ActionCost ActionManager::reload_scripts_assets_and_sids(CreaturePtr creature)
{
  Game& game = Game::instance();
  ScriptEngine& se = game.get_script_engine_ref();
  se.clear_state();

  DisplayPtr display = game.get_display();
  if (display != nullptr)
  {
    display->set_spritesheets(game.get_spritesheets());
    game.set_requires_redraw(true);
  }

  SoundPtr sound = game.get_sound();
  if (sound != nullptr)
  {
    sound->set_effects(game.get_sound_effects_cref());
  }

  StringTable::load(game.get_sid_ini_filename());

  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  manager.add_new_message(StringTable::get(GameEnvTextKeys::GAME_ENV_LUA_STATE_CLEARED));
  manager.send();

  return get_action_cost(creature, 0);
}

ActionCost ActionManager::run_script_command(CreaturePtr creature)
{
  Game& game = Game::instance();
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  bool disallow_score_on_exploration = game.get_settings_ref().get_setting_as_bool(Setting::DISALLOW_SCORE_ON_EXPLORATION);
  bool confirmation = (game.should_count_score() == false);

  if (disallow_score_on_exploration && game.should_count_score())
  {
    manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_USE_LUA_CONSOLE));
    confirmation = creature->get_decision_strategy()->get_confirmation();
  }

  if (disallow_score_on_exploration == false || confirmation)
  {
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

    DisplayPtr display = game.get_display();
    if (display != nullptr)
    {
      display->clear_messages();
    }

    se.run_command(command);

    if (disallow_score_on_exploration)
    {
      game.set_count_score(false);
    }
  }

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
  return bestiary(creature, no_search_text, nullptr);
}

ActionCost ActionManager::bestiary(CreaturePtr creature, const string& creature_search_text, CreaturePtr tile_creature)
{
  BestiaryAction bestiary;

  return get_action_cost(creature, bestiary.display_creature_information(creature, creature_search_text, tile_creature));
}

ActionCost ActionManager::item_codex(CreaturePtr creature)
{
  ItemCodexAction ica;

  return get_action_cost(creature, ica.item_details(creature));
}

ActionCost ActionManager::item_codex(CreaturePtr creature, const EquipmentWornLocation ewl)
{
  ItemCodexAction ica;

  return get_action_cost(creature, ica.item_details(creature, ewl));
}

ActionCost ActionManager::item_codex(CreaturePtr creature, ItemPtr item, const bool /* error_as_alert */)
{
  ItemCodexAction ica;

  return get_action_cost(creature, ica.item_details(creature, item));
}

ActionCost ActionManager::switch_graphics_mode(CreaturePtr creature)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

  // Flip the force_ascii setting
  Game& game = Game::instance();
  DisplayPtr display = game.get_display();
  Settings& settings = game.get_settings_ref();
  bool force_ascii = settings.get_setting_as_bool(Setting::DISPLAY_FORCE_ASCII);
  bool new_force_ascii = !force_ascii;
  settings.set_setting(Setting::DISPLAY_FORCE_ASCII, std::to_string(new_force_ascii));

  if (display != nullptr)
  {
    display->set_force_ascii(new_force_ascii);

    // Add a message about the display name
    string display_name = display->get_name();
    string display_msg = ActionTextKeys::get_graphics_mode_switch_message(display_name);

    IMessageManager& manager = MMF::instance();
    manager.add_new_message(display_msg);
    manager.send();
  }

  // Now force a redraw
  game.set_requires_redraw(true);

  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::switch_colour_palettes(CreaturePtr creature)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();
  DisplayPtr display = game.get_display();
  string display_id;

  // Get the current palette ID
  if (creature != nullptr && display != nullptr)
  {
    display_id = creature->get_additional_property(DisplayProperties::DISPLAY_PROPERTIES_ID);

    // Try switching
    pair<bool, pair<string, string>> switch_result = display->switch_colour_palette(display_id);

    // If successful, display a message
    if (switch_result.first)
    {
      string new_pal_id = switch_result.second.first;
      string name_sid = switch_result.second.second;

      // Display msg
      string palette_msg = ActionTextKeys::get_palette_switch_message(name_sid);
      IMessageManager& manager = MMF::instance();

      display->clear_messages();
      manager.add_new_message(palette_msg);
      //x Bmanager.send();

      // Update palette ID
      creature->set_additional_property(DisplayProperties::DISPLAY_PROPERTIES_ID, new_pal_id);

      // Force a redraw
      game.set_requires_redraw(true);
    }
  }


  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::toggle_window_mode(CreaturePtr creature)
{
  DisplayPtr display = Game::instance().get_display();

  if (display != nullptr && creature != nullptr && creature->get_is_player())
  {
    string result_sid = display->toggle_fullscreen();
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(result_sid));
    manager.send();
  }

  return get_action_cost(creature, ActionCostConstants::NO_ACTION);
}

ActionCost ActionManager::order(CreaturePtr creature)
{
  OrderAction oa;
  return get_action_cost(creature, oa.order(creature));
}

ActionCost ActionManager::evoke(CreaturePtr creature)
{
  EvokeAction ea;

  return get_action_cost(creature, ea.evoke(creature, this));
}

ActionCost ActionManager::evoke(CreaturePtr creature, const string& wand_id, const Direction d)
{
  EvokeAction ea;

  return get_action_cost(creature, ea.evoke(creature, wand_id, d));
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

ActionCost ActionManager::show_skills(CreaturePtr creature, SkillsSelectionType sst)
{
  return get_action_cost(creature, skills_action.show_skills(creature, sst));
}

ActionCost ActionManager::latest_messages(CreaturePtr creature)
{
  LatestMessagesAction lma;

  return get_action_cost(creature, lma.latest_messages(creature));
}

ActionCost ActionManager::kick(CreaturePtr creature, const Direction kick_dir)
{
  KickAction ka;

  return get_action_cost(creature, ka.kick(creature, kick_dir));
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
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  PietyAction pa;
  return get_action_cost(creature, pa.piety(creature, map));
}

ActionCost ActionManager::experience(CreaturePtr creature)
{
  ExperienceAction ea;

  return get_action_cost(creature, ea.experience(creature));
}

// Pick up an item, doing any necessary checks first.
ActionCost ActionManager::pick_up(CreaturePtr creature, const PickUpType pick_up_type)
{
  PickupAction pa;
  return get_action_cost(creature, pa.pick_up(creature, this, pick_up_type));
}

ActionCost ActionManager::pick_up(CreaturePtr creature, const string& ground_item_id)
{
  PickupAction pa;
  return get_action_cost(creature, pa.pick_up(creature, ground_item_id));
}

// Drop an item, doing any necessary checks first.
ActionCost ActionManager::drop(CreaturePtr creature)
{
  DropAction da;
  return get_action_cost(creature, da.drop(creature, this));
}

ActionCost ActionManager::drop(CreaturePtr creature, const string& drop_item_id)
{
  DropAction da;
  return get_action_cost(creature, da.drop(creature, drop_item_id));
}

// Display the inventory; potentially select something.
ItemPtr ActionManager::inventory(CreaturePtr creature, IInventoryPtr inv, const list<IItemFilterPtr>& base_display_filter_list, const list<IItemFilterPtr>& additional_display_filter_list, const bool inventory_is_read_only, const bool allow_multiple_selected_items)
{
  ItemPtr selected_item;
  vector<ItemPtr> items = inventory_multiple(creature, inv, base_display_filter_list, additional_display_filter_list, inventory_is_read_only, allow_multiple_selected_items);

  if (!items.empty())
  {
    selected_item = items[0];
  }

  return selected_item;
}

// Select (potentially) multiple items from the inventory.
vector<ItemPtr> ActionManager::inventory_multiple(CreaturePtr creature, IInventoryPtr inv, const list<IItemFilterPtr>& base_display_filter_list, const list<IItemFilterPtr>& additional_display_filter_list, const bool inventory_is_read_only, const bool allow_multiple_selected_items)
{
  vector<ItemPtr> items;  
  Game& game = Game::instance();
  
  if (creature)
  {
    DisplayPtr game_display = game.get_display();
    InventoryManager inv_manager(game_display, creature);

    items = inv_manager.manage_inventory(inv, base_display_filter_list, additional_display_filter_list, inventory_is_read_only, allow_multiple_selected_items);
  }
  
  return items;
}

// Wear/unwear equipment
ActionCost ActionManager::equipment(CreaturePtr creature)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();
  
  if (creature)
  {
    DisplayPtr game_display = game.get_display();
    
    EquipmentManager equipment_manager(game_display, creature);
    action_cost_value = equipment_manager.manage_equipment();
  }

  return get_action_cost(creature, action_cost_value);
}

ActionCost ActionManager::equipment(CreaturePtr creature, ItemPtr i, const EquipmentWornLocation ewl)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();

  if (creature != nullptr)
  {
    DisplayPtr game_display = game.get_display();
    EquipmentManager equipment_manager(game_display, creature);

    equipment_manager.equip(creature, i, ewl);
  }

  return get_action_cost(creature, acv);
}

ItemPtr ActionManager::select_equipment_or_inventory_item(CreaturePtr creature)
{
  ItemPtr item;
  Game& game = Game::instance();

  if (creature != nullptr)
  {
    DisplayPtr game_display = game.get_display();

    EquipmentManager equipment_manager(game_display, creature);
    item = equipment_manager.select_item();
  }

  return item;
}

ActionCost ActionManager::pray(CreaturePtr creature)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
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
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  CurrentCreatureAbilities cca;

  if (creature && cca.can_see(creature, true))
  {
    action_cost_value = tile_selection_action.select_tile(creature, ActionTextKeys::ACTION_LOOK, TileReset::TILE_RESET_ON_CREATURE);
  }
  
  return get_action_cost(creature, action_cost_value);
}

ActionCostValue ActionManager::select_tile(CreaturePtr creature, const SelectCreatureType sct, TileSelectionAction* const tsa)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

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
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
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

ActionCost ActionManager::fire_missile(CreaturePtr creature, const bool skip_targetting)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  CurrentCreatureAbilities cca;
  
  if (creature && cca.can_see(creature))
  {
    action_cost_value = ranged_combat_action.fire_missile(creature, skip_targetting);
  }
  else
  {
    if (creature && creature->get_is_player())
    {
      IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, true);
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
  int rest_turns = String::to_int(settings.get_setting(Setting::REST_TURNS));
  creature->get_automatic_movement_ref().set_turns(rest_turns);
  MapPtr map = game.get_current_map();

  if (creature && creature->get_is_player() && map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
  {
    IMessageManager& manager = MMF::instance();

    manager.clear_if_necessary();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_RESTING));
    manager.send(MessageSpacing::NO_SPACING);
  }

  AutomaticMovementAction ama;
  return get_action_cost(creature, ama.rest(creature));
}

ActionCost ActionManager::help(CreaturePtr creature)
{
  HelpAction ha;
  return get_action_cost(creature, ha.help(creature));
}

ActionCost ActionManager::inscribe(CreaturePtr creature)
{
  InscribeAction ia;
  return get_action_cost(creature, ia.inscribe(creature));
}

ActionCost ActionManager::automatic_actions(CreaturePtr creature)
{
  AutomaticActionsAction aaa;
  return get_action_cost(creature, aaa.automatic_actions(creature));
}

ActionCost ActionManager::sound_actions(CreaturePtr creature)
{
  SoundSettingsAction ssa;
  return get_action_cost(creature, ssa.sound_actions(creature));
}

ActionCost ActionManager::breed(CreaturePtr creature)
{
  BreedAction ba;
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  return get_action_cost(creature, ba.breed(creature, map));
}

ActionCost ActionManager::save(CreaturePtr creature, const bool quit_after_save)
{
  ExitGameAction ega;
  return get_action_cost(creature, ega.save(creature, quit_after_save));
}

ActionCost ActionManager::quit(CreaturePtr creature)
{
  ExitGameAction ega;
  return get_action_cost(creature, ega.quit(creature, true));
}

// Create an ActionCost based on the ActionCostValue already generated,
// assuming no action multiplier.
ActionCost ActionManager::get_action_cost(CreaturePtr creature, const ActionCostValue action_cost_value)
{
  return get_action_cost(creature, action_cost_value, 1.0);
}

// Create an ActionCost based on the ACV already generated, plus a multiplier.
ActionCost ActionManager::get_action_cost(CreaturePtr creature, const ActionCostValue action_cost_value, const float total_multiplier)
{
  ActionCostValue total_action_cost_value = ActionCostConstants::NO_ACTION;
  
  if (creature && (action_cost_value > 0))
  {
    total_action_cost_value = creature->get_speed().get_current() + action_cost_value;
    total_action_cost_value = static_cast<ActionCostValue>(total_action_cost_value * total_multiplier);
  }
  
  ActionCost ac(total_action_cost_value);
  return ac;
}

SkillsAction& ActionManager::get_skills_action_ref()
{
  return skills_action;
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

