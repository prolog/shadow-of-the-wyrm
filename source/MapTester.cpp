#ifndef MAP_TESTER
#define MAP_TESTER 1
#endif

// MSXML is a POS and doesn't play nice with Xerces.
#ifndef __MSXML_LIBRARY_DEFINED__
#define __MSXML_LIBRARY_DEFINED__
#endif

#include <iostream>
#include <fstream>
#include <memory>
#include "global_prototypes.hpp"
#include "BresenhamLine.hpp"
#include "Display.hpp"
#include "Random.hpp"
#include "RNG.hpp"
#include "Calendar.hpp"
#include "Date.hpp"
#include "CastleGenerator.hpp"
#include "CathedralGenerator.hpp"
#include "CavernGenerator.hpp"
#include "CreatureGenerationManager.hpp"
#include "CryptGenerator.hpp"
#include "DesertGenerator.hpp"
#include "DungeonGenerator.hpp"
#include "FieldGenerator.hpp"
#include "FileConstants.hpp"
#include "FloatingTowerGenerator.hpp"
#include "ForestGenerator.hpp"
#include "FortifiedChurchGenerator.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "GrandTempleGenerator.hpp"
#include "GraveyardGeneratorFactory.hpp"
#include "HillsGenerator.hpp"
#include "IslandSacrificeSiteGenerator.hpp"
#include "ItemGenerationManager.hpp"
#include "RockySacrificeSiteGenerator.hpp"
#include "OvergrownSacrificeSiteGenerator.hpp"
#include "RoadGenerator.hpp"
#include "RuinsGenerator.hpp"
#include "MarshGenerator.hpp"
#include "MineGenerator.hpp"
#include "ScrubGenerator.hpp"
#include "SeaGenerator.hpp"
#include "SettlementGenerator.hpp"
#include "HamletGenerator.hpp"
#include "WalledSettlementGenerator.hpp"
#include "ScatteredSettlementGenerator.hpp"
#include "SewerGenerator.hpp"
#include "SimpleChurchGenerator.hpp"
#include "KeepRuinsGenerator.hpp"
#include "MapTranslator.hpp"
#include "Naming.hpp"
#include "ShadowOfTheWyrmEngine.hpp"
#include "SettlementRuinsGenerator.hpp"
#include "ShrineGeneratorFactory.hpp"
#include "SimpleTempleGenerator.hpp"
#include "SnakingTempleGenerator.hpp"
#include "SpiralDungeonGenerator.hpp"
#include "VoidGenerator.hpp"
#include "WellGenerator.hpp"
#include "WorldGenerator.hpp"
#include "XMLDataStructures.hpp"
#include "XMLConfigurationReader.hpp"
#include "XMLFileReader.hpp"
#include "StringTable.hpp"
#include "Skills.hpp"
#include "common.hpp"

std::string map_to_string(MapPtr map, bool html=true);
std::string map_to_html_string(MapPtr map);
void tile_to_string(TilePtr tile, std::string& tile_ascii, std::string& map_s, const bool use_html, std::string& start_tag, std::string& end_tag, const int row, const int col, const bool show_coords);
void output_map(std::string map, std::string filename);

// Random number generation function prototypes
void test_rng();
void test_range();
void test_dice();
void test_poisson();

// Miscellaneous testing
void misc();
void test_calendar();
void test_item_generation();
void test_creature_generation();
void settlement_name_generation();
void set_game_player();
void artifact_name_generation();

// Other maps
void test_other_maps();
std::string generate_void();

// Custom maps
void load_custom_maps();
MapPtr load_custom_map(const std::string& fname_pattern, const std::string& map_id);

// Map testing stuff
void test_bresenham_line();

// Terrain generation function prototypes
std::string generate_field();
std::string generate_coast();
std::string generate_field_ruins();
std::string generate_field_settlement_ruins();
std::string generate_forest();
std::string generate_marsh();
std::string generate_settlement();
std::string generate_hamlet();
std::string generate_walled_settlement();
std::string generate_scattered_settlement();
std::string generate_dungeon();
std::string generate_spiral_dungeon();
std::string generate_field_road();
std::string generate_forest_road();
std::string generate_sea();
std::string generate_world();
std::string generate_cavern();
std::string generate_ordered_graveyard();
std::string generate_scattered_graveyard();
std::string generate_keep();
std::string generate_crypt();
std::string generate_simple_church();
std::string generate_fortified_church();
std::string generate_cathedral();
std::string generate_snaking_temple();
std::string generate_simple_temple();
std::string generate_grand_temple();
std::string generate_island_sacrifice_site();
std::string generate_rocky_sacrifice_site();
std::string generate_overgrown_sacrifice_site();
std::string generate_mine();
std::string generate_castle();
std::string generate_sewer();
std::string generate_rectangular_shrine();
std::string generate_cross_shrine();
std::string generate_floating_tower();
std::string generate_well();

void   settlement_maps();
void   city_maps();
void   church_maps();
void   initialize_settings();
void   race_info();
void   class_info();
void   print_race_info(const RaceMap& race_map, const std::string& id);
void   print_class_info(ClassMap& class_map, const std::string& id);

void initialize_settings()
{
  StringTable::load("shadowofthewyrmtext_en.ini");
}

void output_map(std::string map, std::string filename)
{
  std::ofstream output;
  output.open(filename.c_str());
  output << map << std::endl;
  output.close();
}

