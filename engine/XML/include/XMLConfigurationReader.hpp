#pragma once
#include <string>
#include "XMLClassesReader.hpp"
#include "XMLCreaturesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLDeitiesReader.hpp"
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

    DeityMap get_deities();
    RaceMap get_races();
    ClassMap get_classes();
    std::pair<CreatureMap, CreatureGenerationValuesMap> get_creatures();
    ItemMap get_items();    
    std::vector<DisplayTile> get_tile_info();
    std::vector<MapPtr> get_custom_maps();

  protected:
    void initialize_parser();

    // Member variables for the base XML configuration file parsing.
    //xercesc::XercesDOMParser* parser;
    std::string filename;
    XMLNode root;

    // Member variables for reading the various XML nodes and setting the data into world objects.
    XMLClassesReader classes_reader;
    XMLDeitiesReader deities_reader;
    XMLCreaturesReader creatures_reader;
    XMLItemsReader items_reader;
    XMLRacesReader races_reader;
    XMLTilesReader tiles_reader;
};
