#include "gtest/gtest.h"

Class create_test_class();
Class create_test_class()
{
  Class cl;

  cl.set_class_id("class");
  cl.set_class_name_sid("class name");
  cl.set_class_short_description_sid("aaa");
  cl.set_class_description_sid("bbb");
  cl.set_class_abbreviation_sid("cl");

  Symbol s;
  s.set_symbol('a');
  s.set_colour(Colour::COLOUR_BLUE);

  cl.set_symbol(s);

  Modifier m;
  m.set_strength_modifier(3);
  cl.set_modifier(m);

  Resistances r;
  r.set_all_resistances_to(0.5);
  cl.set_resistances(r);
  
  cl.set_crowning_gifts({ "abc", "def" });
  cl.set_piety_regen_bonus(3);
  cl.set_piety_cost_multiplier(1.2f);

  Skills sk;
  sk.set_all_to(47);
  cl.set_skills(sk);

  cl.set_user_playable(true);
  cl.set_experience_multiplier(1.1f);
  cl.set_hp_regen_multiplier(0.9f);
  cl.set_ap_regen_multiplier(1.2f);
  cl.set_hit_dice(6);
  cl.set_ap_dice(8);

  InitialItem i;
  i.set_item_id("arrow");
  Dice d;
  d.set_num_dice(3);
  d.set_dice_sides(1);
  i.set_item_quantity(d);
  std::map<EquipmentWornLocation, InitialItem> ie = { {EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION, i} };
  std::vector<InitialItem> ii = { i, i };

  cl.set_initial_equipment(ie);
  cl.set_initial_inventory(ii);
  cl.set_level_script("abc123");
  cl.set_kill_script("def123");
  cl.set_titles({ {4, "sir"}, {50, "big sir"}});
  cl.set_deity_dislike_multipliers({ {"abc", 2.0f} });
  cl.set_starting_pet_ids({ "cat", "fish", "dragon" });
  return cl;
}

TEST(SW_World_Class, copy_constructor)
{
  Class c = create_test_class();
  Class c2(c);

  EXPECT_EQ(c, c2);
}

TEST(SW_World_Class, equals_operator)
{
  Class c = create_test_class();
  Class c2 = c;

  EXPECT_EQ(c, c2);
}

