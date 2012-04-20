#include <vector>
#include <boost/foreach.hpp>
#include "XMLDataStructures.hpp"
#include "XMLDeitiesReader.hpp"

using namespace std;

// Read all the deities from the XML and place them into a map keyed by deity ID.
DeityMap XMLDeitiesReader::get_deities(const XMLNode& deities_node)
{
  DeityMap deities;
  
  if (!deities_node.is_null())
  {
    vector<XMLNode> deities_nodes = XMLUtils::get_elements_by_local_name(deities_node, "Deity");
    
    BOOST_FOREACH(XMLNode deity_node, deities_nodes)
    {
      DeityPtr deity = parse_deity(deity_node);
      
      if (deity)
      {
        deities.insert(make_pair(deity->get_id(), deity));
      }
    }
  }
  
  return deities;
}

// Parse an individual Deity
DeityPtr XMLDeitiesReader::parse_deity(const XMLNode& deity_node)
{
  DeityPtr deity;
  
  if (!deity_node.is_null())
  {
    deity = DeityPtr(new Deity());
    
    string deity_id  = XMLUtils::get_attribute_value (deity_node, "id");
    string name_sid  = XMLUtils::get_child_node_value(deity_node, "NameSID");
    string sdesc_id  = XMLUtils::get_child_node_value(deity_node, "ShortDescriptionSID");
    string desc_sid  = XMLUtils::get_child_node_value(deity_node, "DescriptionSID");
    string death_sid = XMLUtils::get_child_node_value(deity_node, "DeathMessageSID");
    AlignmentRange alignment = static_cast<AlignmentRange>(XMLUtils::get_child_node_int_value(deity_node, "Alignment"));
    WorshipSiteType worship_site_type = static_cast<WorshipSiteType>(XMLUtils::get_child_node_int_value(deity_node, "WorshipSiteType"));
    
    deity->set_id(deity_id);
    deity->set_name_sid(name_sid);
    deity->set_short_description_sid(sdesc_id);
    deity->set_description_sid(desc_sid);
    deity->set_death_message_sid(death_sid);
    deity->set_alignment_range(alignment);
    deity->set_worship_site_type(worship_site_type);
  }
  
  return deity;
}
