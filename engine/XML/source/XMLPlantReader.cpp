#include "XMLPlantReader.hpp"

// Methods for reading in plants
XMLPlantReader::XMLPlantReader()
{
}

XMLPlantReader::~XMLPlantReader()
{
}

void XMLPlantReader::parse(PlantPtr plant, const XMLNode& plant_node)
{
  if (plant && !plant_node.is_null())
  {
    // JCD FIXME: Once a Consumable reader is defined,
    // change this call:
    XMLItemReader::parse(plant, plant_node);
  }
}
