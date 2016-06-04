#include "ScoreCalculator.hpp"
#include "ScoreConstants.hpp"

using namespace std;

long long ScoreCalculator::calculate_score(CreaturePtr creature)
{
  long long score = 0;

  if (creature != nullptr)
  {
    update_score_end_boss(creature, score);
    update_score_currency(creature, score);
    update_score_skill_points(creature, score);
    update_score_experience(creature, score);
    update_score_level(creature, score);
    update_score_artifacts(creature, score);
    update_score_spells(creature, score);
    update_score_conducts(creature, score);
  }

  return score;
}

// Update the score based on whether the end boss was killed.
void ScoreCalculator::update_score_end_boss(CreaturePtr creature, long long& score)
{
  Mortuary& mortuary = creature->get_mortuary_ref();
  if (mortuary.get_num_creature_killed("end_boss") > 0)
  {
    score += ScoreConstants::END_BOSS_BONUS;
  }
}

// Update the score based on the number of ivory pieces accumulated.
void ScoreCalculator::update_score_currency(CreaturePtr creature, long long& score)
{
  IInventoryPtr inv = creature->get_inventory();

  // Spending ivory can help in game, but saving it helps after.
  ItemPtr item = inv->get_from_base_id(ItemIdKeys::ITEM_ID_CURRENCY);
  if (item != nullptr)
  {
    score += item->get_quantity();
  }
}

void ScoreCalculator::update_score_skill_points(CreaturePtr creature, long long& score)
{
  int skill_points = creature->get_skill_points();

  score  += (skill_points * 75);
}

void ScoreCalculator::update_score_experience(CreaturePtr creature, long long& score)
{
  uint exp = creature->get_experience_points();
  uint exp_score = 0;

  // For each tier, calculate how many experience points over that tier the
  // player has, multiply that by the tier multiplier, and add that to the
  // score.
  //
  // For example, say the player has 400000 experience points.
  //
  // For having over 100000 points, the player gets 0.1 pts per point
  // over: (400000 - 100000) = 300000 * 0.2 = 30000
  //
  // For having over 10000 points, the player gets 0.2 pts per point
  // over: 90000 over = 90000 * 0.2 = 18000
  //
  // For having over 0 points, the player gets 1 point per, so
  // 10000.
  //
  // Total is 30000 + 18000 + 10000 = 58000.
  vector<pair<uint, double>> exp_tiers = ScoreConstants::EXPERIENCE_TIER_MULTIPLIERS;

  // Make sure it's in descending order, so that we look at the higher
  // tiers first, otherwise, the algorithm below won't work.
  sort(exp_tiers.begin(), exp_tiers.end(), greater<pair<int, double>>());
  size_t num_tiers = exp_tiers.size();

  for (uint i = 0; i < num_tiers; i++)
  {
    pair<uint, double> current_tier = exp_tiers.at(i);
    int next_tier_amount = 0;

    uint tier_amount = current_tier.first;
    double exp_multiplier = current_tier.second;

    if (i < (num_tiers - 1))
    {
      next_tier_amount = exp_tiers.at(i+1).first;
    }

    if (exp < tier_amount)
    {
      continue;
    }

    if (exp > tier_amount)
    {
      exp = exp - tier_amount;
    }
    else if (exp == tier_amount)
    {
      exp = tier_amount - next_tier_amount;
    }
    
    exp_score += static_cast<int>(exp * exp_multiplier);
    exp = tier_amount;
  }

  score += exp_score;
}

// If the player gained levels, count that.
void ScoreCalculator::update_score_level(CreaturePtr creature, long long& score)
{
  uint current_level = creature->get_level().get_current();

  if (current_level > 1)
  {
    score += (current_level * ScoreConstants::LEVEL_MULTIPLIER);
  }
}

// For each artifact collected, add its value to the score.
void ScoreCalculator::update_score_artifacts(CreaturePtr creature, long long& score)
{
  long long eq_score = 0;

  Equipment& eq = creature->get_equipment();
  IInventoryPtr inv = creature->get_inventory();

  EquipmentMap em = eq.get_equipment();

  for (const auto& eq_pair : em)
  {
    ItemPtr item = eq_pair.second;

    if (item != nullptr && item->get_artifact())
    {
      eq_score += item->get_value();
    }
  }

  list<ItemPtr> items = inv->get_items_cref();
  for (ItemPtr item : items)
  {
    if (item != nullptr && item->get_artifact())
    {
      eq_score += item->get_value();
    }
  }

  score += eq_score;
}

// The creature gets a few points for each spell casting.
void ScoreCalculator::update_score_spells(CreaturePtr creature, long long& score)
{
  if (creature != nullptr)
  {
    SpellKnowledgeMap skm = creature->get_spell_knowledge_ref().get_known_spells();
    
    for (auto& spell_pair : skm)
    {
      uint castings = spell_pair.second.get_castings();
      uint bonus = spell_pair.second.get_bonus().get_current();

      score += (castings * 4);
      score += (bonus * 2);
    }
  }
}

void ScoreCalculator::update_score_conducts(CreaturePtr creature, long long& score)
{
  if (creature != nullptr)
  {
    // Each conduct is worth 100 points per level at the end of the game
    int level = creature->get_level().get_current();

    Conducts cond = creature->get_conducts_ref();

    auto cond_array = cond.get_conducts();

    for (const auto& conduct : cond_array)
    {
      if (conduct == true)
      {
        score += (100 * level);
      }
    }
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/ScoreCalculator_test.cpp"
#endif
