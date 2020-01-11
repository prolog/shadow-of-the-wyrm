#include "XMLRingReader.hpp"

XMLRingReader::XMLRingReader()
{
}

XMLRingReader::~XMLRingReader()
{
}

// Methods for reading in ring details from an XML node conformant to the Ring type.
void XMLRingReader::parse(RingPtr ring, GenerationValues& igv, const XMLNode& ring_node, const bool force_ascii)
{
  XMLWearableReader::parse(ring, igv, ring_node, force_ascii);
}
