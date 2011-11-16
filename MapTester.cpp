#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include "RNG.hpp"
#include "CavernGenerator.hpp"
#include "FieldGenerator.hpp"
#include "ForestGenerator.hpp"
#include "RoadGenerator.hpp"
#include "RuinsGenerator.hpp"
#include "MarshGenerator.hpp"
#include "SettlementGenerator.hpp"
#include "KeepRuinsGenerator.hpp"
#include "SettlementRuinsGenerator.hpp"
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

// Terrain generation function prototypes
string generate_field();
string generate_field_ruins();
string generate_field_settlement_ruins();
string generate_forest();
string generate_marsh();
string generate_settlement();
string generate_spiral_dungeon();
string generate_field_road();
string generate_forest_road();
string generate_world();
string generate_cavern();
void   initialize_settings();
void   print_skill_name();
void   race_info();
void   class_info();
void   print_race_info(RaceMap& race_map, const string& id);
void   print_class_info(ClassMap& class_map, const string& id);

void initialize_settings()
{
  StringTable::load("savagelandstext_en.ini");
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
    map_s = map_s + "<html><head><title>SL Map</title></head><body>";
    end_tag = "</font>";
  }

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr tile = map->at(row, col);
      TileType type = tile->get_tile_type();

      switch(type)
      {
        case TILE_TYPE_FIELD:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
          tile_ascii = ".";
          break;
        case TILE_TYPE_BUSH:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
          tile_ascii = "\"";
          break;
        case TILE_TYPE_WEEDS:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#008000\">";
          tile_ascii = "\"";
          break;
        case TILE_TYPE_FOREST:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
          tile_ascii = "&";
          break;
        case TILE_TYPE_MOUNTAINS:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#C0C0C0\">";
          tile_ascii = "^";
          break;
        case TILE_TYPE_TREE:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FF00\">";
          tile_ascii = "T";
          break;
        case TILE_TYPE_CAIRN:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#808080\">";
          tile_ascii = "*";
          break;
        case TILE_TYPE_SPRINGS:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#00FFFF\">";
          tile_ascii = "v";
          break;
        case TILE_TYPE_RIVER:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#0000FF\">";
          tile_ascii = "~";
          break;
        case TILE_TYPE_DUNGEON:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#C0C0C0\">";
          tile_ascii = ".";
          break;
        case TILE_TYPE_ROCK:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#808080\">";
          tile_ascii = "#";
          break;
        case TILE_TYPE_SCRUB:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#CCFF00\">";
          tile_ascii = ".";
          break;
        case TILE_TYPE_ROAD:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#A52A2A\">";
          tile_ascii = ".";
          break;
        case TILE_TYPE_MARSH:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"008000\">";
          tile_ascii = "~";
          break;
        case TILE_TYPE_REEDS:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#A52A2A\">";
          tile_ascii = "|";
          break;
        case TILE_TYPE_SEA:
          if (use_html) start_tag = "<font face=\"Courier\" color=\"#0000FF\">";
          tile_ascii = "~";
          break;
        default:
          tile_ascii = "?";
          break;
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
  GeneratorPtr cavern_gen = GeneratorPtr(new CavernGenerator());
  MapPtr map = cavern_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);
}

string generate_field()
{
  GeneratorPtr field_gen = GeneratorPtr(new FieldGenerator());
  MapPtr map = field_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);
}

string generate_forest()
{
  GeneratorPtr forest_gen = GeneratorPtr(new ForestGenerator());
  MapPtr map = forest_gen->generate();
  cout << map_to_string(map, false);
  return map_to_string(map);
}

string generate_field_road()
{
  CardinalDirection direction = static_cast<CardinalDirection>(RNG::range(0, 3));
  int width = RNG::range(3, 6);
  GeneratorPtr field_gen = GeneratorPtr(new FieldGenerator());
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
  GeneratorPtr forest_gen = GeneratorPtr(new ForestGenerator());
  MapPtr map = forest_gen->generate();
  RoadGenerator road_gen(direction, width);
  MapPtr final_map = road_gen.generate(map);
  cout << map_to_string(map, false);
  return map_to_string(final_map);
}

string generate_field_settlement_ruins()
{
  GeneratorPtr field_gen = GeneratorPtr(new FieldGenerator());
  MapPtr field_map = field_gen->generate();
  SettlementRuinsGenerator sr_gen;
  MapPtr ruins_map = sr_gen.generate(field_map);
  cout << map_to_string(ruins_map, false);
  return map_to_string(ruins_map);
}

string generate_field_ruins()
{
  GeneratorPtr field_gen = GeneratorPtr(new FieldGenerator());
  MapPtr field_map = field_gen->generate();
  MapPtr ruins_map = RuinsGenerator::generate(field_map, RUINS_TYPE_KEEP);
  cout << map_to_string(ruins_map, false);
  return map_to_string(ruins_map);
}

string generate_marsh()
{
  GeneratorPtr marsh_gen = GeneratorPtr(new MarshGenerator());
  MapPtr marsh_map = marsh_gen->generate();
  cout << map_to_string(marsh_map, false);
  return map_to_string(marsh_map);
}

string generate_settlement()
{
  GeneratorPtr field_gen = GeneratorPtr(new FieldGenerator());
  SettlementGenerator settle_gen;
  MapPtr field_map = field_gen->generate();
  MapPtr settlement_map = settle_gen.generate(field_map);
  cout << map_to_string(settlement_map, false);
  return map_to_string(settlement_map);
}

string generate_spiral_dungeon()
{
  GeneratorPtr sd_gen = GeneratorPtr(new SpiralDungeonGenerator());
  MapPtr sd_map = sd_gen->generate();
  cout << map_to_string(sd_map, false);
  return map_to_string(sd_map);
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

  XMLConfigurationReader xml_config_reader("data/SavageLands.xml");
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

  XMLConfigurationReader xml_config_reader("data/SavageLands.xml");
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

void print_skill_name()
{
  Awareness awareness;
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

  while (option != -1)
  {
    cout << "Map Generator!" << endl << endl;
    cout << "0. RNG" << endl;
    cout << "1. Field" << endl;
    cout << "2. Forest" << endl;
    cout << "3. Ruins (Field)" << endl;
    cout << "4. Settlement (Field)" << endl;
    cout << "5. Settlement Ruins (Field)" << endl;
    cout << "6. Marsh" << endl;
    cout << "7. Regular Dungeon (TODO)" << endl;
    cout << "8. Spiral Dungeon" << endl;
    cout << "9. Road (Field)" << endl;
    cout << "10. Road (Forest)" << endl;
    cout << "11. World" << endl;
    cout << "12. Cavern" << endl;
    cout << "13. Quick skill name test" << endl;
    cout << "14. Display race info" << endl;
    cout << "15. Display class info" << endl;
    cout << "-1. Quit" << endl << endl;
    cin >> option;
    //option = 1;

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
        map = generate_settlement();
        output_map(map, "settlement_test.html");
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
        map = generate_world();
        output_map(map, "world_test.html");
        break;
      case 12:
        map = generate_cavern();
        output_map(map, "cavern_test.html");
        break;
      case 13:
        print_skill_name();
        break;
      case 14:
        race_info();
        break;
      case 15:
        class_info();
        break;
      default:
        break;
    }
  }

  XML::tear_down();
}
