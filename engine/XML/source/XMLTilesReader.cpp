#include <boost/assert.hpp>
#include "XMLTilesReader.hpp"
#include "DisplayTile.hpp"
#include "tiles.hpp"

using namespace std;

vector<DisplayTile> XMLTilesReader::get_tiles(const XMLNode& xml_configuration_tiles_node)
{
  static_assert(TileType::TILE_TYPE_LAST == static_cast<TileType>(53), "Unexpected TileType::TILE_TYPE_LAST value.");

  vector<DisplayTile> tiles;
  vector<string> tile_names = {"FieldTile", "ScrubTile", "WheatTile", "CairnTile", "TreeTile", "DesertTile", "RoadTile",
                               "RiverTile", "SeaTile", "ShoalsTile", "DungeonTile", "RockTile", "GraveTile", "MarshTile",
                               "ReedsTile", "HillsTile", "MountainsTile", "BeachTile", "BushTile", "WeedsTile", "SpringsTile",
                               "ForestTile", "UpStaircaseTile", "DownStaircaseTile", "CavernTile", "VillageTile", "DungeonComplexTile",
                               "BarracksTile", "CastleTile", "ChurchTile", "GraveyardTile", "KeepTile", "LibraryTile", "SiteOfDeathTile",
                               "TempleTile", "DaisTile", "PierTile", "BarrowTile", "WildOrchardTile", "FruitTreeTile", "EvergreenTreeTile",
                               "RockyEarthTile", "MineTile", "WellTile", "CryptTile", "AirTile", "EarthTile", "SewerComplexTile",
                               "SewerTile", "ShrineTile", "SeabedTile", "AquaticVegetationTile", "FloatingTowerTile"};
  
  vector<XMLNode> tile_nodes;
  tiles.reserve(static_cast<int>(TileType::TILE_TYPE_LAST));

  if (!xml_configuration_tiles_node.is_null())
  {
    // These push back items into the tile details in order, so if you're defining
    // a new tile type, add at appropriate place in the vector above!
    for (const string& tile_n : tile_names)
    {
      tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, tile_n));
    }

    BOOST_ASSERT(tile_nodes.size() == XMLUtils::get_child_nodes(xml_configuration_tiles_node).size());

    for (const auto& xml_tile : tile_nodes)
    {
      parse_tile_text_details(tiles, xml_tile);
    }
  }

  return tiles;
}

// Takes in the "Text" node of a particular tile, as well as a shared pointer to some
// data structure I haven't defined, yet.
void XMLTilesReader::parse_tile_text_details(vector<DisplayTile>& tile_info, const XMLNode& tile_node)
{
  if (!tile_node.is_null())
  {
    XMLNode text_node = XMLUtils::get_next_element_by_local_name(tile_node, "Text");

    if (!text_node.is_null())
    {
      string symbol_s = XMLUtils::get_child_node_value(text_node, "Symbol");
      uchar symbol = '?';

      if (!symbol_s.empty())
      {
        // Well, it is a uchar!
        symbol = symbol_s.at(0);
      }

      SeasonTileColourMap tile_colours;

      // May be null, if seasonal colours are provided for the tile type.
      XMLNode colour_node = XMLUtils::get_next_element_by_local_name(text_node, "Colour");

      if (!colour_node.is_null())
      {
        int colour = XMLUtils::get_node_int_value(colour_node, 0);

        for (int i = static_cast<int>(Season::SEASON_SPRING); i < static_cast<int>(Season::SEASON_LAST); i++)
        {
          Season season = static_cast<Season>(i);
          tile_colours[season] = colour;
        }
      }

      XMLNode colours_node = XMLUtils::get_next_element_by_local_name(text_node, "Colours");

      if (!colours_node.is_null())
      {
        tile_colours.clear();

        int spring_colour = XMLUtils::get_child_node_int_value(colours_node, "Spring");
        int summer_colour = XMLUtils::get_child_node_int_value(colours_node, "Summer");
        int autumn_colour = XMLUtils::get_child_node_int_value(colours_node, "Autumn");
        int winter_colour = XMLUtils::get_child_node_int_value(colours_node, "Winter");

        tile_colours[Season::SEASON_SPRING] = spring_colour;
        tile_colours[Season::SEASON_SUMMER] = summer_colour;
        tile_colours[Season::SEASON_AUTUMN] = autumn_colour;
        tile_colours[Season::SEASON_WINTER] = winter_colour;
      }

      DisplayTile current_tile_info(symbol, tile_colours);
      tile_info.push_back(current_tile_info);
    }
  }
}
