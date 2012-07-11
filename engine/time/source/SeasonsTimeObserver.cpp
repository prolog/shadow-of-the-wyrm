#include "Game.hpp"
#include "SeasonsTimeObserver.hpp"

SeasonsTimeObserver::SeasonsTimeObserver()
{
}

void SeasonsTimeObserver::notify(const ulonglong minutes_passed)
{
  Game* game = Game::instance();
  
  if (game)
  {
    WorldPtr world = game->worlds.at(game->current_world_ix);
    
    if (world)
    {
      Calendar& calendar = world->get_calendar();
      calendar.update_season_if_necessary();
    }
  }
}
