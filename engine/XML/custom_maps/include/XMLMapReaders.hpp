#pragma once
#include <map>
#include <vector>
#include "Map.hpp"
#include "XMLDataStructures.hpp"

// Reads an individual map from the given <CustomMap> element.
class XMLMapReader
{
  public:
    MapPtr get_custom_map(const XMLNode& custom_map_node);

  protected:
    std::string parse_id(const XMLNode& parent_node);
    Dimensions parse_dimensions(const XMLNode& dimensions_node);
    void parse_initial_placements(const XMLNode& initial_placements_node, MapPtr map);
    void parse_random_placements(const XMLNode& random_placements_node, MapPtr map);
    
    void parse_initial_creature_placements(const XMLNode& creatures_node, MapPtr map);
    void parse_initial_item_placements(const XMLNode& items_node, MapPtr map);
    void parse_properties(const XMLNode& properties_node, MapPtr map);

    std::pair<int, int> parse_placement_range(const XMLNode& node);
    void parse_random_creature_placements(const XMLNode& creatures_node, MapPtr map);

    void log_placement_error(MapPtr map, const std::string& bad_id);
};
