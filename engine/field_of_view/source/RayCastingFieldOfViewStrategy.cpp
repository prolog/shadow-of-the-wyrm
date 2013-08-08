#include <sstream>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "RayCastingFieldOfViewStrategy.hpp"
#include "BresenhamLine.hpp"
#include "MapUtils.hpp"

#include "Conversion.hpp"
#include "Log.hpp"

using std::string;
using std::vector;

RayCastingFieldOfViewStrategy::RayCastingFieldOfViewStrategy(const bool set_view_property)
: FieldOfViewStrategy(set_view_property)
{
}

MapPtr RayCastingFieldOfViewStrategy::calculate(CreaturePtr fov_creature, MapPtr view_map, const Coordinate& centre_coord, const int los_length)
{
  MapPtr fov_map = boost::make_shared<Map>(view_map->size());
  BresenhamLine bl;
  
  int row = centre_coord.first;
  int col = centre_coord.second;
  
  // Always add the centre position to the view map - the creature always knows its own location.
  add_point_to_map(fov_creature, centre_coord, view_map, fov_map);

  Coordinate cur_coord;
  vector<Coordinate> line_points;
  
  // Top and bottom rows
  for (int row_cur_x = col - los_length; row_cur_x <= col + los_length; row_cur_x++)
  {
    // Top
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, row - los_length, row_cur_x);
    add_points_to_map_as_appropriate(fov_creature, line_points, view_map, fov_map);
    
    // Bottom
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, row + los_length, row_cur_x);
    add_points_to_map_as_appropriate(fov_creature, line_points, view_map, fov_map);
  }
  
  // Left and right columns
  for (int col_cur_y = row - los_length; col_cur_y <= row + los_length; col_cur_y++)
  {
    // Top
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, col_cur_y, col - los_length);
    add_points_to_map_as_appropriate(fov_creature, line_points, view_map, fov_map);

    // Bottom
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, col_cur_y, col + los_length);
    add_points_to_map_as_appropriate(fov_creature, line_points, view_map, fov_map);
  }
  
  // Pass 1: regular walls/blocking tiles
  post_process_to_remove_artifacts(fov_creature, centre_coord, view_map, fov_map, PASS_NON_CORNER_BLOCKING_TILES);
  
  // Pass 2: corner walls/blocking tiles
  post_process_to_remove_artifacts(fov_creature, centre_coord, view_map, fov_map, PASS_CORNER_BLOCKING_TILES);
  
  return fov_map;
}

void RayCastingFieldOfViewStrategy::add_points_to_map_as_appropriate(CreaturePtr fov_creature, const std::vector<Coordinate>& coords, MapPtr view_map, MapPtr fov_map)
{
  CurrentCreatureAbilities cca;
  bool creature_blinded = (cca.can_see(fov_creature) == false);

  BOOST_FOREACH(Coordinate c, coords)
  {
    TilePtr tile = view_map->at(c);
    
    if (!tile)
    {
      return;
    }
    else
    {
      if (!creature_blinded)
      {
        add_point_to_map(fov_creature, c, view_map, fov_map);
      }

      if (tile->get_is_blocking())
      {
        return;
      }
    }
  }
}

// Credit where credit is due: this is based on jice's "piece of cake visibility determination" page.
void RayCastingFieldOfViewStrategy::post_process_to_remove_artifacts(CreaturePtr fov_creature, const Coordinate& centre_coord, MapPtr view_map, MapPtr fov_map, const PassType type)
{
  TilesContainer tile_cont = view_map->get_tiles();
  TilesContainer fov_tile_cont = fov_map->get_tiles();
  TilesContainer::iterator t_it;
  
  Log::instance().log("Centre coord: " + Integer::to_string(centre_coord.first) + "," + Integer::to_string(centre_coord.second));

  for (t_it = tile_cont.begin(); t_it != tile_cont.end(); t_it++)
  {
    string tile_coords = t_it->first;
    TilePtr current_view_tile = t_it->second;
    
    if (current_view_tile && current_view_tile->get_is_blocking() && (fov_tile_cont.find(tile_coords) == fov_tile_cont.end()))
    {
      Coordinate c = MapUtils::convert_map_key_to_coordinate(tile_coords);
      
      std::ostringstream ss;
      
      // If we're in the north-west region, and the current tile is north or west of a ground cell in the FOV map, add it to the FOV map.
      if ((c.first < centre_coord.first) && (c.second < centre_coord.second))
      {
        if (is_artifact_nw(fov_map, c, type))
        {
          Log::instance().debug(tile_coords + " not in list, NW, adjacent to a lit tile.");
          add_point_to_map(fov_creature, c, view_map, fov_map);
        }
      }
      // If we're in the north-east region, and the current tile is north or east of a ground cell in the FOV map, add it to the FOV map.
      else if ((c.first < centre_coord.first) && (c.second > centre_coord.second))
      {
        if (is_artifact_ne(fov_map, c, type))
        {
          Log::instance().debug(tile_coords + " not in list, NE, adjacent to a lit tile.");
          add_point_to_map(fov_creature, c, view_map, fov_map);
        }
      }
      // If we're in the south-west region, and the current tile is south or west of a ground cell in the FOV map, add it to the FOV map.
      else if ((c.first > centre_coord.first) && (c.second < centre_coord.second))
      {
        if (is_artifact_sw(fov_map, c, type))
        {
          Log::instance().debug(tile_coords + " not in list, SW, adjacent to a lit tile.");
          add_point_to_map(fov_creature, c, view_map, fov_map);
        }
      }
      // If we're in the south-east region, and the current tile is south or east of a ground cell in the FOV map, add it to the FOV map.
      else if ((c.first > centre_coord.first) && (c.second > centre_coord.second))
      {
        if (is_artifact_se(fov_map, c, type))
        {
          Log::instance().debug(tile_coords + " not in list, SE, adjacent to a lit tile.");
          add_point_to_map(fov_creature, c, view_map, fov_map);
        }
      }
    }
  }
}

