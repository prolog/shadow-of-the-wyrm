#include "XMLMapReaders.hpp"

using namespace std;

// XMLMapsReader reads in all the custom maps from the data/maps
// directory.
vector<MapPtr> XMLMapsReader::get_custom_maps()
{
  vector<MapPtr> custom_maps;

  return custom_maps;
}


// XMLMapReader reads in the details from a CustomMap element, and
// creates a MapPtr based on it.
MapPtr XMLMapReader::get_custom_map(const XMLNode& custom_map_node)
{
  MapPtr custom_map;

  return custom_map;
}

