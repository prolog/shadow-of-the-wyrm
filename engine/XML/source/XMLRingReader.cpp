#include "XMLRingReader.hpp"

XMLRingReader::XMLRingReader()
{
}

XMLRingReader::~XMLRingReader()
{
}

// Methods for reading in ring details from an XML node conformant to the Ring type.
void XMLRingReader::parse(RingPtr ring, GenerationValues& igv, const XMLNode& ring_node)
{
  XMLWearableReader::parse(ring, igv, ring_node);
}
