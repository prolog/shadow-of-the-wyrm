#include "PacificationCalculator.hpp"

// The chance to pacify musically is:
//
// The musician's music score
// + half the musician's level
// + half the musician's charisma
// - half the opponent's level
// - half the opponent's willpower
int PacificationCalculator::calculate_pct_chance_pacify_music(CreaturePtr music_creature, CreaturePtr fov_creature)
{
  int pct_chance_pacify = 0;

  if (music_creature != nullptr && fov_creature != nullptr)
  {
    int music_val = music_creature->get_skills().get_value(SkillType::SKILL_GENERAL_MUSIC);
    int music_lvl = music_creature->get_level().get_current() / 2;
    int music_cha = music_creature->get_charisma().get_current() / 2;
    int opp_lvl   = fov_creature->get_level().get_current() / 2;
    int opp_will  = fov_creature->get_willpower().get_current() / 2;

    pct_chance_pacify = music_val
                      + music_lvl
                      + music_cha
                      - opp_lvl
                      - opp_will;
  }

  return pct_chance_pacify;
}

#ifdef UNIT_TESTS
#include "unit_tests/PacificationCalculator_test.cpp"
#endif

