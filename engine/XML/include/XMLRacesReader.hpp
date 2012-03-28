#pragma once
#include "Race.hpp"
#include "Range.hpp"
#include "XMLDataStructures.hpp"

class XMLRacesReader
{
  public:
    RaceMap get_races(const XMLNode& xml_configuration_races_node);

  protected:
    RacePtr parse_race(const XMLNode& race_node);
    void parse_race_age_info(RacePtr race, const XMLNode& age_info_node);
    void parse_race_initial_statistics(RacePtr race, const XMLNode& initial_statistics_node);
    void parse_race_initial_modifiers(RacePtr race, const XMLNode& initial_modifiers_node);
    void parse_initial_deity_ids(RacePtr race, const XMLNode& initial_deity_ids_node);
    void parse_race_resistances(RacePtr race, const XMLNode& resistances_node);
    void parse_race_skills(RacePtr race, const XMLNode& skills_node);
    
    Range<uint> get_age(const XMLNode& age_node);
};
