#include "XMLConfigurationReader.hpp"
#include <iostream>

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

void XMLConfigurationReader::initialize_parser()
{
  XMLFileReader reader;
  root = reader.get_xml_from_file("data/SavageLands.xml");
}


