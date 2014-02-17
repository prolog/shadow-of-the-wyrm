#include <vector>
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

    // JCD FIXME: Once "exit to previous map, and use some sort of tile ID" is
    // implemented, change this so that map ID isn't necessary to create a
    // map exit.
    TilePtr tile = map->at(c);

    if (tile && !exit_map.empty())
    {
      MapExitPtr map_exit = MapExitPtr(new MapExit());
      map_exit->set_map_id(exit_map);

      TileExitMap& exits = tile->get_tile_exit_map_ref();
      exits.insert(make_pair(dir, map_exit));
    }

  }
}

