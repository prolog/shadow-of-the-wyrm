#include "PacificationCalculator.hpp"

const int PacificationCalculator::MAX_PCT_CHANCE_PACIFY_MUSIC = 80;
const int PacificationCalculator::MAX_PCT_CHANCE_TAME_BEASTMASTERY = 80;
const int PacificationCalculator::CHARMS_BONUS = 25;
const int PacificationCalculator::BASE_EXP_PROPORTION_LEADERSHIP = 10;
const int PacificationCalculator::LEADERSHIP_EXP_DIVISOR = 4;
const int PacificationCalculator::LEADERSHIP_DAMAGE_DIVISOR = 4;
const int PacificationCalculator::PCT_CHANCE_PACIFY_MUSIC_ENRAGED = 0;
const int PacificationCalculator::PCT_CHANCE_PACIFY_BEASTMASTERY_ENRAGED = 5;

// The chance to pacify musically is:
//
// 0, if enraged. Otherwise:
// 
// The musician's music score
// + half the musician's level
// + half the musician's charisma
// - the opponent's music score
// - half the opponent's level
// - half the opponent's willpower
// + charms bonus, if specified
// + applicable item status bonus or penalty
int PacificationCalculator::calculate_pct_chance_pacify_music(CreaturePtr music_creature, CreaturePtr fov_creature, bool charms_creature, const ItemStatus item_status) const
{
  int pct_chance_pacify = 0;

  if (music_creature != nullptr && fov_creature != nullptr)
  {
    if (fov_creature->has_status(StatusIdentifiers::STATUS_ID_RAGE))
    {
      pct_chance_pacify = PCT_CHANCE_PACIFY_MUSIC_ENRAGED;
    }
    else
    {
      int music_val = music_creature->get_skills().get_value(SkillType::SKILL_GENERAL_MUSIC);
      int music_lvl = music_creature->get_level().get_current() / 2;
      int music_cha = music_creature->get_charisma().get_current() / 2;
      int opp_music = fov_creature->get_skills().get_value(SkillType::SKILL_GENERAL_MUSIC);
      int opp_lvl = fov_creature->get_level().get_current() / 2;
      int opp_will = fov_creature->get_willpower().get_current() / 2;
      int charms = charms_creature ? CHARMS_BONUS : 0;
      int status = get_item_status_bonus(item_status);

      pct_chance_pacify = music_val
        + music_lvl
        + music_cha
        - opp_music
        - opp_lvl
        - opp_will
        + charms
        + status;
    }
  }

  pct_chance_pacify = std::max<int>(pct_chance_pacify, 0);
  return std::min<int>(pct_chance_pacify, MAX_PCT_CHANCE_PACIFY_MUSIC);
}

int PacificationCalculator::get_item_status_bonus(const ItemStatus status) const
{
  int bonus = 0;

  switch (status)
  {
    case ItemStatus::ITEM_STATUS_CURSED:
      bonus = -20;
      break;
    case ItemStatus::ITEM_STATUS_BLESSED:
      bonus = 20;
      break;
    case ItemStatus::ITEM_STATUS_UNCURSED:
    default:
      bonus = 0;
      break;
  }

  return bonus;
}

// Chance to pacify via beastmastery is:
// 
// - small, if the creature is enraged (5%)
// - otherwise, equal to the tamer's beastmastery plus the level difference
//   between the tamer and tamee.
int PacificationCalculator::calculate_pct_chance_tame_beastmastery(CreaturePtr taming_creature, CreaturePtr tamed_creature)
{
  int taming_pct = 0;

  if (taming_creature != nullptr && tamed_creature != nullptr)
  {
    if (tamed_creature->has_status(StatusIdentifiers::STATUS_ID_RAGE))
    {
      taming_pct = PCT_CHANCE_PACIFY_BEASTMASTERY_ENRAGED;
    }
    else
    {
      taming_pct = taming_creature->get_skills().get_value(SkillType::SKILL_GENERAL_BEASTMASTERY) - 10;
      int level_diff = taming_creature->get_level().get_current() - tamed_creature->get_level().get_current();

      taming_pct += level_diff;

      taming_pct = std::max<int>(taming_pct, 0);
      taming_pct = std::min<int>(taming_pct, MAX_PCT_CHANCE_TAME_BEASTMASTERY);
    }
  }

  return taming_pct;
}

double PacificationCalculator::calculate_exp_proportion(CreaturePtr taming_creature, const SkillType skill)
{
  double exp = 0.0;

  if (taming_creature != nullptr)
  {
    exp = taming_creature->get_skills().get_value(skill) / 100.0;
  }

  return exp;
}

double PacificationCalculator::calculate_exp_proportion_follower_kill(CreaturePtr leader)
{
  double exp = 0.0;

  if (leader != nullptr)
  {
    int base_exp = BASE_EXP_PROPORTION_LEADERSHIP;
    int leadership_val = leader->get_skills().get_value(SkillType::SKILL_GENERAL_LEADERSHIP);

    if (leadership_val > 0)
    {
      base_exp += leadership_val / LEADERSHIP_EXP_DIVISOR;
      exp = base_exp / 100.0;
    }
  }

  return exp;
}

Damage PacificationCalculator::calculate_follower_damage_bonus(CreaturePtr leader)
{
  Damage d;

  if (leader != nullptr)
  {
    int level = leader->get_level().get_current();
    int level_bonus = level / 2;

    int leadership = leader->get_skills().get_value(SkillType::SKILL_GENERAL_LEADERSHIP);
    int leader_bonus = leadership / LEADERSHIP_DAMAGE_DIVISOR;

    d.set_num_dice(1);
    d.set_modifier(level_bonus + leader_bonus);
  }

  return d;
}

#ifdef UNIT_TESTS
#include "unit_tests/PacificationCalculator_test.cpp"
#endif