std::string map_to_string(MapPtr map, bool use_html)
{
  std::string map_s = "";
  std::string tile_ascii = "";

  Dimensions d = map->size();
  int rows = d.get_y();
  int cols = d.get_x();

  std::string start_tag, end_tag;

  if (use_html)
  {
    map_s = map_s + "<html><head><title>Shadow of the Wyrm Map</title></head><body bgcolor=\"#000000\">";
    end_tag = "</font>";
  }

  Dimensions dim = map->size();
  int row_end = dim.get_y() - 1;
  int col_end = dim.get_x() - 1;

  MapPtr row_reset_map = map;
  MapPtr cur_map = map;
  int cur_map_y = 0;
  int cur_map_x = 0;

  for (int y = 0; y <= row_end; y++)
  {
    for (int x = 0; x <= col_end; x++)
    {
      TilePtr tile = cur_map->at(cur_map_y, cur_map_x);

      if (tile != nullptr)
      {
        tile_to_string(tile, tile_ascii, map_s, use_html, start_tag, end_tag, y, x, false);
      }

      if (x == col_end)
      {
        // Is there a map to the east?
        MapExitPtr exit = cur_map->get_map_exit(Direction::DIRECTION_EAST);

        if (exit && exit->is_using_map_id())
        {
          cur_map = Game::instance().get_map_registry_ref().get_map(exit->get_map_id());
          Dimensions dim = cur_map->size();
          col_end += dim.get_x() - 1;
        }

        cur_map_x = 0;
      }
      else
      {
        cur_map_x++;
      }
    }

    if (use_html)
    {
      map_s = map_s + "<br/>";
    }

    if (y == row_end)
    {
      // Is there a map to the south?
      MapExitPtr exit = row_reset_map->get_map_exit(Direction::DIRECTION_SOUTH);

      if (exit && exit->is_using_map_id())
      {
        row_reset_map = Game::instance().get_map_registry_ref().get_map(exit->get_map_id());
        Dimensions dim = cur_map->size();
        row_end += dim.get_y() - 1;
        cur_map_y = 0;
        cur_map_x = 0;
      }
    }
    else
    {
      cur_map_y++;
    }

    cur_map = row_reset_map;
    col_end = cur_map->size().get_x() - 1;
  }

  if (use_html)
  {
    map_s = map_s + "</body></html>";
  }

  return map_s;
}

void tile_to_string(TilePtr tile, std::string& tile_ascii, std::string& map_s, const bool use_html, std::string& start_tag, std::string& end_tag, const int row, const int col, const bool show_coords)
{
  IInventoryPtr items = tile->get_items();
  bool has_creature = tile->has_creature();

  if (items->size() > 0 && !has_creature)
  {
    ItemPtr item = items->at(0);
    if (use_html) start_tag = "<font face=\"Courier\" color=\"" + convert_colour_to_hex_code(item->get_colour()) + "\">";
    std::ostringstream ss;
    ss << item->get_symbol().get_symbol();
    tile_ascii = html_encode(ss.str());
  }
  else if (tile->has_feature() && !has_creature)
  {
    if (use_html) start_tag = "<font face=\"Courier\" color=\"" + convert_colour_to_hex_code(tile->get_feature()->get_colour()) + "\">";
    std::ostringstream ss;
    ss << tile->get_feature()->get_symbol().get_symbol();
    tile_ascii = html_encode(ss.str());
  }
  else
  {
    ShimmerColours sc({ Colour::COLOUR_UNDEFINED, Colour::COLOUR_UNDEFINED, Colour::COLOUR_UNDEFINED });
    DisplayTile dt = MapTranslator::create_display_tile(false /* player blinded? not in the map tester */, false /*not timewalking*/, { Colour::COLOUR_UNDEFINED, Colour::COLOUR_UNDEFINED } /* ditto for colour overrides */, sc, tile, tile, row, col);
    if (use_html) start_tag = "<font face=\"Courier\" color=\"" + convert_colour_to_hex_code(static_cast<Colour>(dt.get_colour())) + "\">";
    std::ostringstream ss;

    if (show_coords)
    {
      ss << "(" << row << "," << col << ")";
    }
    
    ss << dt.get_symbol().get_symbol();

    tile_ascii = html_encode(ss.str());
  }

  map_s = map_s + start_tag + tile_ascii + end_tag;
}

std::string generate_cavern()
{
  GeneratorPtr cavern_gen = std::make_unique<CavernGenerator>("");
  MapPtr map = cavern_gen->generate();
  std::cout << map_to_string(map, false);
  return map_to_string(map);
}

std::string generate_ordered_graveyard()
{
  bool inc_tomb = false;
  int rand = RNG::range(0, 1);
  if (rand) inc_tomb = true;

  GeneratorPtr graveyard_gen = GraveyardGeneratorFactory::create_ordered_graveyard_generator("", inc_tomb);
  MapPtr map = graveyard_gen->generate();
  std::cout << map_to_string(map, false);
  return map_to_string(map);
}

std::string generate_scattered_graveyard()
{
  bool inc_tomb = false;
  int rand = RNG::range(0, 1);
  if (rand) inc_tomb = true;
  
  GeneratorPtr graveyard_gen = GraveyardGeneratorFactory::create_scattered_graveyard_generator("", inc_tomb);
  MapPtr map = graveyard_gen->generate();
  std::cout << map_to_string(map, false);
  return map_to_string(map);  
}

std::string generate_keep()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr base_map = field_gen->generate();
  GeneratorPtr keep_gen = std::make_unique<KeepGenerator>(base_map);
  MapPtr keep_map = keep_gen->generate();
  std::cout << map_to_string(keep_map, false);
  return map_to_string(keep_map);
}

std::string generate_crypt()
{
  GeneratorPtr crypt_gen = std::make_unique<CryptGenerator>("");
  MapPtr crypt_map = crypt_gen->generate();
  std::cout << map_to_string(crypt_map, false);
  return map_to_string(crypt_map);
}

std::string generate_simple_church()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr map = field_gen->generate();
  GeneratorPtr church_gen = std::make_unique<SimpleChurchGenerator>("", map);
  MapPtr church_map = church_gen->generate();
  std::cout << map_to_string(church_map, false);
  return map_to_string(church_map);
}

