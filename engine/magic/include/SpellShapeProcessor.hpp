#pragma once
#include <vector>
#include <memory>
#include "Animation.hpp"
#include "AttackTypes.hpp"
#include "common.hpp"
#include "Directions.hpp"
#include "DisplayTile.hpp"
#include "Effect.hpp"
#include "Map.hpp"
#include "Spell.hpp"
#include "Tile.hpp"
#include "MapMovementTypes.hpp"

class ActionManager;

// An abstract class for representing shape processing in a particular
// direction.  As an example, a beam processor would handle iterating over
// the points north (or east, etc) for a particular range, applying the
// damage/effect to each tile, determining when to stop, etc.
class SpellShapeProcessor
{
  public:
    virtual ~SpellShapeProcessor();

    // Pure virtual function to get the affected tiles for a particular spell.
    // This will be dependant on the shape: beams generate a line, balls are
    // centered on the caster, etc.
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) = 0;
    virtual bool process_damage_and_effect(CreaturePtr caster, const std::vector<std::pair<Coordinate, TilePtr>>& affected_coords_and_tiles, const Spell& spell, const int bonus, const ItemStatus effect_status, ActionManager * const am, const AttackType attack_type);

  protected:
    virtual std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> create_affected_tiles_and_animation(CreaturePtr caster, MapPtr map, const std::vector<std::pair<Coordinate, TilePtr>>& affected_coords_and_tiles, const MovementPath& movement_path);

    virtual bool apply_damage_and_effect(CreaturePtr caster, const std::vector<std::pair<Coordinate, TilePtr>>& affected_tiles, const Spell& spell, const int bonus, const ItemStatus effect_status, ActionManager * const am, const AttackType attack_type);
    virtual bool apply_damage(CreaturePtr caster, const Coordinate& c, TilePtr tile, const Spell& spell, ActionManager * const am, const AttackType attack_type);
    virtual bool apply_effect(Effect* effect, CreaturePtr caster, const Coordinate& coord, TilePtr tile, const Spell& spell, const int bonus, const ItemStatus effect_status, ActionManager * const am);

    bool is_coordinate_adjacent_to_coordinate_in_previous_frame(const Coordinate& coord, const std::vector<Coordinate>& prev_frame);
};

using SpellShapeProcessorPtr = std::unique_ptr<SpellShapeProcessor>;
