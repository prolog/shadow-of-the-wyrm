#pragma once
#include "Deity.hpp"
#include "XMLReader.hpp"

class XMLNode;

class XMLDeitiesReader : public XMLReader
{
  public:
    DeityMap get_deities(const XMLNode& xml_configuration_deities_node);

  protected:
    DeityPtr parse_deity(const XMLNode& deity_node);
    void     parse_dislikes(const XMLNode& dislikes_node, Deity& deity);
    void     parse_likes(const XMLNode& likes_node, Deity& deity);
    void     parse_burial_races(const XMLNode& burial_races_node, Deity& deity);
    void     parse_generator_filters(const XMLNode& generator_filters_node, Deity& deity);
    void     parse_crowning_gifts(const XMLNode& crowning_node, Deity& deity);
    void     parse_summons(const XMLNode& summons_node, Deity& deity);
};
