#include <vector>
#include "CoordUtils.hpp"
#include "DirectionUtils.hpp"
#include "MapExitUtils.hpp"
#include "MapProperties.hpp"
#include "MapTypes.hpp"
#include "TileProperties.hpp"
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
  if (!exit_node.is_null() && map != nullptr)
  {
    XMLNode coord_node = XMLUtils::get_next_element_by_local_name(exit_node, "Coord");
    string map_id = map->get_map_id();
    EventScriptsMap scripts;
    Coordinate c = {-1, -1};

    if (!coord_node.is_null())
    {
      XMLMapCoordinateReader coord_reader;
      c = coord_reader.parse_fixed_coordinate(coord_node);
    }

    Direction dir = static_cast<Direction>(XMLUtils::get_child_node_int_value(exit_node, "Direction"));
    string exit_map = XMLUtils::get_child_node_value(exit_node, "MapID");
    
    MapExitPtr map_exit = MapExitPtr(new MapExit());
    XMLNode event_scripts_node = XMLUtils::get_next_element_by_local_name(exit_node, "EventScripts");
    std::map<string, string> node_details = {{"CreateScript", MapEventScripts::MAP_EVENT_SCRIPT_CREATE}};
    parse_depth_details(exit_node, map_exit);
    parse_event_scripts(event_scripts_node, node_details, scripts);
    
    // If the coordinate is the end coord, this is a map-based exit, used for
    // multi-maps like Carcassia.
    if (CoordUtils::is_end(c))
    {
      // JCD FIXME Improve this if I ever need to do "terrain generated off
      // the edge of a custom map".
      map_exit->set_map_id(exit_map);
      map->set_map_exit(dir, map_exit);
    }
    // Handle a set map exit (to another custom map)
    else if (!exit_map.empty())
    {
      map_exit = MapExitUtils::add_exit_to_tile(map, c, dir, exit_map);
    }
    // Handle map exits using tile types/subtypes (terrain generation)
    else
    {        
      TileType tt = TileType::TILE_TYPE_UNDEFINED;
      tt = static_cast<TileType>(XMLUtils::get_child_node_int_value(exit_node, "TileType", static_cast<int>(tt)));
      map_exit->set_terrain_type(tt);
      map_exit->set_property(TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID, map_id);

      MapExitUtils::add_exit_to_tile(map, c, dir, map_exit);
    }

    map_exit->set_event_scripts(scripts);
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
      map_exit->set_property(MapProperties::MAP_PROPERTIES_DEPTH, to_string(depth));
    }

    XMLNode min_depth_node = XMLUtils::get_next_element_by_local_name(exit_node, "MinDepth");
    if (!min_depth_node.is_null())
    {
      int min_depth = XMLUtils::get_node_int_value(min_depth_node, -1);
      map_exit->set_property(MapProperties::MAP_PROPERTIES_MIN_DEPTH, to_string(min_depth));
    }

    XMLNode max_depth_node = XMLUtils::get_next_element_by_local_name(exit_node, "MaxDepth");
    if (!max_depth_node.is_null())
    {
      int max_depth = XMLUtils::get_node_int_value(max_depth_node, -1);
      map_exit->set_property(MapProperties::MAP_PROPERTIES_MAX_DEPTH, to_string(max_depth));
    }

    XMLNode increment_node = XMLUtils::get_next_element_by_local_name(exit_node, "Increment");
    if (!increment_node.is_null())
    {
      int increment = XMLUtils::get_node_int_value(increment_node, 1);
      map_exit->set_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT, to_string(increment));
    }
  }
}
