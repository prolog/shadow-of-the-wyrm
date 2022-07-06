#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_LineOfSightCalculator, tod_penalty)
{
  CreaturePtr creature = std::make_shared<Creature>();
  LineOfSightCalculator losc;

  int los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_DAY);
  EXPECT_EQ(6, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_DUSK);
  EXPECT_EQ(5, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_DAWN);
  EXPECT_EQ(5, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_NIGHT);
  EXPECT_EQ(3, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_UNDERWORLD, TimeOfDayType::TIME_OF_DAY_NIGHT);
  EXPECT_EQ(6, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_COSMOS, TimeOfDayType::TIME_OF_DAY_NIGHT);
  EXPECT_EQ(6, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_AIR, TimeOfDayType::TIME_OF_DAY_NIGHT);
  EXPECT_EQ(3, los_length);
}

TEST(SW_Engine_Calculators_LineOfSightCalculator, night_vision_bonus)
{
  CreaturePtr creature = std::make_shared<Creature>();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_NIGHT_SIGHT, 33);

  LineOfSightCalculator losc;

  int los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_DAY);
  EXPECT_EQ(6, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_DUSK);
  EXPECT_EQ(6, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_DAWN);
  EXPECT_EQ(6, los_length);

  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_NIGHT);
  EXPECT_EQ(4, los_length);

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_NIGHT_SIGHT, 67);
  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_NIGHT);
  EXPECT_EQ(5, los_length);

  creature->get_skills().set_value(SkillType::SKILL_GENERAL_NIGHT_SIGHT, 100);
  los_length = losc.calculate_los_length(creature, MapType::MAP_TYPE_OVERWORLD, TimeOfDayType::TIME_OF_DAY_NIGHT);
  EXPECT_EQ(6, los_length);
}