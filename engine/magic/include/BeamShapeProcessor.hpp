#pragma once
#include <map>
#include "SpellShapeProcessor.hpp"

// A class for processing beam-type spells.
class BeamShapeProcessor : public SpellShapeProcessor
{
  public:
    BeamShapeProcessor();

protected:
  virtual std::pair<std::vector<TilePtr>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) override;
    virtual bool should_beam_reflect() const;

    virtual Direction get_new_beam_direction_after_impact(const Direction old_direction, const Coordinate& current_coord, MapPtr map);

    Direction get_ne_reflection(const Coordinate& current_coord, MapPtr map);
    Direction get_nw_reflection(const Coordinate& current_coord, MapPtr map);
    Direction get_se_reflection(const Coordinate& current_coord, MapPtr map);
    Direction get_sw_reflection(const Coordinate& current_coord, MapPtr map);

    void initialize_reflection_maps();
    void initialize_cardinal_reflection_map();

    static std::map<Direction, Direction> cardinal_reflection_map;
};

typedef std::map<Direction, Direction>::iterator ReflectionMapIterator;
typedef std::map<Direction, Direction>::const_iterator ReflectionMapCIterator;

