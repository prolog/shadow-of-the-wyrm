#include "ReligionConstants.hpp"
#include "RNG.hpp"
#include "SpellbookCalculator.hpp"
#include "SpellConstants.hpp"

using namespace std;

const int SpellbookCalculator::BASE_PCT_CHANCE_WILD_INCINERATION = 5;
const int SpellbookCalculator::MAX_PCT_CHANCE_WILD_INCINERATION = 80;
const int SpellbookCalculator::DIVINE_DIFFICULTY_GODLESS_MODIFIER = -100;
const int SpellbookCalculator::DIVINE_CASTINGS_GODLESS_DIVISOR = 5;

SpellbookCalculator::SpellbookCalculator()
{
  initialize_status_failure_levels();
  initialize_status_casting_multipliers();
}

int SpellbookCalculator::calculate_pct_chance_wild_incineration(const uint quantity)
{
  int pct_chance = BASE_PCT_CHANCE_WILD_INCINERATION * static_cast<int>(quantity);
  pct_chance = std::min<int>(pct_chance, MAX_PCT_CHANCE_WILD_INCINERATION);

  return pct_chance;
}

int SpellbookCalculator::get_ap_amount(const int spell_ap, CreaturePtr creature)
{
  int ap_amount = 0;

  if (creature != nullptr)
  {
    Statistic& ap = creature->get_arcana_points_ref();
    int pts_from_max = ap.get_base() - ap.get_current();
    ap_amount = std::min<int>(spell_ap, pts_from_max);
  }

  return ap_amount;
}

void SpellbookCalculator::initialize_status_failure_levels()
{
  status_failure_levels.clear();

  // The pct chance of being destroyed after a successful reading.
  status_failure_levels = std::map<ItemStatus, int>{{ItemStatus::ITEM_STATUS_CURSED, 100}, {ItemStatus::ITEM_STATUS_UNCURSED, 65}, {ItemStatus::ITEM_STATUS_BLESSED, 45}};
}

void SpellbookCalculator::initialize_status_casting_multipliers()
{
  status_casting_multipliers.clear();

  // 75% as many from a cursed book, 100% as many from an uncursed book, 120% as many from a blessed book.
  status_casting_multipliers = std::map<ItemStatus, float>{ { ItemStatus::ITEM_STATUS_CURSED, 0.75f }, { ItemStatus::ITEM_STATUS_UNCURSED, 1.0f }, { ItemStatus::ITEM_STATUS_BLESSED, 1.2f } };
}

// Learning a spell uses the following mechanic:
//
// - Roll 1d100
// - Add (Magic General Skill / 2)
// - Add (Literacy Skill / 4)
// - Add appropriate magic skill, if > 0; otherwise, Subtract 100.
// - Add (Int / 5)
// - Add (Will / 5)
// - Subtract 10 for every 0.01 BAC
// - Subtract 100 if it's divine magic and the creature is godless
//
// If the resultant number is > Difficulty, the spell is learned.
pair<bool, int> SpellbookCalculator::learn_spell(CreaturePtr creature, const SkillType magic_category, const int difficulty)
{
  pair<bool, int> spell_learned(false, 0);

  if (creature)
  {
    Skills& skills = creature->get_skills();

    int rand = RNG::dice(1, 100);
    int magic_general_skill = skills.get_skill(SkillType::SKILL_GENERAL_MAGIC)->get_value();
    int magic_category_skill_raw = skills.get_skill(magic_category)->get_value();
    int magic_category_skill = (magic_category_skill_raw > 0) ? magic_category_skill_raw 
                                                              : SpellConstants::NO_CATEGORY_SKILL_SPELL_LEARNING_PENALTY;
    int literacy_skill = skills.get_value(SkillType::SKILL_GENERAL_LITERACY);
    int int_stat = creature->get_intelligence().get_current();
    int will_stat = creature->get_willpower().get_current();
    int bac_modifier = static_cast<int>(creature->get_blood().get_blood_alcohol_content() * 100) * 10;

    int godless_modifier = 0;

    if (magic_category == SkillType::SKILL_MAGIC_DIVINE && creature->is_godless())
    {
      godless_modifier = DIVINE_DIFFICULTY_GODLESS_MODIFIER;
    }

    int i = (rand
          + (magic_general_skill / 2)
          + (literacy_skill / 4)
          + magic_category_skill
          + (int_stat / 5)
          + (will_stat / 5))
          - bac_modifier
          + godless_modifier;

    if (i > difficulty)
    {
      spell_learned.first = true;
    }

    spell_learned.second = (i - difficulty);
  }

  return spell_learned;
}

// Get the number of castings available to the creature.
//
// This is calculated as:
//
// min(SpellConstants::MIN_CASTINGS,
//      (spellbook status factor * 
//         (Random value between SpellConstants::MIN_CASTINGS, SpellConstants::MAX_CASTINGS
//       + (Creature's intelligence / 2)
//       + Creature's willpower
//       + (Creature's magic general skill / 4)
//       + (Creature's magic category skill / 2)
//       + (Creature's literacy score / 3)
//       - (Difficulty / 3)))) 
//               / 1 if not godless, 5 if divine magic and godless
//
//  If the creature is 
int SpellbookCalculator::get_num_castings(CreaturePtr creature, const SkillType magic_category, const ItemStatus spellbook_status, const int difficulty)
{
  int castings = 0;

  if (creature != nullptr) 
  {
    Skills& skills = creature->get_skills();
    int int_score = creature->get_intelligence().get_current();
    int will_score = creature->get_willpower().get_current();
    int magic_general_score = skills.get_skill(SkillType::SKILL_GENERAL_MAGIC)->get_value();
    int magic_category_score = skills.get_skill(magic_category)->get_value();
    int literacy_score = skills.get_skill(SkillType::SKILL_GENERAL_LITERACY)->get_value();
    int random_factor = RNG::range(SpellConstants::BASE_MIN_CASTINGS, SpellConstants::BASE_MAX_CASTINGS);
    int divisor = 1;

    if (magic_category == SkillType::SKILL_MAGIC_DIVINE && creature->is_godless())
    {
      divisor = DIVINE_CASTINGS_GODLESS_DIVISOR;
    }

    int calculated_castings = random_factor
      + (int_score / 2)
      + will_score
      + (magic_general_score / 4)
      + (magic_category_score / 2)
      + (literacy_score / 3)
      - (difficulty / 3);

    calculated_castings = static_cast<int>(calculated_castings * status_casting_multipliers[spellbook_status]);
    calculated_castings = calculated_castings / divisor;

    castings = std::max<int>(SpellConstants::MIN_CASTINGS, calculated_castings);
  }

  return castings;
}

// Check to see if the spellbook is destroyed after a successful reading.
bool SpellbookCalculator::get_is_spellbook_destroyed(const ItemStatus spellbook_status)
{
  bool spellbook_destroyed = false;

  int failure_check = RNG::dice(1, 100);
  int failure_level = status_failure_levels[spellbook_status];

  if (failure_check <= failure_level)
  {
    spellbook_destroyed = true;
  }

  return spellbook_destroyed;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpellbookCalculator_test.cpp"
#endif