std::string generate_fortified_church()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr church_gen = std::make_unique<FortifiedChurchGenerator>("", field_map);
  MapPtr church_map = church_gen->generate();
  std::cout << map_to_string(church_map, false);
  return map_to_string(church_map);
}

std::string generate_cathedral()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr cathedral_gen = std::make_unique<CathedralGenerator>("", field_map);
  MapPtr cathedral_map = cathedral_gen->generate();
  std::cout << map_to_string(cathedral_map, false);
  return map_to_string(cathedral_map);
}

std::string generate_snaking_temple()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr temple_gen = std::make_unique<SnakingTempleGenerator>("", field_map);
  MapPtr temple_map = temple_gen->generate();
  std::cout << map_to_string(temple_map, false);
  return map_to_string(temple_map);
}

std::string generate_simple_temple()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr temple_gen = std::make_unique<SimpleTempleGenerator>("", field_map);
  MapPtr temple_map = temple_gen->generate();
  std::cout << map_to_string(temple_map, false);
  return map_to_string(temple_map);
}

std::string generate_grand_temple()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr temple_gen = std::make_unique<GrandTempleGenerator>("", field_map);
  MapPtr temple_map = temple_gen->generate();
  std::cout << map_to_string(temple_map, false);
  return map_to_string(temple_map);
}

std::string generate_island_sacrifice_site()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr site_gen = std::make_unique<IslandSacrificeSiteGenerator>("", field_map);
  MapPtr site_map = site_gen->generate();
  std::cout << map_to_string(site_map, false);
  return map_to_string(site_map);
}

std::string generate_rocky_sacrifice_site()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr site_gen = std::make_unique<RockySacrificeSiteGenerator>("", field_map);
  MapPtr site_map = site_gen->generate();
  std::cout << map_to_string(site_map, false);
  return map_to_string(site_map);
}

std::string generate_overgrown_sacrifice_site()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr site_gen = std::make_unique<OvergrownSacrificeSiteGenerator>("", field_map);
  MapPtr site_map = site_gen->generate();
  std::cout << map_to_string(site_map, false);
  return map_to_string(site_map);
}

std::string generate_field()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr map = field_gen->generate();
  std::cout << map_to_string(map, false);
  return map_to_string(map);
}

std::string generate_coast()
{
  std::cout << "Coast N? ";
  bool north = false;
  std::cin >> north;

  std::cout << "Coast S? ";
  bool south = false;
  std::cin >> south;

  std::cout << "Coast E? ";
  bool east = false;
  std::cin >> east;

  std::cout << "Coast W? ";
  bool west = false;
  std::cin >> west;

  std::vector<Direction> coastline_dirs;

  if (north)
  {
    coastline_dirs.push_back(Direction::DIRECTION_NORTH);
  }

  if (south)
  {
    coastline_dirs.push_back(Direction::DIRECTION_SOUTH);
  }

  if (east)
  {
    coastline_dirs.push_back(Direction::DIRECTION_EAST);
  }

  if (west)
  {
    coastline_dirs.push_back(Direction::DIRECTION_WEST);
  }

  GeneratorPtr gen; 

  int choice = 0;

  std::cout << std::endl << "1. Field" << std::endl;
  std::cout << "2. Forest" << std::endl;
  std::cout << "3. Desert" << std::endl;
  std::cout << "4. Scrub" << std::endl;
  std::cout << "5. Marsh" << std::endl;
  std::cout << "6. Hills" << std::endl;

  std::cin >> choice;

  switch (choice)
  {
    case -1:
      return "";
    case 1:
      gen = std::make_unique<FieldGenerator>("");
      break;
    case 2:
      gen = std::make_unique<ForestGenerator>("");
      break;
    case 3:
      gen = std::make_unique<DesertGenerator>("");
      break;
    case 4:
      gen = std::make_unique<ScrubGenerator>("");
      break;
    case 5:
      gen = std::make_unique<MarshGenerator>("");
      break;
    case 6:
      gen = std::make_unique<HillsGenerator>("");   
      break;
    default:
      return "";
  }

  MapUtils::set_coastline_generator_dirs(gen.get(), coastline_dirs);
  MapPtr map = gen->generate();
  std::cout << map_to_string(map, false);
  return map_to_string(map);
}

std::string generate_forest()
{
  GeneratorPtr forest_gen = std::make_unique<ForestGenerator>("");
  MapPtr map = forest_gen->generate();
  std::cout << map_to_string(map, false);
  return map_to_string(map);
}

std::string generate_field_road()
{
  CardinalDirection direction = static_cast<CardinalDirection>(RNG::range(0, 3));
  int width = RNG::range(3, 6);
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr map = field_gen->generate();
  RoadGenerator road_gen(direction, width);
  MapPtr final_map = road_gen.generate(map);
  std::cout << map_to_string(map, false);
  return map_to_string(final_map);
}

std::string generate_forest_road()
{
  CardinalDirection direction = static_cast<CardinalDirection>(RNG::range(0, 3));
  int width = RNG::range(3, 6);
  GeneratorPtr forest_gen = std::make_unique<ForestGenerator>("");
  MapPtr map = forest_gen->generate();
  RoadGenerator road_gen(direction, width);
  MapPtr final_map = road_gen.generate(map);
  std::cout << map_to_string(map, false);
  return map_to_string(final_map);
}

std::string generate_field_settlement_ruins()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  SettlementRuinsGenerator sr_gen(field_map);
  MapPtr ruins_map = sr_gen.generate();
  std::cout << map_to_string(ruins_map, false);
  return map_to_string(ruins_map);
}

