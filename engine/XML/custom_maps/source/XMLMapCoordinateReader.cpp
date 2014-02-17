#include "RNG.hpp"
#include "XMLMapCoordinateReader.hpp"

using namespace std;

// Given a parent node, which may have either a Coord or a Random element (xs:choice),
// parse it and return an engine Coordinate.
Coordinate XMLMapCoordinateReader::parse_coordinate(const XMLNode& parent_node)
{
  Coordinate c(0,0);

  XMLNode child_node = XMLUtils::get_next_element_by_local_name(parent_node, "Coord");

  if (!child_node.is_null())
  {
    c = parse_fixed_coordinate(child_node);
  }
  else
  {
    child_node = XMLUtils::get_next_element_by_local_name(parent_node, "Random");

    if (!child_node.is_null())
    {
      c = parse_random_coordinate(child_node);
    }
  }

  return c;
}

// Given a node of type Coord in the schema, return an engine Coordinate.
Coordinate XMLMapCoordinateReader::parse_fixed_coordinate(const XMLNode& coord_node)
{
  Coordinate c(0,0);

  if (!coord_node.is_null())
  {
    c.first = XMLUtils::get_child_node_int_value(coord_node, "Row");
    c.second = XMLUtils::get_child_node_int_value(coord_node, "Col");
  }

  return c;
}

// Given a node of type Random in the schema, return an engine coordinate.
Coordinate XMLMapCoordinateReader::parse_random_coordinate(const XMLNode& random_coord_node)
{
  Coordinate c(0,0);

  vector<XMLNode> coord_nodes = XMLUtils::get_elements_by_local_name(random_coord_node, "Coord");

  if (!coord_nodes.empty())
  {
    XMLNode node = coord_nodes.at(RNG::range(0, coord_nodes.size()-1));
    c = parse_fixed_coordinate(node);
  }

  return c;
}