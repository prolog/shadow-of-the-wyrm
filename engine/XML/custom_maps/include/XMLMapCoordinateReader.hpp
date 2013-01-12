#pragma once
#include "common.hpp"
#include "XMLDataStructures.hpp"

// A simple class for reading in Coord values from custom map XML.
class XMLMapCoordinateReader
{
  public:
    Coordinate parse_coordinate(const XMLNode& coord_node);
};

