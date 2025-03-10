#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class KickAction : public IActionManager
{
  public:
    ActionCostValue kick(CreaturePtr creature, const Direction kick_dir = Direction::DIRECTION_NULL);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    KickAction();

    ActionCostValue kick_on_world_map(CreaturePtr creature, MapPtr current_map);
    ActionCostValue kick_on_regular_map(CreaturePtr creature, MapPtr current_map, const Direction kick_dir);
    ActionCostValue kick_in_direction(CreaturePtr creature, MapPtr current_map, const Direction direction);
    ActionCostValue kick_creature(CreaturePtr kicking_creature, CreaturePtr kicked_creature);
    ActionCostValue kick_feature(CreaturePtr creature, MapPtr current_map, TilePtr kick_tile, const Coordinate& kick_coord, FeaturePtr tile_feature);
    ActionCostValue kick_item(CreaturePtr creature, MapPtr current_map, TilePtr kick_tile, TilePtr new_tile);
    ActionCostValue kick_tile(CreaturePtr creature, TilePtr kick_tile);
};