std::string generate_field_ruins()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  RuinsGenerator rg("fdsa", TileType::TILE_TYPE_FIELD, RuinsType::RUINS_TYPE_KEEP);
  MapPtr ruins_map = rg.generate(field_map->size());
  std::cout << map_to_string(ruins_map, false);
  return map_to_string(ruins_map);
}

std::string generate_marsh()
{
  GeneratorPtr marsh_gen = std::make_unique<MarshGenerator>("");
  MapPtr marsh_map = marsh_gen->generate();
  std::cout << map_to_string(marsh_map, false);
  return map_to_string(marsh_map);
}

std::string generate_settlement()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  SettlementGenerator settle_gen(field_map);
  settle_gen.set_additional_property(TileProperties::TILE_PROPERTY_NAME, "test");

  MapPtr settlement_map = settle_gen.generate();
  std::cout << map_to_string(settlement_map, false);
  return map_to_string(settlement_map);
}

std::string generate_hamlet()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  HamletGenerator hamlet_gen(field_map);
  hamlet_gen.set_additional_property(TileProperties::TILE_PROPERTY_NAME, "test");

  MapPtr hamlet_map = hamlet_gen.generate();
  std::cout << map_to_string(hamlet_map, false);
  return map_to_string(hamlet_map);
}

std::string generate_walled_settlement()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  WalledSettlementGenerator ws_gen(field_map);
  ws_gen.set_additional_property(TileProperties::TILE_PROPERTY_NAME, "test");

  MapPtr ws_map = ws_gen.generate();
  std::cout << map_to_string(ws_map, false);
  return map_to_string(ws_map);
}

std::string generate_scattered_settlement()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  ScatteredSettlementGenerator sc_gen(field_map);
  sc_gen.set_additional_property(TileProperties::TILE_PROPERTY_NAME, "test");

  MapPtr sc_map = sc_gen.generate();
  std::cout << map_to_string(sc_map, false);
  return map_to_string(sc_map);  
}

std::string generate_dungeon()
{
  GeneratorPtr dun_gen = std::make_unique<DungeonGenerator>(""); // ha ha
  MapPtr dun_gen_map = dun_gen->generate();
  std::cout << map_to_string(dun_gen_map, false);
  return map_to_string(dun_gen_map);
}

std::string generate_spiral_dungeon()
{
  GeneratorPtr sd_gen = std::make_unique<SpiralDungeonGenerator>("");
  MapPtr sd_map = sd_gen->generate();
  std::cout << map_to_string(sd_map, false);
  return map_to_string(sd_map);
}

std::string generate_sea()
{
  GeneratorPtr sea_gen = std::make_unique<SeaGenerator>("");
  MapPtr sea_map = sea_gen->generate();
  std::cout << map_to_string(sea_map, false);
  return map_to_string(sea_map);
}

std::string generate_mine()
{
  GeneratorPtr mine_gen = std::make_unique<MineGenerator>("");
  MapPtr mine_map = mine_gen->generate();
  std::cout << map_to_string(mine_map, false);
  return map_to_string(mine_map);
}

std::string generate_castle()
{
  GeneratorPtr castle_gen = std::make_unique<CastleGenerator>("", TileType::TILE_TYPE_FIELD);
  MapPtr castle_map = castle_gen->generate();
  std::cout << map_to_string(castle_map, false);
  return map_to_string(castle_map);
}

std::string generate_sewer()
{
  GeneratorPtr sewer_gen = std::make_unique<SewerGenerator>("");
  MapPtr sewer_map = sewer_gen->generate();
  std::cout << map_to_string(sewer_map, false);
  return map_to_string(sewer_map);
}

std::string generate_rectangular_shrine()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr shrine_gen = ShrineGeneratorFactory::create_rectangular_shrine_generator(field_map);
  MapPtr shrine_map = shrine_gen->generate();
  std::cout << map_to_string(shrine_map, false);
  return map_to_string(shrine_map);
}

std::string generate_cross_shrine()
{
  GeneratorPtr field_gen = std::make_unique<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr shrine_gen = ShrineGeneratorFactory::create_cross_shrine_generator(field_map);
  MapPtr shrine_map = shrine_gen->generate();
  std::cout << map_to_string(shrine_map, false);
  return map_to_string(shrine_map);
}

std::string generate_floating_tower()
{
  GeneratorPtr ft_gen = std::make_unique<FloatingTowerGenerator>("");
  MapPtr ft_map = ft_gen->generate();
  std::cout << map_to_string(ft_map, false);
  return map_to_string(ft_map);
}

std::string generate_well()
{
  GeneratorPtr well_gen = std::make_unique<WellGenerator>("");
  MapPtr well_map = well_gen->generate();
  std::cout << map_to_string(well_map, false);
  return map_to_string(well_map);
}

std::string generate_world()
{
  // Add inputs for parameters later!
  WorldGenerator wg;
  MapPtr map = wg.generate();
  std::cout << "World map created - see html." << std::endl;
  return map_to_string(map);
}

void print_race_info(const RaceMap& race_map, const std::string& id)
{
  Race* race = race_map.find(id)->second.get();

  if (race)
  {
    std::string race_details = race->str();
    std::cout << race_details << std::endl;
  }
  else
  {
    std::cout << "No race with that ID found." << std::endl;
  }
}

void print_class_info(ClassMap& class_map, const std::string& id)
{
  Class* current_class = class_map[id].get();

  if (current_class)
  {
    std::string class_details = current_class->str();
    std::cout << class_details << std::endl;
  }
  else
  {
    std::cout << "No class with that ID found." << std::endl;
  }
}

