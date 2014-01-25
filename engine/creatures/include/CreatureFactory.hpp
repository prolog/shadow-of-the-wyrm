#pragma once
#include <string>
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "Deity.hpp"

class CreatureFactory
{
  public:
    CreatureFactory();

    void set_hostility_for_creatures(const bool override_host, const bool host);

    CreaturePtr create_by_creature_id(ActionManager& am, const std::string& creature_id);
    CreaturePtr create_by_race_and_class(ActionManager& am, const std::string& race_id, const std::string& class_id, const std::string& creature_name, const CreatureSex creature_sex, const std::string& deity_id = "");

  protected:
    void revert_to_original_configuration_values(CreaturePtr newly_created_creature, const Creature& configuration_instance, DecisionStrategyPtr template_decision_strategy);

    void set_age(CreaturePtr creature, const AgeInfo& age_info);
    void set_initial_statistics(CreaturePtr creature, RacePtr race, ClassPtr char_class, DeityPtr deity);
    void set_default_resistances(CreaturePtr creature);
    void set_initial_resistances(CreaturePtr creature, RacePtr race, ClassPtr char_class);
    void set_initial_skills(CreaturePtr creature, RacePtr race, ClassPtr char_class);
    HairColour get_random_hair_colour();
    EyeColour get_random_eye_colour();
    
    // Additional NPC functions
    void set_hostility_to_player(CreaturePtr npc);

    // Called to initialize a new ID and set any other ID-like values that are more for
    // book-keeping than game-playing.
    void initialize(CreaturePtr creature);

    bool override_hostility_setting;
    bool create_hostile;
};
