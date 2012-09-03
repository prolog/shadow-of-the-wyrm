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
  }
}
