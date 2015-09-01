#include "FileConstants.hpp"

using namespace std;

FileConstants::FileConstants()
{
}

FileConstants::~FileConstants()
{
}

const string FileConstants::XML_CONFIGURATION_FILE = "data/ShadowOfTheWyrm.xml";
const string FileConstants::WORLD_MAP_AREAS_FILE = "data/maps/world/WorldMapAreas.xml";
const string FileConstants::SAVEFILE_PATTERN = ".(sws)$"; // Savefile regex pattern required by boost::filesystem
const string FileConstants::CUSTOM_MAPS_DIRECTORY = "data/maps/";
const string FileConstants::CUSTOM_MAPS_PATTERN = ".(xml)$";
