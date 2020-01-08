#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Trap, triggered)
{
  Symbol s('&', Colour::COLOUR_WHITE);
  Trap trap(s);

  trap.set_triggered(false);

  EXPECT_FALSE(trap.get_triggered());
  EXPECT_TRUE(trap.get_is_hidden());

  trap.set_triggered(true);

  EXPECT_TRUE(trap.get_triggered());
  EXPECT_FALSE(trap.get_is_hidden());
}

TEST(SW_World_Tiles_Features_Trap, set_hidden)
{
  Symbol s('^', Colour::COLOUR_WHITE);
  Trap trap(s);
  trap.set_triggered(false);

  EXPECT_TRUE(trap.get_is_hidden());

  trap.set_is_hidden(false);

  EXPECT_TRUE(trap.get_triggered());
  EXPECT_FALSE(trap.get_is_hidden());
}

TEST(SW_World_Tiles_Features_Trap, serialization_id)
{
  Symbol s('^', Colour::COLOUR_WHITE);
  Trap trap(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TRAP, trap.get_class_identifier());
}

TEST(SW_World_Tiles_Features_Trap, saveload)
{
  try {
    Symbol s('^', Colour::COLOUR_WHITE);
    Trap t1(s), t2(s);
    Damage d1(5, 5, 7, DamageType::DAMAGE_TYPE_COLD, {}, false, false, false, false, false, false, false, false, 0, {});

    t1.set_triggered(true);
    t1.set_id("foo");
    t1.set_damage(d1);
    t1.set_description_sid("abc2465");
    t1.set_trigger_message_sid("fdsafdsa");
    t1.set_trigger_symbol(Symbol('*', Colour::COLOUR_WHITE));
    t1.set_colour(Colour::COLOUR_BLUE);
    t1.set_player_damage_message_sid("thathurt");
    t1.set_item_id("arrow");
    t1.set_effect(EffectType::EFFECT_TYPE_ANTIDOTE); // not real, obviously

    EXPECT_FALSE(t1 == t2);

    ostringstream oss;
    t1.serialize(oss);

    istringstream iss(oss.str());
    t2.deserialize(iss);

    EXPECT_TRUE(t1 == t2);
    EXPECT_TRUE(t2.get_effect() == EffectType::EFFECT_TYPE_ANTIDOTE);
  }
  catch (std::exception& e)
  {
    cout << e.what();
  }
}
