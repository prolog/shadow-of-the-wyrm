#pragma once
#include <utility>
#include "Creature.hpp"
#include "CreatureGenerationValues.hpp"
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"
#include "XMLSkillsReaders.hpp"

class XMLCreaturesReader : public XMLReader
{
  public:
    std::pair<CreatureMap, CreatureGenerationValuesMap> get_creatures(const XMLNode& xml_configuration_creatures_node);

  protected:
    std::pair<CreaturePtr, CreatureGenerationValues> parse_creature(const XMLNode& creature_node);
    CreatureGenerationValues parse_creature_generation_values(const XMLNode& creature_generation_values_node);

    void parse_event_scripts(const XMLNode& event_scripts_node, CreaturePtr creature);
    void parse_spells(const XMLNode& spells_node, CreaturePtr creature);
    void parse_decision_strategy(const XMLNode& decision_strategy_node, CreaturePtr creature);

    XMLSkillsReader skill_reader;
};
