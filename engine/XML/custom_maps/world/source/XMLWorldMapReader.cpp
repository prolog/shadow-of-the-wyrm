#include "Game.hpp"
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
    string area_id = XMLUtils::get_attribute_value(area_node, "id");

    vector<XMLNode> row_nodes = XMLUtils::get_elements_by_local_name(area_node, "Row");

    // Read in the basic tile details.
    for (const XMLNode& row_node : row_nodes)
    {
      read_row(map, row_node);
    }

    // If there is a script associated with this area, execute that script.
    string script = XMLUtils::get_child_node_value(area_node, "Script");

    if (!script.empty())
    {
      ScriptEngine& se = Game::instance().get_script_engine_ref();
      se.execute(script);
    }
  }
}

// Read in a particular row into the map.
void XMLWorldMapReader::read_row(MapPtr map, const XMLNode& row_node)
{
  Dimensions dim = map->size();
  int y = dim.get_y();
  int x = dim.get_x();

  if (!row_node.is_null())
  {
    int row = XMLUtils::get_attribute_int_value(row_node, "y");
    int col = XMLUtils::get_attribute_int_value(row_node, "x");

    string tiles = XMLUtils::get_node_value(row_node);

    // Safety checks: ensure the user hasn't done something totally awesome,
    // like specify that the current row is 208 in a map with 100 rows.
    if (row < y)
    {
      for (char ctile : tiles)
      {
        // Ditto for the specified column value.
        if (col < x)
        {
          // Convert to TilePtr
          // Insert into map
          TilePtr tile = mapper.create_tile(ctile);
          map->insert(row, col, tile);

          col++;
        }
      }
    }
  }
}