#include "ScoreCalculator.hpp"
#include "ScoreConstants.hpp"

ulonglong ScoreCalculator::calculate_score(CreaturePtr creature)
{
  ulonglong score = 0;

  if (creature != nullptr)
  {
    update_score_end_boss(creature, score);
    update_score_currency(creature, score);
    update_score_experience(creature, score);
  }

  return score;
}

// Update the score based on whether the end boss was killed.
void ScoreCalculator::update_score_end_boss(CreaturePtr creature, ulonglong& score)
{
  Mortuary& mortuary = creature->get_mortuary_ref();
  if (mortuary.get_num_creature_killed("end_boss") > 0)
  {
    score += ScoreConstants::END_BOSS_BONUS;
  }
}

// Update the score based on the number of ivory pieces accumulated.
void ScoreCalculator::update_score_currency(CreaturePtr creature, ulonglong& score)
{
  Inventory& inv = creature->get_inventory();

  // Spending ivory can help in game, but saving it helps after.
  ItemPtr item = inv.get_from_base_id(ItemIdKeys::ITEM_ID_CURRENCY);
  if (item != nullptr)
  {
    score += item->get_quantity();
  }
}

void ScoreCalculator::update_score_experience(CreaturePtr creature, ulonglong& score)
{
  uint exp = creature->get_experience_points();

  // ...
}

#ifdef UNIT_TESTS
#include "unit_tests/ScoreCalculator_test.cpp"
#endif
