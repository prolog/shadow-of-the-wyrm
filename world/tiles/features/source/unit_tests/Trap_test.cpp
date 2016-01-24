#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Trap, triggered)
{
  Trap trap;

  trap.set_triggered(false);

  EXPECT_FALSE(trap.get_triggered());
  EXPECT_TRUE(trap.get_is_hidden());

  trap.set_triggered(true);

  EXPECT_TRUE(trap.get_triggered());
  EXPECT_FALSE(trap.get_is_hidden());
}

TEST(SW_World_Tiles_Features_Trap, serialization_id)
{
  Trap trap;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TRAP, trap.get_class_identifier());
}

TEST(SW_World_Tiles_Features_Trap, saveload)
{
  try {
    Trap t1, t2;
    Damage d1(5, 5, 7, DamageType::DAMAGE_TYPE_COLD, false, false, false, 0, {});

    t1.set_triggered(true);
    t1.set_id("foo");
    t1.set_damage(d1);
    t1.set_description_sid("abc2465");
    t1.set_trigger_message_sid("fdsafdsa");
    t1.set_trigger_symbol('*');
    t1.set_colour(Colour::COLOUR_BLUE);
    t1.set_player_damage_message_sid("thathurt");
    t1.set_item_id("arrow");

    EXPECT_FALSE(t1 == t2);

    ostringstream oss;
    t1.serialize(oss);

    istringstream iss(oss.str());
    t2.deserialize(iss);

    EXPECT_TRUE(t1 == t2);
  }
  catch (std::exception e)
  {
    cout << e.what();
  }
}
