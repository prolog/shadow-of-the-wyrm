#include "CommandFactoryFactory.hpp"
#include "CombatTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "KeyboardCommandMapFactory.hpp"
#include "MapCursor.hpp"
#include "MessageManagerFactory.hpp"
#include "SelectionUtils.hpp"
#include "Serialize.hpp"
#include "TileDescription.hpp"
#include "TileSelectionAction.hpp"
#include "TileSelectionCommandProcessor.hpp"
#include "TileSelectionCommandFactory.hpp"
#include "TileSelectionKeyboardCommandMap.hpp"
#include "TileSelectionRangeChecker.hpp"

using namespace std;

TileSelectionAction::TileSelectionAction()
: show_tile_description(true), show_feature_description(true), show_creature_description(true), show_item_descriptions(true)
{
  command_factory = std::make_shared<TileSelectionCommandFactory>();
  kb_command_map  = std::make_shared<TileSelectionKeyboardCommandMap>();
}

bool TileSelectionAction::operator==(const TileSelectionAction& tsa) const
{
  bool result = true;

  result = result && kb_command_map && tsa.kb_command_map && (*kb_command_map == *tsa.kb_command_map);
  result = result && (selection_key == tsa.selection_key);
  result = result && (show_tile_description == tsa.show_tile_description);
  result = result && (show_creature_description == tsa.show_creature_description);
  result = result && (show_feature_description == tsa.show_feature_description);
  result = result && (show_item_descriptions == tsa.show_item_descriptions);

  return result;
}

void TileSelectionAction::set_keyboard_command_map(const KeyboardCommandMapPtr new_command_map)
{
  kb_command_map = new_command_map;
}

KeyboardCommandMapPtr TileSelectionAction::get_keyboard_command_map()
{
  return kb_command_map;
}

void TileSelectionAction::set_show_tile_description(const bool tile_desc)
{
  show_tile_description = tile_desc;
}

bool TileSelectionAction::get_show_tile_description() const
{
  return show_tile_description;
}

void TileSelectionAction::set_show_feature_description(const bool feature_desc)
{
  show_feature_description = feature_desc;
}

bool TileSelectionAction::get_show_feature_description() const
{
  return show_feature_description;
}

void TileSelectionAction::set_show_creature_description(const bool creature_desc)
{
  show_creature_description = creature_desc;
}

bool TileSelectionAction::get_show_creature_description() const
{
  return show_creature_description;
}

void TileSelectionAction::set_show_item_descriptions(const bool items_desc)
{
  show_item_descriptions = items_desc;
}

bool TileSelectionAction::get_show_item_descriptions() const
{
  return show_item_descriptions;
}

void TileSelectionAction::set_selection_key(const string& new_selection_key)
{
  selection_key = new_selection_key;
}

ActionCostValue TileSelectionAction::select_tile(CreaturePtr creature, const string& initial_message_sid, const TileReset tre)
{  
  pair<bool, ActionCostValue> command_result(false, 0);
  
  Game& game = Game::instance();
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (creature)
  {
    bool continue_select_tiles = true;
       
    if (creature->get_is_player())
    {
      string look_msg = StringTable::get(initial_message_sid);
      
      manager.add_new_message(look_msg);
      manager.send();

      MapPtr current_map = game.get_current_map();
      reset_cursor_appropriately(creature, current_map, tre);
    }
    
    while (continue_select_tiles)
    {
      DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
      if (decision_strategy)
      {
        CommandPtr tile_selection_command = decision_strategy->get_decision(true, creature->get_id(), command_factory, kb_command_map);
        command_result = TileSelectionCommandProcessor::process(creature, tile_selection_command, this);
        
        continue_select_tiles = command_result.first;
      }
      else
      {
        continue_select_tiles = false;
      }
      
      // Update the screen after the creature's choice
      if (creature->get_is_player())
      {
        game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);        
      }

      if (!continue_select_tiles)
      {
        // If we're no longer selecting the tile, clear the map cursor info.
        select_tile_cancel(creature);
      }
    }
  }
  
  return command_result.second;
}

void TileSelectionAction::reset_cursor_appropriately(CreaturePtr creature, MapPtr current_map, const TileReset tre)
{
  Game& game = Game::instance();

  if (tre == TileReset::TILE_RESET_ON_CREATURE)
  {
    MapCursor mc;
    mc.set_cursor_location(current_map, current_map->get_location(creature->get_id()));
  }
  else if (tre == TileReset::TILE_RESET_ON_PREV_TARGET)
  {
    SelectionUtils::select_existing_target(creature, current_map);
  }

  game.update_display(creature, current_map, creature->get_decision_strategy()->get_fov_map(), false);
}

TilePtr TileSelectionAction::get_cursor_tile()
{
  TilePtr tile;

  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (map)
  {
    MapCursor mc;
    tile = map->at(mc.get_cursor_location(map).first);
  }

  return tile;
}

