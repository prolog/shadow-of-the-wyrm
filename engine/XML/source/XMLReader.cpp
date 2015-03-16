#include "XMLReader.hpp"
#include "CombatConstants.hpp"

using namespace std;

// Parse the dice from a node according to the Dice format.
void XMLReader::parse_dice(Dice& dice, const XMLNode& dice_node) const
{
  if (!dice_node.is_null())
  {
    uint num_sides = static_cast<uint>(XMLUtils::get_child_node_int_value(dice_node, "NumSides"));
    dice.set_dice_sides(num_sides);

    uint num_dice = static_cast<uint>(XMLUtils::get_child_node_int_value(dice_node, "NumDice"));
    dice.set_num_dice(num_dice);
    
    int modifier = XMLUtils::get_child_node_int_value(dice_node, "Modifier");
    dice.set_modifier(modifier);
  }
}

// Parse the damage from a node according to the Damage format in the schemas, and return a
// Damage object containing the appropriate values.
void XMLReader::parse_damage(Damage& damage, const XMLNode& damage_node) const
{
  if (!damage_node.is_null())
  {
    parse_dice(damage, damage_node);
    
    DamageType damage_type = CombatConstants::DEFAULT_UNARMED_DAMAGE_TYPE;
    damage_type = static_cast<DamageType>(XMLUtils::get_child_node_int_value(damage_node, "Type"));
    damage.set_damage_type(damage_type);

    bool chaotic = XMLUtils::get_attribute_bool_value(damage_node, "chaotic");
    damage.set_chaotic(chaotic);

    bool piercing = XMLUtils::get_attribute_bool_value(damage_node, "piercing");
    damage.set_piercing(piercing);

    int effect_bonus = XMLUtils::get_child_node_int_value(damage_node, "EffectBonus");
    damage.set_effect_bonus(effect_bonus);

    XMLNode status_ailments_node = XMLUtils::get_next_element_by_local_name(damage_node, "StatusAilments");
    if (!status_ailments_node.is_null())
    {
      StatusAilments ailments;
      parse_status_ailments(ailments, status_ailments_node);

      damage.set_status_ailments(ailments);
    }
  }
}

void XMLReader::parse_status_ailments(StatusAilments& status_ailment, const XMLNode& status_ailments_node) const
{
  set<string> ailments;
  vector<XMLNode> status_ailments = XMLUtils::get_elements_by_local_name(status_ailments_node, "Status");

  for (const XMLNode& status : status_ailments)
  {
    string ailment = XMLUtils::get_node_value(status);
    ailments.insert(ailment);
  }

  status_ailment.set_ailments(ailments);
  status_ailment.set_override_defaults(true);
}

void XMLReader::parse_properties(map<string, string>& properties, const XMLNode& properties_node) const
{
  vector<XMLNode> property_nodes = XMLUtils::get_elements_by_local_name(properties_node, "Property");

  for (const XMLNode& property_node : property_nodes)
  {
    string property_name = XMLUtils::get_child_node_value(property_node, "Name");
    string property_value = XMLUtils::get_child_node_value(property_node, "Value");

    properties[property_name] = property_value;
  }
}

void XMLReader::parse_initial_equipment_and_inventory(map<EquipmentWornLocation, InitialItem>& initial_eq, vector<InitialItem>& initial_inv, const XMLNode& initial_eq_and_inv_node)
{
  if (!initial_eq_and_inv_node.is_null())
  {
    parse_initial_equipment(initial_eq, initial_eq_and_inv_node);

    XMLNode initial_inv_node = XMLUtils::get_next_element_by_local_name(initial_eq_and_inv_node, "InitialInventory");
    parse_initial_inventory(initial_inv, initial_inv_node);
  }
}

// Parse the initial items into the eq.
void XMLReader::parse_initial_equipment(map<EquipmentWornLocation, InitialItem>& initial_eq, const XMLNode& initial_eq_node)
{
  if (!initial_eq_node.is_null())
  {
    // Head
    XMLNode head_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Head");
    InitialItem head_item = get_initial_item(head_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_HEAD, head_item));

    // Neck
    XMLNode neck_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Neck");
    InitialItem neck_item = get_initial_item(neck_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_NECK, neck_item));

    // RFinger
    XMLNode right_finger_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "RightFinger");
    InitialItem right_finger_item = get_initial_item(right_finger_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER, right_finger_item));

    // LFinger
    XMLNode left_finger_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "LeftFinger");
    InitialItem left_finger_item = get_initial_item(left_finger_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER, left_finger_item));

    // RHand
    XMLNode wielded_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Wielded");
    InitialItem wielded_item = get_initial_item(wielded_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED, wielded_item));

    // LHand
    XMLNode off_hand_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "OffHand");
    InitialItem off_hand_item = get_initial_item(off_hand_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND, off_hand_item));

    // Body
    XMLNode body_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Body");
    InitialItem body_item = get_initial_item(body_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_BODY, body_item));

    // Around Body
    XMLNode around_body_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "AroundBody");
    InitialItem around_body_item = get_initial_item(around_body_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY, around_body_item));

    // Feet
    XMLNode feet_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Feet");
    InitialItem feet_item = get_initial_item(feet_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_FEET, feet_item));

    // Ranged
    XMLNode ranged_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Ranged");
    InitialItem ranged_item = get_initial_item(ranged_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON, ranged_item));

    // Ammunition
    XMLNode ammunition_node = XMLUtils::get_next_element_by_local_name(initial_eq_node, "Ammunition");
    InitialItem ammunition = get_initial_item(ammunition_node);
    initial_eq.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION, ammunition));
  }
}

