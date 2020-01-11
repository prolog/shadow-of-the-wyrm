#pragma once
#include <string>
#include "XMLBaseFeatureReader.hpp"
#include "XMLConfigurableFeatureReader.hpp"
#include "XMLCalendarReader.hpp"
#include "XMLClassesReader.hpp"
#include "XMLCreaturesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLDeitiesReader.hpp"
#include "XMLFileReader.hpp"
#include "XMLItemsReaders.hpp"
#include "XMLRacesReader.hpp"
#include "XMLSpellsReader.hpp"
#include "XMLSpritesheetsReader.hpp"
#include "XMLStartingLocationsReader.hpp"
#include "XMLTilesReader.hpp"
#include "XMLTrapsReader.hpp"
#include "XMLScriptsReader.hpp"
#include "Race.hpp"
#include "Class.hpp"
#include "ConfigurableFeature.hpp"

// The XMLConfigurationReader provides methods for reading in data structures
// based on XML configuration files of various sorts.  It is the responsibility
// of the caller to know when to "switch" files by means of "set_new_file".
class XMLConfigurationReader
{
  public:
    XMLConfigurationReader(const std::string& xml_filename, const std::string& cr_file, const std::string& it_file);
    ~XMLConfigurationReader();

    void set_new_file(const std::string& xml_filename);

    std::map<int, CalendarDay> get_calendar_days();
    StartingLocationMap get_starting_locations();
    DeityMap get_deities();
    RaceMap get_races();
    ClassMap get_classes();
    std::pair<CreatureMap, CreatureGenerationValuesMap> get_creatures(const bool force_ascii);
    SpellMap get_spells();
    std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>> get_spritesheets();
    std::pair<ItemMap, GenerationValuesMap> get_items(const bool force_ascii);    
    FeatureSymbolMap get_feature_symbols(const bool force_ascii);
    FeatureMap get_configurable_features(const bool force_ascii);
    std::map<std::string, std::string> get_scripts();
    std::vector<DisplayTile> get_tile_info(const bool force_ascii);
    std::vector<TrapPtr> get_trap_info(const bool force_ascii);
    std::vector<MapPtr> get_custom_maps(const std::string& directory, const std::string& filename_pattern);

  protected:
    void initialize_parser(const std::string& xml_filename);

    // Member variables for the base XML configuration file parsing.
    std::string filename;
    std::string creatures_filename;
    std::string items_filename;

    XMLNode root;

    // Member variables for reading the various XML nodes and setting the data into world objects.
    XMLCalendarReader calendar_reader;
    XMLStartingLocationsReader sl_reader;
    XMLClassesReader classes_reader;
    XMLDeitiesReader deities_reader;
    XMLCreaturesReader creatures_reader;
    XMLItemsReader items_reader;
    XMLRacesReader races_reader;
    XMLSpellsReader spells_reader;
    XMLSpritesheetsReader spritesheets_reader;
    XMLTilesReader tiles_reader;
    XMLTrapsReader traps_reader;
    XMLScriptsReader scripts_reader;
    XMLBaseFeatureReader bf_reader;
    XMLConfigurableFeatureReader cf_reader;
};

