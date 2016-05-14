#include <cmath>
#include "AnimationTranslator.hpp"
#include "StormShapeProcessor.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "RNG.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

pair<vector<TilePtr>, Animation> StormShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  uint spell_range = spell.get_range();
  MovementPath movement_path;
  DisplayTile dt('*', static_cast<int>(spell.get_colour()));
  uint num_tiles_affected = static_cast<uint>(pow(spell_range, 2));

  vector<Coordinate> potential_coords = generate_potential_coords(map, caster_coord, spell_range);
  pair<vector<Coordinate>, vector<TilePtr>> storm_movement_path_and_tiles = select_storm_coords(map, potential_coords, num_tiles_affected);
  vector<Coordinate> storm_coords = storm_movement_path_and_tiles.first;

  // Create a movement path for the animation that does one tile at a time,
  // rather than all at once.
  for (const Coordinate& c : storm_coords)
  {
    movement_path.push_back({make_pair(dt, c)});
  }

  // Create the storm animation.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  return create_affected_tiles_and_animation(caster, map, storm_movement_path_and_tiles.second, movement_path);
}

// Generate all the potential coordinates - those in range with valid tiles,
// that are not the caster's tile.
vector<Coordinate> StormShapeProcessor::generate_potential_coords(MapPtr map, const Coordinate& caster_coord, const uint spell_range)
{
  vector<Coordinate> potential_coords;
  int si_spell_range = static_cast<int>(spell_range);
  TileMagicChecker tmc;

  // Generate the coordinates, leaving the caster safe.
  for (int row = (caster_coord.first - si_spell_range); row <= (caster_coord.first + si_spell_range); row++)
  {
    for (int col = (caster_coord.second - si_spell_range); col <= (caster_coord.second + si_spell_range); col++)
    {
      Coordinate storm_coord(row, col);
      TilePtr tile = map->at(storm_coord);

      if ((storm_coord != caster_coord) && tile != nullptr && !tmc.does_tile_block_spell(tile))
      {
        potential_coords.push_back(storm_coord);
      }
    }
  }

  return potential_coords;
}

// Select a number of the potential coordinates for the spell, allowing
// duplicates.
pair<vector<Coordinate>, vector<TilePtr>> StormShapeProcessor::select_storm_coords(MapPtr map, const vector<Coordinate>& coords, const uint num_tiles_affected)
{
  pair<vector<Coordinate>, vector<TilePtr>> result;
  vector<Coordinate> storm_coords(num_tiles_affected);
  vector<TilePtr> affected_tiles;
  size_t coords_size = coords.size();

  for (uint i = 0; i < num_tiles_affected; i++)
  {
    Coordinate rand_coord = coords.at(RNG::range(0, coords_size-1));
    storm_coords[i] = rand_coord;

    TilePtr tile = map->at(rand_coord);
    affected_tiles.push_back(tile);
  }

  result.first = storm_coords;
  result.second = affected_tiles;

  return result;
}
