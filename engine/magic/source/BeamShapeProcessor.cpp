#include "AnimationTranslator.hpp"
#include "BeamShapeProcessor.hpp"
#include "BeamSpellTranslator.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DirectionUtils.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

map<Direction, Direction> BeamShapeProcessor::cardinal_reflection_map;

BeamShapeProcessor::BeamShapeProcessor()
{
  if (cardinal_reflection_map.empty())
  {
    initialize_reflection_maps();
  }
}

// Set up the directions for the reflection direction lookup maps.
void BeamShapeProcessor::initialize_reflection_maps()
{
  cardinal_reflection_map.clear();

  initialize_cardinal_reflection_map();
}

// Set up the reflection directions when striking a corner tile.
void BeamShapeProcessor::initialize_cardinal_reflection_map()
{
  cardinal_reflection_map = std::map<Direction, Direction>{{DIRECTION_NORTH, DIRECTION_SOUTH},
                                                           {DIRECTION_EAST, DIRECTION_WEST},
                                                           {DIRECTION_WEST, DIRECTION_EAST},
                                                           {DIRECTION_SOUTH, DIRECTION_NORTH}};
}

pair<vector<TilePtr>, Animation> BeamShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<TilePtr> affected_tiles;
  Animation animation;

  uint range = spell.get_range();
  Coordinate current_coord = caster_coord;
  TileMagicChecker tmc;
  

  vector<pair<DisplayTile, vector<Coordinate>>> movement_path;

  // For regular beams, the current direction will always be the passed-in
  // direction (the beam will "fizzle out" if it hits a blocking tile).  For
  // reflective beams (a subclass), the current direction will change as the
  // beam bounces.
  Direction current_direction = d;

  BeamSpellTranslator bst;
  DisplayTile dt = bst.create_display_tile(spell.get_range(), current_direction, spell.get_colour());

  uint count = 0;
  while (count < range)
  {
    Coordinate c = CoordUtils::get_new_coordinate(current_coord, current_direction);
    
    TilePtr tile = map->at(c);

    // Check to see if the tile blocks the spell.
    if (tmc.does_tile_block_spell(tile))
    {
      if (should_beam_reflect())
      {
        // The beam is reflective. Update the direction based on the the
        // incoming direction and map characteristics.
        current_direction = get_new_beam_direction_after_impact(current_direction, c, map);

        // Edge case: caster is standing by the wall.
        if (current_coord == caster_coord)
        {
          current_coord = c;
        }

        // Update the symbol for the display
        dt = bst.create_display_tile(spell.get_range(), current_direction, spell.get_colour());

        // The beam bounces off this tile, but it does not affect it - exclude it from
        // the animation and from processing.
        continue;
      }
      else
      {
        // The beam dissipates after striking the obstacle.
        break;
      }
    }

    // Update the current coordinate in the beam, and add the tile to the
    // list of affected tiles.
    current_coord = c;
    affected_tiles.push_back(tile);
    vector<Coordinate> beam_vec;
    beam_vec.push_back(current_coord);
    movement_path.push_back(make_pair(dt, beam_vec));
    count++; // Didn't bounce - update the spell range counter.
  }

  // Create the animation using the default movement animation mechanism.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  return create_affected_tiles_and_animation(caster, map, affected_tiles, movement_path);
}

// By default, beams do not reflect - only instances of ReflectiveBeam should.
bool BeamShapeProcessor::should_beam_reflect() const
{
  return false;
}

// Get the new beam direction after an impact.
Direction BeamShapeProcessor::get_new_beam_direction_after_impact(const Direction old_direction, const Coordinate& current_coord, MapPtr map)
{
  if (DirectionUtils::is_cardinal(old_direction))
  {
    return cardinal_reflection_map[old_direction];
  }

  // It's not cardinal, so we're dealing with an ordinal direction
  // (NW, SE, etc).  Figure out the correct reflection direction.
  if (old_direction == DIRECTION_NORTH_EAST)
  {
    return get_ne_reflection(current_coord, map);
  }
  else if (old_direction == DIRECTION_NORTH_WEST)
  {
    return get_nw_reflection(current_coord, map);
  }
  else if (old_direction == DIRECTION_SOUTH_EAST)
  {
    return get_se_reflection(current_coord, map);
  }
  else if (old_direction == DIRECTION_SOUTH_WEST)
  {
    return get_sw_reflection(current_coord, map);
  }

  // Should never actually get to this, based on the above logic:
  return old_direction;
}

