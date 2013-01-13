#pragma once
#include "Map.hpp"
#include "XMLDataStructures.hpp"

class XMLMapTilesReader
{
  public:
    TilesContainer parse_tiles(const XMLNode& tiles_node, const int rows, const int cols);
};

// Maps individual characters from the XML file into tiles as would be found
// in the actual TileMap in the actual Map.
class XMLTileMapper
{
  public:
    TilePtr create_tile(const char xml_tile);
};

