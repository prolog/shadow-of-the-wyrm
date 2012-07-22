#pragma once
#include <string>
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "Deity.hpp"

class CreatureFactory
{
  public:
    static CreaturePtr create_by_creature_id(ActionManager& am, const std::string& creature_id);
    static CreaturePtr create_by_race_and_class(ActionManager& am, const std::string& race_id, const std::string& class_id, const std::string& creature_name, const CreatureSex creature_sex, const std::string& deity_id = "");

  protected:
    static Creature set_age(const Creature& creature, const AgeInfo& age_info);
    static Creature set_initial_statistics(const Creature& creature, RacePtr race, ClassPtr char_class, DeityPtr deity);
    static void     set_default_resistances(CreaturePtr creature);
    static Creature set_initial_resistances(const Creature& creature, RacePtr race, ClassPtr char_class);
    static Creature set_initial_skills(const Creature& creature, RacePtr race, ClassPtr char_class);
    static HairColour get_random_hair_colour();
    static EyeColour get_random_eye_colour();

    // Called to initialize a new ID and set any other ID-like values that are more for
    // book-keeping than game-playing.
    static void initialize(CreaturePtr creature);
};
