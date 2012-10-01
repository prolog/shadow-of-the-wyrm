#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "Game.hpp"
#include "MapCursor.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"
#include "TileDescription.hpp"
#include "TileSelectionManager.hpp"
#include "TileSelectionCommandProcessor.hpp"
#include "TileSelectionCommandFactory.hpp"
#include "TileSelectionKeyboardCommandMap.hpp"
#include "TileSelectionRangeChecker.hpp"

using namespace std;

TileSelectionManager::TileSelectionManager()
: show_tile_description(true), show_feature_description(true), show_creature_description(true), show_item_descriptions(true)
{
  command_factory = boost::make_shared<TileSelectionCommandFactory>();
  kb_command_map  = boost::make_shared<TileSelectionKeyboardCommandMap>();
}

void TileSelectionManager::set_keyboard_command_map(const KeyboardCommandMapPtr new_command_map)
{
  kb_command_map = new_command_map;
}

KeyboardCommandMapPtr TileSelectionManager::get_keyboard_command_map()
{
  return kb_command_map;
}

void TileSelectionManager::set_show_tile_description(const bool tile_desc)
{
  show_tile_description = tile_desc;
}

bool TileSelectionManager::get_show_tile_description() const
{
  return show_tile_description;
}

void TileSelectionManager::set_show_feature_description(const bool feature_desc)
{
  show_feature_description = feature_desc;
}

bool TileSelectionManager::get_show_feature_description() const
{
  return show_feature_description;
}

void TileSelectionManager::set_show_creature_description(const bool creature_desc)
{
  show_creature_description = creature_desc;
}

bool TileSelectionManager::get_show_creature_description() const
{
  return show_creature_description;
}

void TileSelectionManager::set_show_item_descriptions(const bool items_desc)
{
  show_item_descriptions = items_desc;
}

bool TileSelectionManager::get_show_item_descriptions() const
{
  return show_item_descriptions;
}

void TileSelectionManager::set_selection_key(const string& new_selection_key)
{
  selection_key = new_selection_key;
}

ActionCostValue TileSelectionManager::select_tile(CreaturePtr creature, const string& initial_message_sid)
{  
  pair<bool, ActionCostValue> command_result(false, 0);
  
  Game* game = Game::instance();
  MessageManager* manager = MessageManager::instance();
  
  if (creature && game)
  {
    bool continue_select_tiles = true;
       
    if (manager && creature->get_is_player())
    {
      string look_msg = StringTable::get(initial_message_sid);
      
      manager->add_new_message(look_msg);
      manager->send();
      
      game->update_display(creature, game->get_current_map(), creature->get_decision_strategy()->get_fov_map());
    }
    
    while (continue_select_tiles)
    {
      DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
      if (decision_strategy)
      {
        CommandPtr tile_selection_command = decision_strategy->get_decision(creature->get_id(), command_factory, kb_command_map);
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
        game->update_display(creature, game->get_current_map(), creature->get_decision_strategy()->get_fov_map());        
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

ActionCostValue TileSelectionManager::select_tile(CreaturePtr creature, const Direction direction)
{
  Game* game = Game::instance();
  MessageManager* manager = MessageManager::instance();

  if (game && creature && manager && command_factory && kb_command_map)
  {
    MapCursor mc;
    MapPtr current_map = game->get_current_map();
    
    mc.update_cursor_location(current_map, direction);
    Coordinate c = mc.get_cursor_location(current_map);
    
    TilePtr selected_tile = current_map->at(c);
    
    // If the tile exists in the FOV map, note that, so that the
    // describer can return full details.  If the at(..) function
    // returns a null shared pointer, the boolean will be false.
    bool tile_exists_in_fov_map = (creature->get_decision_strategy()->get_fov_map()->at(c));
    
    TileDescription td(show_tile_description, show_feature_description, show_creature_description, show_item_descriptions);
    string tile_desc = td.describe(selected_tile, tile_exists_in_fov_map);

    if (!selection_key.empty())
    {
      pair<string, Coordinate> target(selection_key, c);

      TargetMap& current_targets = creature->get_target_map_ref();
      current_targets[selection_key] = target;
    }
    
    if (creature->get_is_player())
    {
      manager->clear_if_necessary();
      manager->add_new_message(tile_desc);
      manager->send();
    }
  }
  
  return get_action_cost_value();
}

ActionCostValue TileSelectionManager::select_tile_cancel(CreaturePtr creature)
{
  Game* game = Game::instance();
  MessageManager* manager = MessageManager::instance();
  
  if (creature && game && manager)
  {
    MapCursor mc;
    mc.reset_cursor(game->get_current_map());
    
    if (creature->get_is_player())
    {
      manager->clear_if_necessary();
    }
  }
  
  return get_action_cost_value();
}

// Looking is always free.
ActionCostValue TileSelectionManager::get_action_cost_value() const
{
  return 0;
}

// Check to see if the given tile is in range for a particular attack. If it isn't,
// add a message to inform the user.
bool TileSelectionManager::is_tile_in_range_and_add_message_if_not(CreaturePtr creature, AttackType attack_type) const
{
  bool tile_in_range = true;
  TileSelectionRangeChecker tsrc;

  if (!tsrc.is_selected_tile_in_range(creature, attack_type))
  {
    tile_in_range = false;
    
    MessageManager* manager = MessageManager::instance();
    
    if (manager)
    {
      string target_too_far = StringTable::get(CombatTextKeys::COMBAT_TARGET_TOO_FAR_AWAY);
      manager->clear_if_necessary();
      manager->add_new_message(target_too_far);
      manager->send();
    }
  }
  
  return tile_in_range;
}

bool TileSelectionManager::remove_target(CreaturePtr creature, const AttackType attack_type)
{
  bool target_removed = false;
  
  if (creature)
  {
    TargetMap& target_map = creature->get_target_map_ref();
    TargetMap::iterator t_it = target_map.find(Integer::to_string(attack_type));
    
    if (t_it != target_map.end())
    {
      target_map.erase(t_it);
      target_removed = true;
    }
  }
  
  return target_removed;
}
