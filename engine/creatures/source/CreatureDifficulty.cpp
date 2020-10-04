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

map<int, string, greater<int>> CreatureDifficulty::hp_ind_mappings;

// HP thresholds for the various messages
const int CreatureDifficulty::HP_INDICATOR_UNHARMED = 95;
const int CreatureDifficulty::HP_INDICATOR_SCRATCHES = 80;
const int CreatureDifficulty::HP_INDICATOR_WOUNDED = 50;
const int CreatureDifficulty::HP_INDICATOR_BADLY_WOUNDED = 25;
const int CreatureDifficulty::HP_INDICATOR_VERGE_OF_DEATH = 0;

CreatureDifficulty::CreatureDifficulty()
{
  initialize_difficulty_map();
  initialize_hp_indicator_map();
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

void CreatureDifficulty::initialize_hp_indicator_map()
{
  hp_ind_mappings = map<int, string, greater<int>>
  {
    {HP_INDICATOR_VERGE_OF_DEATH, DifficultyTextKeys::HP_INDICATOR_VERGE_OF_DEATH},
    {HP_INDICATOR_BADLY_WOUNDED, DifficultyTextKeys::HP_INDICATOR_BADLY_WOUNDED},
    {HP_INDICATOR_WOUNDED, DifficultyTextKeys::HP_INDICATOR_WOUNDED},
    {HP_INDICATOR_SCRATCHES, DifficultyTextKeys::HP_INDICATOR_SCRATCHES},
    {HP_INDICATOR_UNHARMED, DifficultyTextKeys::HP_INDICATOR_UNHARMED}
  };
}

string CreatureDifficulty::get_difficulty_text_sid(CreaturePtr appraising_creature, CreaturePtr target_creature)
{
  string diff_sid;

  if (appraising_creature != nullptr && target_creature != nullptr)
  {
    if (Creature::is_ancient_beast(target_creature->get_original_id()))
    {
      return DifficultyTextKeys::DIFFICULTY_UNKNOWN;
    }

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

string CreatureDifficulty::get_health_indicator_sid(CreaturePtr target_creature)
{
  string sid;

  if (target_creature != nullptr)
  {
    Statistic hp = target_creature->get_hit_points();
    int hp_pct = static_cast<int>((static_cast<float>(hp.get_current()) / static_cast<float>(hp.get_base())) * 100.0);

    for (auto ind_it : hp_ind_mappings)
    {
      if (hp_pct >= ind_it.first)
      {
        sid = ind_it.second;
        break;
      }
    }
  }

  return sid;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureDifficulty_test.cpp"
#endif
