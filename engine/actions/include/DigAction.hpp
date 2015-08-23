#pragma once
#include "IActionManager.hpp"

class DigAction : public IActionManager
{
  public:
    // Dig within an existing tile.  Eg, dig up a grave, a barrow, etc.
    ActionCostValue dig_within(CreaturePtr creature, MapPtr map, TilePtr tile) const;

    // Dig through an adjacent tile - break up the tile into another type.
    // Eg, rock should become rocky earth, earth should become floor, etc.
    ActionCostValue dig_through(CreaturePtr creature, ItemPtr dig_item, MapPtr map, TilePtr adjacent_tile, const Direction d) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class StairwayMovementAction;
    friend class MovementAction;

    DigAction();

    bool add_cannot_dig_message_if_necessary(CreaturePtr creature, MapPtr map) const;
    TilePtr dig_tile(TilePtr adjacent_tile) const;
    void add_new_tile_to_dig_location(TilePtr new_tile, MapPtr map, const std::string& creature_id, const Direction d) const;
    void handle_potential_item_breakage(CreaturePtr creature, ItemPtr item) const;
    void add_successful_dig_message(CreaturePtr creature) const;

    static const int DIG_PERCENT_CHANCE_ITEM;
};
