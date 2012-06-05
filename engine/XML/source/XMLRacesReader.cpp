#include <boost/foreach.hpp>

#include "Skills.hpp"
#include "StringTable.hpp"
#include "XMLRacesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLResistancesReader.hpp"
#include "XMLSkillsReaders.hpp"

using namespace std;

RaceMap XMLRacesReader::get_races(const XMLNode& races_node)
{
  RaceMap races;

  if (!races_node.is_null())
  {
    vector<XMLNode> races_nodes = XMLUtils::get_elements_by_local_name(races_node, "Race");

    BOOST_FOREACH(XMLNode race_node, races_nodes)
    {
      RacePtr race = parse_race(race_node);

      if (race)
      {
        races.insert(make_pair(race->get_race_id(), race));
      }
    }
  }

  return races;
}

RacePtr XMLRacesReader::parse_race(const XMLNode& race_node)
{
  RacePtr race;

  if (!race_node.is_null())
  {
    XMLNode age_info_node           = XMLUtils::get_next_element_by_local_name(race_node, "AgeInfo");
    XMLNode initial_statistics_node = XMLUtils::get_next_element_by_local_name(race_node, "RaceInitialStatistics");
    XMLNode initial_modifiers_node  = XMLUtils::get_next_element_by_local_name(race_node, "RaceInitialModifiers");
    XMLNode initial_deity_ids_node  = XMLUtils::get_next_element_by_local_name(race_node, "RaceInitialDeities");
    XMLNode resistances_node        = XMLUtils::get_next_element_by_local_name(race_node, "Resistances");
    XMLNode skills_node             = XMLUtils::get_next_element_by_local_name(race_node, "Skills");

    race = RacePtr(new Race());

    string id = XMLUtils::get_attribute_value(race_node, "id");
    race->set_race_id(id);

    bool user_playable = XMLUtils::get_child_node_bool_value(race_node, "UserPlayable");
    race->set_user_playable(user_playable);
    
    SettlementType settlement_type = static_cast<SettlementType>(XMLUtils::get_child_node_int_value(race_node, "SettlementType"));
    race->set_settlement_type(settlement_type);
    
    TileType settlement_tile_subtype = static_cast<TileType>(XMLUtils::get_child_node_int_value(race_node, "SettlementTileSubtype"));
    race->set_settlement_tile_subtype(settlement_tile_subtype);

    string race_name_sid = XMLUtils::get_child_node_value(race_node, "NameSID");
    race->set_race_name_sid(race_name_sid);

    string race_short_description_sid = XMLUtils::get_child_node_value(race_node, "ShortDescriptionSID");
    race->set_race_short_description_sid(race_short_description_sid);

    string race_description_sid = XMLUtils::get_child_node_value(race_node, "DescriptionSID");
    race->set_race_description_sid(race_description_sid);

    string race_abbreviation_sid = XMLUtils::get_child_node_value(race_node, "DisplayAbbreviationSID");
    race->set_race_abbreviation_sid(race_abbreviation_sid);

    CreatureSize size = static_cast<CreatureSize>(XMLUtils::get_child_node_int_value(race_node, "Size"));
    race->set_size(size);
    
    parse_race_age_info(race, age_info_node);
    parse_race_initial_statistics(race, initial_statistics_node);
    parse_race_initial_modifiers(race, initial_modifiers_node);
    parse_initial_deity_ids(race, initial_deity_ids_node);
    parse_race_resistances(race, resistances_node);
    parse_race_skills(race, skills_node);

    float experience_multiplier = XMLUtils::get_child_node_float_value(race_node, "ExperienceMultiplier");
    race->set_experience_multiplier(experience_multiplier);
  }

  return race;
}

