#include <vector>
#include "XMLDataStructures.hpp"
#include "XMLDeitiesReader.hpp"
#include "XMLModifierReader.hpp"

using namespace std;

// Read all the deities from the XML and place them into a map keyed by deity ID.
DeityMap XMLDeitiesReader::get_deities(const XMLNode& deities_node)
{
  DeityMap deities;
  
  // Need a default deity, always.
  DeityPtr default_deity = std::make_unique<Deity>();
  deities.insert(make_pair(default_deity->get_id(), std::move(default_deity)));

  if (!deities_node.is_null())
  {
    vector<XMLNode> deities_nodes = XMLUtils::get_elements_by_local_name(deities_node, "Deity");
    
    for (const XMLNode& deity_node : deities_nodes)
    {
      DeityPtr deity = parse_deity(deity_node);
      
      if (deity)
      {
        deities.insert(make_pair(deity->get_id(), std::move(deity)));
      }
    }
  }
  
  return deities;
}

// Parse an individual Deity
DeityPtr XMLDeitiesReader::parse_deity(const XMLNode& deity_node)
{
  DeityPtr deity = std::make_unique<Deity>();
  
  if (!deity_node.is_null())
  {
    bool playable    = XMLUtils::get_child_node_bool_value(deity_node, "UserPlayable"); 
    string deity_id  = XMLUtils::get_attribute_value (deity_node, "id");
    string name_sid  = XMLUtils::get_child_node_value(deity_node, "NameSID");
    string sdesc_id  = XMLUtils::get_child_node_value(deity_node, "ShortDescriptionSID");
    string desc_sid  = XMLUtils::get_child_node_value(deity_node, "DescriptionSID");
    string anger_sid = XMLUtils::get_child_node_value(deity_node, "AngerMessageSID");
    string death_sid = XMLUtils::get_child_node_value(deity_node, "DeathMessageSID");
    AlignmentRange alignment = static_cast<AlignmentRange>(XMLUtils::get_child_node_int_value(deity_node, "Alignment"));
    XMLNode dislikes_node = XMLUtils::get_next_element_by_local_name(deity_node, "Dislikes");
    XMLNode likes_node = XMLUtils::get_next_element_by_local_name(deity_node, "Likes");
    XMLNode burial_races_node = XMLUtils::get_next_element_by_local_name(deity_node, "BurialRaces");
    XMLNode generator_filters_node = XMLUtils::get_next_element_by_local_name(deity_node, "GeneratorFilters");
    XMLNode crowning_node = XMLUtils::get_next_element_by_local_name(deity_node, "Crowning");
    int class_crowning_chance = XMLUtils::get_child_node_int_value(deity_node, "ClassCrowningChance");
    XMLNode summons_node  = XMLUtils::get_next_element_by_local_name(deity_node, "Summons");
    WorshipSiteType worship_site_type = static_cast<WorshipSiteType>(XMLUtils::get_child_node_int_value(deity_node, "WorshipSiteType"));
    string anger_script = XMLUtils::get_child_node_value(deity_node, "AngerScript");

    XMLModifierReader mr;
    XMLNode modifier_node = XMLUtils::get_next_element_by_local_name(deity_node, "DeityInitialModifiers");
    Modifier m = mr.get_modifier(modifier_node);
    
    deity->set_user_playable(playable);
    deity->set_id(deity_id);
    deity->set_name_sid(name_sid);
    deity->set_short_description_sid(sdesc_id);
    deity->set_description_sid(desc_sid);
    deity->set_anger_message_sid(anger_sid);
    deity->set_death_message_sid(death_sid);
    deity->set_alignment_range(alignment);
    parse_dislikes(dislikes_node, *deity);
    parse_likes(likes_node, *deity);
    parse_burial_races(burial_races_node, *deity);
    parse_generator_filters(generator_filters_node, *deity);
    parse_crowning_gifts(crowning_node, *deity);
    deity->set_pct_chance_class_crowning(class_crowning_chance);
    parse_summons(summons_node, *deity);
    deity->set_worship_site_type(worship_site_type);
    deity->set_anger_script(anger_script);
    deity->set_initial_modifier(m);
  }
  
  return deity;
}

// Read in the dislikes of a particular deity
void XMLDeitiesReader::parse_dislikes(const XMLNode& dislikes_node, Deity& deity)
{
  if (!dislikes_node.is_null())
  {
    vector<XMLNode> dislike_nodes = XMLUtils::get_elements_by_local_name(dislikes_node, "Action");

    for (const XMLNode& dislike_node : dislike_nodes)
    {
      string dislike_action = XMLUtils::get_node_value(dislike_node);
      deity.set_dislike(dislike_action, true);
    }
  }
}

// Read in what the diety likes
void XMLDeitiesReader::parse_likes(const XMLNode& likes_node, Deity& deity)
{
  if (!likes_node.is_null())
  {
    vector<XMLNode> like_nodes = XMLUtils::get_elements_by_local_name(likes_node, "Action");

    for (const XMLNode& like_node : like_nodes)
    {
      string like_action = XMLUtils::get_node_value(like_node);
      deity.set_like(like_action, true);
    }
  }
}

// Read in the races the deity cares about for burial purposes.
void XMLDeitiesReader::parse_burial_races(const XMLNode& burial_races_node, Deity& deity)
{
  if (!burial_races_node.is_null())
  {
    vector<XMLNode> race_id_nodes = XMLUtils::get_elements_by_local_name(burial_races_node, "RaceID");
    vector<string> race_ids;

    for (const XMLNode& race_id_node : race_id_nodes)
    {
      string race_id = XMLUtils::get_node_value(race_id_node);
      race_ids.push_back(race_id);
    }

    deity.set_burial_races(race_ids);
  }
}

// Read in the generator filters, which are tags used to determine if the
// deity should be the default deity for a particular map.  This is used
// because some creatures can be e.g. priests of one deity or another.
void XMLDeitiesReader::parse_generator_filters(const XMLNode& generator_filters_node, Deity& deity)
{
  if (!generator_filters_node.is_null())
  {
    vector<XMLNode> filter_nodes = XMLUtils::get_elements_by_local_name(generator_filters_node, "Filter");
    vector<string> filters;

    for (const XMLNode& filter_node : filter_nodes)
    {
      string filter = XMLUtils::get_node_value(filter_node);
      filters.push_back(filter);
    }

    deity.set_generator_filters(filters);
  }
}

// Read in the deity's summons (the things it summons when angered).
void XMLDeitiesReader::parse_summons(const XMLNode& summons_node, Deity& deity)
{
  if (!summons_node.is_null())
  {
    vector<XMLNode> summon_nodes = XMLUtils::get_elements_by_local_name(summons_node, "Summon");
    vector<string> summons;

    for (const XMLNode& node : summon_nodes)
    {
      string summon = XMLUtils::get_node_value(node);
      summons.push_back(summon);
    }

    deity.set_summons(summons);
  }
}

// Read in the deity's crowning gifts
void XMLDeitiesReader::parse_crowning_gifts(const XMLNode& crowning_node, Deity& deity)
{
  vector<string> crowning_gifts = get_crowning_gifts(crowning_node);
  deity.set_crowning_gifts(crowning_gifts);
}
