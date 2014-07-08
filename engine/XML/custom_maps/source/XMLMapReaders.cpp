#include <sstream>
#include "CreatureFactory.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "WorldMapLocationTextKeys.hpp"
#include "XMLMapCoordinateReader.hpp"
#include "XMLMapExitReader.hpp"
#include "XMLMapFeatureReaders.hpp"
#include "XMLMapReaders.hpp"
#include "XMLMapTilesReader.hpp"
#include "XMLDataStructures.hpp"

using namespace std;

// XMLMapReader reads in the details from a CustomMap element, and
// creates a MapPtr based on it.
MapPtr XMLMapReader::get_custom_map(const XMLNode& custom_map_node)
{
  MapPtr custom_map;
 
  if (!custom_map_node.is_null())
  {
    XMLNode dimensions_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Dimensions");
    XMLNode tiles_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Tiles");
    XMLNode player_start_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "PlayerStart");
    XMLNode initial_placements_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "InitialPlacements");
    XMLNode random_placements_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "RandomPlacements");
    XMLNode exits_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Exits");
    XMLNode features_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Features");

    string map_id = XMLUtils::get_attribute_value(custom_map_node, "id");
    MapType map_type = static_cast<MapType>(XMLUtils::get_child_node_int_value(custom_map_node, "MapType"));

    Dimensions dim = parse_dimensions(dimensions_node);

    XMLMapTilesReader tiles_reader;
    TilesContainer tiles = tiles_reader.parse_tiles(tiles_node, dim.get_y(), dim.get_x());

    // Sanity check: tiles container should have as many tiles
    // as is specified by the dimensions.
    ostringstream oss;
    uint actual = tiles.size();
    uint expected = dim.get_y() * dim.get_x();
    oss << "Incorrect number of tiles for map \"" << map_id << "\": expected " << expected << ", found " << actual << ".";
    BOOST_ASSERT_MSG(tiles.size() == (dim.get_y() * dim.get_x()), oss.str().c_str());

    XMLMapCoordinateReader coord_reader;
    Coordinate player_start_location = coord_reader.parse_fixed_coordinate(player_start_node);

    custom_map = MapPtr(new Map(dim));
    
    custom_map->set_map_id(map_id);
    custom_map->set_map_type(map_type);
    custom_map->set_tiles(tiles);
    custom_map->set_permanent(true); // custom maps are always permanent.
    custom_map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, player_start_location);

    parse_initial_placements(initial_placements_node, custom_map);
    parse_random_placements(random_placements_node, custom_map);

    XMLMapExitReader exit_reader;
    exit_reader.parse_exits(exits_node, custom_map);

    XMLMapFeaturesReader features_reader;
    features_reader.parse_features(features_node, custom_map);

    // Generate the list of creatures on the map, so that it can be accessed
    // later on.
    custom_map->create_creatures();
  }

  return custom_map;
}

string XMLMapReader::parse_id(const XMLNode& parent_node)
{
  string id;

  XMLNode id_node = XMLUtils::get_next_element_by_local_name(parent_node, "ID");
  XMLNode random_ids_node = XMLUtils::get_next_element_by_local_name(parent_node, "Random");

  if (!id_node.is_null())
  {
    id = XMLUtils::get_node_value(id_node);
  }
  else if (!random_ids_node.is_null())
  {
    vector<XMLNode> id_nodes = XMLUtils::get_elements_by_local_name(random_ids_node, "ID");
    vector<string> rand_ids;

    std::for_each(id_nodes.begin(), id_nodes.end(), [&rand_ids](const XMLNode& xn) { rand_ids.push_back(XMLUtils::get_node_value(xn)); });
    if (!rand_ids.empty())
    {
      id = rand_ids.at(RNG::range(0, rand_ids.size()-1));
    }
  }
  else
  {
    // Any additional cases should go here.
  }

  return id;
}

// Parse the rows and columns from the Dimensions element into an actual
// Dimensions engine object.
Dimensions XMLMapReader::parse_dimensions(const XMLNode& dimensions_node)
{
  Dimensions dim;

  if (!dimensions_node.is_null())
  {
    int rows = XMLUtils::get_child_node_int_value(dimensions_node, "Rows", 1);
    int cols = XMLUtils::get_child_node_int_value(dimensions_node, "Columns", 1);

    dim.set_y(rows);
    dim.set_x(cols);
  }

  return dim;
}

// Parse the initial placement of items and creatures.
void XMLMapReader::parse_initial_placements(const XMLNode& initial_placements_node, MapPtr map)
{
  if (!initial_placements_node.is_null())
  {
    XMLNode creatures_node = XMLUtils::get_next_element_by_local_name(initial_placements_node, "Creatures");
    parse_initial_creature_placements(creatures_node, map);

    XMLNode items_node = XMLUtils::get_next_element_by_local_name(initial_placements_node, "Items");
    parse_initial_item_placements(items_node, map);
  }
}

