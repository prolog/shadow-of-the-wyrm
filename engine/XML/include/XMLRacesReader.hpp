#pragma once
#include "Race.hpp"
#include "XMLDataStructures.hpp"

class XMLRacesReader
{
  public:
    RaceMap get_races(const XMLNode& xml_configuration_races_node);

  protected:
    RacePtr parse_race(const XMLNode& race_node);
    void parse_race_initial_statistics(RacePtr race, const XMLNode& initial_statistics_node);
    void parse_race_initial_modifiers(RacePtr race, const XMLNode& initial_modifiers_node);
    void parse_race_resistances(RacePtr race, const XMLNode& resistances_node);
    void parse_race_skills(RacePtr race, const XMLNode& skills_node);
};
