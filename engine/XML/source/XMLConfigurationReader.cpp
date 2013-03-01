#include <utility>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include "CreatureGenerationValues.hpp"
#include "DisplayTile.hpp"
#include "XMLMapReaders.hpp"
#include "XMLConfigurationReader.hpp"

using namespace std;
using namespace boost::filesystem;

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

pair<ItemMap, GenerationValuesMap> XMLConfigurationReader::get_items()
{
  XMLNode items_node = XMLUtils::get_next_element_by_local_name(root, "Items");
  pair<ItemMap, GenerationValuesMap> items = items_reader.get_items(items_node);
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
        XML::set_namespace(xmlns); // these use a different ns than the main savage lands xml.
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


