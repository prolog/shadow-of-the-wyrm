#include "gtest/gtest.h"

TEST(SW_Engine_Creature_GroundSafetyCondition, is_safe)
{
	CreaturePtr fish = std::make_shared<Creature>();
	CreaturePtr dog = std::make_shared<Creature>();
	fish->set_breathes(BreatheType::BREATHE_TYPE_WATER);

	GroundSafetyCondition gsc;

	EXPECT_TRUE(gsc.is_safe(dog, nullptr));
	EXPECT_FALSE(gsc.is_safe(fish, nullptr));
}

