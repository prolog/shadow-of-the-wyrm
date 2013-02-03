#include "Date.hpp"
#include "DateTimeManager.hpp"
#include "Game.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"

using std::string;

DateTimeManager::DateTimeManager()
{
}

ActionCostValue DateTimeManager::date_and_time()
{
  Game& game = Game::instance();
  MessageManager& manager = MessageManager::instance();
  
  if (!game.worlds.empty())
  {
    // Get the date from the game's current world's calendar
    WorldPtr world = game.worlds.at(game.current_world_ix);
    
    if (world)
    {
      Calendar calendar = world->get_calendar();
      Date date = calendar.get_date();
      ISeasonPtr season = calendar.get_season();
      string date_time_message = DateTextKeys::get_date_time_message(date, season->get_description_sid());
      
      manager.add_new_message(date_time_message);
      manager.send();
    }
  }

  return get_action_cost_value();
}

// Displaying the date and time is a non-advancing action.
ActionCostValue DateTimeManager::get_action_cost_value() const
{
  return 0;
}
