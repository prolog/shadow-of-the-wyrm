#include "XMLConfigurationReader.hpp"
#include <iostream>
#include <vector>
#include "DisplayTile.hpp"

using namespace std;

XMLConfigurationReader::XMLConfigurationReader(const std::string& xml_filename)
: filename(xml_filename)
{
  initialize_parser();
}

ClassMap XMLConfigurationReader::get_classes()
{
  XMLNode classes_node = XMLUtils::get_next_element_by_local_name(root, "Classes");
  ClassMap classes = classes_reader.get_classes(classes_node);
  return classes;
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

void XMLConfigurationReader::initialize_parser()
{
  XMLFileReader reader;
  root = reader.get_xml_from_file("data/SavageLands.xml");
}


