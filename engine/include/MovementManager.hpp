#pragma once
#include "Directions.hpp"
#include "Map.hpp"

class MovementManager
{
  public:
    MovementManager();
    ~MovementManager();

    void set_current_map(MapPtr new_map);

    void move(CreaturePtr creature, const Direction d);

  protected:
    MapPtr map;
};
