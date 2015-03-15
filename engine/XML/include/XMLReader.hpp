#pragma once
#include <map>
#include "Class.hpp"
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

    void parse_initial_equipment_and_inventory(ClassPtr current_class, const XMLNode& initial_equipment_and_inventory_node);
    void parse_initial_equipment(ClassPtr current_class, const XMLNode& initial_equipment_node);
    void parse_initial_inventory(ClassPtr current_class, const XMLNode& initial_inventory_node);

    InitialItem get_initial_item(const XMLNode& initial_item_node);

  protected:
    // Parse the schema's Quantity Amount/Random into a Dice object.
    Dice parse_quantity(const XMLNode& quantity_node) const;

    std::vector<std::pair<std::string, Dice>> get_random_item_ids(const XMLNode& initial_random_node) const;
    std::map<std::string, std::pair<std::string, Dice>> get_racial_item_ids(const XMLNode& initial_racial_node) const;
};
