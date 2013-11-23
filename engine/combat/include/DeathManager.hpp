#pragma once
#include <memory>
#include "Creature.hpp"
#include "Map.hpp"

class DeathManager
{
  public:
    DeathManager(CreaturePtr attack_creature, CreaturePtr dead_creature, MapPtr current_map);
    ~DeathManager();

    virtual void die() = 0;
    
  protected:
    CreaturePtr attacking_creature;
    CreaturePtr dead_creature;
    MapPtr map;
};

typedef std::shared_ptr<DeathManager> DeathManagerPtr;
