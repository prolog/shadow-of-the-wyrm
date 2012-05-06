#pragma once
#include <utility>
#include "Creature.hpp"
#include "CreatureGenerationValues.hpp"
#include "XMLDataStructures.hpp"

class XMLCreaturesReader
{
  public:
    // JCD FIXME: Make this return pair<CreatureMap, CreatureGenerationValuesMap>
    std::pair<CreatureMap, CreatureGenerationValuesMap> get_creatures(const XMLNode& xml_configuration_creatures_node);

  protected:
    std::pair<CreaturePtr, CreatureGenerationValues> parse_creature(const XMLNode& creature_node);
    CreatureGenerationValues parse_creature_generation_values(const XMLNode& creature_generation_values_node);
};
