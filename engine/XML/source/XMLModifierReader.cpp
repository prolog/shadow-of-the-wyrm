#include "XMLDataStructures.hpp"
#include "XMLModifierReader.hpp"
#include "Modifier.hpp"

XMLModifierReader::XMLModifierReader()
{
}

XMLModifierReader::~XMLModifierReader()
{
}

Modifier XMLModifierReader::get_modifier(const XMLNode& modifier_node)
{
  Modifier m;

  if (!modifier_node.is_null())
  {
    int strength_modifier     = XMLUtils::get_child_node_int_value(modifier_node, "StrengthModifier");
    int dexterity_modifier    = XMLUtils::get_child_node_int_value(modifier_node, "DexterityModifier");
    int agility_modifier      = XMLUtils::get_child_node_int_value(modifier_node, "AgilityModifier");
    int health_modifier       = XMLUtils::get_child_node_int_value(modifier_node, "HealthModifier");
    int intelligence_modifier = XMLUtils::get_child_node_int_value(modifier_node, "IntelligenceModifier");
    int willpower_modifier    = XMLUtils::get_child_node_int_value(modifier_node, "WillpowerModifier");
    int charisma_modifier     = XMLUtils::get_child_node_int_value(modifier_node, "CharismaModifier");

    m.set_strength_modifier(strength_modifier);
    m.set_dexterity_modifier(dexterity_modifier);
    m.set_agility_modifier(agility_modifier);
    m.set_health_modifier(health_modifier);
    m.set_intelligence_modifier(intelligence_modifier);
    m.set_willpower_modifier(willpower_modifier);
    m.set_charisma_modifier(charisma_modifier);
  }

  return m;
}
