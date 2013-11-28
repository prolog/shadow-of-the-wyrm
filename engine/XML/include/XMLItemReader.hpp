#pragma once
#include "GenerationValues.hpp"
#include "Item.hpp"
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"

// Class for reading in details common to all items.
class XMLItemReader : public XMLReader
{
  public:
    XMLItemReader();
    virtual ~XMLItemReader();
    
    virtual void parse(ItemPtr item, GenerationValues& gv, const XMLNode& item_node);
    
  protected:
    void parse_text_details(ItemPtr item, const XMLNode& text_details_node);

};

