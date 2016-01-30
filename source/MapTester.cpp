#ifndef MAP_TESTER
#define MAP_TESTER 1
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
#include "CryptGenerator.hpp"
#include "DungeonGenerator.hpp"
#include "FieldGenerator.hpp"
#include "ForestGenerator.hpp"
#include "FortifiedChurchGenerator.hpp"
#include "GrandTempleGenerator.hpp"
#include "GraveyardGeneratorFactory.hpp"
#include "IslandSacrificeSiteGenerator.hpp"
#include "RockySacrificeSiteGenerator.hpp"
#include "OvergrownSacrificeSiteGenerator.hpp"
#include "RoadGenerator.hpp"
#include "RuinsGenerator.hpp"
#include "MarshGenerator.hpp"
#include "MineGenerator.hpp"
#include "SeaGenerator.hpp"
#include "SettlementGenerator.hpp"
#include "HamletGenerator.hpp"
#include "WalledSettlementGenerator.hpp"
#include "ScatteredSettlementGenerator.hpp"
#include "SimpleChurchGenerator.hpp"
#include "KeepRuinsGenerator.hpp"
#include "MapTranslator.hpp"
#include "ShadowOfTheWyrmEngine.hpp"
#include "SettlementRuinsGenerator.hpp"
#include "SimpleTempleGenerator.hpp"
#include "SnakingTempleGenerator.hpp"
#include "SpiralDungeonGenerator.hpp"
#include "WorldGenerator.hpp"
#include "XMLDataStructures.hpp"
#include "XMLConfigurationReader.hpp"
#include "XMLFileReader.hpp"
#include "StringTable.hpp"
#include "Skills.hpp"
#include "common.hpp"

using namespace std;

string map_to_string(MapPtr map, bool html=true);
string map_to_html_string(MapPtr map);
void output_map(string map, string filename);

// Random number generation function prototypes
void test_rng();
void test_range();
void test_dice();
void test_poisson();

// Miscellaneous testing
void misc();
void test_calendar();

// Map testing stuff
void test_bresenham_line();

// Terrain generation function prototypes
string generate_field();
string generate_field_ruins();
string generate_field_settlement_ruins();
string generate_forest();
string generate_marsh();
string generate_settlement();
string generate_hamlet();
string generate_walled_settlement();
string generate_scattered_settlement();
string generate_dungeon();
string generate_spiral_dungeon();
string generate_field_road();
string generate_forest_road();
string generate_sea();
string generate_world();
string generate_cavern();
string generate_ordered_graveyard();
string generate_scattered_graveyard();
string generate_keep();
string generate_crypt();
string generate_simple_church();
string generate_fortified_church();
string generate_cathedral();
string generate_snaking_temple();
string generate_simple_temple();
string generate_grand_temple();
string generate_island_sacrifice_site();
string generate_rocky_sacrifice_site();
string generate_overgrown_sacrifice_site();
string generate_mine();
string generate_castle();

void   settlement_maps();
void   city_maps();
void   church_maps();
void   initialize_settings();
void   print_skill_name();
void   race_info();
void   class_info();
void   print_race_info(RaceMap& race_map, const string& id);
void   print_class_info(ClassMap& class_map, const string& id);

void initialize_settings()
{
  StringTable::load("shadowofthewyrmtext_en.ini");
}

void output_map(string map, string filename)
{
  ofstream output;
  output.open(filename.c_str());
  output << map << endl;
  output.close();
}

