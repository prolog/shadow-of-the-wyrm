#pragma once
#include "SpellShapeProcessor.hpp"

class BallShapeProcessor : public SpellShapeProcessor
{
  public:
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) override;
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, MovementPath> get_affected_coords_and_tiles(MapPtr map, const Spell& spell, const Coordinate& caster_coordinate, const bool draw_tile = false);
};
