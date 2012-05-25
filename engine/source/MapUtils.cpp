#include "Conversion.hpp"
#include "MapUtils.hpp"


#include <iostream>
using namespace std;

// Check to see if movement in a given direction is valid.
bool MapUtils::is_valid_move(const Dimensions& dim, const Coordinate& c, const Direction d)
{
  bool valid_move = true;

  int max_row = dim.get_y();
  int max_col = dim.get_x();

  Coordinate new_coord = get_new_coordinate(c, d);
  int new_row = new_coord.first;
  int new_col = new_coord.second;

  if (new_row < 0 || new_row >= max_row || new_col < 0 || new_col >= max_col)
  {
    valid_move = false;
  }

  return valid_move;
}

// Get the direction given start/end coordinates.
Direction MapUtils::get_direction(const Coordinate& start, const Coordinate& end)
{
  Direction d;
  
  int y1 = start.first;
  int x1 = start.second;
  
  int y2 = end.first;
  int x2 = end.second;
  
  // Start greater than end - heading north
  if (y1 > y2)
  {
    if (x1 < x2)
    {
      d = DIRECTION_NORTH_EAST;
    }
    else if (x1 == x2)
    {
      d = DIRECTION_NORTH;
    }
    else
    {
      d = DIRECTION_NORTH_WEST;
    }
  }
  // Start row = end row - heading east or west
  else if (y1 == y2)
  {
    if (x1 < x2)
    {
      d = DIRECTION_EAST;
    }
    {
      d = DIRECTION_WEST;
    }
  }
  // Start row > end row - heading north
  else
  {
    if (x1 < x2)
    {
      d = DIRECTION_SOUTH_EAST;
    }
    else if (x1 == x2)
    {
      d = DIRECTION_SOUTH;
    }
    else
    {
      d = DIRECTION_SOUTH_WEST;
    }
  }
  
  return d;
}

// Generate the next coordinate in a given direction.  Does not do correctness checking!
Coordinate MapUtils::get_new_coordinate(const Coordinate& c, const Direction d)
{
  Coordinate new_coord = c;

  switch(d)
  {
    case DIRECTION_SOUTH_WEST:
      new_coord.first++;
      new_coord.second--;
      break;
    case DIRECTION_SOUTH:
      new_coord.first++;
      break;
    case DIRECTION_SOUTH_EAST:
      new_coord.first++;
      new_coord.second++;
      break;
    case DIRECTION_WEST:
      new_coord.second--;
      break;
    case DIRECTION_EAST:
      new_coord.second++;
      break;
    case DIRECTION_NORTH_WEST:
      new_coord.first--;
      new_coord.second--;
      break;
    case DIRECTION_NORTH:
      new_coord.first--;
      break;
    case DIRECTION_NORTH_EAST:
      new_coord.first--;
      new_coord.second++;
      break;
    case DIRECTION_UP:
    case DIRECTION_DOWN:
    default:
      break;
  }

  return new_coord;
}

// Get the distance between two tiles using Chebyshev distance
int MapUtils::tile_distance_using_chebyshev(Coordinate c1, Coordinate c2)
{
  return max(abs(c1.second - c2.second), abs(c1.first - c2.first));
}

// Check to see if a tile is available for a creature by checking:
// - if a creature is present
// - if a blocking feature is present
// - if the tile type permits movement
bool MapUtils::is_tile_available_for_creature(TilePtr tile)
{
  return (!is_creature_present(tile) && !is_blocking_feature_present(tile) && tile_type_permits_creature_or_object(tile->get_tile_type()));
}

// Check to see if the tile is available for creature or object generation
bool MapUtils::tile_type_permits_creature_or_object(const TileType tile_type)
{
  // There may be other impassable types in future, but for now, just _ROCK.
  if (tile_type == TILE_TYPE_ROCK)
  {
    return false;
  }
  
  return true;
}

// Get the dimensions for a new map based on the current map, the coords, and the size.
// If it's a large map and the coordinates are in the centre, the dimensions will likely
// be size x size.  In other cases, the dimensions will be smaller, particularly if the
// coordinates fall near the map's borders.
Dimensions MapUtils::get_dimensions(MapPtr map, const Coordinate& coords, const int size)
{
  Dimensions new_dimensions(0, 0);
  
  Dimensions original_dimensions = map->size();
  int rows_orig = original_dimensions.get_y();
  int cols_orig = original_dimensions.get_x();
  
  int coord_row = coords.first;
  int coord_col = coords.second;
  
  int num_rows = 0;
  int num_cols = 0;
  
  for(int row = (coord_row - size); row <= (coord_row + size); row++)
  {
    if ((row >= 0) && (row <= rows_orig - 1))
    {
      if (num_cols == 0)
      {
        for (int col = (coord_col - size); col <= (coord_col + size); col++)
        {
          if ((col >= 0) && (col <= cols_orig - 1))
          {
            num_cols++;
          }
        }
      }
      
      num_rows++;
    }
  }

  new_dimensions.set_y(num_rows);
  new_dimensions.set_x(num_cols);
  
  return new_dimensions;
}

// Check for adjacency - distance must be 1 using the Chessboard distance (Chebyshev).
bool MapUtils::are_coordinates_adjacent(const Coordinate& c1, const Coordinate& c2)
{
  return (tile_distance_using_chebyshev(c1, c2) == 1);
}

