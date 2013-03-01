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
    XMLItemReader::parse(potion, gv, potion_node);
    
    EffectType effect_type  = static_cast<EffectType>(XMLUtils::get_child_node_int_value(potion_node, "Effect", EFFECT_TYPE_NULL));
    potion->set_effect_type(effect_type); 
  }
}
