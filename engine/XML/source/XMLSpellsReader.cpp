#include <vector>
#include <boost/foreach.hpp>
#include "SpellShapeFactory.hpp"
#include "XMLSpellsReader.hpp"
#include "XMLDataStructures.hpp"

using namespace std;

XMLSpellsReader::XMLSpellsReader()
{
}

XMLSpellsReader::~XMLSpellsReader()
{
}

SpellMap XMLSpellsReader::get_spells(const XMLNode& spells_node)
{
  SpellMap spells;

  if (!spells_node.is_null())
  {
    vector<XMLNode> spell_nodes = XMLUtils::get_elements_by_local_name(spells_node, "Spell");

    BOOST_FOREACH(const XMLNode& spell_node, spell_nodes)
    {
      Spell spell = parse(spell_node);
      spells.insert(make_pair(spell.get_spell_id(), spell));
    }
  }

  return spells;
}

Spell XMLSpellsReader::parse(const XMLNode& spell_node)
{
  Spell spell;

  if (!spell_node.is_null())
  {
    string spell_id = XMLUtils::get_attribute_value(spell_node, "id");
    string spell_name_sid = XMLUtils::get_child_node_value(spell_node, "NameSID");
    string player_cast_sid = XMLUtils::get_child_node_value(spell_node, "PlayerCastMessageSID");
    string monster_cast_sid = XMLUtils::get_child_node_value(spell_node, "MonsterCastMessageSID");
    SkillType magic_category = static_cast<SkillType>(XMLUtils::get_child_node_int_value(spell_node, "MagicCategory", SKILL_MAGIC_ARCANE));
    Colour spell_colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(spell_node, "Colour"));
    uint ap_cost = XMLUtils::get_child_node_int_value(spell_node, "APCost");
    int speed = XMLUtils::get_child_node_int_value(spell_node, "Speed");
    uint range = XMLUtils::get_child_node_int_value(spell_node, "Range");
    SpellShapeType shape_type = static_cast<SpellShapeType>(XMLUtils::get_child_node_int_value(spell_node, "Shape"));
    SpellShape spell_shape = SpellShapeFactory::create_spell_shape(shape_type);
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(spell_node, "Damage");
    EffectType effect = static_cast<EffectType>(XMLUtils::get_child_node_int_value(spell_node, "Effect"));

    spell.set_spell_id(spell_id);
    spell.set_spell_name_sid(spell_name_sid);
    spell.set_player_cast_message_sid(player_cast_sid);
    spell.set_monster_cast_message_sid(monster_cast_sid);
    spell.set_magic_category(magic_category);
    spell.set_colour(spell_colour);
    spell.set_ap_cost(ap_cost);
    spell.set_speed(speed);
    spell.set_range(range);
    spell.set_shape(spell_shape);

    if (!damage_node.is_null())
    {
      Damage dmg;
      parse_damage(dmg, damage_node);

      spell.set_has_damage(true);
      spell.set_damage(dmg);
    }

    spell.set_effect(effect);
  }

  return spell;
}
