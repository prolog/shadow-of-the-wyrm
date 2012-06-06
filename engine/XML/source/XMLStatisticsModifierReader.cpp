#include "XMLDataStructures.hpp"
#include "XMLStatisticsModifierReader.hpp"
#include "StatisticsModifier.hpp"

XMLStatisticsModifierReader::XMLStatisticsModifierReader()
{
}

XMLStatisticsModifierReader::~XMLStatisticsModifierReader()
{
}

StatisticsModifier XMLStatisticsModifierReader::get_statistics_modifier(const XMLNode& statistics_modifier_node)
{
  StatisticsModifier sm;

  if (!statistics_modifier_node.is_null())
  {
    int strength_modifier     = XMLUtils::get_child_node_int_value(statistics_modifier_node, "StrengthModifier");
    int dexterity_modifier    = XMLUtils::get_child_node_int_value(statistics_modifier_node, "DexterityModifier");
    int agility_modifier      = XMLUtils::get_child_node_int_value(statistics_modifier_node, "AgilityModifier");
    int health_modifier       = XMLUtils::get_child_node_int_value(statistics_modifier_node, "HealthModifier");
    int intelligence_modifier = XMLUtils::get_child_node_int_value(statistics_modifier_node, "IntelligenceModifier");
    int willpower_modifier    = XMLUtils::get_child_node_int_value(statistics_modifier_node, "WillpowerModifier");
    int charisma_modifier     = XMLUtils::get_child_node_int_value(statistics_modifier_node, "CharismaModifier");
    int valour_modifier       = XMLUtils::get_child_node_int_value(statistics_modifier_node, "ValourModifier");
    int spirit_modifier       = XMLUtils::get_child_node_int_value(statistics_modifier_node, "SpiritModifier");

    sm.set_strength_modifier(strength_modifier);
    sm.set_dexterity_modifier(dexterity_modifier);
    sm.set_agility_modifier(agility_modifier);
    sm.set_health_modifier(health_modifier);
    sm.set_intelligence_modifier(intelligence_modifier);
    sm.set_willpower_modifier(willpower_modifier);
    sm.set_charisma_modifier(charisma_modifier);

    sm.set_valour_modifier(valour_modifier);
    sm.set_spirit_modifier(spirit_modifier);
  }

  return sm;
}
