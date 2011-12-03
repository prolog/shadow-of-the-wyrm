#include "XMLTilesReader.hpp"
#include "DisplayTile.hpp"

using namespace std;

vector<DisplayTile> XMLTilesReader::get_tiles(const XMLNode& xml_configuration_tiles_node)
{
  vector<DisplayTile> tiles;

  if (!xml_configuration_tiles_node.is_null())
  {
    XMLNode field_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "FieldTile");
    XMLNode scrub_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ScrubTile");
    XMLNode wheat_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "WheatTile");
    XMLNode cairn_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "CairnTile");
    XMLNode tree_tile_node           = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "TreeTile");
    XMLNode desert_tile_node         = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DesertTile");
    XMLNode road_tile_node           = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RoadTile");
    XMLNode river_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RiverTile");
    XMLNode sea_tile_node            = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "SeaTile");
    XMLNode shoals_tile_node         = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ShoalsTile");
    XMLNode dungeon_tile_node        = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DungeonTile");
    XMLNode rock_tile_node           = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RockTile");
    XMLNode grave_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "GraveTile");
    XMLNode marsh_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "MarshTile");
    XMLNode reeds_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ReedsTile");
    XMLNode hills_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "HillsTile");
    XMLNode mountains_tile_node      = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "MountainsTile");
    XMLNode beach_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BeachTile");
    XMLNode bush_tile_node           = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BushTile");
    XMLNode weeds_tile_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "WeedsTile");
    XMLNode springs_tile_node        = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "SpringsTile");
    XMLNode forest_tile_node         = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ForestTile");
    XMLNode up_staircase_tile_node   = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "UpStaircaseTile");
    XMLNode down_staircase_tile_node = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DownStaircaseTile");

    parse_tile_text_details(tiles, field_tile_node);
    parse_tile_text_details(tiles, scrub_tile_node);
    parse_tile_text_details(tiles, wheat_tile_node);
    parse_tile_text_details(tiles, cairn_tile_node);
    parse_tile_text_details(tiles, tree_tile_node);
    parse_tile_text_details(tiles, desert_tile_node);
    parse_tile_text_details(tiles, road_tile_node);
    parse_tile_text_details(tiles, river_tile_node);
    parse_tile_text_details(tiles, sea_tile_node);
    parse_tile_text_details(tiles, shoals_tile_node);
    parse_tile_text_details(tiles, dungeon_tile_node);
    parse_tile_text_details(tiles, rock_tile_node);
    parse_tile_text_details(tiles, grave_tile_node);
    parse_tile_text_details(tiles, marsh_tile_node);
    parse_tile_text_details(tiles, reeds_tile_node);
    parse_tile_text_details(tiles, hills_tile_node);
    parse_tile_text_details(tiles, mountains_tile_node);
    parse_tile_text_details(tiles, beach_tile_node);
    parse_tile_text_details(tiles, bush_tile_node);
    parse_tile_text_details(tiles, weeds_tile_node);
    parse_tile_text_details(tiles, springs_tile_node);
    parse_tile_text_details(tiles, forest_tile_node);
    parse_tile_text_details(tiles, up_staircase_tile_node);
    parse_tile_text_details(tiles, down_staircase_tile_node);
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
      UChar symbol = '?';

      if (!symbol_s.empty())
      {
        // Well, it is a UChar!
        symbol = symbol_s.at(0);
      }

      int colour = XMLUtils::get_child_node_int_value(text_node, "Colour", 0);

      DisplayTile current_tile_info(symbol, colour);
      tile_info.push_back(current_tile_info);
    }
  }
}