string map_to_string(MapPtr map, bool use_html)
{
  string map_s = "";
  string tile_ascii = "";

  Dimensions d = map->size();
  int rows = d.get_y();
  int cols = d.get_x();

  string start_tag, end_tag;

  if (use_html)
  {
    map_s = map_s + "<html><head><title>SL Map</title></head><body bgcolor=\"#000000\">";
    end_tag = "</font>";
  }

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr tile = map->at(row, col);
      
      IInventoryPtr items = tile->get_items();
      if (items->size() > 0)
      {
        ItemPtr item = items->at(0);
        if (use_html) start_tag = "<font face=\"Courier\" color=\"" + convert_colour_to_hex_code(item->get_colour()) + "\">";
        ostringstream ss;
        ss << item->get_symbol();
        tile_ascii = html_encode(ss.str());
      }
      else if (tile->has_feature())
      {
        if (use_html) start_tag = "<font face=\"Courier\" color=\"" + convert_colour_to_hex_code(tile->get_feature()->get_colour()) + "\">";
        ostringstream ss;
        ss << tile->get_feature()->get_symbol();
        tile_ascii = html_encode(ss.str()); 
      }
      else
      {
        DisplayTile dt = MapTranslator::create_display_tile(false /* player blinded? not in the map tester */, tile, tile);
        if (use_html) start_tag = "<font face=\"Courier\" color=\"" + convert_colour_to_hex_code(static_cast<Colour>(dt.get_colour())) + "\">";
        ostringstream ss;
        ss << dt.get_symbol();
        tile_ascii = html_encode(ss.str());
/*        switch(type)
        {
          case TileType::TILE_TYPE_DAIS:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#848484\">";
            tile_ascii = ".";
            break;
          case TileType::TILE_TYPE_FIELD:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
            tile_ascii = ".";
            break;
          case TileType::TILE_TYPE_BUSH:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
            tile_ascii = "\"";
            break;
          case TileType::TILE_TYPE_WEEDS:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#008000\">";
            tile_ascii = "\"";
            break;
          case TileType::TILE_TYPE_FOREST:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
            tile_ascii = "&";
            break;
          case TileType::TILE_TYPE_MOUNTAINS:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#C0C0C0\">";
            tile_ascii = "^";
            break;
          case TileType::TILE_TYPE_TREE:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
            tile_ascii = "T";
            break;
          case TileType::TILE_TYPE_CAIRN:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#808080\">";
            tile_ascii = "*";
            break;
          case TileType::TILE_TYPE_SPRINGS:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FFFF\">";
            tile_ascii = "v";
            break;
          case TileType::TILE_TYPE_RIVER:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#0000FF\">";
            tile_ascii = "~";
            break;
          case TileType::TILE_TYPE_DUNGEON:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#C0C0C0\">";
            tile_ascii = ".";
            break;
          case TileType::TILE_TYPE_ROCK:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#808080\">";
            tile_ascii = "#";
            break;
          case TileType::TILE_TYPE_SCRUB:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#CCFF00\">";
            tile_ascii = ".";
            break;
          case TileType::TILE_TYPE_ROAD:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#A52A2A\">";
            tile_ascii = ".";
            break;
          case TileType::TILE_TYPE_MARSH:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"008000\">";
            tile_ascii = "~";
            break;
          case TileType::TILE_TYPE_REEDS:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#A52A2A\">";
            tile_ascii = "|";
            break;
          case TileType::TILE_TYPE_SEA:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"#0000FF\">";
            tile_ascii = "~";
            break;
          case TileType::TILE_TYPE_GRAVE:
            if (use_html) start_tag = "<font face=\"Courier\" color=\"C0C0C0\">";
            tile_ascii = "+";
            break;
          case TileType::TILE_TYPE_UP_STAIRCASE:
            if (use_html)
            {
              start_tag = "<font face=\"Courier\" color=\"#C0C0C0\">";
              tile_ascii = "&lt;";
              
            } 
            else tile_ascii = "<";
            break;
          case TileType::TILE_TYPE_DOWN_STAIRCASE:
            if (use_html)
            {
              start_tag = "<font face=\"Courier\" color=\"#C0C0C0\">";
              tile_ascii = "&gt;";
            }
            else tile_ascii = ">";
            break;
          default:
            tile_ascii = "?";
            break;
        } */
      }

      map_s = map_s + start_tag + tile_ascii + end_tag;
    }

    if (use_html)
    {
      map_s = map_s + "<br>";
    }
  }

  if (use_html)
  {
    map_s = map_s + "</body></html>";
  }

  return map_s;
}

string generate_cavern()
{
  GeneratorPtr cavern_gen = std::make_shared<CavernGenerator>("");
  MapPtr map = cavern_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);
}

string generate_ordered_graveyard()
{
  bool inc_tomb = false;
  int rand = RNG::range(0, 1);
  if (rand) inc_tomb = true;

  GeneratorPtr graveyard_gen = GraveyardGeneratorFactory::create_ordered_graveyard_generator("", inc_tomb);
  MapPtr map = graveyard_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);
}

