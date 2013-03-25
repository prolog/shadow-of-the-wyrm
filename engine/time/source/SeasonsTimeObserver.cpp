#include "Game.hpp"
#include "MessageManager.hpp"
#include "SeasonsTimeObserver.hpp"

using std::string;

SeasonsTimeObserver::SeasonsTimeObserver()
{
}

// Call the calendar to update the season if necessary.
// If the season has been updated, add the appropriate season
// transition message.
void SeasonsTimeObserver::notify(const ulonglong minutes_passed)
{
  Game& game = Game::instance();
  
  WorldPtr world = game.worlds.at(game.current_world_ix);
    
  if (world)
  {
    Calendar& calendar = world->get_calendar();
    bool season_updated = calendar.update_season_if_necessary();
      
    if (season_updated)
    {
      string message = calendar.get_season()->get_new_season_message_sid();
      MessageManager& manager = MessageManager::instance();
        
      manager.add_new_message(StringTable::get(message));
      manager.send();

      // Because the seasons are represented by tile colours, we need to
      // ensure that a full redraw of the current map is done so that
      // we don't see a combination of the previous season and the current one.
      Game::instance().set_map_redraw_needed(true);
    }
  }
}

ITimeObserver* SeasonsTimeObserver::clone() 
{
  return new SeasonsTimeObserver(*this);
}

ClassIdentifier SeasonsTimeObserver::internal_class_identifier() const
{
  return CLASS_ID_SEASONS_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/SeasonsTimeObserver_test.cpp"
#endif

