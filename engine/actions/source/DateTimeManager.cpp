#include "Date.hpp"
#include "DateTimeManager.hpp"
#include "Game.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"

DateTimeManager::DateTimeManager()
{
}

ActionCostValue DateTimeManager::date_and_time()
{
  Game* game = Game::instance();
  MessageManager* manager = MessageManager::instance();
  
  if (game && manager && !game->worlds.empty())
  {
    // Get the date from the game's current world's calendar
    WorldPtr world = game->worlds.at(game->current_world_ix);
    
    if (world)
    {
      Date date = world->get_calendar().get_date();

      // Display the date
      // ...
    }
  }

  return get_action_cost_value();
}

// Displaying the date and time is a non-advancing action.
ActionCostValue DateTimeManager::get_action_cost_value() const
{
  return 0;
}
