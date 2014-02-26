#include "CustomAreaGenerator.hpp"
#include "XMLFileReader.hpp"
#include "XMLWorldMapReader.hpp"

using namespace std;

// The CustomAreaGenerator assumes responsibility for creating/destroying XML
// data structures (to reduce the game's memory footprint).  In practical
// terms, this means that the data structures can't already be active -
// it is assumed that they have been previous been destroyed by a call to
// XML::tear_down().
CustomAreaGenerator::CustomAreaGenerator(const string& map_filename)
{
  filename = map_filename;

  XML::initialize();
}

CustomAreaGenerator::~CustomAreaGenerator()
{
  XML::tear_down();
}

// Overlay custom areas onto the world map.
//
// Read in and set the tiles, and run any necessary scripts: delegate this
// task to the XMLWorldMapReader.
void CustomAreaGenerator::overlay_custom_areas(MapPtr map)
{
  XMLFileReader reader;
  XMLNode root = reader.get_xml_from_file("data/maps/world/WorldMapAreas.xml");
  string xmlns = XMLUtils::get_attribute_value(root, "xmlns");
  XML::set_namespace(xmlns); // these use a different ns than the default.
  XMLWorldMapReader wmr;
  wmr.read_world_map(map, root);
}
