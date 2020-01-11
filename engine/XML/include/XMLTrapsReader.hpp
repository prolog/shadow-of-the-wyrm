#pragma once
#include <vector>
#include "Features.hpp"
#include "XMLReader.hpp"
#include "XMLDataStructures.hpp"

class DisplayTile;

class XMLTrapsReader : public XMLReader
{
  public:
    std::vector<TrapPtr> get_traps(const XMLNode& xml_config_traps_node, const bool force_ascii);

  protected:
    void parse_trap(const XMLNode& trap_node, TrapPtr trap, const bool force_ascii);
};
