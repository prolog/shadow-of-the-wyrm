#include "XMLPotionReader.hpp"

XMLPotionReader::XMLPotionReader()
{
}

XMLPotionReader::~XMLPotionReader()
{
}

// Methods for reading in details about potions from XML nodes conformant to the Potion type.
void XMLPotionReader::parse(PotionPtr potion, GenerationValues& gv, const XMLNode& potion_node)
{
  if (!potion_node.is_null())
  {
    XMLConsumableReader::parse(potion, gv, potion_node);
    
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(potion_node, "Damage");
    if (!damage_node.is_null())
    {
      Damage d;
      parse_damage(d, damage_node);

      potion->set_has_damage(true);
      potion->set_damage(d);
    }
  }
}
