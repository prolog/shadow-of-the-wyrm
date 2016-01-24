#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_World_Creature, name)
{
  Creature c;
  string creature_name = "Bubba Ho Tep";
  c.set_name(creature_name);

  EXPECT_EQ(creature_name, c.get_name());
}

TEST(SW_World_Creature, age)
{
  Creature c;
  int age = 25;
  c.set_age(age);

  EXPECT_EQ(age, c.get_age().get_base());
  EXPECT_EQ(age, c.get_age().get_current());
}

TEST(SW_World_Creature, size)
{
  Creature c;
  CreatureSize size = CreatureSize::CREATURE_SIZE_LARGE;
  c.set_size(size);

  EXPECT_EQ(size, c.get_size());
}

TEST(SW_World_Creature, strength)
{
  Creature c;
  int strength = 12;
  c.set_strength(strength);

  EXPECT_EQ(strength, c.get_strength().get_base());
  EXPECT_EQ(strength, c.get_strength().get_current());
}

TEST(SW_World_Creature, serialization_id)
{
  Creature c;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CREATURE, c.get_class_identifier());
}

TEST(SW_World_Creature, saveload)
{
  Creature c, c2;

  Statistic str(12);
  Statistic dex(11);
  Statistic agi(10);
  Statistic hea(11);
  Statistic intel(12);
  Statistic will(13);
  Statistic cha(14);

  c.set_strength(str);
  c.set_dexterity(dex);
  c.set_agility(agi);
  c.set_health(hea);
  c.set_intelligence(intel);
  c.set_willpower(will);
  c.set_charisma(cha);

  AutomaticMovement& am = c.get_automatic_movement_ref();
  am.set_direction(Direction::DIRECTION_SOUTH);
  am.set_engaged(true);

  Blood b;
  b.set_litres(5.3f);
  b.set_grams_alcohol(1.2f);

  c.set_blood(b);

  map<double, vector<pair<string, Modifier>>> cr_m_map;

  Modifier m1(1, 2, 3, 4, 5, 6, 7);
  Modifier m2(2, 3, 4, 5, 6, 7, 8);
  m1.set_evade_modifier(4);
  m2.set_soak_modifier(-5);

  vector<pair<string, Modifier>> vm1{ { "123", m1 } }, vm2{ { "123123", m2 } };
  cr_m_map.insert(make_pair(17456.0, vm1));
  cr_m_map.insert(make_pair(55555.0, vm2));
  c.set_modifiers(cr_m_map);

  ostringstream ss;

  c.serialize(ss);

  istringstream iss(ss.str());

  c2.deserialize(iss);

  EXPECT_TRUE(c == c2);
  EXPECT_FLOAT_EQ(1.2f, c2.get_blood().get_grams_alcohol());
}

TEST(SW_World_Creature, count_items)
{
  Creature c;

  EXPECT_EQ(0, c.count_items());

  ItemPtr first_item = std::make_shared<Amulet>();
  first_item->set_quantity(2);

  Equipment& e = c.get_equipment();
  e.set_item(first_item, EquipmentWornLocation::EQUIPMENT_WORN_NECK);

  EXPECT_EQ(2, c.count_items());
  IInventoryPtr i = c.get_inventory();
  ItemPtr second_item = std::make_shared<Amulet>();
  second_item->set_quantity(5);
  i->add_front(second_item);

  EXPECT_EQ(7, c.count_items());
}