void race_info()
{
  std::string race_id = "";

  XMLConfigurationReader xml_config_reader("data/ShadowOfTheWyrm.xml", "data/ShadowOfTheWyrm_Creatures.xml", "data/ShadowOfTheWyrm_Items.xml");
  RaceMap races = xml_config_reader.get_races();

  std::cout << "Read " << races.size() << " races." << std::endl << std::endl;

  while (race_id != "-1")
  {
    std::cout << "Enter a race id (-1 to quit): ";
    std::cin >> race_id;

    print_race_info(races, race_id);
  }
}

void class_info()
{
  std::string class_id = "";

  XMLConfigurationReader xml_config_reader("data/ShadowOfTheWyrm.xml", "data/ShadowOfTheWyrm_Creatures.xml", "data/ShadowOfTheWyrm_Items.xml");
  ClassMap classes = xml_config_reader.get_classes();

  std::cout << "Read " << classes.size() << " classes." << std::endl << std::endl;

  while (class_id != "-1")
  {
    std::cout << "Enter a class id (-1 to quit): ";
    std::cin >> class_id;

    print_class_info(classes, class_id);
  }
}

void test_range()
{
  int min = 0;
  int max = 0;

  while (min != -1 && max != -1)
  {
    std::cout << "-1 for min or max to quit." << std::endl;
    std::cout << "Min: ";
    std::cin >> min;
    std::cout << "Max: ";
    std::cin >> max;
    std::cout << "Random value is: ";

    if (min != -1 && max != -1)
    {
      int random = RNG::range(min, max);

      std::cout << random << std::endl;
    }
  }

}

void test_dice()
{
  int num = 0;
  int sides = 0;

  while (num != -1 && sides != -1)
  {
    std::cout << "-1 for num or sides to quit." << std::endl;
    std::cout << "Num: ";
    std::cin >> num;
    std::cout << "Sides: ";
    std::cin >> sides;
    std::cout << "Random value is: ";

    if (num != -1 && sides != -1)
    {
      int dice = RNG::dice(num, sides);

      std::cout << dice << std::endl;
    }
  }
}

void test_poisson()
{
  int mean = 1;
  int times = 1;

  while (mean > 0 && times > 0)
  {
    std::cout << "Poisson calculator (mean <= 0 or times <= 0 to quit)" << std::endl;
    std::cout << "Mean: ";
    std::cin >> mean;
    std::cout << "Times: ";
    std::cin >> times;

    if (mean > 0 && times > 0)
    {
      int m = 0;
      int min = std::numeric_limits<int>::max();
      int max = std::numeric_limits<int>::min();
      PoissonDistribution pd(mean);

      for (int i = 0; i < times; i++)
      {
        int v = pd.next();

        if (v < min)
        {
          min = v;
        }

        if (v > max)
        {
          max = v;
        }

        m += v;
      }

      std::cout << "Calculated mean: " << (m / static_cast<float>(times)) << std::endl;
      std::cout << "Min, max: " << min << ", " << max << std::endl << std::endl;
    }
  }
}

void misc()
{
  int choice = 0;
  while (choice != -1)
  {
    std::cout << "-1 to quit." << std::endl;
    std::cout << "1. Bresenham's Line" << std::endl;
    std::cout << "2. Calendar" << std::endl;
    std::cout << "3. Item Generation" << std::endl;
    std::cout << "4. Other Map Types" << std::endl;
    std::cout << "5. Load Custom Map" << std::endl;
    std::cout << "6. Creature Generation" << std::endl;
    std::cout << "7. Settlement Name Generation" << std::endl;
    std::cout << "8. Set player on Game object" << std::endl;
    std::cout << "9. Artifact Name Generation" << std::endl;

    std::cin >> choice;
    
    switch(choice)
    {
      case 1: 
        test_bresenham_line();
        break;
      case 2:
        test_calendar();
        break;
      case 3:
        test_item_generation();
        break;
      case 4:
        test_other_maps();
        break;
      case 5:
        load_custom_maps();
        break;
      case 6:
        test_creature_generation();
      case 7:
        settlement_name_generation();
        break;
      case 8:
        set_game_player();
        break;
      case 9:
        artifact_name_generation();
        break;
      default:
        break;
    }
  }
}

void test_calendar()
{
  double seconds = 0;
  
  while (seconds > -1)
  {
    std::cout << "-1 to quit." << std::endl;
    std::cout << "Number of elapsed seconds: " << std::endl;
    std::cin >> seconds;
    
    if (seconds >= 0)
    {
      Calendar c;
      c.add_seconds(seconds);
      Date d = c.get_date();
      
      std::cout << "Calendar Info: " << std::endl;
      std::cout << "Time: " << d.get_hours() << ":" << d.get_minutes() << ":" << d.get_seconds() << std::endl;
      std::cout << "Day: Day " << d.get_day_of_week() << " of week, day " << d.get_day_of_month() << " of month, day " << d.get_day_of_year() << " of year" << std::endl;
      std::cout << "Month: " << d.get_month() << std::endl;
      std::cout << "Year: " << d.get_year() << std::endl; 
    }
  }
}

