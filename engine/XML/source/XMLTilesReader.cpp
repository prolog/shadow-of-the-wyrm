#include "XMLTilesReader.hpp"
#include "DisplayTile.hpp"
#include "tiles.hpp"

using namespace std;

vector<DisplayTile> XMLTilesReader::get_tiles(const XMLNode& xml_configuration_tiles_node)
{
  static_assert(TILE_TYPE_LAST == 45, "Unexpected TILE_TYPE_LAST value.");

  vector<DisplayTile> tiles;
  vector<XMLNode> tile_nodes;
  tiles.reserve(TILE_TYPE_LAST);

  if (!xml_configuration_tiles_node.is_null())
  {
    // These push back items into the tile details in order, so if you're defining
    // a new tile type, add at appropriate place!
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "FieldTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ScrubTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "WheatTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "CairnTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "TreeTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DesertTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RoadTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RiverTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "SeaTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ShoalsTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DungeonTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RockTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "GraveTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "MarshTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ReedsTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "HillsTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "MountainsTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BeachTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BushTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "WeedsTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "SpringsTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ForestTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "UpStaircaseTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DownStaircaseTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "CavernTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "VillageTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DungeonComplexTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BarracksTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "CastleTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ChurchTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "GraveyardTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "KeepTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "LibraryTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "SiteOfDeathTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "TempleTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DaisTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "PierTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BarrowTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "WildOrchardTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "FruitTreeTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "EvergreenTreeTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RockyEarthTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "MineTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "WellTile"));
    tile_nodes.push_back(XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "CryptTile"));

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

        for (int i = SEASON_SPRING; i < SEASON_LAST; i++)
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

        tile_colours[SEASON_SPRING] = spring_colour;
        tile_colours[SEASON_SUMMER] = summer_colour;
        tile_colours[SEASON_AUTUMN] = autumn_colour;
        tile_colours[SEASON_WINTER] = winter_colour;
      }

      DisplayTile current_tile_info(symbol, tile_colours);
      tile_info.push_back(current_tile_info);
    }
  }
}
