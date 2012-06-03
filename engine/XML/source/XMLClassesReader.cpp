#include <vector>
#include <boost/foreach.hpp>

#include "Resistances.hpp"
#include "XMLClassesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLResistancesReader.hpp"
#include "XMLSkillsReaders.hpp"

using namespace std;

ClassMap XMLClassesReader::get_classes(const XMLNode& classes_node)
{
  ClassMap classes;

  if (!classes_node.is_null())
  {
    vector<XMLNode> classes_nodes = XMLUtils::get_elements_by_local_name(classes_node, "Class");

    BOOST_FOREACH(XMLNode class_node, classes_nodes)
    {
      ClassPtr current_class = parse_class(class_node);

      if (current_class)
      {
        classes.insert(make_pair(current_class->get_class_id(), current_class));
      }
    }
  }

  return classes;
}

ClassPtr XMLClassesReader::parse_class(const XMLNode& class_node)
{
  ClassPtr current_class;

  if (!class_node.is_null())
  {
    current_class = ClassPtr(new Class());

    string internal_class_id = XMLUtils::get_attribute_value(class_node, "id");

    current_class->set_class_id(internal_class_id);

    string class_name_sid = XMLUtils::get_child_node_value(class_node, "NameSID");
    string class_description_sid = XMLUtils::get_child_node_value(class_node, "DescriptionSID");
    string class_abbreviation_sid = XMLUtils::get_child_node_value(class_node, "DisplayAbbreviationSID");

    current_class->set_class_name_sid(class_name_sid);
    current_class->set_class_description_sid(class_description_sid);
    current_class->set_class_abbreviation_sid(class_abbreviation_sid);

    XMLNode initial_statistics_node = XMLUtils::get_next_element_by_local_name(class_node, "ClassInitialStatistics");
    XMLNode initial_modifiers_node = XMLUtils::get_next_element_by_local_name(class_node, "ClassInitialModifiers");

    parse_class_initial_statistics(current_class, initial_statistics_node);
    parse_class_initial_modifiers(current_class, initial_modifiers_node);

    uint hit_dice = XMLUtils::get_child_node_int_value(class_node, "HitDice");
    current_class->set_hit_dice(hit_dice);
    
    uint ap_dice = XMLUtils::get_child_node_int_value(class_node, "APDice");
    current_class->set_ap_dice(ap_dice);

    XMLNode resistances_node = XMLUtils::get_next_element_by_local_name(class_node, "Resistances");
    XMLNode skills_node = XMLUtils::get_next_element_by_local_name(class_node, "Skills");

    parse_class_resistances(current_class, resistances_node);
    parse_class_skills(current_class, skills_node);

    bool user_playable = XMLUtils::get_child_node_bool_value(class_node, "UserPlayable");
    current_class->set_user_playable(user_playable);

    float experience_multiplier = XMLUtils::get_child_node_float_value(class_node, "ExperienceMultiplier", 1.0);
    current_class->set_experience_multiplier(experience_multiplier);
  }

  return current_class;
}

void XMLClassesReader::parse_class_initial_statistics(ClassPtr current_class, const XMLNode& initial_statistics_node)
{
  if (current_class && !initial_statistics_node.is_null())
  {
    int valour = XMLUtils::get_child_node_int_value(initial_statistics_node, "Valour");
    int spirit = XMLUtils::get_child_node_int_value(initial_statistics_node, "Spirit");

    current_class->set_starting_valour(valour);
    current_class->set_starting_spirit(spirit);
  }
}

void XMLClassesReader::parse_class_initial_modifiers(ClassPtr current_class, const XMLNode& initial_modifiers_node)
{
  if (current_class && !initial_modifiers_node.is_null())
  {
    int strength_modifier     = XMLUtils::get_child_node_int_value(initial_modifiers_node, "StrengthModifier");
    int dexterity_modifier    = XMLUtils::get_child_node_int_value(initial_modifiers_node, "DexterityModifier");
    int agility_modifier      = XMLUtils::get_child_node_int_value(initial_modifiers_node, "AgilityModifier");
    int health_modifier       = XMLUtils::get_child_node_int_value(initial_modifiers_node, "HealthModifier");
    int intelligence_modifier = XMLUtils::get_child_node_int_value(initial_modifiers_node, "IntelligenceModifier");
    int willpower_modifier    = XMLUtils::get_child_node_int_value(initial_modifiers_node, "WillpowerModifier");
    int charisma_modifier     = XMLUtils::get_child_node_int_value(initial_modifiers_node, "CharismaModifier");

    current_class->set_strength_modifier(strength_modifier);
    current_class->set_dexterity_modifier(dexterity_modifier);
    current_class->set_agility_modifier(agility_modifier);
    current_class->set_health_modifier(health_modifier);
    current_class->set_intelligence_modifier(intelligence_modifier);
    current_class->set_willpower_modifier(willpower_modifier);
    current_class->set_charisma_modifier(charisma_modifier);
  }
}

void XMLClassesReader::parse_class_resistances(ClassPtr current_class, const XMLNode& resistances_node)
{
  if (current_class && !resistances_node.is_null())
  {
    XMLResistancesReader resistances_reader;

    Resistances resistances = resistances_reader.get_resistances(resistances_node);

    current_class->set_resistances(resistances);
  }
}

void XMLClassesReader::parse_class_skills(ClassPtr current_class, const XMLNode& skills_node)
{
  if (current_class && !skills_node.is_null())
  {
    XMLSkillsReader skills_reader;

    Skills skills = skills_reader.get_skills(skills_node);

    current_class->set_skills(skills);
  }
}
