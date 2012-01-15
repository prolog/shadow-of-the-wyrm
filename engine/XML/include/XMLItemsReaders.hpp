#pragma once
#include "XMLDataStructures.hpp"
#include "Item.hpp"

class XMLItemsReader
{
  public:
    XMLItemsReader();
    ~XMLItemsReader();
    
    ItemMap get_items(const XMLNode& items_node);

  protected:
    ItemMap get_misc_items(const XMLNode& misc_items_node);
    ItemPtr parse_item(const XMLNode& item_node);
};
