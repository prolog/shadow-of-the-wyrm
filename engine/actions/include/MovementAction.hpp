#pragma once
#include "Directions.hpp"
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "MapExit.hpp"
#include "Map.hpp"
#include "MovementTypes.hpp"

class MovementAction : public IActionManager
{
  public:
    bool operator==(const MovementAction& mm) const;

    ActionCostValue move(CreaturePtr creature, const Direction d);
    ActionCostValue ascend(CreaturePtr creature);
    ActionCostValue descend(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
    ActionCostValue get_stumble_action_cost_value() const;

  protected:
    friend class ActionManager;
    friend class StairwayMovementAction;
    friend class AutomaticMovementCoordinator;

    MovementAction();
    ~MovementAction();
    
    // Move off the edge of a map - fields, forests, etc.
    ActionCostValue move_off_map(CreaturePtr creature, MapPtr map, TilePtr old_tile);
    // A standard move within a map.
    ActionCostValue move_within_map(CreaturePtr creature, MapPtr map, TilePtr creatures_old_tile, TilePtr creatures_new_tile, const Coordinate& new_coords, const Direction d);
    // With an existing map, handle the properties on the tile, and then
    // move on to the map.
    ActionCostValue handle_properties_and_move_to_new_map(TilePtr old_tile, MapPtr old_map, MapPtr new_map);
    // Generate a new map, and move to it - staircases, etc.
    ActionCostValue generate_and_move_to_new_map(CreaturePtr creature, MapPtr map, TilePtr tile, const int depth_increment = 0);
    ActionCostValue generate_and_move_to_new_map(CreaturePtr creature, MapPtr map, TilePtr tile, const TileType tile_type, const TileType tile_subtype, const int depth_increment = 0);
    void add_initial_map_messages(CreaturePtr creature, MapPtr map, const TileType tile_type);

    // Handle attempting to move on to a tile where there is a creature present.
    ActionCostValue handle_movement_into_occupied_tile(CreaturePtr creature, TilePtr creatures_new_tile, MapPtr map, const Coordinate& new_coords, const Direction d);
    MovementThroughTileType get_movement_through_tile_type(CreaturePtr creature, CreaturePtr adjacent_creature);

    void add_tile_related_messages(const CreaturePtr& creature, TilePtr tile);
    bool add_message_about_tile_if_necessary(const CreaturePtr& creature, TilePtr tile);
    bool add_message_about_items_on_tile_if_necessary(const CreaturePtr& creature, TilePtr tile);
    void move_to_new_map(TilePtr old_tile, MapPtr old_map, MapPtr new_map);
    void handle_properties_and_move_to_new_map(TilePtr old_tile, MapPtr old_map, MapExitPtr map_exit);
    bool confirm_move_to_tile_if_necessary(CreaturePtr creature, TilePtr creatures_old_tile, TilePtr creatures_new_tile);
};
