#include "ReligionManager.hpp"
#include "Game.hpp"

using std::string;

ReligionManager::ReligionManager()
{
}

// Get the deity's name from the string ID provided.
string ReligionManager::get_deity_name_sid(const string& deity_id) const
{
  string deity_name_sid;
  
  Game* game = Game::instance();
  
  if (game)
  {
    DeityMap deities = game->get_deities_ref();
    DeityPtr deity   = deities[deity_id];
    
    if (deity)
    {
      deity_name_sid = deity->get_name_sid();
    }
  }
  
  return deity_name_sid;
}

// Look up the deity and get the death message based on the provided SID.
string ReligionManager::get_death_message_sid(const string& deity_id) const
{
  string death_message; // "Hurry, hurry - gal you love is dead"?
  
  Game* game = Game::instance();
  
  if (game)
  {
    DeityMap deities = game->get_deities_ref();
    DeityPtr deity   = deities[deity_id];
    
    if (deity)
    {
      death_message = deity->get_death_message_sid();
    }
  }
  
  return death_message;
}
