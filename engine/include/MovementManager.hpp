#pragma once
#include "Directions.hpp"
#include "Creature.hpp"
#include "MapExit.hpp"
#include "Map.hpp"

class MovementManager
{
  public:
    MovementManager();
    ~MovementManager();

    void move(CreaturePtr creature, const Direction d);
    void ascend(CreaturePtr creature);
    void descend(CreaturePtr creature);
    
  protected:
    void move_to_new_map(CreaturePtr creature, MapPtr new_map);
    void move_to_new_map(CreaturePtr creature, MapExitPtr map_exit);
};
