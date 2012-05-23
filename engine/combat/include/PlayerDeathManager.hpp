#pragma once
#include "DeathManager.hpp"

class PlayerDeathManager : public DeathManager
{
  public:
    PlayerDeathManager(CreaturePtr creature, MapPtr map);
    ~PlayerDeathManager();
  
    void die();
};
