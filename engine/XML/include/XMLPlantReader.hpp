#pragma once
#include "Plant.hpp"
#include "XMLConsumableReader.hpp"

// A class for reading in details about Plants
// from an XML node conformant to the Plant type.
class XMLPlantReader : public XMLConsumableReader
{
  public:
    XMLPlantReader();
    ~XMLPlantReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(PlantPtr plant, const XMLNode& plant_node);
};

