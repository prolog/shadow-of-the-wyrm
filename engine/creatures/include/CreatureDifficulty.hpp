#pragma once
#include "Creature.hpp"

// CreatureDifficulty describes the level difference between creature A
// and B.  If creature B is about the same level, it should have Fair
// difficulty - if it's less, Easy, if more, Hard, etc.
//
// This provides a way for the player to look at monsters and get a
// quick read on how difficult they might be.
class CreatureDifficulty
{
  public:
    CreatureDifficulty();

    std::string get_difficulty_text_sid(CreaturePtr appraising_creature, CreaturePtr target_creature);

  protected:
    void initialize_difficulty_map();

    static std::map<int, std::string, std::greater<int>> difficulty_mappings;
    static const int HARMLESS_THRESHOLD;
    static const int EASY_THRESHOLD;
    static const int CAPABLE_THRESHOLD;
    static const int DANGEROUS_THRESHOLD;
    static const int DEADLY_THRESHOLD;
};

