#pragma once
#include "Deity.hpp"

class XMLNode;

class XMLDeitiesReader
{
  public:
    DeityMap get_deities(const XMLNode& xml_configuration_deities_node);

  protected:
    DeityPtr parse_deity(const XMLNode& deity_node);
    void     parse_dislikes(const XMLNode& dislikes_node, DeityPtr deity);
    void     parse_crowning_gifts(const XMLNode& crowning_node, DeityPtr deity);
};
