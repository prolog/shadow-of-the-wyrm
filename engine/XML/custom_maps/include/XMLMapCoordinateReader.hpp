#pragma once
#include "common.hpp"
#include "XMLDataStructures.hpp"

// A simple class for reading in Coord values from custom map XML.
class XMLMapCoordinateReader
{
  public:
    Coordinate parse_coordinate(const XMLNode& parent_node);
    Coordinate parse_fixed_coordinate(const XMLNode& coord_node);
    Coordinate parse_random_coordinate(const XMLNode& rand_coord_node);
};

