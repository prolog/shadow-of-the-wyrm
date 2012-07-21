#pragma once
#include "XMLDataStructures.hpp"
#include "InitialItem.hpp"

class XMLInitialItemReader
{
  public:
    XMLInitialItemReader();
    ~XMLInitialItemReader();
    
    InitialItem get_initial_item(const XMLNode& initial_item_node);
    
  protected:
    std::vector<std::string> get_random_item_ids(const XMLNode& initial_random_node) const;
    std::map<std::string, std::string> get_racial_item_ids(const XMLNode& initial_racial_node) const;
};

