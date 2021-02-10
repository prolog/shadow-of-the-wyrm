#include "gtest/gtest.h"

TEST(SW_World_Resistances, add)
{
  Resistances r1;
  r1.set_all_resistances_to(0.45);

  Resistances r2;
  r2.set_all_resistances_to(0.07);

  r1.add(r2);

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    EXPECT_DOUBLE_EQ(0.52, r1.get_resistance_value(dt));
  }

  Resistances r3;
  r3.set_all_resistances_to(0.03);

  r1.add(r3);

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    EXPECT_DOUBLE_EQ(0.55, r1.get_resistance_value(dt));
  }
}

TEST(SW_World_Resistances, gain_and_lose_messages)
{
  map<DamageType, pair<std::string, std::string>> gain_lose_msgs =
  { { DamageType::DAMAGE_TYPE_SLASH, { ResistanceTextKeys::RESISTANCE_GAIN_SLASH, ResistanceTextKeys::RESISTANCE_LOSE_SLASH } },
    { DamageType::DAMAGE_TYPE_PIERCE, { ResistanceTextKeys::RESISTANCE_GAIN_PIERCE, ResistanceTextKeys::RESISTANCE_LOSE_PIERCE } }, 
    { DamageType::DAMAGE_TYPE_POUND, { ResistanceTextKeys::RESISTANCE_GAIN_POUND, ResistanceTextKeys::RESISTANCE_LOSE_POUND } },
    { DamageType::DAMAGE_TYPE_HEAT, { ResistanceTextKeys::RESISTANCE_GAIN_HEAT, ResistanceTextKeys::RESISTANCE_LOSE_HEAT } },
    { DamageType::DAMAGE_TYPE_COLD, { ResistanceTextKeys::RESISTANCE_GAIN_COLD, ResistanceTextKeys::RESISTANCE_LOSE_COLD } },
    { DamageType::DAMAGE_TYPE_ACID, { ResistanceTextKeys::RESISTANCE_GAIN_ACID, ResistanceTextKeys::RESISTANCE_LOSE_ACID } },
    { DamageType::DAMAGE_TYPE_POISON, { ResistanceTextKeys::RESISTANCE_GAIN_POISON, ResistanceTextKeys::RESISTANCE_LOSE_POISON } },
    { DamageType::DAMAGE_TYPE_HOLY, { ResistanceTextKeys::RESISTANCE_GAIN_HOLY, ResistanceTextKeys::RESISTANCE_LOSE_HOLY } },
    { DamageType::DAMAGE_TYPE_SHADOW, { ResistanceTextKeys::RESISTANCE_GAIN_SHADOW, ResistanceTextKeys::RESISTANCE_LOSE_SHADOW } },
    { DamageType::DAMAGE_TYPE_ARCANE, { ResistanceTextKeys::RESISTANCE_GAIN_ARCANE, ResistanceTextKeys::RESISTANCE_LOSE_ARCANE } },
    { DamageType::DAMAGE_TYPE_LIGHTNING, { ResistanceTextKeys::RESISTANCE_GAIN_LIGHTNING, ResistanceTextKeys::RESISTANCE_LOSE_LIGHTNING } } };

  Resistances res;

  for (const auto& pair : gain_lose_msgs)
  {
    const Resistance& cur_res = res.get_resistance_ref(pair.first);

    string gain_msg = cur_res.get_gain_message_sid();
    string lose_msg = cur_res.get_lose_message_sid();
    string indirect_gain_msg = cur_res.get_gain_or_lose_message_sid(true);
    string indirect_lose_msg = cur_res.get_gain_or_lose_message_sid(false);

    EXPECT_EQ(pair.second.first, gain_msg);
    EXPECT_EQ(pair.second.second, lose_msg);
    EXPECT_EQ(gain_msg, indirect_gain_msg);
    EXPECT_EQ(lose_msg, indirect_lose_msg);
  }
}

TEST(SW_World_Resistances, get_total)
{
  Resistances r;

  EXPECT_DOUBLE_EQ(0.0, r.get_total());

  r.set_resistance_value(DamageType::DAMAGE_TYPE_HEAT, 0.36);
  r.set_resistance_value(DamageType::DAMAGE_TYPE_LIGHTNING, 0.6);

  EXPECT_DOUBLE_EQ(0.96, r.get_total());

  r.set_resistance_value(DamageType::DAMAGE_TYPE_SHADOW, 0.5);

  EXPECT_DOUBLE_EQ(1.46, r.get_total());
}

TEST(SW_World_Resistances, serialization_id)
{
  Resistances resistances;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_RESISTANCES, resistances.get_class_identifier());
}

TEST(SW_World_Resistances, saveload)
{
  Resistances res;
  res.default_resistances();

  for (int i = static_cast<int>(DamageType::DAMAGE_TYPE_SLASH); i <= static_cast<int>(DamageType::DAMAGE_TYPE_LIGHTNING); i++)
  {
    Resistance& res1 = res.get_resistance_ref(static_cast<DamageType>(i));
    Resistance res2;
    res1.set_value(0.23);

    ostringstream ss;

    res1.serialize(ss);

    istringstream iss(ss.str());

    res2.deserialize(iss);

    EXPECT_TRUE(res1 == res2);
  }
}