string generate_scattered_graveyard()
{
  bool inc_tomb = false;
  int rand = RNG::range(0, 1);
  if (rand) inc_tomb = true;
  
  GeneratorPtr graveyard_gen = GraveyardGeneratorFactory::create_scattered_graveyard_generator("", inc_tomb);
  MapPtr map = graveyard_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);  
}

string generate_keep()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr base_map = field_gen->generate();
  GeneratorPtr keep_gen = std::make_shared<KeepGenerator>(base_map);
  MapPtr keep_map = keep_gen->generate();
  cout << map_to_string(keep_map, false);
  return map_to_string(keep_map);
}

string generate_crypt()
{
  GeneratorPtr crypt_gen = std::make_shared<CryptGenerator>("");
  MapPtr crypt_map = crypt_gen->generate();
  cout << map_to_string(crypt_map, false);
  return map_to_string(crypt_map);
}

string generate_simple_church()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr map = field_gen->generate();
  GeneratorPtr church_gen = std::make_shared<SimpleChurchGenerator>("", map);
  MapPtr church_map = church_gen->generate();
  cout << map_to_string(church_map, false);
  return map_to_string(church_map);
}

string generate_fortified_church()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr church_gen = std::make_shared<FortifiedChurchGenerator>("", field_map);
  MapPtr church_map = church_gen->generate();
  cout << map_to_string(church_map, false);
  return map_to_string(church_map);
}

string generate_cathedral()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr cathedral_gen = std::make_shared<CathedralGenerator>("", field_map);
  MapPtr cathedral_map = cathedral_gen->generate();
  cout << map_to_string(cathedral_map, false);
  return map_to_string(cathedral_map);
}

string generate_snaking_temple()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr temple_gen = std::make_shared<SnakingTempleGenerator>("", field_map);
  MapPtr temple_map = temple_gen->generate();
  cout << map_to_string(temple_map, false);
  return map_to_string(temple_map);
}

string generate_simple_temple()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr temple_gen = std::make_shared<SimpleTempleGenerator>("", field_map);
  MapPtr temple_map = temple_gen->generate();
  cout << map_to_string(temple_map, false);
  return map_to_string(temple_map);
}

string generate_grand_temple()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr temple_gen = std::make_shared<GrandTempleGenerator>("", field_map);
  MapPtr temple_map = temple_gen->generate();
  cout << map_to_string(temple_map, false);
  return map_to_string(temple_map);
}

string generate_island_sacrifice_site()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr site_gen = std::make_shared<IslandSacrificeSiteGenerator>("", field_map);
  MapPtr site_map = site_gen->generate();
  cout << map_to_string(site_map, false);
  return map_to_string(site_map);
}

string generate_rocky_sacrifice_site()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr site_gen = std::make_shared<RockySacrificeSiteGenerator>("", field_map);
  MapPtr site_map = site_gen->generate();
  cout << map_to_string(site_map, false);
  return map_to_string(site_map);
}

string generate_overgrown_sacrifice_site()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  GeneratorPtr site_gen = std::make_shared<OvergrownSacrificeSiteGenerator>("", field_map);
  MapPtr site_map = site_gen->generate();
  cout << map_to_string(site_map, false);
  return map_to_string(site_map);
}

string generate_field()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr map = field_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);
}

string generate_forest()
{
  GeneratorPtr forest_gen = std::make_shared<ForestGenerator>("");
  MapPtr map = forest_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);
}

string generate_field_road()
{
  CardinalDirection direction = static_cast<CardinalDirection>(RNG::range(0, 3));
  int width = RNG::range(3, 6);
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr map = field_gen->generate();
  RoadGenerator road_gen(direction, width);
  MapPtr final_map = road_gen.generate(map);
  cout << map_to_string(map, false);
  return map_to_string(final_map);
}

string generate_forest_road()
{
  CardinalDirection direction = static_cast<CardinalDirection>(RNG::range(0, 3));
  int width = RNG::range(3, 6);
  GeneratorPtr forest_gen = std::make_shared<ForestGenerator>("");
  MapPtr map = forest_gen->generate();
  RoadGenerator road_gen(direction, width);
  MapPtr final_map = road_gen.generate(map);
  cout << map_to_string(map, false);
  return map_to_string(final_map);
}

string generate_field_settlement_ruins()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  SettlementRuinsGenerator sr_gen(field_map);
  MapPtr ruins_map = sr_gen.generate();
  cout << map_to_string(ruins_map, false);
  return map_to_string(ruins_map);
}

