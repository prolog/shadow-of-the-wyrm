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

    bool move(CreaturePtr creature, const Direction d);
    bool ascend(CreaturePtr creature);
    bool descend(CreaturePtr creature);
    
  protected:
    void move_to_new_map(MapPtr new_map);
    void move_to_new_map(MapExitPtr map_exit);
};
