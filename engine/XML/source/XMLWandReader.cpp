#include "XMLWandReader.hpp"

XMLWandReader::XMLWandReader()
{
}

XMLWandReader::~XMLWandReader()
{
}

// Methods for reading in Wand details from an XML node conformant to the Wand type.
void XMLWandReader::parse(WandPtr wand, GenerationValues& gv, const XMLNode& wand_node)
{
  if (!wand_node.is_null())
  {
    XMLItemReader::parse(wand, gv, wand_node);
    
    EffectType effect_type  = static_cast<EffectType>(XMLUtils::get_child_node_int_value(wand_node, "Effect", EFFECT_TYPE_NULL));
    wand->set_effect_type(effect_type); 
  }
}