string generate_field_ruins()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  RuinsGenerator rg("fdsa", TileType::TILE_TYPE_FIELD, RuinsType::RUINS_TYPE_KEEP);
  MapPtr ruins_map = rg.generate(field_map->size());
  cout << map_to_string(ruins_map, false);
  return map_to_string(ruins_map);
}

string generate_marsh()
{
  GeneratorPtr marsh_gen = std::make_shared<MarshGenerator>("");
  MapPtr marsh_map = marsh_gen->generate();
  cout << map_to_string(marsh_map, false);
  return map_to_string(marsh_map);
}

string generate_settlement()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  SettlementGenerator settle_gen(field_map);
  MapPtr settlement_map = settle_gen.generate();
  cout << map_to_string(settlement_map, false);
  return map_to_string(settlement_map);
}

string generate_hamlet()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  HamletGenerator hamlet_gen(field_map);
  MapPtr hamlet_map = hamlet_gen.generate();
  cout << map_to_string(hamlet_map, false);
  return map_to_string(hamlet_map);
}

string generate_walled_settlement()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  WalledSettlementGenerator ws_gen(field_map);
  MapPtr ws_map = ws_gen.generate();
  cout << map_to_string(ws_map, false);
  return map_to_string(ws_map);
}

string generate_scattered_settlement()
{
  GeneratorPtr field_gen = std::make_shared<FieldGenerator>("");
  MapPtr field_map = field_gen->generate();
  ScatteredSettlementGenerator sc_gen(field_map);
  MapPtr sc_map = sc_gen.generate();
  cout << map_to_string(sc_map, false);
  return map_to_string(sc_map);  
}

string generate_dungeon()
{
  GeneratorPtr dun_gen = std::make_shared<DungeonGenerator>(""); // ha ha
  MapPtr dun_gen_map = dun_gen->generate();
  cout << map_to_string(dun_gen_map, false);
  return map_to_string(dun_gen_map);
}

string generate_spiral_dungeon()
{
  GeneratorPtr sd_gen = std::make_shared<SpiralDungeonGenerator>("");
  MapPtr sd_map = sd_gen->generate();
  cout << map_to_string(sd_map, false);
  return map_to_string(sd_map);
}

string generate_sea()
{
  GeneratorPtr sea_gen = std::make_shared<SeaGenerator>("");
  MapPtr sea_map = sea_gen->generate();
  cout << map_to_string(sea_map, false);
  return map_to_string(sea_map);
}

string generate_mine()
{
  GeneratorPtr mine_gen = std::make_shared<MineGenerator>("");
  MapPtr mine_map = mine_gen->generate();
  cout << map_to_string(mine_map, false);
  return map_to_string(mine_map);
}

string generate_castle()
{
  GeneratorPtr castle_gen = std::make_shared<CastleGenerator>("", TileType::TILE_TYPE_FIELD);
  MapPtr castle_map = castle_gen->generate();
  cout << map_to_string(castle_map, false);
  return map_to_string(castle_map);
}

string generate_world()
{
  // Add inputs for parameters later!
  WorldGenerator wg;
  MapPtr map = wg.generate();
  cout << "World map created - see html." << endl;
  return map_to_string(map);
}

void print_race_info(RaceMap& race_map, const string& id)
{
  RacePtr race = race_map[id];

  if (race)
  {
    string race_details = race->str();
    cout << race_details << endl;
  }
  else
  {
    cout << "No race with that ID found." << endl;
  }
}

void print_class_info(ClassMap& class_map, const string& id)
{
  ClassPtr current_class = class_map[id];

  if (current_class)
  {
    string class_details = current_class->str();
    cout << class_details << endl;
  }
  else
  {
    cout << "No class with that ID found." << endl;
  }
}

void race_info()
{
  string race_id = "";

  XMLConfigurationReader xml_config_reader("data/ShadowOfTheWyrm.xml");
  RaceMap races = xml_config_reader.get_races();

  cout << "Read " << races.size() << " races." << endl << endl;

  while (race_id != "-1")
  {
    cout << "Enter a race id (-1 to quit): ";
    cin >> race_id;

    print_race_info(races, race_id);
  }
}