// Parse the initial items into the inv.
void XMLReader::parse_initial_inventory(vector<InitialItem>& initial_inv, const XMLNode& initial_inv_node)
{
  if (!initial_inv_node.is_null())
  {
    vector<XMLNode> initial_item_nodes = XMLUtils::get_elements_by_local_name(initial_inv_node, "InitialItem");

    for (const XMLNode& node : initial_item_nodes)
    {
      InitialItem initial_item = get_initial_item(node);
      initial_inv.push_back(initial_item);
    }
  }
}

InitialItem XMLReader::get_initial_item(const XMLNode& initial_item_node)
{
  InitialItem item;

  if (!initial_item_node.is_null())
  {
    string item_id = XMLUtils::get_child_node_value(initial_item_node, "ID");
    item.set_item_id(item_id);

    XMLNode base_item_quantity = XMLUtils::get_next_element_by_local_name(initial_item_node, "Quantity");
    Dice base_quantity = parse_quantity(base_item_quantity);
    item.set_item_quantity(base_quantity);

    XMLNode random_node = XMLUtils::get_next_element_by_local_name(initial_item_node, "Random");
    vector<pair<string, Dice>> random_item_ids = get_random_item_ids(random_node);
    item.set_random_item_ids(random_item_ids);

    XMLNode racial_node = XMLUtils::get_next_element_by_local_name(initial_item_node, "Races");
    map<string, pair<string, Dice>> racial_item_ids = get_racial_item_ids(racial_node);
    item.set_racial_item_ids(racial_item_ids);
  }

  return item;
}

// Parse the quantity
Dice XMLReader::parse_quantity(const XMLNode& quantity_node) const
{
  Dice quantity(1, 1, 0);

  if (!quantity_node.is_null())
  {
    XMLNode amount_node = XMLUtils::get_next_element_by_local_name(quantity_node, "Amount");

    // If a fixed amount has been specified (e.g., 17 items - use 17d1), use that.
    if (!amount_node.is_null())
    {
      int num_dice = XMLUtils::get_node_int_value(amount_node, quantity.get_num_dice());
      quantity.set_num_dice(num_dice);
    }
    // Otherwise, read in the dice values:
    else
    {
      XMLNode random_node = XMLUtils::get_next_element_by_local_name(quantity_node, "Random");
      parse_dice(quantity, random_node);
    }
  }

  return quantity;
}

// Get all the random ids
vector<pair<string, Dice>> XMLReader::get_random_item_ids(const XMLNode& initial_random_node) const
{
  vector<pair<string, Dice>> random_ids;

  if (!initial_random_node.is_null())
  {
    vector<XMLNode> nodes = XMLUtils::get_elements_by_local_name(initial_random_node, "ID");

    XMLNode quantity_node = XMLUtils::get_next_element_by_local_name(initial_random_node, "Quantity");
    Dice quantity = parse_quantity(quantity_node);

    for (const XMLNode& node : nodes)
    {
      string item_id = XMLUtils::get_node_value(node);
      random_ids.push_back(make_pair(item_id, quantity));
    }
  }

  return random_ids;
}

// Get all the racial ids
map<string, pair<string, Dice>> XMLReader::get_racial_item_ids(const XMLNode& initial_racial_node) const
{
  map<string, pair<string, Dice>> racial_ids;

  if (!initial_racial_node.is_null())
  {
    vector<XMLNode> race_nodes = XMLUtils::get_elements_by_local_name(initial_racial_node, "Race");

    for (const XMLNode& node : race_nodes)
    {
      string race_id = XMLUtils::get_child_node_value(node, "RaceID");
      string item_id = XMLUtils::get_child_node_value(node, "ID");

      XMLNode quantity_node = XMLUtils::get_next_element_by_local_name(node, "Quantity");
      Dice quantity = parse_quantity(quantity_node);

      racial_ids.insert(make_pair(race_id, make_pair(item_id, quantity)));
    }
  }

  return racial_ids;
}

