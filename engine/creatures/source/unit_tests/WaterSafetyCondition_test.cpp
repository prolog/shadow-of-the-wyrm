#include "gtest/gtest.h"
#include "Boat.hpp"
#include "RiverTile.hpp"

TEST(SW_Engine_Creature_WaterSafetyCondition, is_safe)
{
	CreaturePtr creature = std::make_shared<Creature>();
	WorldPtr world = std::make_unique<World>();
	Game::instance().set_current_world(std::move(world));
	TilePtr tile = std::make_shared<RiverTile>();

	WaterSafetyCondition wsc;

	EXPECT_FALSE(wsc.is_safe(creature, nullptr));
	EXPECT_FALSE(wsc.is_safe(creature, tile));

	Status st;
	st.set_value(true);

	creature->set_breathes(BreatheType::BREATHE_TYPE_WATER);

	EXPECT_TRUE(wsc.is_safe(creature, tile));

	creature->set_breathes(BreatheType::BREATHE_TYPE_AIR);

	EXPECT_FALSE(wsc.is_safe(creature, tile));

	ItemPtr boat = std::make_shared<Boat>();
	boat->set_id("boat");
	creature->get_inventory()->add(boat);

	EXPECT_TRUE(wsc.is_safe(creature, tile));

	creature->get_inventory()->clear();

	EXPECT_FALSE(wsc.is_safe(creature, tile));

	creature->set_status(StatusIdentifiers::STATUS_ID_FLYING, st);

	EXPECT_TRUE(wsc.is_safe(creature, tile));

	Game::instance().set_current_world(nullptr);
}
