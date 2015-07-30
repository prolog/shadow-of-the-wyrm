#pragma once
#include "XMLDataStructures.hpp"
#include <vector>

class DigChances;
class DisplayTile;

class XMLTilesReader
{
  public:
    std::vector<DisplayTile> get_tiles(const XMLNode& xml_configuration_tiles_node);

  protected:
    void parse_tile_text_details(std::vector<DisplayTile>&, const XMLNode& tile_node);
    void parse_dig_chances(DigChances& dc, const XMLNode& dig_chances_node);
};