Direction BeamShapeProcessor::get_ne_reflection(const Coordinate& current_coord, MapPtr map)
{
  TileMagicChecker tmc;

  Direction reflection;

  // Inside/outside the corner
  if (MapUtils::is_corner(current_coord, DIRECTION_NORTH_EAST, map) || (MapUtils::is_corner(current_coord, DIRECTION_SOUTH_WEST, map)))
  {
    reflection = DIRECTION_SOUTH_WEST;
  }
  else
  {
    // Are we firing at a northern wall?  Reflect south-east.
    TilePtr north_wall_tile = map->at(CoordUtils::get_new_coordinate(current_coord, DIRECTION_WEST));

    if (north_wall_tile && tmc.does_tile_block_spell(north_wall_tile))
    {
      reflection = DIRECTION_SOUTH_EAST;
    }
    else
    {
      reflection = DIRECTION_NORTH_WEST; 
    }
  }

  return reflection;
}

Direction BeamShapeProcessor::get_nw_reflection(const Coordinate& current_coord, MapPtr map)
{
  TileMagicChecker tmc;

  Direction reflection;

  // Inside/outside the corner
  if (MapUtils::is_corner(current_coord, DIRECTION_NORTH_WEST, map) || MapUtils::is_corner(current_coord, DIRECTION_SOUTH_EAST, map))
  {
    reflection = DIRECTION_SOUTH_EAST;
  }
  else
  {
    // Are we firing at a northern wall?  Reflect south-west.
    TilePtr north_wall_tile = map->at(CoordUtils::get_new_coordinate(current_coord, DIRECTION_EAST));

    if (north_wall_tile && tmc.does_tile_block_spell(north_wall_tile))
    {
      reflection = DIRECTION_SOUTH_WEST;
    }
    else
    {
      reflection = DIRECTION_NORTH_EAST; 
    }
  }

  return reflection;
}

Direction BeamShapeProcessor::get_se_reflection(const Coordinate& current_coord, MapPtr map)
{
  TileMagicChecker tmc;
  
  Direction reflection;

  // Inside/outside the corner
  if (MapUtils::is_corner(current_coord, DIRECTION_SOUTH_EAST, map) || MapUtils::is_corner(current_coord, DIRECTION_NORTH_WEST, map))
  {
    reflection = DIRECTION_NORTH_WEST;
  }
  else
  {
    // Are we firing at a southern wall?  Reflect north-east.
    TilePtr south_wall_tile = map->at(CoordUtils::get_new_coordinate(current_coord, DIRECTION_WEST));

    if (south_wall_tile && tmc.does_tile_block_spell(south_wall_tile))
    {
      reflection = DIRECTION_NORTH_EAST;
    }
    else
    {
      reflection = DIRECTION_SOUTH_WEST;
    }
  }

  return reflection;
}

Direction BeamShapeProcessor::get_sw_reflection(const Coordinate& current_coord, MapPtr map)
{
  TileMagicChecker tmc;

  Direction reflection;

  // Inside or outside the corner
  if (MapUtils::is_corner(current_coord, DIRECTION_SOUTH_WEST, map) || MapUtils::is_corner(current_coord, DIRECTION_NORTH_EAST, map))
  {
    reflection = DIRECTION_NORTH_EAST;
  }
  else
  {
    // Are we firing at a southern wall?  Reflect north-east.
    TilePtr south_wall_tile = map->at(CoordUtils::get_new_coordinate(current_coord, DIRECTION_EAST));

    if (south_wall_tile && tmc.does_tile_block_spell(south_wall_tile))
    {
      reflection = DIRECTION_NORTH_WEST;
    }
    else
    {
      reflection = DIRECTION_SOUTH_EAST;
    }
  }

  return reflection;
}