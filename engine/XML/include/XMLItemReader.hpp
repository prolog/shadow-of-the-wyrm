#pragma once
#include "Item.hpp"
#include "XMLDataStructures.hpp"

// Class for reading in details common to all items.
class XMLItemReader
{
  public:
    XMLItemReader();
    virtual ~XMLItemReader();
    
    virtual void parse(ItemPtr item, const XMLNode& item_node);
    
  protected:
            void parse_text_details(ItemPtr item, const XMLNode& text_details_node);

};

