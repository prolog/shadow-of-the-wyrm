#include "EffectFactory.hpp"
#include "XMLPotionReader.hpp"

XMLPotionReader::XMLPotionReader()
{
}

XMLPotionReader::~XMLPotionReader()
{
}

// Methods for reading in details about potions from XML nodes conformant to the Potion type.
void XMLPotionReader::parse(PotionPtr potion, const XMLNode& potion_node)
{
  if (!potion_node.is_null())
  {
    XMLItemReader::parse(potion, potion_node);
    
    EffectType effect_type  = static_cast<EffectType>(XMLUtils::get_child_node_int_value(potion_node, "Effect", EFFECT_TYPE_NULL));
    EffectPtr potion_effect = EffectFactory::create_effect(effect_type);
    potion->set_effect(potion_effect); 
  }
}
