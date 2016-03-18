#include "XMLAmuletReader.hpp"

XMLAmuletReader::XMLAmuletReader()
{
}

XMLAmuletReader::~XMLAmuletReader()
{
}

// Methods for reading in an amulet's details from an XML node conformant to the Amulet type.
void XMLAmuletReader::parse(AmuletPtr amulet, GenerationValues& igv, const XMLNode& amulet_node)
{
  XMLWearableReader::parse(amulet, igv, amulet_node);
}
