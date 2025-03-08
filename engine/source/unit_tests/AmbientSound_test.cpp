#include "gtest/gtest.h"

TEST(SW_Engine_AmbientSound, ambient_sound_probability)
{
	AmbientSoundProbability asp(20, { 1,4 });

	EXPECT_EQ(20, asp.get_turn_mod_trigger());

	auto val = asp.get_x_in_y();
	EXPECT_EQ(1, val.first);
	EXPECT_EQ(4, val.second);
}

TEST(SW_Engine_AmbientSound, ambient_sound_effect)
{
	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);
	map->set_property(MapProperties::MAP_PROPERTIES_WET, std::to_string(true));
	AmbientSound as;

	// Underwater, overworld, world, cosmos, air don't currently have ambient sounds
	vector<MapType> no_ambient_map_types = { MapType::MAP_TYPE_AIR, MapType::MAP_TYPE_COSMOS, MapType::MAP_TYPE_OVERWORLD, MapType::MAP_TYPE_UNDERWATER, MapType::MAP_TYPE_WORLD };
	
	for (const auto& na_mt : no_ambient_map_types)
	{
		map->set_map_type(na_mt);
		EXPECT_EQ("", as.get_sound_effect(map, 0, true));
	}

	map->set_map_type(MapType::MAP_TYPE_UNDERWORLD);
	vector<ulonglong> no_ambient_turns = { 2, 13, 5001, 49497, 123343652 };
	
	for (const auto& na_turn : no_ambient_turns)
	{
		EXPECT_EQ("", as.get_sound_effect(map, na_turn, true));
	}
	
	vector<ulonglong> ambient_turns = { 20, 40, 100, 1000, 10020, 104660 };

	for (const auto& a_turn : ambient_turns)
	{
		string sound_effect = as.get_sound_effect(map, a_turn, true);
		EXPECT_NE("", sound_effect);
	}
}