#include "ReligionManager.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "ReligionConstants.hpp"
#include "TextKeys.hpp"

using std::string;

ReligionManager::ReligionManager()
{
}

Deity* ReligionManager::get_active_deity(CreaturePtr creature)
{
  Religion& religion = creature->get_religion_ref();
  string deity_id = religion.get_active_deity_id();
  return get_deity(deity_id);
}

DeityStatus ReligionManager::get_active_deity_status(CreaturePtr creature)
{
  Religion& religion = creature->get_religion_ref();
  string deity_id = religion.get_active_deity_id();
  DeityStatus status = religion.get_deity_status(deity_id);

  return status;
}

// Get the creature's piety for its active deity.
int ReligionManager::get_piety_for_active_deity(CreaturePtr creature)
{
  DeityStatus status = get_active_deity_status(creature);

  return status.get_piety();
}

// Get a pointer to the deity on the game.
Deity* ReligionManager::get_deity(const string& deity_id) const
{
  Game& game = Game::instance();
  Deity* deity = nullptr;
  
  const DeityMap& deities = game.get_deities_cref();
  auto d_it = deities.find(deity_id);
  if (d_it != deities.end())
  {
    deity = d_it->second.get();
  }
  
  return deity;
}

// Get the deity's name from the string ID provided.
string ReligionManager::get_deity_name_sid(const string& deity_id) const
{
  string deity_name_sid;
  Deity* deity = get_deity(deity_id);
    
  if (deity != nullptr)
  {
    deity_name_sid = deity->get_name_sid();
  }
  else if (deity_id == ReligionConstants::DEITY_ID_GODLESS)
  {
    deity_name_sid = DeityTextKeys::DEITY_GODLESS;
  }
  else
  {
    deity_name_sid = TextKeys::DEITY_GONE;
  }
  
  return deity_name_sid;
}

// Look up the deity and get the death message based on the provided SID.
string ReligionManager::get_death_message_sid(const string& deity_id) const
{
  string death_message; // "Hurry, hurry - gal you love is dead"?
  Deity* deity = get_deity(deity_id);
  
  if (deity != nullptr)
  {
    death_message = deity->get_death_message_sid();
  }
  
  return death_message;
}
