#pragma once
#include "DeathManager.hpp"

class CreatureDeathManager : public DeathManager
{
  public:
    CreatureDeathManager(CreaturePtr attacking_creature, CreaturePtr dead_creature, MapPtr current_map);
    ~CreatureDeathManager();
    
    void die() const override;
};

