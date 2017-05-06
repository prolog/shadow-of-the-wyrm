#include <vector>
#include "MapExitProperties.hpp"
#include "MapExitUtils.hpp"
#include "XMLMapCoordinateReader.hpp"
#include "XMLMapExitReader.hpp"

using namespace std;

// Parse the list of exits on the map
void XMLMapExitReader::parse_exits(const XMLNode& exits_node, MapPtr map)
{
  if (!exits_node.is_null())
  {
    vector<XMLNode> exit_nodes = XMLUtils::get_elements_by_local_name(exits_node, "Exit");

    for (const XMLNode& node : exit_nodes)
    {
      parse_exit(node, map);
    }
  }
}

// Parse an individual exit, setting the exit information for a particular
// direction on to the appropriate tile.
void XMLMapExitReader::parse_exit(const XMLNode& exit_node, MapPtr map)
{
  if (!exit_node.is_null())
  {
    XMLNode coord_node = XMLUtils::get_next_element_by_local_name(exit_node, "Coord");
    
    XMLMapCoordinateReader coord_reader;
    Coordinate c = coord_reader.parse_fixed_coordinate(coord_node);
    Direction dir = static_cast<Direction>(XMLUtils::get_child_node_int_value(exit_node, "Direction"));
    string exit_map = XMLUtils::get_child_node_value(exit_node, "MapID");
    
    MapExitPtr map_exit = MapExitPtr(new MapExit());

    parse_depth_details(exit_node, map_exit);

    // Handle a set map exist (to another custom map)
    if (!exit_map.empty())
    {
      MapExitUtils::add_exit_to_tile(map, c, dir, exit_map);
    }
    // Handle map exits using tile types/subtypes (terrain generation)
    else
    {        
      TileType tt = TileType::TILE_TYPE_UNDEFINED;
      tt = static_cast<TileType>(XMLUtils::get_child_node_int_value(exit_node, "TileType", static_cast<int>(tt)));

      MapExitUtils::add_exit_to_tile(map, c, dir, tt);
    }
  }
}

void XMLMapExitReader::parse_depth_details(const XMLNode& exit_node, MapExitPtr map_exit)
{
  if (map_exit != nullptr)
  {
    XMLNode depth_node = XMLUtils::get_next_element_by_local_name(exit_node, "Depth");
    if (!depth_node.is_null())
    {
      int depth = XMLUtils::get_node_int_value(depth_node, -1);
      map_exit->set_property(MapExitProperties::MAP_EXIT_PROPERTIES_DEPTH, to_string(depth));
    }

    XMLNode max_depth_node = XMLUtils::get_next_element_by_local_name(exit_node, "MaxDepth");
    if (!max_depth_node.is_null())
    {
      int max_depth = XMLUtils::get_node_int_value(max_depth_node, -1);
      map_exit->set_property(MapExitProperties::MAP_EXIT_PROPERTIES_MAX_DEPTH, to_string(max_depth));
    }

    XMLNode increment_node = XMLUtils::get_next_element_by_local_name(exit_node, "Increment");
    if (!increment_node.is_null())
    {
      int increment = XMLUtils::get_node_int_value(increment_node, 1);
      map_exit->set_property(MapExitProperties::MAP_EXIT_PROPERTIES_INCREMENT, to_string(increment));
    }
  }
}
