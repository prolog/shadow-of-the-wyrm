#pragma once
#include "TileGenerator.hpp"

// Maps individual characters from the XML file into tiles as would be found
// in the actual TileMap in the actual Map.
class XMLTileMapper
{
  public:
    virtual TilePtr create_tile(const char xml_tile);

  protected:
    TileGenerator tg;
};


