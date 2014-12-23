#pragma once
#include <string>
#include "XMLClassesReader.hpp"
#include "XMLCreaturesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLDeitiesReader.hpp"
#include "XMLFileReader.hpp"
#include "XMLItemsReaders.hpp"
#include "XMLRacesReader.hpp"
#include "XMLSpellsReader.hpp"
#include "XMLTilesReader.hpp"
#include "XMLTrapsReader.hpp"
#include "XMLScriptsReader.hpp"
#include "Race.hpp"
#include "Class.hpp"

// The XMLConfigurationReader provides methods for reading in data structures
// based on XML configuration files of various sorts.  It is the responsibility
// of the caller to know when to "switch" files by means of "set_new_file".
class XMLConfigurationReader
{
  public:
    XMLConfigurationReader(const std::string& xml_filename);
    ~XMLConfigurationReader();

    void set_new_file(const std::string& xml_filename);

    DeityMap get_deities();
    RaceMap get_races();
    ClassMap get_classes();
    std::pair<CreatureMap, CreatureGenerationValuesMap> get_creatures();
    SpellMap get_spells();
    std::pair<ItemMap, GenerationValuesMap> get_items();    
    std::map<std::string, std::string> get_scripts();
    std::vector<DisplayTile> get_tile_info();
    std::vector<TrapPtr> get_trap_info();
    std::vector<MapPtr> get_custom_maps(const std::string& directory, const std::string& filename_pattern);

  protected:
    void initialize_parser(const std::string& xml_filename);

    // Member variables for the base XML configuration file parsing.
    std::string filename;
    XMLNode root;

    // Member variables for reading the various XML nodes and setting the data into world objects.
    XMLClassesReader classes_reader;
    XMLDeitiesReader deities_reader;
    XMLCreaturesReader creatures_reader;
    XMLItemsReader items_reader;
    XMLRacesReader races_reader;
    XMLSpellsReader spells_reader;
    XMLTilesReader tiles_reader;
    XMLTrapsReader traps_reader;
    XMLScriptsReader scripts_reader;
};
