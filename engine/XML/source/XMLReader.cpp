#include "XMLReader.hpp"
#include "CombatConstants.hpp"

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
  }
}
