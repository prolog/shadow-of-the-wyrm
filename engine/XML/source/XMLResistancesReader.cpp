#include "Resistances.hpp"
#include "XMLDataStructures.hpp"
#include "XMLResistancesReader.hpp"

Resistances XMLResistancesReader::get_resistances(const XMLNode& node)
{
  Resistances resistances;

  parse_resistances(resistances, node);

  return resistances;
}

void XMLResistancesReader::parse_resistances(Resistances& resistances, const XMLNode& resistances_node)
{
  double slash_resist     = XMLUtils::get_child_node_float_value(resistances_node, "Slash");
  double pound_resist     = XMLUtils::get_child_node_float_value(resistances_node, "Pound");
  double pierce_resist    = XMLUtils::get_child_node_float_value(resistances_node, "Pierce");
  double heat_resist      = XMLUtils::get_child_node_float_value(resistances_node, "Heat");
  double cold_resist      = XMLUtils::get_child_node_float_value(resistances_node, "Cold");
  double acid_resist      = XMLUtils::get_child_node_float_value(resistances_node, "Acid");
  double poison_resist    = XMLUtils::get_child_node_float_value(resistances_node, "Poison");
  double holy_resist      = XMLUtils::get_child_node_float_value(resistances_node, "Holy");
  double shadow_resist    = XMLUtils::get_child_node_float_value(resistances_node, "Shadow");
  double arcane_resist    = XMLUtils::get_child_node_float_value(resistances_node, "Arcane");
  double mental_resist    = XMLUtils::get_child_node_float_value(resistances_node, "Mental");
  double sonic_resist     = XMLUtils::get_child_node_float_value(resistances_node, "Sonic");
  double radiant_resist   = XMLUtils::get_child_node_float_value(resistances_node, "Radiant");
  double lightning_resist = XMLUtils::get_child_node_float_value(resistances_node, "Lightning");

  // Set the resistances.
  resistances.set_resistance_value(DAMAGE_TYPE_SLASH, slash_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_POUND, pound_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_PIERCE, pierce_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_HEAT, heat_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_COLD, cold_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_ACID, acid_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_POISON, poison_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_HOLY, holy_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_SHADOW, shadow_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_ARCANE, arcane_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_MENTAL, mental_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_SONIC, sonic_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_RADIANT, radiant_resist);
  resistances.set_resistance_value(DAMAGE_TYPE_LIGHTNING, lightning_resist);
}


