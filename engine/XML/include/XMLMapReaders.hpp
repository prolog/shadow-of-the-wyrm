#pragma once
#include <map>
#include <vector>
#include "Map.hpp"
#include "XMLDataStructures.hpp"

// Reads an individual map from the given <CustomMap> element.
class XMLMapReader
{
  public:
    MapPtr get_custom_map(const XMLNode& custom_map_node);

  protected:
    Dimensions parse_dimensions(const XMLNode& dimensions_node);
    TilesMap parse_tiles(const XMLNode& tiles_node, const int rows, const int cols);
    Coordinate parse_coordinate(const XMLNode& coord_node);
};

// Maps individual characters from the XML file into tiles as would be found
// in the actual TileMap in the actual Map.
class XMLTileMapper
{
  public:
    TilePtr create_tile(const char xml_tile);
};
