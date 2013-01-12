#include "XMLMapCoordinateReader.hpp"

// Given a node of type Coord in the schema, return an engine Coordinate.
Coordinate XMLMapCoordinateReader::parse_coordinate(const XMLNode& coord_node)
{
  Coordinate c(0,0);

  if (!coord_node.is_null())
  {
    c.first = XMLUtils::get_child_node_int_value(coord_node, "Row");
    c.second = XMLUtils::get_child_node_int_value(coord_node, "Col");
  }

  return c;
}

