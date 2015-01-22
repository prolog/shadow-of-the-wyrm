#include <vector>
#include "Resistances.hpp"
#include "XMLClassesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLResistancesReader.hpp"
#include "XMLSkillsReaders.hpp"
#include "XMLModifierReader.hpp"

using namespace std;

ClassMap XMLClassesReader::get_classes(const XMLNode& classes_node)
{
  ClassMap classes;

  // We always need the default class for every creature, regardless
  // of whether there's any XML.
  ClassPtr default_class = std::make_shared<Class>();
  classes.insert(make_pair(default_class->get_class_id(), default_class));

  if (!classes_node.is_null())
  {
    vector<XMLNode> classes_nodes = XMLUtils::get_elements_by_local_name(classes_node, "Class");

    for (const XMLNode& class_node : classes_nodes)
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
    current_class = std::make_shared<Class>();

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

    parse_class_initial_modifiers(current_class, initial_modifiers_node);

    uint hit_dice = XMLUtils::get_child_node_int_value(class_node, "HitDice");
    current_class->set_hit_dice(hit_dice);
    
    uint ap_dice = XMLUtils::get_child_node_int_value(class_node, "APDice");
    current_class->set_ap_dice(ap_dice);

    XMLNode resistances_node = XMLUtils::get_next_element_by_local_name(class_node, "Resistances");
    XMLNode skills_node = XMLUtils::get_next_element_by_local_name(class_node, "Skills");
    XMLNode titles_node = XMLUtils::get_next_element_by_local_name(class_node, "Titles");

    parse_class_resistances(current_class, resistances_node);
    parse_class_skills(current_class, skills_node);
    parse_class_titles(current_class, titles_node);
    
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

    string level_script = XMLUtils::get_child_node_value(class_node, "LevelScript");
    current_class->set_level_script(level_script);
  }

  return current_class;
}

void XMLClassesReader::parse_class_initial_modifiers(ClassPtr current_class, const XMLNode& initial_modifiers_node)
{
  if (current_class && !initial_modifiers_node.is_null())
  {
    XMLModifierReader modifier_reader;
    Modifier m = modifier_reader.get_modifier(initial_modifiers_node);    
    current_class->set_modifier(m);
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

void XMLClassesReader::parse_class_titles(ClassPtr current_class, const XMLNode& titles_node)
{
  if (current_class && !titles_node.is_null())
  {
    string default_title = XMLUtils::get_child_node_value(titles_node, "Default");
    vector<XMLNode> titles_nodes = XMLUtils::get_elements_by_local_name(titles_node, "Title");

    map<int, string> titles{{1, default_title}};

    for (const auto& title_node : titles_nodes)
    {
      int level = XMLUtils::get_child_node_int_value(title_node, "Level");
      string title = XMLUtils::get_child_node_value(title_node, "SID");

      titles.insert(make_pair(level, title));
    }

    current_class->set_titles(titles);
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
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_HEAD, head_item));
    
    // Neck
    XMLNode neck_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Neck");
    InitialItem neck_item = initial_item_reader.get_initial_item(neck_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_NECK, neck_item));

    // RFinger
    XMLNode right_finger_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "RightFinger");
    InitialItem right_finger_item = initial_item_reader.get_initial_item(right_finger_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER, right_finger_item));
    
    // LFinger
    XMLNode left_finger_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "LeftFinger");
    InitialItem left_finger_item = initial_item_reader.get_initial_item(left_finger_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER, left_finger_item));
    
    // RHand
    XMLNode WIELDED_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Wielded");
    InitialItem WIELDED_item = initial_item_reader.get_initial_item(WIELDED_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED, WIELDED_item));
    
    // LHand
    XMLNode OFF_HAND_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "OffHand");
    InitialItem OFF_HAND_item = initial_item_reader.get_initial_item(OFF_HAND_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND, OFF_HAND_item));

    // Body
    XMLNode body_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Body");
    InitialItem body_item = initial_item_reader.get_initial_item(body_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_BODY, body_item));
    
    // Around Body
    XMLNode around_body_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "AroundBody");
    InitialItem around_body_item = initial_item_reader.get_initial_item(around_body_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY, around_body_item));
    
    // Feet
    XMLNode feet_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Feet");
    InitialItem feet_item = initial_item_reader.get_initial_item(feet_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_FEET, feet_item));
    
    // Ranged
    XMLNode ranged_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Ranged");
    InitialItem ranged_item = initial_item_reader.get_initial_item(ranged_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON, ranged_item));
    
    // Ammunition
    XMLNode ammunition_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Ammunition");
    InitialItem ammunition = initial_item_reader.get_initial_item(ammunition_node);
    initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION, ammunition));
    
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
    
    for (const XMLNode& node : initial_item_nodes)
    {
      InitialItem initial_item = initial_item_reader.get_initial_item(node);
      initial_inventory.push_back(initial_item);
    }
    
    current_class->set_initial_inventory(initial_inventory);
  }
}
