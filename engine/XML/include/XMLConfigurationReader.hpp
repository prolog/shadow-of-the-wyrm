#pragma once
#include <string>
#include "XMLClassesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLFileReader.hpp"
#include "XMLItemsReaders.hpp"
#include "XMLRacesReader.hpp"
#include "XMLTilesReader.hpp"
#include "Race.hpp"
#include "Class.hpp"

class XMLConfigurationReader
{
  public:
    XMLConfigurationReader(const std::string& xml_filename);

    RaceMap get_races();
    ClassMap get_classes();
    ItemMap get_items();    
    std::vector<DisplayTile> get_tile_info();

  protected:
    void initialize_parser();

    // Member variables for the base XML configuration file parsing.
    //xercesc::XercesDOMParser* parser;
    std::string filename;
    XMLNode root;

    // Member variables for reading the various XML nodes and setting the data into world objects.
    XMLClassesReader classes_reader;
    XMLItemsReader items_reader;
    XMLRacesReader races_reader;
    XMLTilesReader tiles_reader;
};
