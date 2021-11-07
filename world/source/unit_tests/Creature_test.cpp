#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_World_Creature, name)
{
  Creature c;
  string creature_name = "Bubba Ho Tep";
  c.set_name(creature_name);

  EXPECT_EQ(creature_name, c.get_name());
}

TEST(SW_World_Creature, win_conditions)
{
  Creature c;
  vector<CreatureWin> empty_wins;
  vector<CreatureWin> wins = {CreatureWin::CREATURE_WIN_REGULAR, CreatureWin::CREATURE_WIN_GODSLAYER};
  
  EXPECT_EQ(empty_wins, c.get_satisfied_win_conditions());

  c.set_additional_property(CreatureProperties::CREATURE_PROPERTIES_WINNER + "_1", to_string(true));
  c.set_additional_property(CreatureProperties::CREATURE_PROPERTIES_WINNER + "_3", to_string(true));

  EXPECT_EQ(wins, c.get_satisfied_win_conditions());
}

TEST(SW_World_Creature, get_statistics)
{
  Statistic str(11);
  str.get_marks_ref().set_value(1);

  Statistic dex(12);
  dex.get_marks_ref().set_value(2);

  Statistic agi(13);
  agi.get_marks_ref().set_value(3);

  Statistic hea(14);
  hea.get_marks_ref().set_value(4);

  Statistic itl(15);
  itl.get_marks_ref().set_value(5);

  Statistic wil(16);
  wil.get_marks_ref().set_value(6);

  Statistic cha(17);
  cha.get_marks_ref().set_value(7);

  Creature c;
  c.set_strength(str);
  c.set_dexterity(dex);
  c.set_agility(agi);
  c.set_health(hea);
  c.set_intelligence(itl);
  c.set_willpower(wil);
  c.set_charisma(cha);

  std::map<PrimaryStatisticType, int> stat_marks = {{PrimaryStatisticType::PRIMARY_STATISTIC_STRENGTH, 1},
                                                    {PrimaryStatisticType::PRIMARY_STATISTIC_DEXTERITY, 2},
                                                    {PrimaryStatisticType::PRIMARY_STATISTIC_AGILITY, 3},
                                                    {PrimaryStatisticType::PRIMARY_STATISTIC_HEALTH, 4},
                                                    {PrimaryStatisticType::PRIMARY_STATISTIC_INTELLIGENCE, 5},
                                                    {PrimaryStatisticType::PRIMARY_STATISTIC_WILLPOWER, 6},
                                                    {PrimaryStatisticType::PRIMARY_STATISTIC_CHARISMA, 7}};

  for (const auto& sm_pair : stat_marks)
  {
    Statistic& exp_stat = c.get_statistic_ref(sm_pair.first);
    EXPECT_EQ(sm_pair.second, exp_stat.get_marks().get_value());
  }
}

TEST(SW_World_Creature, primary_stat_maxima)
{
  Creature c;

  c.get_strength_ref().set_base_current(14);

  EXPECT_EQ(14, c.get_strength().get_base());
  EXPECT_EQ(14, c.get_strength().get_current());

  // Should fail, > 99
  c.get_strength_ref().set_base_current(1000);

  EXPECT_EQ(14, c.get_strength().get_base());
  EXPECT_EQ(14, c.get_strength().get_current());

  Statistic new_str(17);
  new_str.set_max(1000); // Try to bypass the maximum by setting a new str stat
  c.set_strength(new_str);
  c.get_strength_ref().set_base_current(500);

  // The attempted bypass should fail: creatures will enforce the primary
  // stat maximum whenever a statistic is set.
  //
  // I guess it's still possible to get it by calling get_strength_ref
  // and then setting the maximum, but that gets into the realm of,
  // "Look, I know what I'm doing, this is intentional."
  EXPECT_EQ(17, c.get_strength().get_base());
  EXPECT_EQ(17, c.get_strength().get_current());  
}

TEST(SW_World_Creature, skill_points)
{
  Creature c;

  EXPECT_EQ(0, c.get_skill_points());

  c.set_skill_points(4);

  EXPECT_EQ(4, c.get_skill_points());

  c.increment_skill_points(3);

  EXPECT_EQ(7, c.get_skill_points());

  c.increment_skill_points(17);

  EXPECT_EQ(24, c.get_skill_points());
}
TEST(SW_World_Creature, age)
{
  Creature c;
  int age = 25;
  c.set_age(age);

  EXPECT_EQ(age, c.get_age().get_base());
  EXPECT_EQ(age, c.get_age().get_current());
}

