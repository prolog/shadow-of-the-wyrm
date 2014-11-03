#pragma once
#include <map>
#include "Damage.hpp"
#include "XMLDataStructures.hpp"

// Common functions useful to a number of different XMLReaders of different types (creatures, items, and so on)
// go here.
class XMLReader
{
  public:
    void parse_dice(Dice& dice, const XMLNode& dice_node) const;
    void parse_damage(Damage& damage, const XMLNode& damage_node) const;
    void parse_status_ailments(StatusAilments& ailments, const XMLNode& status_ailments_node) const;
    void parse_properties(std::map<std::string, std::string>& properties_map, const XMLNode& properties_node) const;
};
