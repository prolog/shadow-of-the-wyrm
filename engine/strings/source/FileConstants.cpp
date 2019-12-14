#include "FileConstants.hpp"

using namespace std;

FileConstants::FileConstants()
{
}

FileConstants::~FileConstants()
{
}

const string FileConstants::SAVEFILE_PATTERN = ".(sws)$"; // Savefile regex pattern required by boost::filesystem
const string FileConstants::CUSTOM_MAPS_DIRECTORY = "data/maps/";
const string FileConstants::CUSTOM_MAPS_PATTERN = ".(xml)$";
