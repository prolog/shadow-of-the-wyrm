#include <sstream>
#include "CreatureFactory.hpp"
#include "EngineConversion.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "ItemManager.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "WorldMapLocationTextKeys.hpp"
#include "XMLMapCoordinateReader.hpp"
#include "XMLMapExitReader.hpp"
#include "XMLMapFeatureReaders.hpp"
#include "XMLMapReaders.hpp"
#include "XMLMapTilesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"

using namespace std;

// XMLMapReader reads in the details from a CustomMap element, and
// creates a MapPtr based on it.
MapPtr XMLMapReader::get_custom_map(const XMLNode& custom_map_node)
{
  MapPtr custom_map;
 
  if (!custom_map_node.is_null())
  {
    XMLNode dimensions_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Dimensions");
    XMLNode level_range_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "LevelRange");
    XMLNode tiles_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Tiles");
    XMLNode player_start_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "PlayerStart");
    XMLNode initial_placements_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "InitialPlacements");
    XMLNode random_placements_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "RandomPlacements");
    XMLNode exits_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Exits");
    XMLNode features_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Features");
    XMLNode properties_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Properties");
    XMLNode shops_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "Shops");
    XMLNode event_scripts_node = XMLUtils::get_next_element_by_local_name(custom_map_node, "EventScripts");
    std::map<string, string> node_details = {{"CreateScript", MapEventScripts::MAP_EVENT_SCRIPT_CREATE}};

    string map_id = XMLUtils::get_attribute_value(custom_map_node, "id");
    MapType map_type = static_cast<MapType>(XMLUtils::get_child_node_int_value(custom_map_node, "MapType"));
    string name_sid = XMLUtils::get_child_node_value(custom_map_node, "NameSID");
    string default_race_id = XMLUtils::get_child_node_value(custom_map_node, "DefaultRaceID");
    
    Dimensions dim = parse_dimensions(dimensions_node);
    custom_map = MapPtr(new Map(dim));

    // Terrain type is set for "normal" maps based on the overworld tile type.
    // Ensure that it's set so that the player can't do sneaky stuff like
    // retreat to a custom map to read-ID scrolls to avoid summoning.
    custom_map->set_terrain_type(MapTileTypes::map_type_to_default_tile_type(map_type));

    // Ensure that the map type is set prior to parsing the tiles so that if
    // the map is submerged, the flag will be set appropriately on each tile.
    custom_map->set_map_type(map_type);

    XMLMapTilesReader tiles_reader;
    TilesContainer tiles = tiles_reader.parse_tiles(tiles_node, dim.get_y(), dim.get_x());

    // Sanity check: tiles container should have as many tiles
    // as is specified by the dimensions.
    ostringstream oss;
    uint actual = tiles.size();
    uint expected = dim.get_y() * dim.get_x();
    oss << "Incorrect number of tiles for map \"" << map_id << "\": expected " << expected << ", found " << actual << ".";
    BOOST_ASSERT_MSG(tiles.size() == static_cast<size_t>((dim.get_y() * dim.get_x())), oss.str().c_str());

    XMLMapCoordinateReader coord_reader;
    Coordinate player_start_location = coord_reader.parse_fixed_coordinate(player_start_node);
    
    custom_map->set_map_id(map_id);
    custom_map->set_name_sid(name_sid);
    custom_map->set_default_race_id(default_race_id);
    custom_map->set_tiles(tiles);
    custom_map->set_permanent(true); // custom maps are always permanent.
    custom_map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, player_start_location);

    parse_initial_placements(initial_placements_node, custom_map);
    parse_random_placements(random_placements_node, custom_map);

    XMLMapExitReader exit_reader;
    exit_reader.parse_exits(exits_node, custom_map);

    XMLMapFeaturesReader features_reader;
    features_reader.parse_features(features_node, custom_map);

    parse_shops(shops_node, custom_map);
    parse_properties(properties_node, custom_map);
    parse_event_scripts(event_scripts_node, node_details, custom_map->get_event_scripts_ref());

    // Custom maps currently don't allow creature updates.
    custom_map->set_allow_creature_updates(false);

    // Generate the list of creatures on the map, so that it can be accessed
    // later on.
    custom_map->create_creatures();

    int danger_level = 1;
    if (!level_range_node.is_null())
    {
      danger_level = XMLUtils::get_child_node_int_value(level_range_node, "Max");
    }

    custom_map->set_danger(danger_level);
  }

  return custom_map;
}

void XMLMapReader::parse_properties(const XMLNode& properties_node, MapPtr map)
{
  if (!properties_node.is_null() && map != nullptr)
  {
    XMLReader xr;

    std::map<string, string> properties;
    xr.parse_properties(properties, properties_node);

    map->set_properties(properties);
  }
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

      CreatureFactory cf;
      cf.set_hostility_for_creatures(override_host, hostility);
      CreaturePtr creature = cf.create_by_creature_id(game.get_action_manager_ref(), id);
      
      // Set any additional properties
      if (creature != nullptr)
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
      else
      {
        log_placement_error(map, id);
      }
    }
  }
}

// Parse the initial placement of items, and place them at the specified coordinates.
void XMLMapReader::parse_initial_item_placements(const XMLNode& items_node, MapPtr map)
{
  if (!items_node.is_null())
  {
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
      else
      {
        log_placement_error(map, id);
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

void XMLMapReader::parse_shops(const XMLNode& shops_node, MapPtr map)
{
  if (!shops_node.is_null())
  {
    vector<XMLNode> shop_nodes = XMLUtils::get_elements_by_local_name(shops_node, "Shop");
    XMLMapCoordinateReader coord_reader;
    std::map<string, Shop> shops;

    for (const XMLNode& shop_node : shop_nodes)
    {
      Shop shop;

      string shop_id = XMLUtils::get_attribute_value(shop_node, "id");
      shop.set_shop_id(shop_id);

      string shopkeeper_id = XMLUtils::get_child_node_value(shop_node, "ShopkeeperID");
      shop.set_shopkeeper_id(shopkeeper_id);

      XMLNode start_coord_node = XMLUtils::get_next_element_by_local_name(shop_node, "StartCoord");
      XMLNode end_coord_node = XMLUtils::get_next_element_by_local_name(shop_node, "EndCoord");

      Coordinate start_coord = coord_reader.parse_fixed_coordinate(start_coord_node);
      shop.set_start(start_coord);

      Coordinate end_coord = coord_reader.parse_fixed_coordinate(end_coord_node);
      shop.set_end(end_coord);

      XMLNode item_types_node = XMLUtils::get_next_element_by_local_name(shop_node, "StockedItemTypes");
      vector<ItemType> stocked_item_types;

      if (!item_types_node.is_null())
      {
        vector<XMLNode> itype_nodes = XMLUtils::get_elements_by_local_name(item_types_node, "ItemType");

        for (const XMLNode& itype_node : itype_nodes)
        {
          ItemType itype = static_cast<ItemType>(XMLUtils::get_node_int_value(itype_node));
          stocked_item_types.push_back(itype);
        }
      }

      shop.set_stocked_item_types(stocked_item_types);

      shops[shop_id] = shop;
    }

    map->set_shops(shops);
  }
}

void XMLMapReader::log_placement_error(MapPtr map, const string& bad_id)
{
  ostringstream ss;
  ss << "Could not set creature or item with id " << bad_id << " on map ID ";

  if (map != nullptr)
  {
    ss << map->get_map_id();
  }
  else
  {
    ss << "(null)";
  }

  Log::instance().error(ss.str());
}