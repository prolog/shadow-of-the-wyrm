#pragma once
#include <vector>
#include "Map.hpp"
#include "XMLDataStructures.hpp"

// Reads all the map .xml files from data/maps.
class XMLMapsReader
{
  public:
    std::vector<MapPtr> get_custom_maps();
};

// Reads an individual map from the given <CustomMap> element.
class XMLMapReader
{
  public:
    MapPtr get_custom_map(const XMLNode& custom_map_node);
};

