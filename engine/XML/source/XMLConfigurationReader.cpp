#include <utility>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include "CreatureGenerationValues.hpp"
#include "DisplayTile.hpp"
#include "Setting.hpp"
#include "XMLMapReaders.hpp"
#include "XMLConfigurationReader.hpp"

using namespace std;
using namespace boost::filesystem;

XMLConfigurationReader::XMLConfigurationReader(const string& xml_filename, const string& cr_filename, const string& it_filename)
: filename(xml_filename), creatures_filename(cr_filename), items_filename(it_filename)
{
  XML::initialize();

  // Generally, this will always be provided, but to prevent unnecessary loading
  // in MapTester, it may also be empty.
  if (!xml_filename.empty())
  {
    initialize_parser(xml_filename);
  }
}

XMLConfigurationReader::~XMLConfigurationReader()
{
  XML::tear_down();
}

DeityMap XMLConfigurationReader::get_deities()
{
  XMLNode deities_node = XMLUtils::get_next_element_by_local_name(root, "Deities");
  DeityMap deities = deities_reader.get_deities(deities_node);
  return deities;  
}

ClassMap XMLConfigurationReader::get_classes()
{
  XMLNode classes_node = XMLUtils::get_next_element_by_local_name(root, "Classes");
  ClassMap classes = classes_reader.get_classes(classes_node);
  return classes;
}

map<int, CalendarDay> XMLConfigurationReader::get_calendar_days()
{
  XMLNode calendar_node = XMLUtils::get_next_element_by_local_name(root, "Calendar");
  return calendar_reader.get_calendar_days(calendar_node);
}

StartingLocationMap XMLConfigurationReader::get_starting_locations()
{
  XMLNode starting_locations_node = XMLUtils::get_next_element_by_local_name(root, "StartingLocations");
  return sl_reader.get_starting_locations(starting_locations_node);
}

pair<CreatureMap, CreatureGenerationValuesMap> XMLConfigurationReader::get_creatures()
{
  XMLNode prev_config = root;
  initialize_parser(creatures_filename);
  XMLNode creatures_node = XMLUtils::get_next_element_by_local_name(root, "Creatures");
  pair<CreatureMap, CreatureGenerationValuesMap> creatures = creatures_reader.get_creatures(creatures_node);
  root = prev_config;

  return creatures;
}

SpellMap XMLConfigurationReader::get_spells()
{
  XMLNode spells_node = XMLUtils::get_next_element_by_local_name(root, "Spells");
  SpellMap spells = spells_reader.get_spells(spells_node);
  return spells;
}

map<string, string> XMLConfigurationReader::get_spritesheets()
{
  XMLNode spritesheets_node = XMLUtils::get_next_element_by_local_name(root, "Spritesheets");
  map<string, string> spritesheets = spritesheets_reader.get_spritesheets(spritesheets_node);
  return spritesheets;
}

pair<ItemMap, GenerationValuesMap> XMLConfigurationReader::get_items()
{
  XMLNode prev_config = root;
  initialize_parser(items_filename);
  XMLNode items_node = XMLUtils::get_next_element_by_local_name(root, "Items");
  pair<ItemMap, GenerationValuesMap> items = items_reader.get_items(items_node);
  root = prev_config;

  return items;
}

FeatureSymbolMap XMLConfigurationReader::get_feature_symbols()
{
  XMLNode features_node = XMLUtils::get_next_element_by_local_name(root, "AllFeatures");
  XMLNode base_features_node = XMLUtils::get_next_element_by_local_name(features_node, "BaseFeatures");
  FeatureSymbolMap fsm = bf_reader.get_feature_symbols(base_features_node);

  return fsm;
}

FeatureMap XMLConfigurationReader::get_configurable_features()
{
  XMLNode features_node = XMLUtils::get_next_element_by_local_name(root, "AllFeatures");
  XMLNode config_features_node = XMLUtils::get_next_element_by_local_name(features_node, "ConfigurableFeatures");
  FeatureMap cfm = cf_reader.get_configurable_features(config_features_node);
  return cfm;
}

map<string, string> XMLConfigurationReader::get_scripts()
{
  XMLNode scripts_node = XMLUtils::get_next_element_by_local_name(root, "Scripts");
  map<string, string> scripts = scripts_reader.get_scripts(scripts_node);
  return scripts;
}

RaceMap XMLConfigurationReader::get_races()
{
  XMLNode races_node = XMLUtils::get_next_element_by_local_name(root, "Races");
  RaceMap races = races_reader.get_races(races_node);
  return races;
}

vector<DisplayTile> XMLConfigurationReader::get_tile_info()
{
  XMLNode tiles_node = XMLUtils::get_next_element_by_local_name(root, "Tiles");
  vector<DisplayTile> tile_info = tiles_reader.get_tiles(tiles_node);
  return tile_info;
}

vector<TrapPtr> XMLConfigurationReader::get_trap_info()
{
  XMLNode traps_node = XMLUtils::get_next_element_by_local_name(root, "Traps");
  vector<TrapPtr> trap_info = traps_reader.get_traps(traps_node);
  return trap_info;
}

vector<MapPtr> XMLConfigurationReader::get_custom_maps(const string& directory, const string& filename_pattern)
{
  vector<MapPtr> custom_maps;
  XMLMapReader map_reader;

  directory_iterator end_it;
  boost::regex e(filename_pattern);

  for (directory_iterator d_it(directory); d_it != end_it; d_it++)
  {
    string filename = d_it->path().string();

    if (boost::regex_search(filename, e))
    {
      initialize_parser(filename);

      if (!root.is_null())
      {
        string xmlns = XMLUtils::get_attribute_value(root, "xmlns");
        XML::set_namespace(xmlns); // these use a different ns than the main shadow of the wyrm xml.
      }

      MapPtr custom_map = map_reader.get_custom_map(root);

      if (custom_map)
      {
        custom_maps.push_back(custom_map);
      }
    }
  }

  return custom_maps;
}

void XMLConfigurationReader::set_new_file(const string& xml_filename)
{
  initialize_parser(xml_filename);
}

void XMLConfigurationReader::initialize_parser(const string& xml_filename)
{
  XMLFileReader reader;
  root = reader.get_xml_from_file(xml_filename);
}


