#include "XMLInitialItemReader.hpp"

using namespace std;

// Methods for reading in an InitialItem, which represents a number of potential items that
// can be generated on creature/character creation.
XMLInitialItemReader::XMLInitialItemReader()
{
}

XMLInitialItemReader::~XMLInitialItemReader()
{
}

InitialItem XMLInitialItemReader::get_initial_item(const XMLNode& initial_item_node)
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
Dice XMLInitialItemReader::parse_quantity(const XMLNode& quantity_node) const
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
vector<pair<string, Dice>> XMLInitialItemReader::get_random_item_ids(const XMLNode& initial_random_node) const
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
map<string, pair<string, Dice>> XMLInitialItemReader::get_racial_item_ids(const XMLNode& initial_racial_node) const
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

