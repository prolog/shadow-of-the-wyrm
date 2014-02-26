#include "XMLWorldMapReader.hpp"

using namespace std;

// Read in the custom areas of the world map, setting them into a
// passed-in, already-mostly-initialized map pointer.
void XMLWorldMapReader::read_world_map(MapPtr map, const XMLNode& world_map_node)
{
  if (!world_map_node.is_null())
  {
    XMLNode areas_node = XMLUtils::get_next_element_by_local_name(world_map_node, "Areas");

    read_areas(map, areas_node);
  }
}

// Read in the areas of the world map.
void XMLWorldMapReader::read_areas(MapPtr map, const XMLNode& areas_node)
{
  if (!areas_node.is_null())
  {
    vector<XMLNode> area_nodes = XMLUtils::get_elements_by_local_name(areas_node, "Area");

    for (const XMLNode& area_node : area_nodes)
    {
      read_area(map, area_node);
    }
  }
}

// Read in a particular area.
void XMLWorldMapReader::read_area(MapPtr map, const XMLNode& area_node)
{
  if (!area_node.is_null())
  {
    vector<XMLNode> row_nodes = XMLUtils::get_elements_by_local_name(area_node, "Row");

    for (const XMLNode& row_node : row_nodes)
    {
      read_row(map, row_node);
    }

    string script = XMLUtils::get_child_node_value(area_node, "Script");

    // Run the script:
    // ...
  }
}

// Read in a particular row into the map.
void XMLWorldMapReader::read_row(MapPtr map, const XMLNode& row_node)
{
  if (!row_node.is_null())
  {
    int row = XMLUtils::get_attribute_int_value(row_node, "y");
    int col = XMLUtils::get_attribute_int_value(row_node, "x");

    string tiles = XMLUtils::get_node_value(row_node);

    for (char ctile : tiles)
    {
      // Convert to TilePtr
      // Insert into map
      TilePtr tile = mapper.create_tile(ctile);
      map->insert(row, col, tile);

      col++;
    }
  }
}