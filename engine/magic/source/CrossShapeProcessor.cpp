#include "AnimationTranslator.hpp"
#include "CrossShapeProcessor.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DirectionUtils.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

pair<vector<TilePtr>, Animation> CrossShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<TilePtr> affected_tiles;
  Animation animation;

  uint range = spell.get_range();
  MovementPath movement_path;
  DisplayTile dt('*', static_cast<int>(spell.get_colour()));
  vector<Direction> directions = {Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH, Direction::DIRECTION_EAST, Direction::DIRECTION_WEST};
  int offset = 1;
  TileMagicChecker tmc;
  vector<Direction> stop_vec;

  // The cross shape is drawn so that each step i in the animation is
  // distance i from the caster.  So all the distance-1 tiles are drawn,
  // then all the distance-2 tiles, etc.
  vector<Coordinate> cross_vec;

  for (uint i = 1; i <= range; i++)
  {
    for (Direction d : directions)
    {
      // Check to see if the spell has already run into a wall, etc,
      // in the given direction.  If so, we should move on to the
      // next direction, since no more spell processing in the first
      // direction should be possible.
      if (find(stop_vec.begin(), stop_vec.end(), d) != stop_vec.end())
      {
        continue;
      }

      Coordinate c = CoordUtils::get_new_coordinate(caster_coord, d, offset);

      TilePtr tile = map->at(c);

      if (tile)
      {
        // If the tile blocks the spell, stop trying to process whatever
        // direction we're currently working with.  This ensures that
        // spells won't be able to go through walls, etc.
        if (tmc.does_tile_block_spell(tile))
        {
          stop_vec.push_back(d);
        }

        affected_tiles.push_back(tile);
        cross_vec.push_back(c);
      }
    }

    vector<pair<DisplayTile, Coordinate>> frame;
    for (const Coordinate& c : cross_vec)
    {
      frame.push_back(make_pair(dt, c));
    }

    movement_path.push_back(frame);
    cross_vec.clear();
    offset++;
  }

  // Create the animation using the default movement animation mechanism.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  MapPtr fov_map = caster->get_decision_strategy()->get_fov_map();
  Game& game = Game::instance();
  AnimationTranslator at(game.get_display());
  CurrentCreatureAbilities cca;
  CreaturePtr player = game.get_current_player();

  // Create the animation, not redrawing the previous frame at each
  // step, as that will give the desired "beam" shape.
  animation = at.create_movement_animation(!cca.can_see(player), game.get_current_world()->get_calendar().get_season()->get_season(), movement_path, false, map, fov_map);

  pair<vector<TilePtr>, Animation> affected_tiles_and_animation(affected_tiles, animation);
  return affected_tiles_and_animation;
}

