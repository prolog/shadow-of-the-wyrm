#include "XMLFoodReader.hpp"

// Methods for reading in food
XMLFoodReader::XMLFoodReader()
{
}

XMLFoodReader::~XMLFoodReader()
{
}

void XMLFoodReader::parse(FoodPtr food, GenerationValues& gv, const XMLNode& food_node, const bool force_ascii)
{
  if (food && !food_node.is_null())
  {
    XMLConsumableReader::parse(food, gv, food_node, force_ascii);
  }
}

