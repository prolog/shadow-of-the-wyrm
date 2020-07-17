#include "XMLTrapsReader.hpp"
#include "FeatureGenerator.hpp"
#include "FeatureProperties.hpp"

using namespace std;

vector<TrapPtr> XMLTrapsReader::get_traps(const XMLNode& xml_config_traps_node)
{
  vector<TrapPtr> traps;

  if (!xml_config_traps_node.is_null())
  {
    vector<XMLNode> trap_nodes = XMLUtils::get_elements_by_local_name(xml_config_traps_node, "Trap");

    for (const auto& xml_trap : trap_nodes)
    {
      TrapPtr trap = FeatureGenerator::create_trap();
      parse_trap(xml_trap, trap);

      traps.push_back(trap);
    }
  }

  return traps;
}

// Takes in the "Trap" node and sets the details
void XMLTrapsReader::parse_trap(const XMLNode& trap_node, TrapPtr trap)
{
  if (!trap_node.is_null() && trap != nullptr)
  {
    string trap_id = XMLUtils::get_attribute_value(trap_node, "id");
    string description_sid = XMLUtils::get_child_node_value(trap_node, "DescriptionSID");
    string trigger_message_sid = XMLUtils::get_child_node_value(trap_node, "TriggerMessageSID");
    string player_damage_message_sid = XMLUtils::get_child_node_value(trap_node, "PlayerDamageMessageSID");
    string item_id = XMLUtils::get_child_node_value(trap_node, "Item");
    EffectType effect = static_cast<EffectType>(XMLUtils::get_child_node_int_value(trap_node, "Effect"));

    XMLNode effect_status_node = XMLUtils::get_next_element_by_local_name(trap_node, "EffectStatus");
    string effect_status = to_string(static_cast<int>(ItemStatus::ITEM_STATUS_UNCURSED));
    if (!effect_status_node.is_null())
    {
      effect_status = XMLUtils::get_node_value(effect_status_node);
    }

    trap->set_additional_property(FeatureProperties::FEATURE_PROPERTIES_TRAP_EFFECT_STATUS, effect_status);

    Damage dam;
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(trap_node, "Damage");
    parse_damage(dam, damage_node);

    int uses = XMLUtils::get_child_node_int_value(trap_node, "Uses", 1);

    trap->set_id(trap_id);
    trap->set_description_sid(description_sid);
    trap->set_trigger_message_sid(trigger_message_sid);

    XMLNode trigger_node = XMLUtils::get_next_element_by_local_name(trap_node, "Trigger");
    Symbol trigger_symbol('?', Colour::COLOUR_WHITE);
    parse_symbol(trigger_symbol, trigger_node);
    trap->set_trigger_symbol(trigger_symbol);

    Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(trigger_node, "Colour"));
    trap->set_colour(colour);

    trap->set_player_damage_message_sid(player_damage_message_sid);
    trap->set_colour(colour);
    trap->set_item_id(item_id);
    trap->set_damage(dam);
    trap->set_effect(effect);
    trap->set_uses(uses);
  }
}
