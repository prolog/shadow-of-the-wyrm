#pragma once
#include <memory>
#include "Creature.hpp"
#include "Map.hpp"

class DeathManager
{
  public:
    DeathManager(CreaturePtr attack_creature, CreaturePtr dead_creature, MapPtr current_map);
    ~DeathManager();

    virtual void die() const = 0;
    
  protected:
    void run_death_event(CreaturePtr dead_creature, MapPtr map) const;

    CreaturePtr attacking_creature;
    CreaturePtr dead_creature;
    MapPtr map;

    static const int PCT_CHANCE_CORPSE;
};

using DeathManagerPtr = std::shared_ptr<DeathManager>;