void XMLRacesReader::parse_race_initial_statistics(RacePtr race, const XMLNode& initial_statistics_node)
{
  if (race && !initial_statistics_node.is_null())
  {
    Statistic initial_strength     = XMLUtils::get_child_node_int_value(initial_statistics_node, "Strength");
    Statistic initial_dexterity    = XMLUtils::get_child_node_int_value(initial_statistics_node, "Dexterity");
    Statistic initial_agility      = XMLUtils::get_child_node_int_value(initial_statistics_node, "Agility");
    Statistic initial_health       = XMLUtils::get_child_node_int_value(initial_statistics_node, "Health");
    Statistic initial_intelligence = XMLUtils::get_child_node_int_value(initial_statistics_node, "Intelligence");
    Statistic initial_willpower    = XMLUtils::get_child_node_int_value(initial_statistics_node, "Willpower");
    Statistic initial_charisma     = XMLUtils::get_child_node_int_value(initial_statistics_node, "Charisma");
    Statistic initial_speed        = XMLUtils::get_child_node_int_value(initial_statistics_node, "Speed");

    race->set_starting_strength(initial_strength);
    race->set_starting_dexterity(initial_dexterity);
    race->set_starting_agility(initial_agility);
    race->set_starting_health(initial_health);
    race->set_starting_intelligence(initial_intelligence);
    race->set_starting_willpower(initial_willpower);
    race->set_starting_charisma(initial_charisma);
    race->set_starting_speed(initial_speed);
  }
}

void XMLRacesReader::parse_race_age_info(RacePtr race, const XMLNode& age_info_node)
{
  if (race && !age_info_node.is_null())
  {
    XMLNode starting_age_node = XMLUtils::get_next_element_by_local_name(age_info_node, "StartingAge");
    XMLNode maximum_age_node  = XMLUtils::get_next_element_by_local_name(age_info_node, "MaximumAge");
    
    Range<uint> start_age = get_age(starting_age_node);
    Range<uint> max_age = get_age(maximum_age_node);
    
    AgeInfo age_info;
    age_info.set_starting_age(start_age);
    age_info.set_maximum_age(max_age);
    
    race->set_age_info(age_info);
  }
}

void XMLRacesReader::parse_race_initial_modifiers(RacePtr race, const XMLNode& initial_modifiers_node)
{
  if (race && !initial_modifiers_node.is_null())
  {
    int valour_modifier = XMLUtils::get_child_node_int_value(initial_modifiers_node, "ValourModifier");
    int spirit_modifier = XMLUtils::get_child_node_int_value(initial_modifiers_node, "SpiritModifier");

    StatisticsModifier sm;
    sm.set_valour_modifier(valour_modifier);
    sm.set_spirit_modifier(spirit_modifier);
    
    race->set_statistics_modifier(sm);
  }
}

void XMLRacesReader::parse_initial_deity_ids(RacePtr race, const XMLNode& initial_deities_node)
{
  if (race && !initial_deities_node.is_null())
  {
    vector<string> race_deity_ids;
    vector<XMLNode> initial_deity_ids = XMLUtils::get_elements_by_local_name(initial_deities_node, "DeityID");
    
    BOOST_FOREACH(XMLNode deity_id_node, initial_deity_ids)
    {
      string deity_id = XMLUtils::get_node_value(deity_id_node);
      race_deity_ids.push_back(deity_id);
    }
    
    if (!race_deity_ids.empty())
    {
      race->set_initial_deity_ids(race_deity_ids);
    }
  }
}

void XMLRacesReader::parse_race_resistances(RacePtr race, const XMLNode& resistances_node)
{
  XMLResistancesReader resistances_reader;

  Resistances race_resistances = resistances_reader.get_resistances(resistances_node);

  race->set_resistances(race_resistances);
}

void XMLRacesReader::parse_race_skills(RacePtr race, const XMLNode& skills_node)
{
  XMLSkillsReader skills_reader;

  Skills race_skills = skills_reader.get_skills(skills_node);

  race->set_skills(race_skills);
}

Range<uint> XMLRacesReader::get_age(const XMLNode& age_node)
{
  Range<uint> age_range(0, 0);

  if (!age_node.is_null())
  {
    uint min = static_cast<uint>(XMLUtils::get_child_node_int_value(age_node, "Min"));
    uint max = static_cast<uint>(XMLUtils::get_child_node_int_value(age_node, "Max"));
    
    age_range.set_min(min);
    age_range.set_max(max);
  }
  
  return age_range;
}
