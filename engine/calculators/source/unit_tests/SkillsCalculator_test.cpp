#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_SkillsCalculator, calculate_general_skills)
{
  RacePtr racep = std::make_unique<Race>();
  ClassPtr classp = std::make_unique<Class>();

  CreaturePtr creature = CreaturePtr(new Creature());

  Skills race_skills;
  Skills class_skills;

  race_skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 5);
  class_skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 7);

  race_skills.set_value(SkillType::SKILL_GENERAL_MOUNTAIN_LORE, 27);

  class_skills.set_value(SkillType::SKILL_GENERAL_WEAVING, 46);

  racep->set_skills(race_skills);
  classp->set_skills(class_skills);

  Skills calculated_skills = SkillsCalculator::calculate_skills(racep.get(), classp.get());

  EXPECT_EQ(0,  calculated_skills.get_value(SkillType::SKILL_GENERAL_COMBAT));
  EXPECT_EQ(12, calculated_skills.get_value(SkillType::SKILL_GENERAL_BOWYER));
  EXPECT_EQ(27, calculated_skills.get_value(SkillType::SKILL_GENERAL_MOUNTAIN_LORE));
  EXPECT_EQ(46, calculated_skills.get_value(SkillType::SKILL_GENERAL_WEAVING));
}

TEST(SW_Engine_Calculators_SkillsCalculator, calculate_melee_weapon_skills)
{
  RacePtr racep = std::make_unique<Race>();
  ClassPtr classp = std::make_unique<Class>();

  CreaturePtr creature = CreaturePtr(new Creature());

  Skills race_skills;
  Skills class_skills;

  race_skills.set_value(SkillType::SKILL_MELEE_AXES, 15);
  class_skills.set_value(SkillType::SKILL_MELEE_AXES, 20);

  race_skills.set_value(SkillType::SKILL_MELEE_DAGGERS, 25);

  class_skills.set_value(SkillType::SKILL_MELEE_SHORT_BLADES, 52);

  racep->set_skills(race_skills);
  classp->set_skills(class_skills);

  Skills calculated_skills = SkillsCalculator::calculate_skills(racep.get(), classp.get());

  EXPECT_EQ(35, calculated_skills.get_value(SkillType::SKILL_MELEE_AXES));
  EXPECT_EQ(25, calculated_skills.get_value(SkillType::SKILL_MELEE_DAGGERS));
  EXPECT_EQ(0,  calculated_skills.get_value(SkillType::SKILL_MELEE_RODS_AND_STAVES));
  EXPECT_EQ(52, calculated_skills.get_value(SkillType::SKILL_MELEE_SHORT_BLADES));
}

TEST(SW_Engine_Calculators_SkillsCalculator, calculate_ranged_weapon_skills)
{
  RacePtr racep = std::make_unique<Race>();
  ClassPtr classp = std::make_unique<Class>();

  CreaturePtr creature = CreaturePtr(new Creature());

  Skills race_skills;
  Skills class_skills;

  race_skills.set_value(SkillType::SKILL_RANGED_BLUDGEONS, 50);
  class_skills.set_value(SkillType::SKILL_RANGED_BLUDGEONS, 4);

  race_skills.set_value(SkillType::SKILL_RANGED_CROSSBOWS, 35);

  class_skills.set_value(SkillType::SKILL_RANGED_SLINGS, 10);

  racep->set_skills(race_skills);
  classp->set_skills(class_skills);

  Skills calculated_skills = SkillsCalculator::calculate_skills(racep.get(), classp.get());

  EXPECT_EQ(0, calculated_skills.get_value(SkillType::SKILL_RANGED_BOWS));
  EXPECT_EQ(54, calculated_skills.get_value(SkillType::SKILL_RANGED_BLUDGEONS));
  EXPECT_EQ(35, calculated_skills.get_value(SkillType::SKILL_RANGED_CROSSBOWS));
  EXPECT_EQ(10, calculated_skills.get_value(SkillType::SKILL_RANGED_SLINGS));
}

TEST(SW_Engine_Calculators_SkillsCalculator, calculate_magic_skills)
{
  RacePtr racep = std::make_unique<Race>();
  ClassPtr classp = std::make_unique<Class>();

  CreaturePtr creature = CreaturePtr(new Creature());

  Skills race_skills;
  Skills class_skills;

  race_skills.set_value(SkillType::SKILL_MAGIC_ARCANE, 6);
  class_skills.set_value(SkillType::SKILL_MAGIC_ARCANE, 16);

  race_skills.set_value(SkillType::SKILL_MAGIC_DIVINE, 12);

  class_skills.set_value(SkillType::SKILL_MAGIC_PRIMORDIAL, 29);

  racep->set_skills(race_skills);
  classp->set_skills(class_skills);

  Skills calculated_skills = SkillsCalculator::calculate_skills(racep.get(), classp.get());

  EXPECT_EQ(22, calculated_skills.get_value(SkillType::SKILL_MAGIC_ARCANE));
  EXPECT_EQ(12, calculated_skills.get_value(SkillType::SKILL_MAGIC_DIVINE));
  EXPECT_EQ(29, calculated_skills.get_value(SkillType::SKILL_MAGIC_PRIMORDIAL));
  EXPECT_EQ(0,  calculated_skills.get_value(SkillType::SKILL_MAGIC_MYSTIC));
}

TEST(SW_Engine_Calculators_SkillsCalculator, calculate_total_treasure_val)
{
  EXPECT_EQ(0, SkillsCalculator::calculate_hidden_treasure_total_skill_value(nullptr, MapType::MAP_TYPE_WORLD, -10));
  EXPECT_EQ(100, SkillsCalculator::calculate_hidden_treasure_total_skill_value(nullptr, MapType::MAP_TYPE_WORLD, 9999));

  CreaturePtr creature = std::make_shared<Creature>();

  EXPECT_EQ(50, SkillsCalculator::calculate_hidden_treasure_total_skill_value(creature, MapType::MAP_TYPE_WORLD, 50));

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_DUNGEONEERING, 50);

  EXPECT_EQ(55, SkillsCalculator::calculate_hidden_treasure_total_skill_value(creature, MapType::MAP_TYPE_WORLD, 50));
  EXPECT_EQ(50, SkillsCalculator::calculate_hidden_treasure_total_skill_value(creature, MapType::MAP_TYPE_OVERWORLD, 50));
}