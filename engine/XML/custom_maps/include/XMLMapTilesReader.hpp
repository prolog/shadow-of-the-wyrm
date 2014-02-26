#pragma once
#include "Map.hpp"
#include "TileGenerator.hpp"
#include "XMLDataStructures.hpp"

class XMLMapTilesReader
{
  public:
    TilesContainer parse_tiles(const XMLNode& tiles_node, const int rows, const int cols);
};