void class_info()
{
  string class_id = "";

  XMLConfigurationReader xml_config_reader("data/ShadowOfTheWyrm.xml");
  ClassMap classes = xml_config_reader.get_classes();

  cout << "Read " << classes.size() << " classes." << endl << endl;

  while (class_id != "-1")
  {
    cout << "Enter a class id (-1 to quit): ";
    cin >> class_id;

    print_class_info(classes, class_id);
  }
}

void test_range()
{
  int min = 0;
  int max = 0;

  while (min != -1 && max != -1)
  {
    cout << "-1 for min or max to quit." << endl;
    cout << "Min: ";
    cin >> min;
    cout << "Max: ";
    cin >> max;
    cout << "Random value is: ";

    if (min != -1 && max != -1)
    {
      int random = RNG::range(min, max);

      cout << random << endl;
    }
  }

}

void test_dice()
{
  int num = 0;
  int sides = 0;

  while (num != -1 && sides != -1)
  {
    cout << "-1 for num or sides to quit." << endl;
    cout << "Num: ";
    cin >> num;
    cout << "Sides: ";
    cin >> sides;
    cout << "Random value is: ";

    if (num != -1 && sides != -1)
    {
      int dice = RNG::dice(num, sides);

      cout << dice << endl;
    }
  }
}

void test_poisson()
{
  int mean = 1;
  int times = 1;

  while (mean > 0 && times > 0)
  {
    cout << "Poisson calculator (mean <= 0 or times <= 0 to quit)" << endl;
    cout << "Mean: ";
    cin >> mean;
    cout << "Times: ";
    cin >> times;

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

      cout << "Calculated mean: " << (m / static_cast<float>(times)) << endl;
      cout << "Min, max: " << min << ", " << max << endl << endl;
    }
  }
}

void misc()
{
  int choice = 0;
  while (choice != -1)
  {
    cout << "-1 to quit." << endl;
    cout << "1. Bresenham's Line" << endl;
    cout << "2. Calendar" << endl;
    cin >> choice;
    
    switch(choice)
    {
      case 1: 
        test_bresenham_line();
        break;
      case 2:
      default:
        test_calendar();
        break;
    }
  }
}

void test_calendar()
{
  double seconds = 0;
  
  while (seconds > -1)
  {
    cout << "-1 to quit." << endl;
    cout << "Number of elapsed seconds: " << endl;
    cin >> seconds;
    
    if (seconds >= 0)
    {
      Calendar c;
      c.add_seconds(seconds);
      Date d = c.get_date();
      
      cout << "Calendar Info: " << endl;
      cout << "Time: " << d.get_hours() << ":" << d.get_minutes() << ":" << d.get_seconds() << endl;
      cout << "Day: Day " << d.get_day_of_week() << " of week, day " << d.get_day_of_month() << " of month, day " << d.get_day_of_year() << " of year" << endl;
      cout << "Month: " << d.get_month() << endl;
      cout << "Year: " << d.get_year() << endl; 
    }
  }
}
void test_bresenham_line()
{
  int start_y, start_x, end_y, end_x;
  BresenhamLine bl;
  
  start_y = start_x = end_y = end_x = 0;
  
  while (start_y != -1 && start_x != -1 && end_y != -1 && end_x != -1)
  {
    cout << "-1 for any value to quit." << endl;
    cout << "Start y: ";
    cin >> start_y;
    cout << "Start x: ";
    cin >> start_x;
    cout << "End y: ";
    cin >> end_y;
    cout << "End x: ";
    cin >> end_x;
    cout << "Line contains points: " << endl;

    if (start_y != -1 && start_x != -1 && end_y != -1 && end_x != -1)
    {
      vector<Coordinate> coords = bl.get_points_in_line(start_y, start_x, end_y, end_x);
      
      for (const Coordinate& c : coords)
      {
        cout << "(" << c.first << "," << c.second << ")" << endl;
      }
    }
  }  
}

void print_skill_name()
{
  AwarenessSkill awareness;
  string awareness_skill_name = StringTable::get(awareness.get_skill_name_sid());
  cout << awareness_skill_name << endl;
}

