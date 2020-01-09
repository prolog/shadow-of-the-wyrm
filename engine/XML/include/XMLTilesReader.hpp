#pragma once
#include <vector>
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"

class DisplayTile;

class XMLTilesReader : public XMLReader
{
  public:
    std::vector<DisplayTile> get_tiles(const XMLNode& xml_configuration_tiles_node, const bool force_ascii);

  protected:
    void parse_tile_text_details(std::vector<DisplayTile>&, const XMLNode& tile_node, const bool force_ascii);
};
