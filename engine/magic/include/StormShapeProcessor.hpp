#pragma once
#include "SpellShapeProcessor.hpp"

class StormShapeProcessor : public SpellShapeProcessor
{
  public:
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) override;

  protected:
    virtual std::vector<Coordinate> generate_potential_coords(MapPtr map, const Coordinate& caster_coord, const Spell& spell);
    virtual std::vector<std::pair<Coordinate, TilePtr>> select_storm_coords(MapPtr map, const Spell& spell, const Coordinate& caster_coord, const std::vector<Coordinate>& coordinates, const uint num_tiles_affected);
};