TEST(SW_World_Creature, can_learn_spells)
{
  CreaturePtr no_spells = std::make_shared<Creature>();
  EXPECT_FALSE(no_spells->can_learn_spells());

  vector<SkillType> spell_categories = { SkillType::SKILL_MAGIC_CANTRIPS, SkillType::SKILL_MAGIC_ARCANE, SkillType::SKILL_MAGIC_DIVINE, SkillType::SKILL_MAGIC_MYSTIC, SkillType::SKILL_MAGIC_PRIMORDIAL };

  for (const SkillType spell_cat : spell_categories)
  {
    CreaturePtr s_creature = std::make_shared<Creature>();
    s_creature->get_skills().set_value(spell_cat, 1);

    EXPECT_TRUE(s_creature->can_learn_spells());
  }
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

TEST(SW_World_Creature, get_short_description_sid)
{
  Creature c;
  string short_desc = "asdf";
  string name = "buddy";
  c.set_short_description_sid(short_desc);
 
  EXPECT_EQ(short_desc, c.get_short_description_sid());

  c.set_name(name);

  EXPECT_EQ(name, c.get_short_description_sid());
  EXPECT_EQ(short_desc, c.get_short_description_sid(true));
}

TEST(SW_World_Creature, get_description_sid)
{
  Creature c;
  string short_desc = "aaaaaa";
  string name = "name!";
  c.set_description_sid(short_desc);

  EXPECT_EQ(short_desc, c.get_description_sid());

  c.set_name(name);

  EXPECT_EQ(name, c.get_description_sid());
  EXPECT_EQ(short_desc, c.get_description_sid(true));
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
  c.set_skill_points(26);

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
  EXPECT_EQ(26, c2.get_skill_points());
  EXPECT_FLOAT_EQ(1.2f, c2.get_blood().get_grams_alcohol());
}

TEST(SW_World_Creature, binary_string_serialization)
{
  CreaturePtr c = std::make_shared<Creature>();
  ostringstream ss;

  string bprop = Serialize::BINARY_PROPERTY_PREFIX + "1";
  string bval = "04021431\0\tdsjlkaf\0\0dsajl\0";
  c->set_name("ted");
  c->set_id("fdsa'f324932849320rdsaldal");
  c->set_age(36);
  c->set_additional_property(bprop, bval);

  c->serialize(ss);
  istringstream iss(ss.str());

  CreaturePtr c2 = std::make_shared<Creature>();
  c2->deserialize(iss);

  EXPECT_TRUE(*c == *c2);
  EXPECT_EQ(bval, c2->get_additional_property(bprop));
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

TEST(SW_World_Creature, breathes_types)
{
  Creature water_creature;
  water_creature.set_breathes(BreatheType::BREATHE_TYPE_WATER);

  EXPECT_TRUE(water_creature.can_breathe(BreatheType::BREATHE_TYPE_WATER));

  Creature land_creature;
  land_creature.set_breathes(BreatheType::BREATHE_TYPE_AIR);

  EXPECT_TRUE(land_creature.can_breathe(BreatheType::BREATHE_TYPE_AIR));
  EXPECT_FALSE(land_creature.can_breathe(BreatheType::BREATHE_TYPE_WATER));

  Status wb_status(StatusIdentifiers::STATUS_ID_WATER_BREATHING, true, 1, "");
  land_creature.set_status(StatusIdentifiers::STATUS_ID_WATER_BREATHING, wb_status);

  EXPECT_TRUE(land_creature.can_breathe(BreatheType::BREATHE_TYPE_WATER));
}

TEST(SW_World_Creature, breathe_any_type)
{
  Creature c;
  c.set_breathes(BreatheType::BREATHE_TYPE_ALL);

  vector<BreatheType> vals = { BreatheType::BREATHE_TYPE_AIR, BreatheType::BREATHE_TYPE_WATER, BreatheType::BREATHE_TYPE_ALL };

  for (const BreatheType breathe_type : vals)
  {
    EXPECT_TRUE(c.can_breathe(breathe_type));
  }
}

TEST(SW_World_Creature, status_details)
{
  Creature c;
  Status poi("abc", true, 10, "123");
  Status haste("cde", false, 1, "");
  Status depression("aaa", true, 50, "some_monster");

  c.set_status("poison", poi);
  c.set_status("haste", haste);
  c.set_status("depression", depression);

  Creature c2;
  ostringstream ss;
  c.serialize(ss);
  istringstream iss(ss.str());
  c2.deserialize(iss);
  
  CreatureStatusMap csm = c2.get_statuses();
  EXPECT_EQ(poi, csm.find("poison")->second);
  EXPECT_EQ(haste, csm.find("haste")->second);
  EXPECT_EQ(depression, csm.find("depression")->second);
}

TEST(SW_World_Creature, is_dead)
{
  Creature c;

  Statistic hp(20);
  hp.set_current(-5);

  c.set_hit_points(hp);

  EXPECT_TRUE(c.is_dead());

  hp.set_current(-1);
  c.set_hit_points(hp);

  EXPECT_TRUE(c.is_dead());

  hp.set_current(0);
  c.set_hit_points(hp);

  EXPECT_TRUE(c.is_dead());

  hp.set_current(1);
  c.set_hit_points(hp);

  EXPECT_FALSE(c.is_dead());

  hp.set_current(36);
  c.set_hit_points(hp);

  EXPECT_FALSE(c.is_dead());
}

TEST(SW_World_Creature, increment_free_hidden_actions)
{
  CreaturePtr c = std::make_shared<Creature>();
  c->set_free_hidden_actions(2);

  EXPECT_EQ(2, c->get_free_hidden_actions());

  for (int i = 0; i < 5; i++)
  {
    c->increment_free_hidden_actions();
  }

  EXPECT_EQ(2, c->get_free_hidden_actions());
}

TEST(SW_World_Creature, decrement_free_hidden_actions)
{
  CreaturePtr c = std::make_shared<Creature>();
  c->set_free_hidden_actions(17);

  for (int i = 0; i < 9; i++)
  {
    c->decrement_free_hidden_actions();
  }

  EXPECT_EQ(8, c->get_free_hidden_actions());
}

TEST(SW_World_Creature, ancient_beast)
{
  EXPECT_TRUE(Creature::is_ancient_beast(CreatureID::CREATURE_ID_PREFIX_ANCIENT_BEAST + "something"));
  EXPECT_FALSE(Creature::is_ancient_beast("a small kitty in a wizard hat"));
}