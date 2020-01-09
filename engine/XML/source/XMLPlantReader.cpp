#include "XMLPlantReader.hpp"

// Methods for reading in plants
XMLPlantReader::XMLPlantReader()
{
}

XMLPlantReader::~XMLPlantReader()
{
}

void XMLPlantReader::parse(PlantPtr plant, GenerationValues& gv, const XMLNode& plant_node, const bool force_ascii)
{
  if (plant && !plant_node.is_null())
  {
    XMLConsumableReader::parse(plant, gv, plant_node, force_ascii);
  }
}
