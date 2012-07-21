#include <boost/foreach.hpp>
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
    
    XMLNode random_node = XMLUtils::get_next_element_by_local_name(initial_item_node, "Random");
    vector<string> random_item_ids = get_random_item_ids(random_node);
    item.set_random_item_ids(random_item_ids);

    XMLNode racial_node = XMLUtils::get_next_element_by_local_name(initial_item_node, "Races");
    map<string, string> racial_item_ids = get_racial_item_ids(racial_node);
    item.set_racial_item_ids(racial_item_ids);
  }
  
  return item;
}

// Get all the random ids
vector<string> XMLInitialItemReader::get_random_item_ids(const XMLNode& initial_random_node) const
{
  vector<string> random_ids;
  
  if (!initial_random_node.is_null())
  {
    vector<XMLNode> nodes = XMLUtils::get_elements_by_local_name(initial_random_node, "ID");
    
    BOOST_FOREACH(XMLNode node, nodes)
    {
      string item_id = XMLUtils::get_node_value(node);
      random_ids.push_back(item_id);
    }
  }
  
  return random_ids;
}

// Get all the racial ids
map<string, string> XMLInitialItemReader::get_racial_item_ids(const XMLNode& initial_racial_node) const
{
  map<string, string> racial_ids;
  
  if (!initial_racial_node.is_null())
  {
    vector<XMLNode> race_nodes = XMLUtils::get_elements_by_local_name(initial_racial_node, "Race");
    
    BOOST_FOREACH(XMLNode node, race_nodes)
    {
      string race_id = XMLUtils::get_child_node_value(node, "RaceID");
      string item_id = XMLUtils::get_child_node_value(node, "ID");
      
      racial_ids.insert(make_pair(race_id, item_id));
    }
  }
  
  return racial_ids;
}

