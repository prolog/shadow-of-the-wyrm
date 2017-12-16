#include "PacificationCalculator.hpp"

const int PacificationCalculator::MAX_PCT_CHANCE_PACIFY_MUSIC = 90;
const int PacificationCalculator::CHARMS_BONUS = 25;

// The chance to pacify musically is:
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
    int music_val = music_creature->get_skills().get_value(SkillType::SKILL_GENERAL_MUSIC);
    int music_lvl = music_creature->get_level().get_current() / 2;
    int music_cha = music_creature->get_charisma().get_current() / 2;
    int opp_music = fov_creature->get_skills().get_value(SkillType::SKILL_GENERAL_MUSIC);
    int opp_lvl   = fov_creature->get_level().get_current() / 2;
    int opp_will  = fov_creature->get_willpower().get_current() / 2;
    int charms    = charms_creature ? CHARMS_BONUS : 0;
    int status    = get_item_status_bonus(item_status);

    pct_chance_pacify = music_val
                      + music_lvl
                      + music_cha
                      - opp_music
                      - opp_lvl
                      - opp_will
                      + charms
                      + status;
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

#ifdef UNIT_TESTS
#include "unit_tests/PacificationCalculator_test.cpp"
#endif

