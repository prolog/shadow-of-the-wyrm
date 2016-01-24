#include "gtest/gtest.h"

TEST(SW_World_CreatureGenerationValues, serialization_id)
{
  CreatureGenerationValues cgv;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CREATURE_GENERATION_VALUES, cgv.get_class_identifier());
}

TEST(SW_World_CreatureGenerationValues, saveload)
{
  CreatureGenerationValues cgv, cgv2;

  vector<string> g_v = { "fdsa", "asdf" };
  cgv.set_current(1);
  cgv.incr_current();
  cgv.set_maximum(4);
  cgv.set_friendly(true);
  cgv.set_danger_level(22);
  cgv.set_rarity(Rarity(10));
  cgv.set_generator_filters(g_v);

  cgv.add_allowable_terrain_type(TileType::TILE_TYPE_BARRACKS);
  cgv.add_allowable_terrain_type(TileType::TILE_TYPE_MARSH);
  cgv.add_allowable_terrain_type(TileType::TILE_TYPE_PIER);

  Dice hp(5, 6, 7);
  Dice ap(9, 1, 3);
  cgv.set_initial_hit_points(hp);
  cgv.set_initial_arcana_points(ap);
  cgv.set_base_experience_value(105);

  vector<InitialItem> initial_items;
  InitialItem i;
  initial_items.push_back(i);
  initial_items.push_back(i);

  cgv.set_initial_inventory(initial_items);

  map<EquipmentWornLocation, InitialItem> initial_equipment;
  initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_HEAD, i));
  initial_equipment.insert(make_pair(EquipmentWornLocation::EQUIPMENT_WORN_FEET, i));

  cgv.set_initial_equipment(initial_equipment);

  ostringstream ss;

  cgv.serialize(ss);

  istringstream iss(ss.str());

  cgv2.deserialize(iss);

  EXPECT_TRUE(cgv == cgv2);

  vector<string> generator_filters = cgv2.get_generator_filters();

  EXPECT_TRUE(find(generator_filters.begin(), generator_filters.end(), "asdf") != generator_filters.end());
}

