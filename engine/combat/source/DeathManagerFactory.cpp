#include "CreatureDeathManager.hpp"
#include "PlayerDeathManager.hpp"
#include "DeathManagerFactory.hpp"

DeathManagerFactory::DeathManagerFactory()
{
}

DeathManagerFactory::~DeathManagerFactory()
{
}

DeathManagerPtr DeathManagerFactory::create_death_manager(CreaturePtr attacking, CreaturePtr dead, MapPtr map)
{
  DeathManagerPtr manager;

  if (dead->get_is_player())
  {
    manager = std::make_shared<PlayerDeathManager>(attacking, dead, map);
  }
  else
  {
    manager = std::make_shared<CreatureDeathManager>(attacking, dead, map);
  }

  return manager;
}

