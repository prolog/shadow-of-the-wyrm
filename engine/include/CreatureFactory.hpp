#pragma once
#include <string>

class Creature;

class CreatureFactory
{
  public:
    static Creature create_by_creature_id(const std::string& creature_id);
    static Creature create_by_race_and_class(const std::string& race_id, const std::string& class_id, const std::string& creature_name);

  protected:
    static Creature set_initial_statistics(Creature creature, RacePtr race, ClassPtr char_class);
    static Creature set_initial_resistances(Creature creature, RacePtr race, ClassPtr char_class);
    static Creature set_initial_skills(Creature creature, RacePtr race, ClassPtr char_class);
};
