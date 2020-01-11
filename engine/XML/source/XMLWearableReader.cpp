#include "XMLWearableReader.hpp"

// Methods for reading in the common elements of all Wearable items.
XMLWearableReader::XMLWearableReader()
{
}

XMLWearableReader::~XMLWearableReader()
{
}

void XMLWearableReader::parse(WearablePtr wearable, GenerationValues& gv, const XMLNode& wearable_node, const bool force_ascii)
{
  if (wearable && !wearable_node.is_null())
  {
    XMLItemReader::parse(wearable, gv, wearable_node, force_ascii);
    
    int evade = XMLUtils::get_child_node_int_value(wearable_node, "Evade");
    wearable->set_evade(evade);
    
    int soak = XMLUtils::get_child_node_int_value(wearable_node, "Soak");
    wearable->set_soak(soak);

    int speed_bonus = XMLUtils::get_child_node_int_value(wearable_node, "SpeedBonus");
    wearable->set_speed_bonus(speed_bonus);

    int to_hit = XMLUtils::get_child_node_int_value(wearable_node, "ToHit");
    wearable->set_to_hit(to_hit);

    int addl_damage = XMLUtils::get_child_node_int_value(wearable_node, "AddlDamage");
    wearable->set_addl_damage(addl_damage);

    XMLNode sa_node = XMLUtils::get_next_element_by_local_name(wearable_node, "StatusAilments");
    StatusAilments sa;
    parse_status_ailments(sa, sa_node);
    wearable->set_status_ailments(sa);
  }
}