bool RayCastingFieldOfViewStrategy::does_adjacent_non_blocking_tile_exist_in_fov_map(MapPtr fov_map, const Coordinate& centre_coord, const Direction direction)
{
  Coordinate c_dir = CoordUtils::get_new_coordinate(centre_coord, direction);
  TilePtr tile = fov_map->at(c_dir);
  
  if (tile)
  {
    std::ostringstream ss;
    ss << "(" << c_dir.first << "," << c_dir.second << ")";
    Log::instance().log(ss.str());
  }
  
  return (tile && (tile->get_is_blocking() == false));
}

bool RayCastingFieldOfViewStrategy::does_adjacent_blocking_tile_exist_in_fov_map(MapPtr fov_map, const Coordinate& centre_coord, const Direction direction)
{
  Coordinate c_dir = CoordUtils::get_new_coordinate(centre_coord, direction);
  TilePtr tile = fov_map->at(c_dir);

  return (tile && tile->get_is_blocking());
}

bool RayCastingFieldOfViewStrategy::is_artifact_nw(MapPtr fov_map, const Coordinate& c, const PassType type)
{
  switch(type)
  {
    case PASS_NON_CORNER_BLOCKING_TILES:
      return (is_non_corner_blocking_tile(fov_map, c, DIRECTION_SOUTH, DIRECTION_EAST));
    case PASS_CORNER_BLOCKING_TILES:
      return (is_corner_blocking_tile(fov_map, c, DIRECTION_SOUTH, DIRECTION_EAST, DIRECTION_SOUTH_EAST));
    default: return false;
  }
  
  return false;
}

bool RayCastingFieldOfViewStrategy::is_artifact_ne(MapPtr fov_map, const Coordinate& c, const PassType type)
{
  switch(type)
  {
    case PASS_NON_CORNER_BLOCKING_TILES:
      return (is_non_corner_blocking_tile(fov_map, c, DIRECTION_SOUTH, DIRECTION_WEST));
    case PASS_CORNER_BLOCKING_TILES:
      return (is_corner_blocking_tile(fov_map, c, DIRECTION_SOUTH, DIRECTION_WEST, DIRECTION_SOUTH_WEST));
    default: return false;
  }
  
  return false;
}

bool RayCastingFieldOfViewStrategy::is_artifact_sw(MapPtr fov_map, const Coordinate& c, const PassType type)
{
  switch(type)
  {
    case PASS_NON_CORNER_BLOCKING_TILES:
      return (is_non_corner_blocking_tile(fov_map, c, DIRECTION_NORTH, DIRECTION_EAST));
    case PASS_CORNER_BLOCKING_TILES:
      return (is_corner_blocking_tile(fov_map, c, DIRECTION_NORTH, DIRECTION_EAST, DIRECTION_NORTH_EAST));
    default: return false;
  }
  
  return false;
}

bool RayCastingFieldOfViewStrategy::is_artifact_se(MapPtr fov_map, const Coordinate& c, const PassType type)
{
  switch(type)
  {
    case PASS_NON_CORNER_BLOCKING_TILES:
      return (is_non_corner_blocking_tile(fov_map, c, DIRECTION_NORTH, DIRECTION_WEST));
    case PASS_CORNER_BLOCKING_TILES:
      return (is_corner_blocking_tile(fov_map, c, DIRECTION_NORTH, DIRECTION_WEST, DIRECTION_NORTH_WEST));
    default: return false;
  }
  
  return false;
}

bool RayCastingFieldOfViewStrategy::is_non_corner_blocking_tile(MapPtr fov_map, const Coordinate& c, const Direction direction1, const Direction direction2)
{
  return ((does_adjacent_non_blocking_tile_exist_in_fov_map(fov_map, c, direction1)
  || (does_adjacent_non_blocking_tile_exist_in_fov_map(fov_map, c, direction2))));
}

bool RayCastingFieldOfViewStrategy::is_corner_blocking_tile(MapPtr fov_map, const Coordinate& c, const Direction blocking1, const Direction blocking2, const Direction non_blocking)
{
  return ((does_adjacent_blocking_tile_exist_in_fov_map(fov_map, c, blocking1))
       && (does_adjacent_blocking_tile_exist_in_fov_map(fov_map, c, blocking2))
       && (does_adjacent_non_blocking_tile_exist_in_fov_map(fov_map, c, non_blocking)));
}
