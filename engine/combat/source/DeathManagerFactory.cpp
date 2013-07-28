#include <boost/make_shared.hpp>
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
    manager = boost::make_shared<PlayerDeathManager>(attacking, dead, map);
  }
  else
  {
    manager = boost::make_shared<CreatureDeathManager>(attacking, dead, map);
  }

  return manager;
}