void test_item_generation()
{
  int item_count = 0;
  int danger_level = 0;
  int irarity = 0;
  Rarity rarity = Rarity::RARITY_COMMON;
  std::string filename = "test.txt";
  Game& game = Game::instance();

  while (item_count > -1 && danger_level > -1 && !filename.empty())
  {
    std::cout << "-1 to any prompt to quit" << std::endl;
    std::cout << "Item Generation" << std::endl;
    std::cout << "Items to generate: ";
    std::cin >> item_count;
    std::cout << "Danger level: ";
    std::cin >> danger_level;
    std::cout << "Rarity: ";
    std::cin >> irarity;
    
    rarity = static_cast<Rarity>(irarity);

    std::cout << "Filename: ";
    std::cin >> filename;

    if (item_count > -1 && danger_level > -1 && filename != "-1")
    {
      ItemGenerationManager igm;
      ItemGenerationConstraints igc(1, danger_level, rarity, {}, -1);
      auto igmap = igm.generate_item_generation_map(igc);
      std::map<std::string, int> item_map;
      std::map<ItemType, int> type_map;

      for (int i = 0; i < item_count; i++)
      {
        ItemPtr item = igm.generate_item(game.get_action_manager_ref(), igmap, rarity, {}, 0);

        if (item != nullptr)
        {
          std::string base_id = item->get_base_id();
          ItemType type = item->get_type();

          auto i_it = item_map.find(base_id);

          if (i_it != item_map.end())
          {
            item_map[base_id]++;
          }
          else
          {
            item_map[base_id] = 1;
          }

          auto t_it = type_map.find(type);

          if (t_it != type_map.end())
          {
            type_map[type]++;
          }
          else
          {
            type_map[type] = 1;
          }
        }
      }

      std::ofstream outfile(filename);
      
      for (const auto& item_pair : item_map)
      {
        outfile << item_pair.first << ": " << item_pair.second << std::endl;
      }

      for (const auto& type_pair : type_map)
      {
        float pct = ((float) type_pair.second / (float) item_count) * 100.0f;
        outfile << "Item Type " << static_cast<int>(type_pair.first) << ": " << type_pair.second << "(" << pct << "%)" << std::endl;
      }

      outfile.close();
      std::cout << "Wrote to " << filename << std::endl << std::endl;
    }
  }
}

void test_creature_generation()
{
  int min_level = 1;
  int max_level = 1;
  int tile_type = -1;
  int num_creatures = 1;
  std::string filename;

  Game& game = Game::instance();
  CreatureGenerationManager cgm;
  ActionManager& am = game.get_action_manager_ref();

  while (min_level > 0)
  {
    std::cout << "Creature Generation" << std::endl << std::endl;
    std::cout << "Min Level: ";
    std::cin >> min_level;

    std::cout << "Max Level: ";
    std::cin >> max_level;

    std::cout << "Tile Type: ";
    std::cin >> tile_type;

    std::cout << "Number of creatures: ";
    std::cin >> num_creatures;

    std::cout << "Filename: ";
    std::cin >> filename;

    CreatureGenerationIndex generation_list = cgm.generate_creature_generation_map({ static_cast<TileType>(tile_type) }, false, false, min_level, max_level, Rarity::RARITY_COMMON, {});
    const auto& cgl = generation_list.get();

    std::map<std::string, int> creature_count;

    if (num_creatures > 0)
    {
      for (int i = 0; i < num_creatures; i++)
      {
        CreaturePtr creature = cgm.generate_creature(am, cgl, nullptr);

        if (creature != nullptr)
        {
          std::string creature_id = creature->get_original_id();

          if (creature_count.find(creature_id) == creature_count.end())
          {
            creature_count[creature_id] = 1;
          }
          else
          {
            creature_count[creature_id]++;
          }
        }
      }
    }

    if (!creature_count.empty())
    {
      std::ofstream outfile(filename);

      for (const auto& cr_pair : creature_count)
      {
        outfile << cr_pair.first << ": " << cr_pair.second << std::endl;
      }

      outfile.close();
    }
  }
}

void settlement_name_generation()
{
  for (int i = 0; i < 15; i++)
  {
    std::cout << Naming::generate_settlement_name() << std::endl;
  }
}

void artifact_name_generation()
{
  for (int i = 0; i < 15; i++)
  {
    std::cout << Naming::generate_artifact_name() << std::endl;
  }
}

void set_game_player()
{
  CreaturePtr player = std::make_shared<Creature>();
  player->set_is_player(true, nullptr);

  std::cout << "Cantrips: ";
  int cantrips = 0;
  std::cin >> cantrips;
  player->get_skills().set_value(SkillType::SKILL_MAGIC_CANTRIPS, cantrips);

  std::cout << "Arcane: ";
  int arcane = 0;
  std::cin >> arcane;
  player->get_skills().set_value(SkillType::SKILL_MAGIC_ARCANE, arcane);

  std::cout << "Divine: ";
  int divine = 0;
  std::cin >> divine;
  player->get_skills().set_value(SkillType::SKILL_MAGIC_DIVINE, divine);

  std::cout << "Mystic: ";
  int mystic = 0;
  std::cin >> mystic;
  player->get_skills().set_value(SkillType::SKILL_MAGIC_MYSTIC, mystic);

  std::cout << "Primordial: ";
  int primordial = 0;
  std::cin >> primordial;
  player->get_skills().set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, primordial);

  Dimensions d;
  MapPtr map = std::make_shared<Map>(d);
  GeneratorUtils::fill(map, { 0,0 }, { d.get_y() - 1, d.get_x() - 1 }, TileType::TILE_TYPE_FIELD);
  TilePtr tile = map->at(0, 0);
  
  if (tile != nullptr)
  {
    tile->set_creature(player);
  }

  map->set_map_id("default");
  map->set_permanent(true);

  Game::instance().set_current_map(map);
}

void test_bresenham_line()
{
  int start_y, start_x, end_y, end_x;
  BresenhamLine bl;
  
  start_y = start_x = end_y = end_x = 0;
  
  while (start_y != -1 && start_x != -1 && end_y != -1 && end_x != -1)
  {
    std::cout << "-1 for any value to quit." << std::endl;
    std::cout << "Start y: ";
    std::cin >> start_y;
    std::cout << "Start x: ";
    std::cin >> start_x;
    std::cout << "End y: ";
    std::cin >> end_y;
    std::cout << "End x: ";
    std::cin >> end_x;
    std::cout << "Line contains points: " << std::endl;

    if (start_y != -1 && start_x != -1 && end_y != -1 && end_x != -1)
    {
      std::vector<Coordinate> coords = bl.get_points_in_line(start_y, start_x, end_y, end_x);
      
      for (const Coordinate& c : coords)
      {
        std::cout << "(" << c.first << "," << c.second << ")" << std::endl;
      }
    }
  }  
}

