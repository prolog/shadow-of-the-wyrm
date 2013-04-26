#include "AnimationTranslator.hpp"
#include "BeamShapeProcessor.hpp"
#include "BeamSpellTranslator.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

pair<vector<TilePtr>, Animation> BeamShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<TilePtr> affected_tiles;
  Animation animation;

  uint range = spell.get_range();
  Coordinate current_coord = caster_coord;
  TileMagicChecker tmc;
  vector<vector<Coordinate> > movement_path;

  for (uint i = 0; i < range; i++)
  {
    Coordinate c = CoordUtils::get_new_coordinate(current_coord, d);
    TilePtr tile = map->at(c);

    // Check to see if the tile blocks the spell.
    if (tmc.does_tile_block_spell(tile))
    {
      break;
    }

    // Update the current coordinate in the beam, and add the tile to the
    // list of affected tiles.
    current_coord = c;
    affected_tiles.push_back(tile);
    vector<Coordinate> beam_vec;
    beam_vec.push_back(current_coord);
    movement_path.push_back(beam_vec);
  }

  BeamSpellTranslator bst;
  DisplayTile dt = bst.create_display_tile(d, spell.get_colour());

  // Create the animation using the default movement animation mechanism.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  MapPtr fov_map = caster->get_decision_strategy()->get_fov_map();
  Game& game = Game::instance();
  AnimationTranslator at(game.get_display());

  // Create the animation, not redrawing the previous frame at each
  // step, as that will give the desired "beam" shape.
  animation = at.create_movement_animation(dt, game.get_current_world()->get_calendar().get_season()->get_season(), movement_path, false, map, fov_map);

  pair<vector<TilePtr>, Animation> affected_tiles_and_animation(affected_tiles, animation);
  return affected_tiles_and_animation;
}

