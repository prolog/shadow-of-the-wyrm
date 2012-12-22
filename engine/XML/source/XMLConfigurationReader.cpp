#include "XMLConfigurationReader.hpp"
#include <utility>
#include <vector>
#include "CreatureGenerationValues.hpp"
#include "DisplayTile.hpp"
#include "XMLMapReaders.hpp"

using namespace std;

XMLConfigurationReader::XMLConfigurationReader(const std::string& xml_filename)
: filename(xml_filename)
{
  initialize_parser(xml_filename);
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

pair<CreatureMap, CreatureGenerationValuesMap> XMLConfigurationReader::get_creatures()
{
  XMLNode creatures_node = XMLUtils::get_next_element_by_local_name(root, "Creatures");
  pair<CreatureMap, CreatureGenerationValuesMap> creatures = creatures_reader.get_creatures(creatures_node);
  return creatures;
}

ItemMap XMLConfigurationReader::get_items()
{
  XMLNode items_node = XMLUtils::get_next_element_by_local_name(root, "Items");
  ItemMap items = items_reader.get_items(items_node);
  return items;
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

vector<MapPtr> XMLConfigurationReader::get_custom_maps()
{
  XMLMapsReader maps_reader;

  return maps_reader.get_custom_maps();
}

void XMLConfigurationReader::initialize_parser(const string& xml_filename)
{
  XMLFileReader reader;
  root = reader.get_xml_from_file(xml_filename);
}