void test_rng()
{
  int option = 0;
  while(option != -1)
  {
    cout << "RNG Test!" << endl << endl;
    cout << "1. Range" << endl;
    cout << "2. Dice" << endl;
    cout << "3. Poisson" << endl;
    cout << "-1. Quit" << endl << endl;
    cin >> option;

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

void settlement_maps()
{
  string map;
  int settlement_map = 0;
  
  while (settlement_map != -1)
  {
    cout << "Enter a map number (-1 to quit):" << endl << endl;
    cout << "1. Settlement" << endl;
    cout << "2. Hamlet" << endl;
    cout << "3. Walled Settlement" << endl;
    cout << "4. Scattered Settlement" << endl;
    
    cin >> settlement_map;
    
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
  string map;
  int city_adjacent_map = 0;
  
  while (city_adjacent_map != -1)
  {
    cout << "Enter a map number (-1 to quit)" << endl << endl;
    cout << "1. Ordered Graveyard" << endl;
    cout << "2. Scattered Graveyard" << endl;
    cout << "3. Keep" << endl;
    cout << "4. Churches, Temples, Sites of Death" << endl;
    cout << "5. Crypt" << endl;
    cout << "6. Mine" << endl;
    cout << "7. Castle" << endl;

    cin >> city_adjacent_map;
    
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
        output_map(map, "castle.html");
        break;
      default:
        break;
    }
  }
}

void church_maps()
{
  string map;
  int church_map = 0;
  
  while (church_map != -1)
  {
    cout << "Enter a map number (-1 to quit)" << endl << endl;
    cout << "1. Cathedral (Celeste)" << endl;
    cout << "2. Fortified Church (Aurelion)" << endl;
    cout << "3. Simple Church (The Lady)" << endl;
    cout << "4. Grand Temple (Vedere)" << endl;
    cout << "5. Snaking Temple (Voros)" << endl;
    cout << "6. Simple Temple (The Trickster)" << endl;
    cout << "7. Island Sacrifice Site (Shiver)" << endl;
    cout << "8. Rocky Sacrifice Site (Urgoth)" << endl;
    cout << "9. Overgrown Sacrifice Site (Sceadugenga)" << endl;
    cin >> church_map;
    
    switch(church_map)
    {
      case 1: 
        map = generate_cathedral();
        output_map(map, "cathedral.html");
        break;
      case 2:
        map = generate_fortified_church();
        output_map(map, "fortified_church.html");
        break;
      case 3:
        map = generate_simple_church();
        output_map(map, "simple_church.html");
        break;
      case 4:
        map = generate_grand_temple();
        output_map(map, "grand_temple.html");
        break;
      case 5:
        map = generate_snaking_temple();
        output_map(map, "snaking_temple.html");
        break;
      case 6:
        map = generate_simple_temple();
        output_map(map, "simple_temple.html");
        break;
      case 7:
        map = generate_island_sacrifice_site();
        output_map(map, "island_site.html");
        break;
      case 8:
        map = generate_rocky_sacrifice_site();
        output_map(map, "rocky_site.html");
        break;
      case 9:
        map = generate_overgrown_sacrifice_site();
        output_map(map, "overgrown_site.html");
        break;
      default:
        break;
    }
  }  
}

int main(int argc, char** argv)
{
  string map;
  int option = 0;
  XML::initialize();
  initialize_settings();
  
  // Set up the items, so that I can see what gets generated...
  ShadowOfTheWyrmEngine engine;
  engine.setup_game();

  while (option != -1)
  {
    cout << "Map Generator!" << endl << endl;
    cout << "0. RNG" << endl;
    cout << "1. Field" << endl;
    cout << "2. Forest" << endl;
    cout << "3. Ruins (Field)" << endl;
    cout << "4. Settlements" << endl;
    cout << "5. Settlement Ruins (Field)" << endl;
    cout << "6. Marsh" << endl;
    cout << "7. Regular Dungeon" << endl;
    cout << "8. Spiral Dungeon" << endl;
    cout << "9. Road (Field)" << endl;
    cout << "10. Road (Forest)" << endl;
    cout << "11. Sea" << endl;
    cout << "12. World" << endl;
    cout << "13. Cavern" << endl;
    cout << "14. Quick skill name test" << endl;
    cout << "15. Display race info" << endl;
    cout << "16. Display class info" << endl;
    cout << "17. City-adjacent maps" << endl;
    cout << "18. Misc" << endl;
    cout << "-1. Quit" << endl << endl;
    cin >> option;

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
        print_skill_name();
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
}
