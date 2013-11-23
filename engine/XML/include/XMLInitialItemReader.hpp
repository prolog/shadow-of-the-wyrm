#pragma once
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"
#include "InitialItem.hpp"

class XMLInitialItemReader : public XMLReader
{
  public:
    XMLInitialItemReader();
    ~XMLInitialItemReader();
    
    InitialItem get_initial_item(const XMLNode& initial_item_node);
    
  protected:
    // Parse the schema's Quantity Amount/Random into a Dice object.
    Dice parse_quantity(const XMLNode& quantity_node) const;
    
    std::vector<std::pair<std::string, Dice>> get_random_item_ids(const XMLNode& initial_random_node) const;
    std::map<std::string, std::pair<std::string, Dice>> get_racial_item_ids(const XMLNode& initial_racial_node) const;
};

