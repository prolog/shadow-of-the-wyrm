#include <string>
#include "DeathManager.hpp"
#include "DeathScript.hpp"
#include "Game.hpp"
#include "RNG.hpp"

using namespace std;

const int DeathManager::PCT_CHANCE_CORPSE = 15;

// Abstract base class for all death managers (general creatures, players,
// etc.)
DeathManager::DeathManager(CreaturePtr attacking, CreaturePtr attacked_creature, MapPtr current_map)
: attacking_creature(attacking), dead_creature(attacked_creature), map(current_map)
{
}

DeathManager::~DeathManager()
{
}

// Run the death event.
void DeathManager::run_death_event(CreaturePtr attacked_creature, MapPtr map) const
{
  ScriptDetails sd = attacked_creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH);
  string event_script_name = sd.get_script();
  int chance = sd.get_chance();
  string creature_id;

  if (attacked_creature != nullptr)
  {
    creature_id = attacked_creature->get_id();
  }

  if (!event_script_name.empty() && RNG::percent_chance(chance))
  {
    ScriptEngine& se = Game::instance().get_script_engine_ref();
    DeathScript ds;
    ds.execute(se, event_script_name, attacked_creature);
  }
}

