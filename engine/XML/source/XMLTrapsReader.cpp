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
    }
  }

  return traps;
}

// Takes in the "Trap" node and sets the details
void XMLTrapsReader::parse_trap(const XMLNode& trap_node, TrapPtr trap)
{
  if (!trap_node.is_null() && trap != nullptr)
  {
    string description_sid = XMLUtils::get_child_node_value(trap_node, "DescriptionSID");
    string trigger_message_sid = XMLUtils::get_child_node_value(trap_node, "TriggerMessageSID");

    Damage dam;
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(trap_node, "Damage");
    parse_damage(dam, damage_node);

    trap->set_description_sid(description_sid);
    trap->set_trigger_message_sid(trigger_message_sid);
    trap->set_damage(dam);
  }
}
