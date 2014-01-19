#include "CreatureDifficulty.hpp"
#include "DifficultyTextKeys.hpp"

using namespace std;

map<int, string, greater<int>> CreatureDifficulty::difficulty_mappings;

// Thresholds for the various difficulties - these represent the difference
// between the appraising creature's level and the target creature's.
const int CreatureDifficulty::HARMLESS_THRESHOLD = 8;
const int CreatureDifficulty::EASY_THRESHOLD = 3;
const int CreatureDifficulty::CAPABLE_THRESHOLD = -3;
const int CreatureDifficulty::DANGEROUS_THRESHOLD = -8;
const int CreatureDifficulty::DEADLY_THRESHOLD = std::numeric_limits<int>::min();

CreatureDifficulty::CreatureDifficulty()
{
  if (difficulty_mappings.empty())
  {
    initialize_difficulty_map();
  }
}

void CreatureDifficulty::initialize_difficulty_map()
{
  difficulty_mappings = map<int, string, std::greater<int>>
  {
    { HARMLESS_THRESHOLD, DifficultyTextKeys::DIFFICULTY_HARMLESS },
    { EASY_THRESHOLD, DifficultyTextKeys::DIFFICULTY_EASY },
    { CAPABLE_THRESHOLD, DifficultyTextKeys::DIFFICULTY_CAPABLE },
    { DANGEROUS_THRESHOLD, DifficultyTextKeys::DIFFICULTY_DANGEROUS },
    { DEADLY_THRESHOLD, DifficultyTextKeys::DIFFICULTY_DEADLY }
  };
}

string CreatureDifficulty::get_difficulty_text_sid(CreaturePtr appraising_creature, CreaturePtr target_creature)
{
  string diff_sid;

  if (appraising_creature != nullptr && target_creature != nullptr)
  {
    int appraise_level = appraising_creature->get_level().get_current();
    int target_level = target_creature->get_level().get_current();

    int level_difference = appraise_level - target_level;

    // Iterate over the threshold map.  Once the level difference is greater
    // than the current threshold, we've found our difficulty - stop there.
    for (auto& d_map : difficulty_mappings)
    {
      if (level_difference >= d_map.first)
      {
        return d_map.second;
      }
    }
  }

  return diff_sid;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureDifficulty_test.cpp"
#endif
