#include "XMLReadableReader.hpp"

XMLReadableReader::XMLReadableReader()
{
}

XMLReadableReader::~XMLReadableReader()
{
}

void XMLReadableReader::parse(ReadablePtr readable, const XMLNode& node)
{
  if (readable && !node.is_null())
  {
    XMLItemReader::parse(readable, node);

    EffectType effect_type = static_cast<EffectType>(XMLUtils::get_child_node_int_value(node, "Effect", EFFECT_TYPE_NULL));
    readable->set_effect_type(effect_type);
  }
}

