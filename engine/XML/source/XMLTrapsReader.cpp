#include "XMLTrapsReader.hpp"

using namespace std;

vector<TrapPtr> XMLTrapsReader::get_traps(const XMLNode& xml_config_traps_node)
{
  vector<TrapPtr> traps;

  if (!xml_config_traps_node.is_null())
  {
    vector<XMLNode> trap_nodes = XMLUtils::get_elements_by_local_name(xml_config_traps_node, "Trap");

    for (const auto& xml_tile : trap_nodes)
    {
      TrapPtr trap = std::make_shared<Trap>();
      parse_trap(xml_tile, trap);

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
    string trigger_char = XMLUtils::get_child_node_value(trap_node, "TriggerSymbol");
    string player_damage_message_sid = XMLUtils::get_child_node_value(trap_node, "PlayerDamageMessageSID");
    Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(trap_node, "Colour"));
    string item_id = XMLUtils::get_child_node_value(trap_node, "Item");

    Damage dam;
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(trap_node, "Damage");
    parse_damage(dam, damage_node);

    int uses = XMLUtils::get_child_node_int_value(trap_node, "Uses", 1);

    trap->set_id(trap_id);
    trap->set_description_sid(description_sid);
    trap->set_trigger_message_sid(trigger_message_sid);

    if (!trigger_char.empty())
    {
      trap->set_trigger_symbol(trigger_char.at(0));
    }

    trap->set_player_damage_message_sid(player_damage_message_sid);
    trap->set_colour(colour);
    trap->set_item_id(item_id);
    trap->set_damage(dam);
    trap->set_uses(uses);
  }
}
