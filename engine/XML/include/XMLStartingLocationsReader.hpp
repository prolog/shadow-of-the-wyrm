#pragma once
#include <vector>
#include "StartingLocation.hpp"
#include "XMLReader.hpp"

class XMLStartingLocationsReader : public XMLReader
{
  public:
    std::vector<StartingLocation> get_starting_locations(const XMLNode& starting_locations_node);

  protected:
    void parse_starting_location(StartingLocation& sl, const XMLNode& starting_location_node);
};
