#include "XMLBoatReader.hpp"

XMLBoatReader::XMLBoatReader()
{
}

XMLBoatReader::~XMLBoatReader()
{
}

void XMLBoatReader::parse(BoatPtr boat, GenerationValues& gv, const XMLNode& boat_node, const bool force_ascii)
{
  if (!boat_node.is_null())
  {
    XMLItemReader::parse(boat, gv, boat_node, force_ascii);
  }
}
