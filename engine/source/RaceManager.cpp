#include "RaceManager.hpp"
#include "Game.hpp"

using namespace std;

RaceManager::RaceManager()
{
}

// Gets a race from a given race ID, using the race map stored on the
// Game singleton.
RacePtr RaceManager::get_race(const string& race_id)
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

// Checks to see if one race is related to another
bool RaceManager::is_race_or_descendent(const string race_id, const string& race_to_match)
{
  bool matches = false;

  RacePtr current_race;
  string parent_race_id;
  string current_race_id;

  Game& game = Game::instance();
  RaceMap races = game.get_races_ref();

  RaceMap::iterator r_it = races.find(race_id);
    
  if (r_it != races.end())
  {
    current_race = r_it->second;
    parent_race_id = current_race->get_parent_race_id();
    current_race_id = current_race->get_race_id();

    // Walk up the race hierarchy, checking to see if the parent matches.
    // Keep track of the races we've seen to break any cycles that occur.
    set<string> seen_races;

    // If the parent race isn't in the "seen" set yet, add it, and continue.
    while (seen_races.find(current_race_id) == seen_races.end())
    {
      seen_races.insert(current_race_id);

      if (current_race_id == race_to_match)
      {
        matches = true;
      }
      else
      {
        r_it = races.find(parent_race_id);

        if (r_it != races.end())
        {
          current_race    = r_it->second;
          current_race_id = current_race->get_race_id();
          parent_race_id  = current_race->get_parent_race_id();
        }
      }
    }
  }

  return matches;
}
