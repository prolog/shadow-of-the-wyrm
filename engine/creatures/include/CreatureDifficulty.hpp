#pragma once
#include "Creature.hpp"

// CreatureDifficulty describes indicators that show how difficult
// a creature is, how badly they're beat up, etc.
//
// This provides a way for the player to look at monsters and get a
// quick read on how difficult they might be, how much HP they
// might have remaining, etc.
class CreatureDifficulty
{
  public:
    CreatureDifficulty();

    std::string get_difficulty_text_sid(CreaturePtr appraising_creature, CreaturePtr target_creature);
    std::string get_health_indicator_sid(CreaturePtr target_creature);

  protected:
    void initialize_difficulty_map();
    void initialize_hp_indicator_map();

    static std::map<int, std::string, std::greater<int>> difficulty_mappings;
    static const int HARMLESS_THRESHOLD;
    static const int EASY_THRESHOLD;
    static const int CAPABLE_THRESHOLD;
    static const int DANGEROUS_THRESHOLD;
    static const int DEADLY_THRESHOLD;

    static std::map<int, std::string, std::greater<int>> hp_ind_mappings;
    static const int HP_INDICATOR_UNHARMED;
    static const int HP_INDICATOR_SCRATCHES;
    static const int HP_INDICATOR_WOUNDED;
    static const int HP_INDICATOR_BADLY_WOUNDED;
    static const int HP_INDICATOR_VERGE_OF_DEATH;
};

