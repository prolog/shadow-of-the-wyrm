#include <vector>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Resistances.hpp"
#include "XMLClassesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLResistancesReader.hpp"
#include "XMLSkillsReaders.hpp"
#include "XMLStatisticsModifierReader.hpp"

using namespace std;
using boost::make_shared;

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
    current_class = make_shared<Class>();

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
    
    float piety_cost_multiplier = XMLUtils::get_child_node_float_value(class_node, "PietyCostMultiplier", current_class->get_piety_cost_multiplier());
    current_class->set_piety_cost_multiplier(piety_cost_multiplier);

    int piety_regen_bonus = XMLUtils::get_child_node_int_value(class_node, "PietyRegenBonus", current_class->get_piety_regen_bonus());
    current_class->set_piety_regen_bonus(piety_regen_bonus);

    bool user_playable = XMLUtils::get_child_node_bool_value(class_node, "UserPlayable");
    current_class->set_user_playable(user_playable);

    float experience_multiplier = XMLUtils::get_child_node_float_value(class_node, "ExperienceMultiplier", current_class->get_experience_multiplier());
    current_class->set_experience_multiplier(experience_multiplier);
    
    XMLNode initial_equipment_and_inventory_node = XMLUtils::get_next_element_by_local_name(class_node, "InitialEquipmentAndInventory");
    parse_initial_equipment_and_inventory(current_class, initial_equipment_and_inventory_node);
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
    XMLStatisticsModifierReader stat_modifier_reader;
    StatisticsModifier sm = stat_modifier_reader.get_statistics_modifier(initial_modifiers_node);    
    current_class->set_statistics_modifier(sm);
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

void XMLClassesReader::parse_initial_equipment_and_inventory(ClassPtr current_class, const XMLNode& initial_eq_and_inv_node)
{
  if (current_class && !initial_eq_and_inv_node.is_null())
  {
    parse_initial_equipment(current_class, initial_eq_and_inv_node);
    
    XMLNode initial_inv_node = XMLUtils::get_next_element_by_local_name(initial_eq_and_inv_node, "InitialInventory");
    parse_initial_inventory(current_class, initial_inv_node);
  }
}

// Parse the initial items into the eq.
void XMLClassesReader::parse_initial_equipment(ClassPtr current_class, const XMLNode& initial_eq_node)
{
  if (current_class && !initial_eq_node.is_null())
  {
    map<EquipmentWornLocation, InitialItem> initial_equipment;
    
    // Head
    XMLNode head_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Head");
    InitialItem head_item = initial_item_reader.get_initial_item(head_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_HEAD, head_item));
    
    // Neck
    XMLNode neck_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Neck");
    InitialItem neck_item = initial_item_reader.get_initial_item(neck_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_NECK, neck_item));

    // RFinger
    XMLNode right_finger_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "RightFinger");
    InitialItem right_finger_item = initial_item_reader.get_initial_item(right_finger_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_RIGHT_FINGER, right_finger_item));
    
    // LFinger
    XMLNode left_finger_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "LeftFinger");
    InitialItem left_finger_item = initial_item_reader.get_initial_item(left_finger_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_LEFT_FINGER, left_finger_item));
    
    // RHand
    XMLNode WIELDED_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Wielded");
    InitialItem WIELDED_item = initial_item_reader.get_initial_item(WIELDED_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_WIELDED, WIELDED_item));
    
    // LHand
    XMLNode OFF_HAND_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "OffHand");
    InitialItem OFF_HAND_item = initial_item_reader.get_initial_item(OFF_HAND_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_OFF_HAND, OFF_HAND_item));

    // Body
    XMLNode body_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Body");
    InitialItem body_item = initial_item_reader.get_initial_item(body_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_BODY, body_item));
    
    // About Body
    XMLNode about_body_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "AboutBody");
    InitialItem about_body_item = initial_item_reader.get_initial_item(about_body_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_ABOUT_BODY, about_body_item));
    
    // Feet
    XMLNode feet_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Feet");
    InitialItem feet_item = initial_item_reader.get_initial_item(feet_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_FEET, feet_item));
    
    // Ranged
    XMLNode ranged_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Ranged");
    InitialItem ranged_item = initial_item_reader.get_initial_item(ranged_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_RANGED_WEAPON, ranged_item));
    
    // Ammunition
    XMLNode ammunition_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Ammunition");
    InitialItem ammunition = initial_item_reader.get_initial_item(ammunition_node);
    initial_equipment.insert(make_pair(EQUIPMENT_WORN_AMMUNITION, ammunition));
    
    current_class->set_initial_equipment(initial_equipment);
  }
}

// Parse the initial items into the inv.
void XMLClassesReader::parse_initial_inventory(ClassPtr current_class, const XMLNode& initial_inv_node)
{
  if (current_class && !initial_inv_node.is_null())
  {
    vector<InitialItem> initial_inventory;
    vector<XMLNode> initial_item_nodes = XMLUtils::get_elements_by_local_name(initial_inv_node, "InitialItem");
    
    BOOST_FOREACH(XMLNode node, initial_item_nodes)
    {
      InitialItem initial_item = initial_item_reader.get_initial_item(node);
      initial_inventory.push_back(initial_item);
    }
    
    current_class->set_initial_inventory(initial_inventory);
  }
}
