#include "MapUtils.hpp"
#include <iostream>

using namespace std;

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

