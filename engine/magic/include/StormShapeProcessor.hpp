#pragma once
#include "SpellShapeProcessor.hpp"

class StormShapeProcessor : public SpellShapeProcessor
{
  public:
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) override;

  protected:
    virtual std::vector<Coordinate> generate_potential_coords(MapPtr map, const Coordinate& caster_coord, const Spell& spell);
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, MovementPath> get_storm_tiles_and_movement(MapPtr map, const Spell& spell, const Coordinate& caster_coord, const std::vector<Coordinate>& coordinates, const uint num_tiles_affected);
    virtual void remove_caster_details_from_ball(std::pair<std::vector<std::pair<Coordinate, TilePtr>>, MovementPath>& ball_details, const Coordinate& caster_coord);
};