ActionCostValue TileSelectionAction::select_tile(CreaturePtr creature, const Direction direction)
{
  Game& game = Game::instance();
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (creature && command_factory && kb_command_map)
  {
    MapCursor mc;
    MapPtr current_map = game.get_current_map();
    
    mc.update_cursor_location(current_map, direction);
    Coordinate c = mc.get_cursor_location(current_map).first;
    
    TilePtr selected_tile = current_map->at(c);
    
    // If the tile exists in the FOV map, note that, so that the
    // describer can return full details.  If the at(..) function
    // returns a null shared pointer, the boolean will be false.
    bool tile_exists_in_fov_map = (creature->get_decision_strategy()->get_fov_map()->at(c)) != nullptr;
    
    TileDescription td(show_tile_description, show_feature_description, show_creature_description, show_item_descriptions);
    string tile_desc = td.describe(creature, selected_tile, tile_exists_in_fov_map);

    if (!selection_key.empty())
    {
      pair<string, Coordinate> target(selection_key, c);

      TargetMap& current_targets = creature->get_target_map_ref();
      current_targets[selection_key] = target;
    }
    
    if (creature->get_is_player())
    {
      manager.clear_if_necessary();
      manager.add_new_message(tile_desc);
      manager.send();
    }
  }
  
  return get_action_cost_value(creature);
}

ActionCostValue TileSelectionAction::select_tile(CreaturePtr creature, const SelectCreatureType sct)
{
  if (creature)
  {
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();

    SelectionUtils::select_target_in_cycle(creature, fov_map, sct);
  }

  return get_action_cost_value(creature);
}

ActionCostValue TileSelectionAction::select_tile_cancel(CreaturePtr creature)
{
  Game& game = Game::instance();
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (creature)
  {
    MapCursor mc;
    mc.reset_cursor(game.get_current_map());
    
    if (creature->get_is_player())
    {
      manager.clear_if_necessary();
    }
  }
  
  return get_action_cost_value(creature);
}

// Looking is always free.
ActionCostValue TileSelectionAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

// Check to see if the given tile is in range for a particular attack. If it isn't,
// add a message to inform the user.
bool TileSelectionAction::is_tile_in_range_and_add_message_if_not(CreaturePtr creature, AttackType attack_type) const
{
  bool tile_in_range = true;
  TileSelectionRangeChecker tsrc;

  if (!tsrc.is_selected_tile_in_range(creature, attack_type))
  {
    tile_in_range = false;
    
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    
    string target_too_far = StringTable::get(CombatTextKeys::COMBAT_TARGET_TOO_FAR_AWAY);
    manager.clear_if_necessary();
    manager.add_new_message(target_too_far);
    manager.send();
  }
  
  return tile_in_range;
}

bool TileSelectionAction::remove_target(CreaturePtr creature, const AttackType attack_type)
{
  bool target_removed = false;
  
  if (creature)
  {
    TargetMap& target_map = creature->get_target_map_ref();
    TargetMap::iterator t_it = target_map.find(std::to_string(static_cast<int>(attack_type)));
    
    if (t_it != target_map.end())
    {
      target_map.erase(t_it);
      target_removed = true;
    }
  }
  
  return target_removed;
}

bool TileSelectionAction::serialize(std::ostream& stream) const
{
  Serialize::write_class_id(stream, command_factory->get_class_identifier());
  command_factory->serialize(stream);

  Serialize::write_class_id(stream, kb_command_map->get_class_identifier());
  kb_command_map->serialize(stream);

  Serialize::write_string(stream, selection_key);
  Serialize::write_bool(stream, show_tile_description);
  Serialize::write_bool(stream, show_feature_description);
  Serialize::write_bool(stream, show_creature_description);
  Serialize::write_bool(stream, show_item_descriptions);

  return true;
}

bool TileSelectionAction::deserialize(std::istream& stream)
{
  ClassIdentifier cf_ci;
  Serialize::read_class_id(stream, cf_ci);
  command_factory = CommandFactoryFactory::create_command_factory(cf_ci);
  if (!command_factory) return false;
  if (!command_factory->deserialize(stream)) return false;

  ClassIdentifier kb_cm_ci;
  Serialize::read_class_id(stream, kb_cm_ci);
  kb_command_map = KeyboardCommandMapFactory::create_keyboard_command_map(kb_cm_ci);
  if (!kb_command_map) return false;
  if (!kb_command_map->deserialize(stream)) return false;

  Serialize::read_string(stream, selection_key);
  Serialize::read_bool(stream, show_tile_description);
  Serialize::read_bool(stream, show_feature_description);
  Serialize::read_bool(stream, show_creature_description);
  Serialize::read_bool(stream, show_item_descriptions);

  return true;
}

ClassIdentifier TileSelectionAction::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TILE_SELECTION_ACTION;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileSelectionAction_test.cpp"
#endif

