#include "XMLConsumableReader.hpp"

XMLConsumableReader::XMLConsumableReader()
{
}

XMLConsumableReader::~XMLConsumableReader()
{
}

// Methods for parsing a Consumable based on a provided XML node
// conformant to the "Consumable" type in the schema.
void XMLConsumableReader::parse(ConsumablePtr consumable, GenerationValues& gv, const XMLNode& node)
{
  if (consumable && !node.is_null())
  {
    XMLItemReader::parse(consumable, gv, node);
    uint nutrition = static_cast<uint>(XMLUtils::get_child_node_int_value(node, "Nutrition", 0));

    consumable->set_nutrition(nutrition);
  }
}
