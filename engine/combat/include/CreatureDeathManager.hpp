#pragma once
#include "DeathManager.hpp"

class CreatureDeathManager : public DeathManager
{
  public:
    CreatureDeathManager(CreaturePtr attacked_creature, MapPtr current_map);
    ~CreatureDeathManager();
    
    void die();
};

