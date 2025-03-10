#pragma once
#include "DeathManager.hpp"

class PlayerDeathManager : public DeathManager
{
  public:
    PlayerDeathManager(CreaturePtr attacking_creature, CreaturePtr dead_creature, MapPtr map);
    virtual ~PlayerDeathManager();
  
    void die() const override;
};
