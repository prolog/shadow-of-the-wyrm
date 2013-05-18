#include "XMLWandReader.hpp"

XMLWandReader::XMLWandReader()
{
}

XMLWandReader::~XMLWandReader()
{
}

// Methods for reading in Wand details from an XML node conformant to the Wand type.
void XMLWandReader::parse(WandPtr wand, GenerationValues& gv, const XMLNode& wand_node)
{
  if (!wand_node.is_null())
  {
    XMLItemReader::parse(wand, gv, wand_node);
    
    EffectType effect_type  = static_cast<EffectType>(XMLUtils::get_child_node_int_value(wand_node, "Effect", EFFECT_TYPE_NULL));
    wand->set_effect_type(effect_type);

    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(wand_node, "Damage");
    if (!damage_node.is_null())
    {
      Damage d;
      parse_damage(d, damage_node);

      wand->set_has_damage(true);
      wand->set_damage(d);
    }

    uint range = XMLUtils::get_child_node_int_value(wand_node, "Range");
    wand->set_range(range);

    SpellShapeType spell_shape = static_cast<SpellShapeType>(XMLUtils::get_child_node_int_value(wand_node, "BeamType", SPELL_SHAPE_BEAM));
    wand->set_spell_shape_type(spell_shape);
  }
}

