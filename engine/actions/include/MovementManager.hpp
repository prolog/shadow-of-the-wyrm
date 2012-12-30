#pragma once
#include "Directions.hpp"
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "MapExit.hpp"
#include "Map.hpp"

class MessageManager;

class MovementManager : public IActionManager
{
  public:
    bool operator==(const MovementManager& mm);

    ActionCostValue move(CreaturePtr creature, const Direction d);
    ActionCostValue ascend(CreaturePtr creature);
    ActionCostValue descend(CreaturePtr creature);

  protected:
    friend class ActionManager;

    MovementManager();
    ~MovementManager();
    
    ActionCostValue get_action_cost_value() const;

    ActionCostValue move_off_map(CreaturePtr creature, MapPtr map, TilePtr old_tile);
    ActionCostValue move_within_map(CreaturePtr creature, MapPtr map, TilePtr creatures_old_tile, TilePtr creatures_new_tile, const Coordinate& new_coords);
    
    void add_tile_related_messages(const CreaturePtr& creature, MessageManager* manager, TilePtr tile);
    void add_message_about_tile_if_necessary(const CreaturePtr& creature, MessageManager* manager, TilePtr tile);
    void add_message_about_items_on_tile_if_necessary(const CreaturePtr& creature, MessageManager* manager, TilePtr tile);
    void move_to_new_map(TilePtr old_tile, MapPtr old_map, MapPtr new_map);
    void move_to_new_map(TilePtr old_tile, MapPtr old_map, MapExitPtr map_exit);
    bool confirm_move_to_tile_if_necessary(CreaturePtr creature, TilePtr creatures_old_tile, TilePtr creatures_new_tile);
};
