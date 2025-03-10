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
void DeathManager::run_death_event(CreaturePtr attacked_creature, CreaturePtr attack_creature, MapPtr cur_map) const
{
  string death_script_id = CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH;
  ScriptDetails sd = attacked_creature->get_event_script(death_script_id);
  string event_script_name = sd.get_script();
  int chance = sd.get_chance();

  if (!event_script_name.empty() && RNG::percent_chance(chance))
  {
    ScriptEngine& se = Game::instance().get_script_engine_ref();
    DeathScript ds;
    ds.execute(se, event_script_name, attacked_creature, attack_creature, cur_map);

    // Ensure each creature's death script is only run once.
    attacked_creature->remove_event_script(death_script_id);
  }
}

