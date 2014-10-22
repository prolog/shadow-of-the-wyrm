#include <vector>
#include "XMLDataStructures.hpp"
#include "XMLDeitiesReader.hpp"
#include "XMLStatisticsModifierReader.hpp"

using namespace std;

// Read all the deities from the XML and place them into a map keyed by deity ID.
DeityMap XMLDeitiesReader::get_deities(const XMLNode& deities_node)
{
  DeityMap deities;
  
  // Need a default deity, always.
  DeityPtr default_deity = std::make_shared<Deity>();
  deities.insert(make_pair(default_deity->get_id(), default_deity));

  if (!deities_node.is_null())
  {
    vector<XMLNode> deities_nodes = XMLUtils::get_elements_by_local_name(deities_node, "Deity");
    
    for (const XMLNode& deity_node : deities_nodes)
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
    deity = std::make_shared<Deity>();

    bool playable    = XMLUtils::get_child_node_bool_value(deity_node, "UserPlayable"); 
    string deity_id  = XMLUtils::get_attribute_value (deity_node, "id");
    string name_sid  = XMLUtils::get_child_node_value(deity_node, "NameSID");
    string sdesc_id  = XMLUtils::get_child_node_value(deity_node, "ShortDescriptionSID");
    string desc_sid  = XMLUtils::get_child_node_value(deity_node, "DescriptionSID");
    string anger_sid = XMLUtils::get_child_node_value(deity_node, "AngerMessageSID");
    string death_sid = XMLUtils::get_child_node_value(deity_node, "DeathMessageSID");
    AlignmentRange alignment = static_cast<AlignmentRange>(XMLUtils::get_child_node_int_value(deity_node, "Alignment"));
    XMLNode dislikes_node = XMLUtils::get_next_element_by_local_name(deity_node, "Dislikes");
    XMLNode crowning_node = XMLUtils::get_next_element_by_local_name(deity_node, "Crowning");
    XMLNode summons_node  = XMLUtils::get_next_element_by_local_name(deity_node, "Summons");
    WorshipSiteType worship_site_type = static_cast<WorshipSiteType>(XMLUtils::get_child_node_int_value(deity_node, "WorshipSiteType"));
    string anger_script = XMLUtils::get_child_node_value(deity_node, "AngerScript");

    XMLStatisticsModifierReader smr;
    XMLNode statistics_modifier_node = XMLUtils::get_next_element_by_local_name(deity_node, "DeityInitialModifiers");
    StatisticsModifier sm = smr.get_statistics_modifier(statistics_modifier_node);
    
    deity->set_user_playable(playable);
    deity->set_id(deity_id);
    deity->set_name_sid(name_sid);
    deity->set_short_description_sid(sdesc_id);
    deity->set_description_sid(desc_sid);
    deity->set_anger_message_sid(anger_sid);
    deity->set_death_message_sid(death_sid);
    deity->set_alignment_range(alignment);
    parse_dislikes(dislikes_node, deity);
    parse_crowning_gifts(crowning_node, deity);
    parse_summons(summons_node, deity);
    deity->set_worship_site_type(worship_site_type);
    deity->set_anger_script(anger_script);
    deity->set_initial_statistics_modifier(sm);
  }
  
  return deity;
}

// Read in the dislikes of a particular deity
void XMLDeitiesReader::parse_dislikes(const XMLNode& dislikes_node, DeityPtr deity)
{
  if (deity && !dislikes_node.is_null())
  {
    vector<XMLNode> dislike_nodes = XMLUtils::get_elements_by_local_name(dislikes_node, "Action");

    for (const XMLNode& dislike_node : dislike_nodes)
    {
      string dislike_action = XMLUtils::get_node_value(dislike_node);
      deity->set_dislike(dislike_action, true);
    }
  }
}

// Read in the deity's summons (the things it summons when angered).
void XMLDeitiesReader::parse_summons(const XMLNode& summons_node, DeityPtr deity)
{
  if (deity && !summons_node.is_null())
  {
    vector<XMLNode> summon_nodes = XMLUtils::get_elements_by_local_name(summons_node, "Summon");
    vector<string> summons;

    for (const XMLNode& node : summon_nodes)
    {
      string summon = XMLUtils::get_node_value(node);
      summons.push_back(summon);
    }

    deity->set_summons(summons);
  }
}

// Read in the deity's crowning gifts
void XMLDeitiesReader::parse_crowning_gifts(const XMLNode& crowning_node, DeityPtr deity)
{
  if (deity && !crowning_node.is_null())
  {
    vector<XMLNode> artifact_nodes = XMLUtils::get_elements_by_local_name(crowning_node, "Artifact");
    vector<string> artifacts;

    for (const XMLNode& artifact_node : artifact_nodes)
    {
      string artifact = XMLUtils::get_node_value(artifact_node);
      artifacts.push_back(artifact);
    }

    deity->set_crowning_gifts(artifacts);
  }
}
