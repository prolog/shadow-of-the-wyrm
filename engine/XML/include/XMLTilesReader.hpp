#pragma once
#include "XMLDataStructures.hpp"
#include <vector>

class DisplayTile;

class XMLTilesReader
{
  public:
    std::vector<DisplayTile> get_tiles(const XMLNode& xml_configuration_tiles_node);

  protected:
    void parse_tile_text_details(std::vector<DisplayTile>&, const XMLNode& tile_node);
};
