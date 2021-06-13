#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_CorpseCalculator, calculate_chance_successful_skin)
{
  CorpseCalculator cc;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  EXPECT_EQ(35, cc.calculate_chance_successful_skin(creature));

  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 1);
  creature->set_skills(skills);

  EXPECT_EQ(35, cc.calculate_chance_successful_skin(creature));

  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 22);
  creature->set_skills(skills);

  EXPECT_EQ(46, cc.calculate_chance_successful_skin(creature));

  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(85, cc.calculate_chance_successful_skin(creature));

  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 60);
  creature->set_skills(skills);

  EXPECT_EQ(100, cc.calculate_chance_successful_skin(creature));
}

TEST(SW_Engine_Calculators_CorpseCaclulator, calculate_chance_resistance)
{
  CorpseCalculator cc;

  EXPECT_EQ(25, cc.calculate_chance_resistance(nullptr));

  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_EQ(25, cc.calculate_chance_resistance(creature));

  Skills skills;
  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 40);
  creature->set_skills(skills);

  EXPECT_EQ(38, cc.calculate_chance_resistance(creature));

  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(58, cc.calculate_chance_resistance(creature));
  
}

TEST(SW_Engine_Calculators_CorpseCalculator, calculate_chance_corpse)
{
  CorpseCalculator cc;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  EXPECT_EQ(7, cc.calculate_chance_corpse(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 1);
  creature->set_skills(skills);

  EXPECT_EQ(7, cc.calculate_chance_corpse(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 22);
  creature->set_skills(skills);

  EXPECT_EQ(14, cc.calculate_chance_corpse(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(40, cc.calculate_chance_corpse(creature));

  skills.set_value(SkillType::SKILL_GENERAL_HUNTING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(80, cc.calculate_chance_corpse(creature));
}

TEST(SW_Engine_Calculators_CorpseCalculator, calculate_pct_chance_primordial_essence)
{
  CorpseCalculator cc;

  CreaturePtr attacking_creature = std::make_shared<Creature>();
  CreaturePtr deathblow_creature = std::make_shared<Creature>();

  EXPECT_EQ(0, cc.calculate_chance_primordial_essence(nullptr, nullptr));
  EXPECT_EQ(0, cc.calculate_chance_primordial_essence(attacking_creature, nullptr));
  EXPECT_EQ(0, cc.calculate_chance_primordial_essence(nullptr, deathblow_creature));

  Damage d;
  d.set_damage_type(DamageType::DAMAGE_TYPE_SHADOW);
  deathblow_creature->set_base_damage(d);

  EXPECT_EQ(5, cc.calculate_chance_primordial_essence(attacking_creature, deathblow_creature));

  attacking_creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 33);

  EXPECT_EQ(11, cc.calculate_chance_primordial_essence(attacking_creature, deathblow_creature));

  attacking_creature->get_skills().set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, 100);

  EXPECT_EQ(25, cc.calculate_chance_primordial_essence(attacking_creature, deathblow_creature));
}