void test_rng()
{
  int option = 0;
  while(option != -1)
  {
    std::cout << "RNG Test!" << std::endl << std::endl;
    std::cout << "1. Range" << std::endl;
    std::cout << "2. Dice" << std::endl;
    std::cout << "3. Poisson" << std::endl;
    std::cout << "-1. Quit" << std::endl << std::endl;
    std::cin >> option;

    switch(option)
    {
      case 1:
        test_range();
        break;
      case 2:
        test_dice();
        break;
      case 3:
        test_poisson();
        break;
      default:
        break;
    }
  }
}

void test_other_maps()
{
  std::string map;
  int option = 0;
  while(option != -1)
  {
    std::cout << "Other Maps" << std::endl << std::endl;
    std::cout << "0. Void" << std::endl;
    std::cout << "-1. Quit" << std::endl << std::endl;
    std::cin >> option;

    switch(option)
    {
      case 0:
        map = generate_void();
        output_map(map, "void_test.html");
        break;
      default: 
        break;
    }
  }
}

void load_custom_maps()
{
  std::string map;
  int selection = 0;
  std::map<int, std::pair<std::string, std::string>> selection_mappings = {{1, {"(Carcassia.*\\.xml)", "carcassia_a1"}},
                                                                           {2, {"(Carcassia_GuildOfThieves\\.xml)", "carcassia_guild_of_thieves"}}};

  while (selection != -1)
  {
    std::string fname_pattern;

    std::cout << "Load Custom Map" << std::endl << std::endl;
    std::cout << "1. Carcassia" << std::endl;
    std::cout << "2. Carcassia Guild of Thieves" << std::endl;
    std::cout << "-1. Quit" << std::endl;

    std::cin >> selection;

    if (selection != -1)
    {
      auto s_it = selection_mappings.find(selection);

      if (s_it != selection_mappings.end())
      {
        std::pair<std::string, std::string> filter_mid = s_it->second;
        MapPtr map = load_custom_map(filter_mid.first, filter_mid.second);

        if (map != nullptr)
        {
          output_map(map_to_string(map), "custom_map.html");
        }
      }
    }
  }
}

MapPtr load_custom_map(const std::string& fname_pattern, const std::string& custom_map_id)
{
  MapPtr custom_map;

  if (!fname_pattern.empty() && !custom_map_id.empty())
  {
    // We don't care about reading actual configuration data, just the maps.
    XMLConfigurationReader cr("", "", "");
    Game& game = Game::instance();

    std::vector<MapPtr> maps = cr.get_custom_maps(FileConstants::CUSTOM_MAPS_DIRECTORY, fname_pattern);
    game.set_custom_maps(maps);

    custom_map = game.get_map_registry_ref().get_map(custom_map_id);
  }

  return custom_map;
}

std::string generate_void()
{
  GeneratorPtr void_gen = std::make_unique<VoidGenerator>("");
  MapPtr map = void_gen->generate();
  std::cout << map_to_string(map, false);
  return map_to_string(map);
}

void settlement_maps()
{
  std::string map;
  int settlement_map = 0;
  
  while (settlement_map != -1)
  {
    std::cout << "Enter a map number (-1 to quit):" << std::endl << std::endl;
    std::cout << "1. Settlement" << std::endl;
    std::cout << "2. Hamlet" << std::endl;
    std::cout << "3. Walled Settlement" << std::endl;
    std::cout << "4. Scattered Settlement" << std::endl;
    
    std::cin >> settlement_map;
    
    switch(settlement_map)
    {
      case 1:
        map = generate_settlement();
        output_map(map, "settlement_test.html");
        break;
      case 2:
        map = generate_hamlet();
        output_map(map, "hamlet_test.html");
        break;
      case 3:
        map = generate_walled_settlement();
        output_map(map, "walled_settlement_test.html");
        break;
      case 4:
        map = generate_scattered_settlement();
        output_map(map, "scattered_settlement_test.html");
        break;
      default: 
        break;
    }
  }
}

void city_maps()
{
  std::string map;
  int city_adjacent_map = 0;
  
  while (city_adjacent_map != -1)
  {
    std::cout << "Enter a map number (-1 to quit)" << std::endl << std::endl;
    std::cout << "1. Ordered Graveyard" << std::endl;
    std::cout << "2. Scattered Graveyard" << std::endl;
    std::cout << "3. Keep" << std::endl;
    std::cout << "4. Churches, Temples, Sites of Death" << std::endl;
    std::cout << "5. Crypt" << std::endl;
    std::cout << "6. Mine" << std::endl;
    std::cout << "7. Castle" << std::endl;
    std::cout << "8. Sewer" << std::endl;
    std::cout << "9. Rectangular Shrine" << std::endl;
    std::cout << "10. Cross Shrine" << std::endl;
    std::cout << "11. Floating Tower" << std::endl;
    std::cout << "12. Well" << std::endl;

    std::cin >> city_adjacent_map;
    
    switch(city_adjacent_map)
    {
      case 1:
        map = generate_ordered_graveyard();
        output_map(map, "graveyard_ordered_test.html");
        break;
      case 2:
        map = generate_scattered_graveyard();
        output_map(map, "graveyard_scattered_test.html");
        break;
      case 3:
        map = generate_keep();
        output_map(map, "keep_test.html");
        break;
      case 4: 
        church_maps();
        break;
      case 5:
        map = generate_crypt();
        output_map(map, "crypt_test.html");
        break;
      case 6:
        map = generate_mine();
        output_map(map, "mine_test.html");
        break;
      case 7:
        map = generate_castle();
        output_map(map, "castle_test.html");
        break;
      case 8:
        map = generate_sewer();
        output_map(map, "sewer_test.html");
        break;
      case 9:
        map = generate_rectangular_shrine();
        output_map(map, "rect_shrine_test.html");
        break;
      case 10:
        map = generate_cross_shrine();
        output_map(map, "cross_shrine_test.html");
        break;
      case 11:
        map = generate_floating_tower();
        output_map(map, "floating_tower_test.html");
        break;
      case 12:
        map = generate_well();
        output_map(map, "well_test.html");
        break;
      default:
        break;
    }
  }
}

