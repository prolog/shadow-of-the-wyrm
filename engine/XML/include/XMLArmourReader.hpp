#pragma once
#include "Armour.hpp"
#include "XMLWearableReader.hpp"

// A class used for reading in details about Armour from a given
// XML node conformant to Armour in the schema.
class XMLArmourReader : public XMLWearableReader
{
  public:
    XMLArmourReader();
    ~XMLArmourReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(ArmourPtr armour, GenerationValues& gv, const XMLNode& armour_node);
};

