#include "MaterialFactory.hpp"
#include "XMLItemReader.hpp"

using namespace std;

// Methods for reading in the base item details
XMLItemReader::XMLItemReader()
{
}

XMLItemReader::~XMLItemReader()
{
}

void XMLItemReader::parse(ItemPtr item, const XMLNode& item_node)
{
  if (item && !item_node.is_null())
  {    
    string id = XMLUtils::get_attribute_value(item_node, "id");
    item->set_id(id);
    item->set_base_id(id);
    
    string description_sid = XMLUtils::get_child_node_value(item_node, "DescriptionSID");
    item->set_description_sid(description_sid);
    
    // If no unidentified description SID/unidentified usage description SID are provided,
    // use the values provided for the description SID and usage description SID
    // (unidentified = identified).
    //
    // In most cases, this is the desired behaviour: e.g., an unidentified dagger can still
    // be identified as a dagger.  This differentiation is mostly for things like herbs,
    // flowers, etc., that have some sort of generic description ("a yellow flower") that
    // should change if the character knows what it is ("a kingsflower").
    string unidentified_description_sid = XMLUtils::get_child_node_value(item_node, "UnidentifiedDescriptionSID");
    if (unidentified_description_sid.empty())
    {
      unidentified_description_sid = description_sid;
    }
    item->set_unidentified_description_sid(unidentified_description_sid);

    string usage_description_sid = XMLUtils::get_child_node_value(item_node, "UsageDescriptionSID");
    item->set_usage_description_sid(usage_description_sid);
    
    string unidentified_usage_description_sid = XMLUtils::get_child_node_value(item_node, "UnidentifiedUsageDescriptionSID");
    if (unidentified_usage_description_sid.empty())
    {
      unidentified_usage_description_sid = usage_description_sid;
    }
    item->set_unidentified_usage_description_sid(unidentified_usage_description_sid);

    XMLNode weight_node = XMLUtils::get_next_element_by_local_name(item_node, "Weight");
    
    if (!weight_node.is_null())
    {
      Weight weight;
      
      uint pounds = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Pounds"));
      uint ounces = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Ounces"));
      
      weight.set_weight(pounds, ounces);
            
      item->set_weight(weight);
    }

    EquipmentWornLocation location = static_cast<EquipmentWornLocation>(XMLUtils::get_child_node_int_value(item_node, "WornLocation", EQUIPMENT_WORN_NONE));
    item->set_worn_location(location);

    ItemStatus status = static_cast<ItemStatus>(XMLUtils::get_child_node_int_value(item_node, "ItemStatus"));
    item->set_status(status);
    
    bool is_artifact = XMLUtils::get_child_node_bool_value(item_node, "Artifact");
    item->set_artifact(is_artifact);
    
    MaterialType material_type = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(item_node, "Material", MATERIAL_TYPE_WOOD));
    MaterialPtr material = MaterialFactory::create_material(material_type);
    item->set_material(material);
    
    // Overridden text details - most items will not have this, unless a very specific
    // symbol or colour is desired.
    XMLNode text_details_node = XMLUtils::get_next_element_by_local_name(item_node, "TextDetails");
    parse_text_details(item, text_details_node);
  }
}

// Typically, all items of a particular type have the same symbol, with a colour based on
// the item type.  Sometimes this needs to be overridden, which is what this function 
// allows.
void XMLItemReader::parse_text_details(ItemPtr item, const XMLNode& text_details_node)
{
  // This function will only be used in a few places - to differentiate rocks from
  // other missiles, for example.
  if (item && !text_details_node.is_null())
  {
    string symbol_s = XMLUtils::get_child_node_value(text_details_node, "Symbol");
    
    if (!symbol_s.empty())
    {
      uchar symbol = symbol_s.at(0);
      item->set_symbol(symbol);
    }
    
    Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(text_details_node, "Colour"));
    item->set_colour(colour);
  }
}
