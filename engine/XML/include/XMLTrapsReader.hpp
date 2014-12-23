#pragma once
#include <vector>
#include "XMLReader.hpp"
#include "XMLDataStructures.hpp"
#include "Trap.hpp"

class DisplayTile;

class XMLTrapsReader : public XMLReader
{
  public:
    std::vector<TrapPtr> get_traps(const XMLNode& xml_config_traps_node);

  protected:
    void parse_trap(const XMLNode& trap_node, TrapPtr trap);
};
