#include "XMLReader.hpp"
#include "CombatConstants.hpp"

using namespace std;

// Parse the dice from a node according to the Dice format.
void XMLReader::parse_dice(Dice& dice, const XMLNode& dice_node) const
{
  if (!dice_node.is_null())
  {
    uint num_sides = static_cast<uint>(XMLUtils::get_child_node_int_value(dice_node, "NumSides"));
    dice.set_dice_sides(num_sides);

    uint num_dice = static_cast<uint>(XMLUtils::get_child_node_int_value(dice_node, "NumDice"));
    dice.set_num_dice(num_dice);
    
    int modifier = XMLUtils::get_child_node_int_value(dice_node, "Modifier");
    dice.set_modifier(modifier);
  }
}

// Parse the damage from a node according to the Damage format in the schemas, and return a
// Damage object containing the appropriate values.
void XMLReader::parse_damage(Damage& damage, const XMLNode& damage_node) const
{
  if (!damage_node.is_null())
  {
    parse_dice(damage, damage_node);
    
    DamageType damage_type = CombatConstants::DEFAULT_UNARMED_DAMAGE_TYPE;
    damage_type = static_cast<DamageType>(XMLUtils::get_child_node_int_value(damage_node, "Type"));
    damage.set_damage_type(damage_type);

    bool chaotic = XMLUtils::get_attribute_bool_value(damage_node, "chaotic");
    damage.set_chaotic(chaotic);

    bool piercing = XMLUtils::get_attribute_bool_value(damage_node, "piercing");
    damage.set_piercing(piercing);

    int effect_bonus = XMLUtils::get_child_node_int_value(damage_node, "EffectBonus");
    damage.set_effect_bonus(effect_bonus);

    XMLNode status_ailments_node = XMLUtils::get_next_element_by_local_name(damage_node, "StatusAilments");
    if (!status_ailments_node.is_null())
    {
      StatusAilments ailments;
      parse_status_ailments(ailments, status_ailments_node);

      damage.set_status_ailments(ailments);
    }
  }
}

void XMLReader::parse_status_ailments(StatusAilments& status_ailment, const XMLNode& status_ailments_node) const
{
  set<string> ailments;
  vector<XMLNode> status_ailments = XMLUtils::get_elements_by_local_name(status_ailments_node, "Status");

  for (const XMLNode& status : status_ailments)
  {
    string ailment = XMLUtils::get_node_value(status);
    ailments.insert(ailment);
  }

  status_ailment.set_ailments(ailments);
  status_ailment.set_override_defaults(true);
}

void XMLReader::parse_properties(map<string, string>& properties, const XMLNode& properties_node) const
{
  vector<XMLNode> property_nodes = XMLUtils::get_elements_by_local_name(properties_node, "Property");

  for (const XMLNode& property_node : property_nodes)
  {
    string property_name = XMLUtils::get_child_node_value(property_node, "Name");
    string property_value = XMLUtils::get_child_node_value(property_node, "Value");

    properties[property_name] = property_value;
  }
}