void XMLMapReader::parse_random_placements(const XMLNode& random_placements_node, MapPtr map)
{
  if (!random_placements_node.is_null())
  {
    XMLNode creatures_node = XMLUtils::get_next_element_by_local_name(random_placements_node, "Creatures");
    parse_random_creature_placements(creatures_node, map);
  }
}

// Parse the initial placement of creatures, and place them on the map at the specified location.
void XMLMapReader::parse_initial_creature_placements(const XMLNode& creatures_node, MapPtr map)
{
  if (!creatures_node.is_null())
  {
    vector<XMLNode> placement_nodes = XMLUtils::get_elements_by_local_name(creatures_node, "Placement");

    for (const XMLNode& placement_node : placement_nodes)
    {
      string id = parse_id(placement_node);

      XMLNode friendly_node = XMLUtils::get_next_element_by_local_name(placement_node, "Friendly");

      bool override_host = false;
      bool hostility = false;

      if (!friendly_node.is_null())
      {
        override_host = true;
        hostility = (XMLUtils::get_child_node_bool_value(placement_node, "Friendly", false) == false);
      }

      string name;
      XMLNode name_node = XMLUtils::get_next_element_by_local_name(placement_node, "Name");

      if (!name_node.is_null())
      {
        name = XMLUtils::get_node_value(name_node);
      }

      XMLMapCoordinateReader coord_reader;
      Coordinate coord = coord_reader.parse_coordinate(placement_node);

      // Place the specified creature on the map.
      Game& game = Game::instance();

      CreatureFactory cfactory;
      cfactory.set_hostility_for_creatures(override_host, hostility);
      CreaturePtr creature = cfactory.create_by_creature_id(game.get_action_manager_ref(), id);
      
      // Set any additional properties
      if (creature)
      {
        if (!name.empty())
        {
          creature->set_name(name);
        }
      }

      TilePtr placement_tile = map->at(coord);

      if (creature && placement_tile)
      {
        if (MapUtils::is_tile_available_for_creature(creature, placement_tile))
        {
          MapUtils::add_or_update_location(map, creature, coord);
        }
      }
    }
  }
}

// Parse the initial placement of items, and place them at the specified coordinates.
void XMLMapReader::parse_initial_item_placements(const XMLNode& items_node, MapPtr map)
{
  if (!items_node.is_null())
  {
    Game& game = Game::instance();

    vector<XMLNode> placement_nodes = XMLUtils::get_elements_by_local_name(items_node, "Placement");

    for (const XMLNode& item_node : placement_nodes)
    {
      string id = parse_id(item_node);
      int quantity = XMLUtils::get_child_node_int_value(item_node, "Quantity", 1);  

      XMLMapCoordinateReader coord_reader;
      Coordinate c = coord_reader.parse_coordinate(item_node);

      // Create the item, and set it on the specified coordinate.
      ItemPtr item = ItemManager::create_item(id);

      if (item != nullptr)
      {
        item->set_quantity(quantity);
        TilePtr tile = map->at(c);

        if (item && tile)
        {
          tile->get_items()->add(item);
        }
      }
    }
  }
}

// Parse a range <min, max> from a random placement.
pair<int, int> XMLMapReader::parse_placement_range(const XMLNode& node)
{
  pair<int, int> range(0,0);

  if (!node.is_null())
  {
    range.first = XMLUtils::get_child_node_int_value(node, "Min");
    range.second = XMLUtils::get_child_node_int_value(node, "Max");
  }

  return range;
}

// Place a certain range of random creatures on the map
void XMLMapReader::parse_random_creature_placements(const XMLNode& creatures_node, MapPtr map)
{
  if (!creatures_node.is_null() && map)
  {
    Dimensions dim = map->size();
    pair<int, int> random_range = parse_placement_range(creatures_node);

    int num_creatures = RNG::range(random_range.first, random_range.second);
    XMLNode idlist_node = XMLUtils::get_next_element_by_local_name(creatures_node, "IDList");
    vector<XMLNode> id_nodes = XMLUtils::get_elements_by_local_name(idlist_node, "ID");
    
    if (!id_nodes.empty())
    {
      for (int i = 0; i < num_creatures; i++)
      {
        string creature_id = XMLUtils::get_node_value(id_nodes.at(RNG::range(0, id_nodes.size() - 1)));
        MapUtils::place_creature_randomly(map, creature_id);
      }
    }
  }
}

