#pragma once
#include "SpellShapeProcessor.hpp"

class ConeShapeProcessor : public SpellShapeProcessor
{
  public:
    virtual ~ConeShapeProcessor() = default;

    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) override;
};
