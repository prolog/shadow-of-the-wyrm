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
    
    virtual void parse(ItemPtr item, GenerationValues& gv, const XMLNode& item_node, const bool force_ascii);
    
  protected:
    void parse_item_scripts(ItemPtr item, const XMLNode& item_scripts_node);
};

