#pragma once
#include "DeathManager.hpp"

class DeathManagerFactory
{
  public:
    static DeathManagerPtr create_death_manager(CreaturePtr attacking_creature, CreaturePtr dead_creature, MapPtr map);

  protected:
    DeathManagerFactory();
    ~DeathManagerFactory();
};
