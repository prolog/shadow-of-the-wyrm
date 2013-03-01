#include "XMLArmourReader.hpp"

// Methods for reading in armour from the XML configuration.
XMLArmourReader::XMLArmourReader()
{
}

XMLArmourReader::~XMLArmourReader()
{
}

void XMLArmourReader::parse(ArmourPtr armour, GenerationValues& gv, const XMLNode& armour_node)
{
  if (armour && !armour_node.is_null())
  {
    XMLWearableReader::parse(armour, gv, armour_node);
  }
}

