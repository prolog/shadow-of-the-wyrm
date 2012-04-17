#pragma once
#include "Food.hpp"
#include "XMLItemReader.hpp"

// JCD FIXME: Define a Consumable reader.
// Then, change the inherited class for plant and food...
class XMLFoodReader : public XMLItemReader
{
  public:
    XMLFoodReader();
    ~XMLFoodReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(FoodPtr food, const XMLNode& food_node);
};

