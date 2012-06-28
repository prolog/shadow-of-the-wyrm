#include "XMLBoatReader.hpp"

XMLBoatReader::XMLBoatReader()
{
}

XMLBoatReader::~XMLBoatReader()
{
}

void XMLBoatReader::parse(BoatPtr boat, const XMLNode& boat_node)
{
  if (!boat_node.is_null())
  {
    XMLItemReader::parse(boat, boat_node);
  }
}
