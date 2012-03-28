#pragma once
#include "Deity.hpp"

class XMLNode;

class XMLDeitiesReader
{
  public:
    DeityMap get_deities(const XMLNode& xml_configuration_deities_node);

  protected:
    DeityPtr parse_deity(const XMLNode& deity_node);
};
