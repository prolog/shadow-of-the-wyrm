#include "Game.hpp"
#include "TileSelectionManager.hpp"
#include "TileSelectionCommandProcessor.hpp"
#include "TileSelectionCommandFactory.hpp"
#include "TileSelectionKeyboardCommandMap.hpp"

TileSelectionManager::TileSelectionManager()
{
}

ActionCostValue TileSelectionManager::select_tile(CreaturePtr creature)
{  
  if (creature)
  {
    ActionCostValue action_cost = 0;
    bool continue_select_tiles = true;
    
    CommandFactoryPtr command_factory    = CommandFactoryPtr(new TileSelectionCommandFactory());
    KeyboardCommandMapPtr kb_command_map = KeyboardCommandMapPtr(new TileSelectionKeyboardCommandMap());
    
    while (continue_select_tiles)
    {
      DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
      if (decision_strategy)
      {
        CommandPtr tile_selection_command = decision_strategy->get_decision(creature->get_id(), command_factory, kb_command_map);
        action_cost = TileSelectionCommandProcessor::process(creature, tile_selection_command);      
      }
      else
      {
        continue_select_tiles = false;
      }
      
      // "Cancel" action received
      if (action_cost == -1)
      {
        continue_select_tiles = false;
      }
    }
  }
  
  return get_action_cost_value();
}

ActionCostValue TileSelectionManager::select_tile(CreaturePtr creature, const Direction d)
{
  Game* game = Game::instance();

  if (game && creature)
  {
    
  }
  
  return get_action_cost_value();
}

// Looking is always free.
ActionCostValue TileSelectionManager::get_action_cost_value() const
{
  return 0;
}
