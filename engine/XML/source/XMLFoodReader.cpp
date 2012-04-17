#include "XMLFoodReader.hpp"

// Methods for reading in food
XMLFoodReader::XMLFoodReader()
{
}

XMLFoodReader::~XMLFoodReader()
{
}

void XMLFoodReader::parse(FoodPtr food, const XMLNode& food_node)
{
  if (food && !food_node.is_null())
  {
    XMLItemReader::parse(food, food_node);
  }
}

