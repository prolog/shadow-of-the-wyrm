#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_PacificationCalculator, calculate_pct_chance_pacify_music)
{
  CreaturePtr music_creature;
  CreaturePtr fov_creature;
  PacificationCalculator pc;

  EXPECT_EQ(0, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature));

  music_creature = std::make_shared<Creature>();
  fov_creature = std::make_shared<Creature>();

  music_creature->get_skills().set_value(SkillType::SKILL_GENERAL_MUSIC, 30);
  music_creature->set_level(10);
  fov_creature->set_level(5);

  music_creature->set_charisma(22);
  fov_creature->set_willpower(10);

  EXPECT_EQ(39, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature));
}

