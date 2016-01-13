#include "XMLItemReader.hpp"
#include "ItemTypes.hpp"
#include "XMLResistancesReader.hpp"
#include "XMLScriptsReader.hpp"

using namespace std;

// Methods for reading in the base item details
XMLItemReader::XMLItemReader()
{
}

XMLItemReader::~XMLItemReader()
{
}

void XMLItemReader::parse(ItemPtr item, GenerationValues& gv, const XMLNode& item_node)
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

    XMLNode value_node = XMLUtils::get_next_element_by_local_name(item_node, "Value");
    if (!value_node.is_null())
    {
      uint value = static_cast<uint>(XMLUtils::get_node_int_value(value_node, 0));

      item->set_value(value);
    }

    XMLNode weight_node = XMLUtils::get_next_element_by_local_name(item_node, "Weight");
    
    if (!weight_node.is_null())
    {
      Weight weight;
      
      uint pounds = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Pounds"));
      uint ounces = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Ounces"));
      
      weight.set_weight(pounds, ounces);
            
      item->set_weight(weight);
    }

    EquipmentWornLocation location = static_cast<EquipmentWornLocation>(XMLUtils::get_child_node_int_value(item_node, "WornLocation", static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_NONE)));
    item->set_worn_location(location);

    ItemStatus status = static_cast<ItemStatus>(XMLUtils::get_child_node_int_value(item_node, "ItemStatus"));
    item->set_status(status);
    
    bool is_artifact = XMLUtils::get_child_node_bool_value(item_node, "Artifact");
    item->set_artifact(is_artifact);

    // If the item is an artifact, set the maximum to 1.
    if (is_artifact) gv.set_maximum(1);

    int hands_required = XMLUtils::get_child_node_int_value(item_node, "HandsRequired", 1);
    item->set_hands_required(hands_required);

    MaterialType material_type = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(item_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_WOOD)));
    item->set_material_type(material_type);

    // Get whether the item is glowing (visible when blind).
    bool glow = XMLUtils::get_child_node_bool_value(item_node, "Glow", item->get_glowing());

    if (is_artifact)
    {
      glow = true;
    }

    item->set_glowing(glow);
    
    // Overridden text details - most items will not have this, unless a very specific
    // symbol or colour is desired.
    XMLNode text_details_node = XMLUtils::get_next_element_by_local_name(item_node, "TextDetails");
    parse_text_details(item, text_details_node);

    // Danger Level
    int danger_level = XMLUtils::get_child_node_int_value(item_node, "DangerLevel");
    gv.set_danger_level(danger_level);

    // Rarity
    Rarity rarity = static_cast<Rarity>(XMLUtils::get_child_node_int_value(item_node, "Rarity"));
    gv.set_rarity(rarity);

    // Resistances
    XMLNode resistances_node = XMLUtils::get_next_element_by_local_name(item_node, "Resistances");
    if (!resistances_node.is_null())
    {
      XMLResistancesReader rr;
      item->set_resistances(rr.get_resistances(resistances_node));
    }

    // Properties
    XMLNode properties_node = XMLUtils::get_next_element_by_local_name(item_node, "Properties");
    if (!properties_node.is_null())
    {
      map<string, string> addl_props;
      parse_properties(addl_props, properties_node);
      item->set_additional_properties(addl_props);
    }

    // Scripts
    XMLNode item_scripts_node = XMLUtils::get_next_element_by_local_name(item_node, "ItemScripts");
    if (!item_scripts_node.is_null())
    {
      parse_item_scripts(item, item_scripts_node);
    }
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

void XMLItemReader::parse_item_scripts(ItemPtr item, const XMLNode& item_scripts_node)
{
  XMLScriptsReader xsr;

  if (item != nullptr && !item_scripts_node.is_null())
  {
    vector<pair<string, string>> item_scripts = { {"AmmunitionDestructionScript", ItemEventScripts::ITEM_EVENT_AMMO_DESTRUCT} };

    for (const pair<string, string>& script_pair : item_scripts)
    {
      XMLNode node = XMLUtils::get_next_element_by_local_name(item_scripts_node, script_pair.first);
      ScriptDetails sd = xsr.get_script_details(node);
      item->add_event_script(script_pair.second, sd);
    }
  }
}