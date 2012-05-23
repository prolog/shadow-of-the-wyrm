#pragma once
#include <boost/shared_ptr.hpp>
#include "Creature.hpp"
#include "Map.hpp"

class DeathManager
{
  public:
    DeathManager(CreaturePtr attacked_creature, MapPtr current_map);
    ~DeathManager();

    virtual void die() = 0;
    
  protected:
    CreaturePtr creature;
    MapPtr map;
};

typedef boost::shared_ptr<DeathManager> DeathManagerPtr;
