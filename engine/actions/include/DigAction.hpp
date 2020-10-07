#pragma once
#include "IActionManager.hpp"

class DigAction : public IActionManager
{
  public:
    // Dig within an existing tile.  Eg, dig up a grave, a barrow, etc.
    ActionCostValue dig_within(CreaturePtr creature, ItemPtr dig_item, MapPtr map, TilePtr tile) const;

    // Dig through an adjacent tile - break up the tile into another type.
    // Eg, rock should become rocky earth, earth should become floor, etc.
    ActionCostValue dig_through(const std::string& digging_creature_id, ItemPtr dig_item, MapPtr map, TilePtr adjacent_tile, const Coordinate& adjacent_coordinate, const bool add_messages, const bool dig_tile_only) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class StairwayMovementAction;
    friend class MovementAction;
    friend class DiggingEffect;

    DigAction();

    TilePtr dig_tile(CreaturePtr creature, TilePtr adjacent_tile, const bool dig_tile_only) const;
    bool dig_feature(TilePtr adjacent_tile) const;
    bool dig_items(IInventoryPtr inv) const;

    bool add_cannot_dig_message_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile) const;
    void add_cannot_dig_on_tile_super_type_message(CreaturePtr creature) const;
    bool tile_super_type_supports_digging(const TileSuperType tst) const;
    void handle_potential_item_breakage(CreaturePtr creature, TilePtr adjacent_tile, ItemPtr item) const;
    void add_successful_dig_message(CreaturePtr creature) const;
    void add_stone_dust_message(CreaturePtr creature) const;

    static const int DIG_PERCENT_CHANCE_MARK_STATISTIC;
};
