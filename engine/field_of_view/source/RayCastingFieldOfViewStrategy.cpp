#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "RayCastingFieldOfViewStrategy.hpp"
#include "BresenhamLine.hpp"

using std::vector;
using boost::make_shared;

MapPtr RayCastingFieldOfViewStrategy::calculate(MapPtr view_map, const Coordinate& centre_coord, const int los_length)
{
  MapPtr fov_map = make_shared<Map>(*view_map);
  BresenhamLine bl;
  
  int row = centre_coord.first;
  int col = centre_coord.second;
  
  // Always add the centre position to the view map - the creature always knows its own location.
  add_point_to_map(centre_coord, view_map, fov_map);

  Coordinate cur_coord;
  vector<Coordinate> line_points;
  
  // Top and bottom rows
  for (int row_cur_x = col - los_length; row_cur_x <= col + los_length; row_cur_x++)
  {
    // Top
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, row - los_length, row_cur_x);
    add_points_to_map_as_appropriate(line_points, view_map, fov_map);
    
    // Bottom
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, row + los_length, row_cur_x);
    add_points_to_map_as_appropriate(line_points, view_map, fov_map);
  }
  
  // Left and right columns
  for (int col_cur_y = row - los_length; col_cur_y <= row + los_length; col_cur_y++)
  {
    // Top
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, col_cur_y, col - los_length);
    add_points_to_map_as_appropriate(line_points, view_map, fov_map);

    // Bottom
    line_points = bl.get_points_in_line(centre_coord.first, centre_coord.second, col_cur_y, col + los_length);
    add_points_to_map_as_appropriate(line_points, view_map, fov_map);
  }
  
  post_process_to_remove_artifacts(view_map, fov_map);
  
  return fov_map;
}

void RayCastingFieldOfViewStrategy::add_points_to_map_as_appropriate(const std::vector<Coordinate>& coords, MapPtr view_map, MapPtr fov_map)
{
  BOOST_FOREACH(Coordinate c, coords)
  {
    TilePtr tile = view_map->at(c);
    
    if (!tile)
    {
      return;
    }
    else
    {
      add_point_to_map(c, view_map, fov_map);

      if (tile->get_is_blocking())
      {
        return;
      }
    }
  }
}

void RayCastingFieldOfViewStrategy::post_process_to_remove_artifacts(MapPtr view_map, MapPtr fov_map)
{
  
}
