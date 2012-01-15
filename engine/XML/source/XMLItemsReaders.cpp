#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "XMLItemsReaders.hpp"

using namespace std;
using boost::make_shared;

XMLItemsReader::XMLItemsReader()
{
}

XMLItemsReader::~XMLItemsReader()
{
}

// Gets all the items of the various types and returns them in a map,
// keyed by their ID (specified in the XML).
ItemMap XMLItemsReader::get_items(const XMLNode& items_node)
{
  ItemMap items;
  
  if (!items_node.is_null())
  {
    XMLNode misc_items_node = XMLUtils::get_next_element_by_local_name(items_node, "MiscItems");
    
    if (!misc_items_node.is_null())
    {
      ItemMap misc_items_map = get_misc_items(misc_items_node);
      items.insert(misc_items_map.begin(), misc_items_map.end());
    }
  }
  
  return items;
}

ItemMap XMLItemsReader::get_misc_items(const XMLNode& misc_items_node)
{
  ItemMap misc_items;
  
  if (!misc_items_node.is_null())
  {
    vector<XMLNode> misc_items_nodes = XMLUtils::get_elements_by_local_name(misc_items_node, "Item");
    
    BOOST_FOREACH(XMLNode node, misc_items_nodes)
    {
      ItemPtr sl_item = parse_item(node);
      
      if (sl_item)
      {
        misc_items.insert(make_pair(sl_item->get_id(), sl_item));  
      }
    }
  }
  
  return misc_items;
}

// Parse the elements common to every item.
ItemPtr XMLItemsReader::parse_item(const XMLNode& item_node)
{
  ItemPtr item;
  
  if (!item_node.is_null())
  {
    item = make_shared<Item>();
    
    string id = XMLUtils::get_attribute_value(item_node, "id");
    item->set_id(id);

    string description_sid = XMLUtils::get_child_node_value(item_node, "DescriptionSID");
    item->set_description_sid(description_sid);

    XMLNode weight_node = XMLUtils::get_next_element_by_local_name(item_node, "Weight");
    
    if (!weight_node.is_null())
    {
      Weight weight;
      
      uint pounds = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Pounds"));
      uint ounces = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Ounces"));
      
      weight.set_weight(pounds, ounces);
            
      item->set_weight(weight);
    }

    EquipmentWornLocation location = static_cast<EquipmentWornLocation>(XMLUtils::get_child_node_int_value(item_node, "WornLocation"));
    item->set_worn_location(location);

    ItemStatus status = static_cast<ItemStatus>(XMLUtils::get_child_node_int_value(item_node, "ItemStatus"));
    item->set_status(status);
  }
  
  return item;
}
