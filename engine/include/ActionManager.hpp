#pragma once
#include "Creature.hpp"
#include "Directions.hpp"
#include "Map.hpp"
#include "MovementManager.hpp"

class ActionManager
{
  public:
    ActionManager();
    ~ActionManager();

    void set_current_map(MapPtr new_map);

    void version();
    void search(CreaturePtr creature);
    void move(CreaturePtr creature, const Direction d);

  protected:
    MovementManager movement_manager;
    MapPtr map;
};
