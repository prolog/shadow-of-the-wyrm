#include "gtest/gtest.h"
#include "Currency.hpp"
#include "Weapon.hpp"

using CreaturePtr = std::shared_ptr<Creature>;

CreaturePtr create_conductless_creature();

// Create a creature without any active conducts, to more easily unit test
// the various score components.
CreaturePtr create_conductless_creature() 
{
  static_assert(ConductType::CONDUCT_SIZE == ConductType(9), "Unexpected CONDUCT_SIZE");

  CreaturePtr cp = std::make_shared<Creature>();
  Conducts& cond = cp->get_conducts_ref();

  vector<ConductType> conducts = { ConductType::CONDUCT_TYPE_FOODLESS, ConductType::CONDUCT_TYPE_VEGETARIAN, ConductType::CONDUCT_TYPE_CORPSELESS, ConductType::CONDUCT_TYPE_AGNOSTIC, ConductType::CONDUCT_TYPE_ILLITERATE, ConductType::CONDUCT_TYPE_WEAPONLESS, ConductType::CONDUCT_TYPE_NO_GRAVEDIGGING, ConductType::CONDUCT_TYPE_QUESTLESS, ConductType::CONDUCT_TYPE_SILENT };
  for (const ConductType c : conducts)
  {
    cond.break_conduct(c);
  }

  return cp;
}

TEST(SW_Engine_Calculators_ScoreCalculator, end_boss_component)
{
  CreaturePtr cp = create_conductless_creature();

  Mortuary& m = cp->get_mortuary_ref();
  m.add_creature_kill("end_boss");

  ScoreCalculator sc;

  EXPECT_EQ(ScoreConstants::END_BOSS_BONUS, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, currency_component)
{
  CreaturePtr cp = create_conductless_creature();

  CurrencyPtr currency = std::make_shared<Currency>();
  currency->set_base_id(ItemIdKeys::ITEM_ID_CURRENCY);
  currency->set_quantity(12345);

  IInventoryPtr inv = cp->get_inventory();
  inv->add(currency);

  ScoreCalculator sc;

  EXPECT_EQ(12345, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, skill_points_component)
{
  CreaturePtr cp = create_conductless_creature();
  ScoreCalculator sc;

  EXPECT_EQ(0, sc.calculate_score(cp));

  cp->set_skill_points(86);

  EXPECT_EQ(6450, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, experience_component)
{
  CreaturePtr cp = create_conductless_creature();

  cp->set_experience_points(400000);

  ScoreCalculator sc;

  EXPECT_EQ(58000, sc.calculate_score(cp));

  cp->set_experience_points(1234567);

  EXPECT_EQ(129728, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, level_component)
{
  CreaturePtr cp = create_conductless_creature();

  Statistic level(36);
  cp->set_level(level);

  ScoreCalculator sc;

  EXPECT_EQ(3600, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculator_ScoreCalculator, artifact_component)
{
  CreaturePtr cp = create_conductless_creature();

  WeaponPtr w1 = std::make_shared<MeleeWeapon>();
  w1->set_artifact(true);
  w1->set_value(555);

  WeaponPtr w2 = std::make_shared<MeleeWeapon>();
  w2->set_artifact(true);
  w2->set_value(445);

  IInventoryPtr inv = cp->get_inventory();
  inv->add(w1);
  cp->get_equipment().set_item(w2, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

  ScoreCalculator sc;

  EXPECT_EQ(1000, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, spell_component)
{
  CreaturePtr cp = create_conductless_creature();

  SpellKnowledge sk;
  IndividualSpellKnowledge isk;

  isk.set_castings(30);
  isk.set_bonus(5);

  sk.set_spell_knowledge("asdf", isk);

  isk.set_bonus(15);

  sk.set_spell_knowledge("aaa", isk);

  isk.set_bonus(10);

  sk.set_spell_knowledge("fdsa", isk);

  cp->set_spell_knowledge(sk);

  ScoreCalculator sc;

  EXPECT_EQ(420, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, conducts)
{
  CreaturePtr cp = make_shared<Creature>();
  Statistic level(16);
  cp->set_level(level);

  ScoreCalculator sc;

  EXPECT_EQ(16 * 100 * static_cast<int>(ConductType::CONDUCT_SIZE) + 1600, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, total_score)
{
  CreaturePtr cp = make_shared<Creature>();
  Statistic clevel(10);
  cp->set_level(clevel);

  // exp
  cp->set_experience_points(400000);

  // currency & artifacts
  CurrencyPtr currency = std::make_shared<Currency>();
  currency->set_base_id(ItemIdKeys::ITEM_ID_CURRENCY);
  currency->set_quantity(12345);

  WeaponPtr w1 = std::make_shared<MeleeWeapon>();
  w1->set_artifact(true);
  w1->set_value(555);

  WeaponPtr w2 = std::make_shared<MeleeWeapon>();
  w2->set_artifact(true);
  w2->set_value(445);

  IInventoryPtr inv = cp->get_inventory();
  inv->add(currency);
  inv->add(w1);
  cp->get_equipment().set_item(w2, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

  Membership mem;

  cp->get_memberships_ref().add_membership("1", mem);
  cp->get_memberships_ref().add_membership("2", mem);

  // end boss
  Mortuary& m = cp->get_mortuary_ref();
  m.add_creature_kill("end_boss");

  ScoreCalculator sc;

  int expected_score = (static_cast<int>(ConductType::CONDUCT_SIZE) * 10 * 100) 
                     + ScoreConstants::END_BOSS_BONUS 
                     + 58000 
                     + 12345 
                     + 1000 
                     + 1000
                     + 5000;

  EXPECT_EQ(expected_score, sc.calculate_score(cp));
}

TEST(SW_Engine_Calculators_ScoreCalculator, memberships)
{
  CreaturePtr cp = make_shared<Creature>();
  Statistic level(16);
  cp->set_level(level);
  Membership m;

  cp->get_memberships_ref().add_membership("1", m);
  cp->get_memberships_ref().add_membership("2", m);
  cp->get_memberships_ref().add_membership("3", m);
  cp->get_memberships_ref().add_membership("4", m);

  ScoreCalculator sc;

  EXPECT_EQ(16000 /* level, conducts */ + (16 * 250 * 4)
          , sc.calculate_score(cp));
}

