#pragma once
#include "DeathManager.hpp"

class DeathManagerFactory
{
  public:
    static DeathManagerPtr create_death_manager(CreaturePtr creature, MapPtr map);

  protected:
    DeathManagerFactory();
    ~DeathManagerFactory();
};
