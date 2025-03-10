#pragma once
#include <map>
#include "SpellShapeProcessor.hpp"

// A class for processing cross-shape spells:
//    *
//    *
//  **@**
//    *
//    *
class CrossShapeProcessor : public SpellShapeProcessor
{
  public:
    virtual ~CrossShapeProcessor() = default;

  protected:
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) override;
};

