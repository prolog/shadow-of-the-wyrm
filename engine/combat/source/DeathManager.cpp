#include "DeathManager.hpp"

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

