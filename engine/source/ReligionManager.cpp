#include "ReligionManager.hpp"
#include "Game.hpp"

using std::string;

ReligionManager::ReligionManager()
{
}

DeityStatus ReligionManager::get_active_deity_status(CreaturePtr creature)
{
  Religion& religion = creature->get_religion_ref();
  string deity_id = religion.get_active_deity_id();
  DeityPtr creature_deity = get_deity(deity_id);
  DeityStatus status = religion.get_deity_status(deity_id);

  return status;
}

// Get the creature's piety for its active deity.
int ReligionManager::get_piety_for_active_deity(CreaturePtr creature)
{
  DeityStatus status = get_active_deity_status(creature);

  return status.get_piety();
}

// Get a shared pointer to the deity.
DeityPtr ReligionManager::get_deity(const string& deity_id) const
{
  Game& game = Game::instance();
  DeityPtr deity;
  
  DeityMap deities = game.get_deities_ref();
  deity            = deities[deity_id];
  
  return deity;
}

// Get the deity's name from the string ID provided.
string ReligionManager::get_deity_name_sid(const string& deity_id) const
{
  string deity_name_sid;
  DeityPtr deity = get_deity(deity_id);
    
  if (deity)
  {
    deity_name_sid = deity->get_name_sid();
  }
  
  return deity_name_sid;
}

// Look up the deity and get the death message based on the provided SID.
string ReligionManager::get_death_message_sid(const string& deity_id) const
{
  string death_message; // "Hurry, hurry - gal you love is dead"?
  DeityPtr deity = get_deity(deity_id);
  
  if (deity)
  {
    death_message = deity->get_death_message_sid();
  }
  
  return death_message;
}
