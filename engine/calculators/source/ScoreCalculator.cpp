#include "ScoreCalculator.hpp"
#include "ScoreConstants.hpp"

ulonglong ScoreCalculator::calculate_score(CreaturePtr creature)
{
  ulonglong score = 0;

  if (creature != nullptr)
  {
    Inventory& inv = creature->get_inventory();

    // Did the player win?
    Mortuary& mortuary = creature->get_mortuary_ref();
    if (mortuary.get_num_creature_killed("end_boss") > 0)
    {
      score += ScoreConstants::END_BOSS_BONUS;
    }

    // Spending ivory can help in game, but saving it helps after.
    ItemPtr item = inv.get_from_base_id(ItemIdKeys::ITEM_ID_CURRENCY);
    if (item != nullptr)
    {
      score += item->get_quantity();
    }
  }

  return score;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScoreCalculator_test.cpp"
#endif
