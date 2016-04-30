#include "FishingCalculator.hpp"

using namespace std;

vector<pair<FishingOutcomeType, int>> FishingCalculator::calculate_fishing_outcomes(CreaturePtr creature)
{
  vector<pair<FishingOutcomeType, int>> outcomes;

  if (creature != nullptr)
  {
    int fishing = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_FISHING);

    int pct_catch = std::max(1, fishing / 2);
    int pct_nibble = std::max(0, pct_catch - 4);
    int pct_escape = std::max(0, pct_catch - 9);
    int pct_no_catch = 100; // the default if none of the other outcomes occurs.

    outcomes = {{FishingOutcomeType::FISHING_OUTCOME_CATCH, pct_catch},
               {FishingOutcomeType::FISHING_OUTCOME_NIBBLE, pct_nibble},
               {FishingOutcomeType::FISHING_OUTCOME_ESCAPE, pct_escape},
               {FishingOutcomeType::FISHING_OUTCOME_NO_CATCH, pct_no_catch}};
  }

  return outcomes;
}

#ifdef UNIT_TESTS
#include "unit_tests/FishingCalculator_test.cpp"
#endif
