#include "DeathManager.hpp"

// Abstract base class for all death managers (general creatures, players,
// etc.)
DeathManager::DeathManager(CreaturePtr attacked_creature, MapPtr current_map)
: creature(attacked_creature), map(current_map)
{
}

DeathManager::~DeathManager()
{
}

