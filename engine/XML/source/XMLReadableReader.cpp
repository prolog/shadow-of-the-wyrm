#include "XMLReadableReader.hpp"

XMLReadableReader::XMLReadableReader()
{
}

XMLReadableReader::~XMLReadableReader()
{
}

void XMLReadableReader::parse(ReadablePtr readable, GenerationValues& gv, const XMLNode& node)
{
  if (readable && !node.is_null())
  {
    XMLItemReader::parse(readable, gv, node);

    EffectType effect_type = static_cast<EffectType>(XMLUtils::get_child_node_int_value(node, "Effect", static_cast<int>(EffectType::EFFECT_TYPE_NULL)));
    readable->set_effect_type(effect_type);

    std::string text_sid = XMLUtils::get_child_node_value(node, "TextSID");

    readable->set_text_sid(text_sid);
  }
}

