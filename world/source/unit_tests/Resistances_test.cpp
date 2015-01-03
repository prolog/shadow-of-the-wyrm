#include "gtest/gtest.h"
#include "ResistanceFactory.hpp"

TEST(SL_World_Resistances, gain_and_lose_messages)
{
  map<DamageType, pair<std::string, std::string>> gain_lose_msgs =
  { { DAMAGE_TYPE_SLASH, { ResistanceTextKeys::RESISTANCE_GAIN_SLASH, ResistanceTextKeys::RESISTANCE_LOSE_SLASH }},
    { DAMAGE_TYPE_PIERCE, { ResistanceTextKeys::RESISTANCE_GAIN_PIERCE, ResistanceTextKeys::RESISTANCE_LOSE_PIERCE } }, 
    { DAMAGE_TYPE_POUND, { ResistanceTextKeys::RESISTANCE_GAIN_POUND, ResistanceTextKeys::RESISTANCE_LOSE_POUND } }, 
    { DAMAGE_TYPE_HEAT, { ResistanceTextKeys::RESISTANCE_GAIN_HEAT, ResistanceTextKeys::RESISTANCE_LOSE_HEAT } }, 
    { DAMAGE_TYPE_COLD, { ResistanceTextKeys::RESISTANCE_GAIN_COLD, ResistanceTextKeys::RESISTANCE_LOSE_COLD } }, 
    { DAMAGE_TYPE_ACID, { ResistanceTextKeys::RESISTANCE_GAIN_ACID, ResistanceTextKeys::RESISTANCE_LOSE_ACID } }, 
    { DAMAGE_TYPE_POISON, { ResistanceTextKeys::RESISTANCE_GAIN_POISON, ResistanceTextKeys::RESISTANCE_LOSE_POISON } }, 
    { DAMAGE_TYPE_HOLY, { ResistanceTextKeys::RESISTANCE_GAIN_HOLY, ResistanceTextKeys::RESISTANCE_LOSE_HOLY } }, 
    { DAMAGE_TYPE_SHADOW, { ResistanceTextKeys::RESISTANCE_GAIN_SHADOW, ResistanceTextKeys::RESISTANCE_LOSE_SHADOW } }, 
    { DAMAGE_TYPE_ARCANE, { ResistanceTextKeys::RESISTANCE_GAIN_ARCANE, ResistanceTextKeys::RESISTANCE_LOSE_ARCANE } }, 
    { DAMAGE_TYPE_LIGHTNING, { ResistanceTextKeys::RESISTANCE_GAIN_LIGHTNING, ResistanceTextKeys::RESISTANCE_LOSE_LIGHTNING } } };

  Resistances res;

  for (const auto& pair : gain_lose_msgs)
  {
    ResistancePtr cur_res = res.get_resistance(pair.first);

    string gain_msg = cur_res->get_gain_message_sid();
    string lose_msg = cur_res->get_lose_message_sid();
    string indirect_gain_msg = cur_res->get_gain_or_lose_message_sid(true);
    string indirect_lose_msg = cur_res->get_gain_or_lose_message_sid(false);

    EXPECT_EQ(pair.second.first, gain_msg);
    EXPECT_EQ(pair.second.second, lose_msg);
    EXPECT_EQ(gain_msg, indirect_gain_msg);
    EXPECT_EQ(lose_msg, indirect_lose_msg);
  }
}

TEST(SL_World_Resistances, serialization_id)
{
  Resistances resistances;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_RESISTANCES, resistances.get_class_identifier());
}

TEST(SL_World_Resistances, serialization_ids_for_individual_types)
{
  SlashResistance sr;
  PierceResistance pr;
  PoundResistance pr2;
  HeatResistance hr;
  ColdResistance cr;
  AcidResistance ar;
  PoisonResistance pr3;
  HolyResistance hr2;
  ShadowResistance sr2;
  ArcaneResistance ar2;
  LightningResistance lr;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SLASH_RESISTANCE, sr.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_PIERCE_RESISTANCE, pr.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_POUND_RESISTANCE, pr2.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_HEAT_RESISTANCE, hr.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_COLD_RESISTANCE, cr.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_ACID_RESISTANCE, ar.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_POISON_RESISTANCE, pr3.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_HOLY_RESISTANCE, hr2.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SHADOW_RESISTANCE, sr2.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_ARCANE_RESISTANCE, ar2.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_LIGHTNING_RESISTANCE, lr.get_class_identifier());
}

TEST(SL_World_Resistances, saveload)
{
  for (int i = CLASS_ID_SLASH_RESISTANCE; i <= CLASS_ID_LIGHTNING_RESISTANCE; i++)
  {
    std::shared_ptr<Resistance> res1, res2;
    res1 = ResistanceFactory::create_resistance(static_cast<ClassIdentifier>(i));
    res2 = ResistanceFactory::create_resistance(static_cast<ClassIdentifier>(i));

    res1->set_value(0.23);

    ostringstream ss;

    res1->serialize(ss);

    istringstream iss(ss.str());

    res2->deserialize(iss);

    EXPECT_TRUE(*res1 == *res2);
  }
}
