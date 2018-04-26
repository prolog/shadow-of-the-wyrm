#include "Skills.hpp"
#include "StringTable.hpp"
#include "tiles.hpp"
#include "XMLRacesReader.hpp"
#include "XMLDataStructures.hpp"
#include "XMLResistancesReader.hpp"
#include "XMLSkillsReaders.hpp"
#include "XMLModifierReader.hpp"

using namespace std;

RaceMap XMLRacesReader::get_races(const XMLNode& races_node)
{
  RaceMap races;

  // We always need the default race in the mapm regardless of whether there's
  // any XML!
  RacePtr default_race = std::make_shared<Race>();
  races.insert(make_pair(default_race->get_race_id(), default_race));

  if (!races_node.is_null())
  {
    vector<XMLNode> races_nodes = XMLUtils::get_elements_by_local_name(races_node, "Race");

    for (const XMLNode& race_node : races_nodes)
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

    race = std::make_shared<Race>();

    string id = XMLUtils::get_attribute_value(race_node, "id");
    race->set_race_id(id);

    string parent_id = XMLUtils::get_attribute_value(race_node, "parent_id");
    race->set_parent_race_id(parent_id);

    bool user_playable = XMLUtils::get_child_node_bool_value(race_node, "UserPlayable");
    race->set_user_playable(user_playable);

    bool slayable = XMLUtils::get_child_node_bool_value(race_node, "Slayable");
    race->set_slayable(slayable);

    bool leaves_corpse = XMLUtils::get_child_node_bool_value(race_node, "LeavesCorpse");
    race->set_leaves_corpse(leaves_corpse);

    bool corpse_poisoned = XMLUtils::get_child_node_bool_value(race_node, "CorpsePoisoned");
    race->set_corpse_poisoned(corpse_poisoned);

    bool pacifiable = XMLUtils::get_child_node_bool_value(race_node, "Pacifiable");
    race->set_pacifiable(pacifiable);

    bool splits = XMLUtils::get_child_node_bool_value(race_node, "Splits");
    race->set_splits(splits);

    bool has_pockets = XMLUtils::get_child_node_bool_value(race_node, "HasPockets");
    race->set_has_pockets(has_pockets);

    bool has_voice = XMLUtils::get_child_node_bool_value(race_node, "HasVoice");
    race->set_has_voice(has_voice);

    bool has_hair = XMLUtils::get_child_node_bool_value(race_node, "HasHair");
    race->set_has_hair(has_hair);

    XMLNode drops_node = XMLUtils::get_next_element_by_local_name(race_node, "Drops");
    parse_race_drops(race, drops_node);

    bool has_random_villages = XMLUtils::get_child_node_bool_value(race_node, "HasRandomVillages", true);
    race->set_has_random_villages(has_random_villages);
    
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

    bool hungerless = XMLUtils::get_child_node_bool_value(race_node, "Hungerless", race->get_hungerless());
    race->set_hungerless(hungerless);
    
    parse_race_age_info(race, age_info_node);
    parse_race_initial_statistics(race, initial_statistics_node);

    bool corporeal = XMLUtils::get_child_node_bool_value(race_node, "Corporeal", race->get_corporeal().get_base());
    BoolStatistic corporeal_stat(corporeal);
    race->set_corporeal(corporeal_stat);

    bool undead = XMLUtils::get_child_node_bool_value(race_node, "Undead", false);
    BoolStatistic undead_stat(undead);
    race->set_undead(undead_stat);

    bool flying = XMLUtils::get_child_node_bool_value(race_node, "Flying", race->get_flying().get_base());
    BoolStatistic flying_stat(flying);
    race->set_flying(flying_stat);

    bool water_breathing = XMLUtils::get_child_node_bool_value(race_node, "WaterBreathing", false);
    BoolStatistic water_breathing_stat(water_breathing);
    race->set_water_breathing(water_breathing_stat);

    parse_race_initial_modifiers(race, initial_modifiers_node);
    parse_initial_deity_ids(race, initial_deity_ids_node);
    parse_race_resistances(race, resistances_node);
    parse_race_skills(race, skills_node);

    float experience_multiplier = XMLUtils::get_child_node_float_value(race_node, "ExperienceMultiplier");
    race->set_experience_multiplier(experience_multiplier);

    float hp_regen_multiplier = XMLUtils::get_child_node_float_value(race_node, "HPRegenMultiplier", race->get_hp_regen_multiplier());
    race->set_hp_regen_multiplier(hp_regen_multiplier);

    float ap_regen_multiplier = XMLUtils::get_child_node_float_value(race_node, "APRegenMultiplier", race->get_ap_regen_multiplier());
    race->set_ap_regen_multiplier(ap_regen_multiplier);

    int skill_points = XMLUtils::get_child_node_int_value(race_node, "SkillPoints", race->get_skill_points());
    race->set_skill_points(skill_points);

    string race_level_script = XMLUtils::get_child_node_value(race_node, "LevelScript");
    race->set_level_script(race_level_script);
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
    XMLModifierReader modifier_reader;
    
    Modifier m = modifier_reader.get_modifier(initial_modifiers_node);
    race->set_modifier(m);
  }
}

void XMLRacesReader::parse_initial_deity_ids(RacePtr race, const XMLNode& initial_deities_node)
{
  if (race && !initial_deities_node.is_null())
  {
    vector<string> race_deity_ids;
    vector<XMLNode> initial_deity_ids = XMLUtils::get_elements_by_local_name(initial_deities_node, "DeityID");
    
    for (const XMLNode& deity_id_node : initial_deity_ids)
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

void XMLRacesReader::parse_race_drops(RacePtr race, const XMLNode& drops_node)
{
  if (race && !drops_node.is_null())
  {
    vector<XMLNode> drop_nodes = XMLUtils::get_elements_by_local_name(drops_node, "Drop");
    map<string, DropParameters> drop_chances;

    for (const auto& node : drop_nodes)
    {
      string id = XMLUtils::get_child_node_value(node, "ID");
      int pct_chance = XMLUtils::get_child_node_int_value(node, "PercentChance");
      int min = XMLUtils::get_child_node_int_value(node, "Min", 1);
      int max = XMLUtils::get_child_node_int_value(node, "Max", 1);

      DropParameters dp(id, pct_chance, min, max);
      drop_chances[id] = dp;
    }

    race->set_drops(drop_chances);
  }
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