// Add the tile and its connected tiles to the Component.
void MapUtils::add_connected_tiles_to_component(MapPtr map, const Coordinate& coord, const Dimensions& dim, const set<TileType>& exclusion_tiles, Component* component)
{
  int row = coord.first;
  int col = coord.second;

  TilePtr tile2 = map->at(row, col);
  if (exclusion_tiles.find(tile2->get_tile_type()) == exclusion_tiles.end())
  {
    component->insert(coord);

    vector<Coordinate> adjacent_coordinates = get_adjacent_map_coordinates(dim, row, col);

    for (vector<Coordinate>::const_iterator c_it = adjacent_coordinates.begin(); c_it != adjacent_coordinates.end(); c_it++)
    {
      Coordinate adjacent_coord = *c_it;

      // If the adjacent coordinate is not in the component, add it.
      if (component->find(adjacent_coord) == component->end())
      {
        TilePtr tile = map->at(row, col);

        if (exclusion_tiles.find(tile->get_tile_type()) == exclusion_tiles.end())
        {
          add_connected_tiles_to_component(map, adjacent_coord, dim, exclusion_tiles, component);
        }
      }
    }
  }
}

// Get the coordinates adjacent to a given set within the current dimensions
vector<Coordinate> MapUtils::get_adjacent_map_coordinates(const Dimensions& dim, const int row, const int col)
{
  vector<Coordinate> adjacent_coordinates;

  int max_rows = dim.get_y();
  int max_cols = dim.get_x();

  for (int cur_row = row - 1; cur_row <= row+1; cur_row++)
  {
    for (int cur_col = col - 1; cur_col <= col+1; cur_col++)
    {
      // Check bounds
      if (cur_row >= 0 && cur_row < max_rows && cur_col >= 0 && cur_col < max_cols)
      {
        // Neighbours can't include the current tile
        if (cur_row != row || cur_col != col)
        {
          adjacent_coordinates.push_back(make_pair(cur_row, cur_col));
        }
      }
    }
  }

  return adjacent_coordinates;
}

// Generate a list of map components.
// FIXME: Unit tests
MapComponents MapUtils::get_map_components(MapPtr map, const set<TileType>& exclusion_tiles)
{
  MapComponents result;

  set<TileType>::const_iterator c_it;
  Dimensions dimensions = map->size();
  int height = dimensions.get_y();
  int width = dimensions.get_x();

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      Coordinate current_tile_pair = make_pair(y, x);
      TilePtr current_tile = map->at(y, x);

      // Is it a rock tile?  If so, ignore, and check in
      // existing sets.
      c_it = exclusion_tiles.find(current_tile->get_tile_type());
      if (c_it == exclusion_tiles.end())
      {
        if (!is_tile_contained_in_an_existing_component(current_tile_pair, result))
        {
          Component component;
          add_connected_tiles_to_component(map, current_tile_pair, dimensions, exclusion_tiles, &component);

          result.push_back(component);
        }
      }
    }
  }
  return result;
}

bool MapUtils::add_or_update_location(MapPtr map, CreaturePtr creature, const Coordinate& c, TilePtr creatures_old_tile)
{
  bool added_location = true;

  TilePtr creatures_new_tile = map->at(c);
  
  if (creature->get_is_player())
  {
    map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
  }

  map->add_or_update_location(creature->get_id(), c);
  
  // Did the creature belong to a previous tile?  Can we move it to the new tile?  If so, then
  // remove from the old tile, and add to the new.
  if (creatures_new_tile && !creatures_new_tile->has_creature())
  {
    if (creatures_old_tile)
    {
      creatures_old_tile->remove_creature();      
    }
    
    creatures_new_tile->set_creature(creature);
  }
  
  return added_location;
}

TilePtr MapUtils::get_tile_for_creature(const MapPtr& map, const CreaturePtr& creature)
{
  string creature_id = creature->get_id();
  Coordinate creature_location = map->get_location(creature_id);
  TilePtr creatures_tile = map->at(creature_location.first, creature_location.second);
  
  return creatures_tile;
}

bool MapUtils::can_exit_map(MapExitPtr map_exit)
{
  bool can_exit;
  
  if (map_exit && (map_exit->is_using_map_id() || map_exit->is_using_terrain_type()))
  {
    can_exit = true;
  }
  
  return can_exit;
}

// Is there a feature on the tile, and does it block movement?
bool MapUtils::is_blocking_feature_present(TilePtr tile)
{
  if (tile)
  {
    FeaturePtr feature = tile->get_feature();
    
    if (feature)
    {
      return feature->get_blocking();
    }
  }
  
  return false;
}

// Is there a creature on the tile?
bool MapUtils::is_creature_present(TilePtr tile)
{
  if (tile)
  {
    CreaturePtr creature = tile->get_creature();
    
    return (creature);
  }
  
  return false;
}

// Iterate through the existing components of the map, searching each one to see if the coordinates are contained within
// any one of them.
bool MapUtils::is_tile_contained_in_an_existing_component(const Coordinate& coord, const MapComponents& components)
{
  bool result = false;
  for (MapComponentsItc m_it = components.begin(); m_it != components.end(); m_it++)
  {
    Component component = *m_it;
    ComponentItc c_it = component.find(coord);

    if (c_it != component.end())
    {
      return true;
    }
  }

  return result;
}

#ifdef UNIT_TESTS
#include "unit_tests/Map_test.cpp"
#include "unit_tests/MapUtils_test.cpp"
#endif
