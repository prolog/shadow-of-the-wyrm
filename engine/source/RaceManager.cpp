#include "RaceManager.hpp"
#include "Game.hpp"

using namespace std;

RaceManager::RaceManager()
{
}

// Gets a race from a given race ID, using the race map stored on the
// Game singleton.
Race* RaceManager::get_race(const string& race_id)
{
  Race* race = nullptr;
  Game& game = Game::instance();
  const RaceMap& races = game.get_races_ref();
  auto r_it = races.find(race_id);
    
  if (r_it != races.end())
  {
    race = r_it->second.get();
  }

  return race;
}

vector<string> RaceManager::get_race_ids(const bool include_user_playable, const bool include_non_slayable)
{
  Game& game = Game::instance();
  const RaceMap& rm = game.instance().get_races_ref();
  vector<string> race_ids;

  for (const auto& race_pair : rm)
  {
    Race* race = race_pair.second.get();

    if (race != nullptr &&
      !race_pair.first.empty() &&
      (include_user_playable || !race->get_user_playable()) &&
      (include_non_slayable || race->get_slayable()))
    {
      race_ids.push_back(race_pair.first);
    }
  }

  return race_ids;
}

// Checks to see if one race is related to another
bool RaceManager::is_race_or_descendent(const string& race_id, const string& race_to_match)
{
  bool matches = false;

  Race* current_race;
  string parent_race_id;
  string current_race_id;

  Game& game = Game::instance();
  const RaceMap& races = game.get_races_ref();

  auto r_it = races.find(race_id);
    
  if (r_it != races.end())
  {
    current_race = r_it->second.get();
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
          current_race    = r_it->second.get();
          current_race_id = current_race->get_race_id();
          parent_race_id  = current_race->get_parent_race_id();
        }
      }
    }
  }

  return matches;
}

map<string, DropParameters> RaceManager::get_all_drops(const string& race_id)
{
  map<string, DropParameters> drops;

  Game& game = Game::instance();
  const RaceMap& races = game.get_races_ref();
  Race* current_race;
  string current_race_id, parent_race_id;

  auto r_it = races.find(race_id);

  if (r_it != races.end())
  {
    current_race = r_it->second.get();
    parent_race_id = current_race->get_parent_race_id();
    current_race_id = current_race->get_race_id();

    // Walk up the race hierarchy, checking to see if the parent matches.
    // Keep track of the races we've seen to break any cycles that occur.
    set<string> seen_races;

    // If the parent race isn't in the "seen" set yet, add it, and continue.
    while (seen_races.find(current_race_id) == seen_races.end())
    {
      seen_races.insert(current_race_id);

      map<string, DropParameters> cur_race_drops = current_race->get_drops();
      drops.insert(cur_race_drops.begin(), cur_race_drops.end());

      r_it = races.find(parent_race_id);

      if (r_it != races.end())
      {
        current_race = r_it->second.get();
        current_race_id = current_race->get_race_id();
        parent_race_id = current_race->get_parent_race_id();
      }
    }
  }

  return drops;
}
