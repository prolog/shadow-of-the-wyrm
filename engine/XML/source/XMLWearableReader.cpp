#include "XMLWearableReader.hpp"

// Methods for reading in the common elements of all Wearable items.
XMLWearableReader::XMLWearableReader()
{
}

XMLWearableReader::~XMLWearableReader()
{
}

void XMLWearableReader::parse(WearablePtr wearable, GenerationValues& gv, const XMLNode& wearable_node)
{
  if (wearable && !wearable_node.is_null())
  {
    XMLItemReader::parse(wearable, gv, wearable_node);
    
    int evade = XMLUtils::get_child_node_int_value(wearable_node, "Evade");
    wearable->set_evade(evade);
    
    int soak = XMLUtils::get_child_node_int_value(wearable_node, "Soak");
    wearable->set_soak(soak);

    int to_hit = XMLUtils::get_child_node_int_value(wearable_node, "ToHit");
    wearable->set_to_hit(to_hit);

    int addl_damage = XMLUtils::get_child_node_int_value(wearable_node, "AddlDamage");
    wearable->set_addl_damage(addl_damage);
  }
}
