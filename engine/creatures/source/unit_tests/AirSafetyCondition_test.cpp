#include "gtest/gtest.h"

TEST(SW_Engine_Creature_AirSafetyCondition, is_safe)
{
	CreaturePtr creature = std::make_shared<Creature>();

	AirSafetyCondition asc;
	EXPECT_FALSE(asc.is_safe(creature, nullptr));

	Status st;
	st.set_value(true);

	creature->set_status(StatusIdentifiers::STATUS_ID_INCORPOREAL, st);

	EXPECT_TRUE(asc.is_safe(creature, nullptr));

	CreaturePtr creature2 = std::make_shared<Creature>();
	EXPECT_FALSE(asc.is_safe(creature2, nullptr));

	creature2->set_status(StatusIdentifiers::STATUS_ID_FLYING, st);
	EXPECT_TRUE(asc.is_safe(creature2, nullptr));
}
