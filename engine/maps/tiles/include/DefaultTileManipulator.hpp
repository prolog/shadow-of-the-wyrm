#pragma once
#include "ITileManipulator.hpp"

// Default tile manipulator.  Defines manipulation operations that do
// very little - if there's any tile-specific behaviour, the factory
// will instantiate a different class.
class DefaultTileManipulator : public ITileManipulator
{
  public:
    DefaultTileManipulator();

    bool dig(CreaturePtr creature, MapPtr map, TilePtr tile) override;
    void add_undead_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile);
    void add_item_if_necessary(CreaturePtr creature, MapPtr map, TilePtr tile);
    void add_detritus(CreaturePtr creature, MapPtr map, TilePtr tile);

  protected:

    std::map<TileSuperType, std::string> super_type_message_sids;

    // The danger level of the undead considered ranges from half the creature's
    // level to some offset above the creature's level (level + 5).
    static const int UNDEAD_LEVEL_UPPER_BOUND_OFFSET;

    static const int PCT_CHANCE_DETRITUS;
    static const int PCT_CHANCE_CLAY;
    static const int PCT_CHANCE_CLAY_NEARBY;
};