void church_maps()
{
  std::string map;
  int church_map = 0;
  
  while (church_map != -1)
  {
    std::cout << "Enter a map number (-1 to quit)" << std::endl << std::endl;
    std::cout << "1. Cathedral (Celeste)" << std::endl;
    std::cout << "2. Fortified Church (Aurelion)" << std::endl;
    std::cout << "3. Simple Church (The Lady)" << std::endl;
    std::cout << "4. Grand Temple (Vedere)" << std::endl;
    std::cout << "5. Snaking Temple (Voros)" << std::endl;
    std::cout << "6. Simple Temple (The Trickster)" << std::endl;
    std::cout << "7. Island Sacrifice Site (Shiver)" << std::endl;
    std::cout << "8. Rocky Sacrifice Site (Urgoth)" << std::endl;
    std::cout << "9. Overgrown Sacrifice Site (Sceadugenga)" << std::endl;
    std::cin >> church_map;
    
    switch(church_map)
    {
      case 1: 
        map = generate_cathedral();
        output_map(map, "cathedral_test.html");
        break;
      case 2:
        map = generate_fortified_church();
        output_map(map, "fortified_church_test.html");
        break;
      case 3:
        map = generate_simple_church();
        output_map(map, "simple_church_test.html");
        break;
      case 4:
        map = generate_grand_temple();
        output_map(map, "grand_temple_test.html");
        break;
      case 5:
        map = generate_snaking_temple();
        output_map(map, "snaking_temple_test.html");
        break;
      case 6:
        map = generate_simple_temple();
        output_map(map, "simple_temple_test.html");
        break;
      case 7:
        map = generate_island_sacrifice_site();
        output_map(map, "island_site_test.html");
        break;
      case 8:
        map = generate_rocky_sacrifice_site();
        output_map(map, "rocky_site_test.html");
        break;
      case 9:
        map = generate_overgrown_sacrifice_site();
        output_map(map, "overgrown_site_test.html");
        break;
      default:
        break;
    }
  }  
}

int main(int argc, char* argv[])
{
  std::string map;
  int option = 0;
  XML::initialize();
  initialize_settings();
  
  // Set up the items, so that I can see what gets generated...
  Settings settings(true);
  Game::instance().set_settings(settings);

  ShadowOfTheWyrmEngine engine;
  engine.setup_game();

  while (option != -1)
  {
    std::cout << "Map Generator!" << std::endl << std::endl;
    std::cout << "0. RNG" << std::endl;
    std::cout << "1. Field" << std::endl;
    std::cout << "2. Forest" << std::endl;
    std::cout << "3. Ruins (Field)" << std::endl;
    std::cout << "4. Settlements" << std::endl;
    std::cout << "5. Settlement Ruins (Field)" << std::endl;
    std::cout << "6. Marsh" << std::endl;
    std::cout << "7. Regular Dungeon" << std::endl;
    std::cout << "8. Spiral Dungeon" << std::endl;
    std::cout << "9. Road (Field)" << std::endl;
    std::cout << "10. Road (Forest)" << std::endl;
    std::cout << "11. Sea" << std::endl;
    std::cout << "12. World" << std::endl;
    std::cout << "13. Cavern" << std::endl;
    std::cout << "14. Coastline" << std::endl;
    std::cout << "15. Display race info" << std::endl;
    std::cout << "16. Display class info" << std::endl;
    std::cout << "17. City-adjacent maps" << std::endl;
    std::cout << "18. Misc" << std::endl;
    std::cout << "-1. Quit" << std::endl << std::endl;
    std::cin >> option;

    switch(option)
    {
      case 0:
        test_rng();
        break;
      case 1:
        map = generate_field();
        output_map(map, "field_test.html");
        break;
      case 2:
        map = generate_forest();
        output_map(map, "forest_test.html");
        break;
      case 3:
        map = generate_field_ruins();
        output_map(map, "ruins_test.html");
        break;
      case 4:
        settlement_maps();
        break;
      case 5:
        map = generate_field_settlement_ruins();
        output_map(map, "settlement_ruins_test.html");
        break;
      case 6:
        map = generate_marsh();
        output_map(map, "marsh_test.html");
        break;
      case 7:
        map = generate_dungeon();
        output_map(map, "dungeon_test.html");
        break;
      case 8:
        map = generate_spiral_dungeon();
        output_map(map, "spiral_dungeon_test.html");
        break;
      case 9:
        map = generate_field_road();
        output_map(map, "field_road_test.html");
        break;
      case 10:
        map = generate_forest_road();
        output_map(map, "forest_road_test.html");
        break;
      case 11:
        map = generate_sea();
        output_map(map, "sea_test.html");
        break;
      case 12:
        map = generate_world();
        output_map(map, "world_test.html");
        break;
      case 13:
        map = generate_cavern();
        output_map(map, "cavern_test.html");
        break;
      case 14:
        map = generate_coast();
        output_map(map, "coast_test.html");
        break;
      case 15:
        race_info();
        break;
      case 16:
        class_info();
        break;
      case 17:
        city_maps();
        break;
      case 18:
        misc();
        break;
      default:
        break;
    }
  }

  XML::tear_down();
  return 0;
}
