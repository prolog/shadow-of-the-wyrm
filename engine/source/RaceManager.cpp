#include "RaceManager.hpp"
#include "Game.hpp"

RaceManager::RaceManager()
{
}

// Gets a race from a given race ID, using the race map stored on the
// Game singleton.
RacePtr RaceManager::get_race(const std::string& race_id)
{
  RacePtr race;

  Game& game = Game::instance();

  RaceMap races = game.get_races_ref();

  RaceMap::iterator r_it = races.find(race_id);
    
  if (r_it != races.end())
  {
    race = r_it->second;
  }

  return race;
}
