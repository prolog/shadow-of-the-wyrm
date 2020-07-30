#include "XMLStartingLocationsReader.hpp"

using namespace std;

StartingLocationMap XMLStartingLocationsReader::get_starting_locations(const XMLNode& starting_locations_node)
{
  StartingLocationMap starting_locations;

  if (!starting_locations_node.is_null())
  {
    vector<XMLNode> starting_location_nodes = XMLUtils::get_elements_by_local_name(starting_locations_node, "StartingLocation");
    StartingLocation sl;

    for (const auto& sl_node : starting_location_nodes)
    {
      StartingLocation sl;
      parse_starting_location(sl, sl_node);

      starting_locations.insert(make_pair(sl.get_id(), sl));
    }
  }

  return starting_locations;
}

void XMLStartingLocationsReader::parse_starting_location(StartingLocation& sl, const XMLNode& starting_location_node)
{
  if (!starting_location_node.is_null())
  {
    string sl_id = XMLUtils::get_attribute_value(starting_location_node, "id");
    sl.set_id(sl_id);

    int row = XMLUtils::get_child_node_int_value(starting_location_node, "Row");
    int col = XMLUtils::get_child_node_int_value(starting_location_node, "Col");

    sl.set_location(make_pair(row, col));

    string short_desc_sid = XMLUtils::get_child_node_value(starting_location_node, "ShortDescriptionSID");

    sl.set_short_description_sid(short_desc_sid);

    string desc_sid = XMLUtils::get_child_node_value(starting_location_node, "DescriptionSID");

    sl.set_description_sid(desc_sid);
  }
}
