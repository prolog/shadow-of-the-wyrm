#include <vector>
#include "Conversion.hpp"
#include "SpellShapeFactory.hpp"
#include "Modifier.hpp"
#include "SpellAdditionalProperties.hpp"
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

    for (const XMLNode& spell_node : spell_nodes)
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
    SkillType magic_category = static_cast<SkillType>(XMLUtils::get_child_node_int_value(spell_node, "MagicCategory", static_cast<int>(SkillType::SKILL_MAGIC_ARCANE)));
    MagicClassification magic_classification = static_cast<MagicClassification>(XMLUtils::get_child_node_int_value(spell_node, "MagicClassification", static_cast<int>(MagicClassification::MAGIC_CLASSIFICATION_UNDEFINED)));
    Colour spell_colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(spell_node, "Colour"));
    uint ap_cost = XMLUtils::get_child_node_int_value(spell_node, "APCost");
    int speed = XMLUtils::get_child_node_int_value(spell_node, "Speed");
    uint range = XMLUtils::get_child_node_int_value(spell_node, "Range");
    SpellShapeType shape_type = static_cast<SpellShapeType>(XMLUtils::get_child_node_int_value(spell_node, "Shape"));
    SpellShape spell_shape = SpellShapeFactory::create_spell_shape(shape_type);
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(spell_node, "Damage");
    EffectType effect = static_cast<EffectType>(XMLUtils::get_child_node_int_value(spell_node, "Effect"));
    XMLNode properties_node = XMLUtils::get_next_element_by_local_name(spell_node, "Properties");
    map<string, string> properties;

    spell.set_spell_id(spell_id);
    spell.set_spell_name_sid(spell_name_sid);
    spell.set_player_cast_message_sid(player_cast_sid);
    spell.set_monster_cast_message_sid(monster_cast_sid);
    spell.set_magic_category(magic_category);
    spell.set_magic_classification(magic_classification);
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

    parse_spell_properties(properties_node, spell, properties);

    spell.set_effect(effect);
  }

  return spell;
}

void XMLSpellsReader::parse_spell_properties(const XMLNode& properties_node, Spell& spell, map<string, string>& properties)
{
  if (!properties_node.is_null())
  {
    parse_properties(properties, properties_node);

    create_modifiers_if_necessary(spell, properties);

    // Once the modifiers have been created, read the rest of the properties
    // into the spell properties.
    for (const auto& p_it : properties)
    {
        spell.set_property(p_it.first, p_it.second);
    }
  }
}

void XMLSpellsReader::create_modifiers_if_necessary(Spell& spell, map<string, string>& properties)
{
  bool create_modifier = false;
  vector<int> sm_constructor_arg;
  Resistances resists;
  resists.set_all_resistances_to(0);

  parse_statistic_modifiers(create_modifier, sm_constructor_arg, properties);
  parse_resistance_modifiers(create_modifier, resists, properties);

  if (create_modifier)
  {
    Modifier m(sm_constructor_arg);
    m.set_resistances(resists);

    spell.set_modifier(m);
  }
}

void XMLSpellsReader::parse_statistic_modifiers(bool& create_modifier, vector<int>& sm_constructor_arg, map<string, string>& properties)
{
  // Create the statistics modifier
  vector<string> stat_keys = { SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_STR,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_DEX,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_AGI,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_HEA,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_INT,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_WIL,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_CHA,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_EVADE,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_SOAK,
                               SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_TO_HIT};

  for (const auto& key : stat_keys)
  {
    auto prop_it = properties.find(key);

    if (prop_it != properties.end())
    {
      create_modifier = true;
      sm_constructor_arg.push_back(String::to_int(prop_it->second));

      // Remove the statistic modifier key from the map, since it's not needed anymore.
      properties.erase(key);
    }
    else
    {
      sm_constructor_arg.push_back(0);
    }
  }
}

void XMLSpellsReader::parse_resistance_modifiers(bool& create_modifier, Resistances& resists, map<string, string>& properties)
{
  map<string, DamageType> resist_map =  { { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_SLASH, DamageType::DAMAGE_TYPE_SLASH },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_PIERCE, DamageType::DAMAGE_TYPE_PIERCE },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_POUND, DamageType::DAMAGE_TYPE_POUND },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_HEAT, DamageType::DAMAGE_TYPE_HEAT },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_COLD, DamageType::DAMAGE_TYPE_COLD },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_ACID, DamageType::DAMAGE_TYPE_ACID },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_POISON, DamageType::DAMAGE_TYPE_POISON },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_HOLY, DamageType::DAMAGE_TYPE_HOLY },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_SHADOW, DamageType::DAMAGE_TYPE_SHADOW },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_ARCANE, DamageType::DAMAGE_TYPE_ARCANE },
                                          { SpellAdditionalProperties::PROPERTY_RESISTANCE_MODIFIER_LIGHTNING, DamageType::DAMAGE_TYPE_LIGHTNING } };

  for (const auto& pair : resist_map)
  {
    string key = pair.first;
    auto prop_it = properties.find(key);

    if (prop_it != properties.end())
    {
      create_modifier = true;
      
      DamageType dt = pair.second;
      double resist_value = static_cast<double>(String::to_double(prop_it->second));

      resists.set_resistance_value(dt, resist_value);

      // Remove the resistance modifier key from the map, since it's not needed anymore.
      properties.erase(key);
    }
  }
}