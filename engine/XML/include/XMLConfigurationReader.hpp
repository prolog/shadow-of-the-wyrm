#pragma once
#include <vector>
#include <string>
#include "XMLClassesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLFileReader.hpp"
#include "XMLRacesReader.hpp"
#include "Race.hpp"
#include "Class.hpp"

class XMLConfigurationReader
{
  public:
    XMLConfigurationReader(const std::string& xml_filename);

    RaceMap get_races();
    ClassMap get_classes();
    // std::vector<Item> get_items();

  protected:
    void initialize_parser();

    // Member variables for the base XML configuration file parsing.
    //xercesc::XercesDOMParser* parser;
    std::string filename;
    XMLNode root;

    // Member variables for reading the various XML nodes and setting the data into world objects.
    XMLClassesReader classes_reader;
    XMLRacesReader races_reader;
};
