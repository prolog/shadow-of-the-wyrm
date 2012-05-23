#include <boost/make_shared.hpp>
#include "CreatureDeathManager.hpp"
#include "PlayerDeathManager.hpp"
#include "DeathManagerFactory.hpp"

using boost::make_shared;

DeathManagerFactory::DeathManagerFactory()
{
}

DeathManagerFactory::~DeathManagerFactory()
{
}

DeathManagerPtr DeathManagerFactory::create_death_manager(CreaturePtr creature, MapPtr map)
{
  DeathManagerPtr manager;

  if (creature->get_is_player())
  {
    manager = make_shared<PlayerDeathManager>(creature, map);
  }
  else
  {
    manager = make_shared<CreatureDeathManager>(creature, map);
  }

  return manager;
}

