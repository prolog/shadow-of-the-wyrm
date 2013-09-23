#include "XMLTilesReader.hpp"
#include "DisplayTile.hpp"
#include "tiles.hpp"

using namespace std;

vector<DisplayTile> XMLTilesReader::get_tiles(const XMLNode& xml_configuration_tiles_node)
{
  BOOST_STATIC_ASSERT(TILE_TYPE_LAST == 43);

  vector<DisplayTile> tiles;
  tiles.reserve(TILE_TYPE_LAST);

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
    XMLNode cavern_tile_node         = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "CavernTile");
    XMLNode village_tile_node        = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "VillageTile");
    XMLNode dungeon_complex_tile_node= XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DungeonComplexTile");
    XMLNode barracks_node            = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BarracksTile");
    XMLNode castle_node              = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "CastleTile");
    XMLNode church_node              = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "ChurchTile");
    XMLNode graveyard_node           = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "GraveyardTile");
    XMLNode keep_node                = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "KeepTile");
    XMLNode library_node             = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "LibraryTile");
    XMLNode site_of_death_node       = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "SiteOfDeathTile");
    XMLNode temple_node              = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "TempleTile");
    XMLNode dais_node                = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "DaisTile");
    XMLNode pier_node                = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "PierTile");
    XMLNode barrow_node              = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "BarrowTile");
    XMLNode wild_orchard_node        = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "WildOrchardTile");
    XMLNode fruit_tree_node          = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "FruitTreeTile");
    XMLNode evergreen_tree_node      = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "EvergreenTreeTile");
    XMLNode rocky_earth_node         = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "RockyEarthTile");
    XMLNode mine_node                = XMLUtils::get_next_element_by_local_name(xml_configuration_tiles_node, "MineTile");

    // These push back items into the tile details in order, so if you're defining
    // a new tile type, add at appropriate place!
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
    parse_tile_text_details(tiles, cavern_tile_node);
    parse_tile_text_details(tiles, village_tile_node);
    parse_tile_text_details(tiles, dungeon_complex_tile_node);
    parse_tile_text_details(tiles, barracks_node);
    parse_tile_text_details(tiles, castle_node);
    parse_tile_text_details(tiles, church_node);
    parse_tile_text_details(tiles, graveyard_node);
    parse_tile_text_details(tiles, keep_node);
    parse_tile_text_details(tiles, library_node);
    parse_tile_text_details(tiles, site_of_death_node);
    parse_tile_text_details(tiles, temple_node);
    parse_tile_text_details(tiles, dais_node);
    parse_tile_text_details(tiles, pier_node);
    parse_tile_text_details(tiles, barrow_node);
    parse_tile_text_details(tiles, wild_orchard_node);
    parse_tile_text_details(tiles, fruit_tree_node);
    parse_tile_text_details(tiles, evergreen_tree_node);
    parse_tile_text_details(tiles, rocky_earth_node);
    parse_tile_text_details(tiles, mine_node);
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
