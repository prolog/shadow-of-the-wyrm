#include "gtest/gtest.h"

const std::string spell_id = "test_spell";

void setup_spells();
void tear_down_spells();
CreaturePtr setup_creature();

void setup_spells()
{
  Damage d;
  d.set_num_dice(3);
  d.set_dice_sides(4);
  d.set_damage_type(DamageType::DAMAGE_TYPE_COLD);

  Spell spell;
  spell.set_spell_id(spell_id);
  spell.set_damage(d);
  spell.set_has_damage(true);
  spell.set_magic_category(SkillType::SKILL_MAGIC_CANTRIPS);

  SpellMap spells;
  spells[spell_id] = spell;
  Game::instance().set_spells(spells);
}

void tear_down_spells()
{
  Game::instance().set_spells({});
}

CreaturePtr setup_creature()
{
  CreaturePtr creature = std::make_shared<Creature>();
  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  IndividualSpellKnowledge isk;

  sk.set_most_recently_cast_spell_id(spell_id);
  sk.set_spell_knowledge(spell_id, isk);
  return creature;
}

TEST(Engine_Calculators_MagicalDamageCalculator, base_damage_no_bonuses)
{
  setup_spells();
  CreaturePtr creature = setup_creature();

  MagicalDamageCalculator mdc(PhaseOfMoonType::PHASE_OF_MOON_NULL);
  Damage d = mdc.calculate_base_damage_object(creature);

  EXPECT_EQ(static_cast<uint>(3), d.get_num_dice());
  EXPECT_EQ(static_cast<uint>(4), d.get_dice_sides());
  EXPECT_EQ(0, d.get_modifier());

  tear_down_spells();
}

TEST(Engine_Calculators_MagicalDamageCalculator, base_damage_spell_bonus_component)
{
  setup_spells();
  CreaturePtr creature = setup_creature();

  MagicalDamageCalculator mdc(PhaseOfMoonType::PHASE_OF_MOON_NULL);
  Damage d = mdc.calculate_base_damage_with_bonuses_or_penalties(creature);

  EXPECT_EQ(static_cast<uint>(3), d.get_num_dice());
  EXPECT_EQ(static_cast<uint>(4), d.get_dice_sides());
  EXPECT_EQ(0, d.get_modifier());

  IndividualSpellKnowledge isk;
  isk.set_bonus(23);
  creature->get_spell_knowledge_ref().set_spell_knowledge(spell_id, isk);
  d = mdc.calculate_base_damage_with_bonuses_or_penalties(creature);

  EXPECT_EQ(static_cast<uint>(3), d.get_num_dice());
  EXPECT_EQ(static_cast<uint>(4), d.get_dice_sides());
  EXPECT_EQ(23, d.get_modifier());

  tear_down_spells();
}

TEST(Engine_Calculators_MagicalDamageCalculator, base_damage_skill_component)
{
  setup_spells();
  CreaturePtr creature = setup_creature();
  creature->get_skills().set_value(SkillType::SKILL_GENERAL_MAGIC, 22);

  MagicalDamageCalculator mdc(PhaseOfMoonType::PHASE_OF_MOON_NULL);
  Damage d = mdc.calculate_base_damage_with_bonuses_or_penalties(creature);

  EXPECT_EQ(static_cast<uint>(3), d.get_num_dice());
  EXPECT_EQ(static_cast<uint>(4), d.get_dice_sides());
  EXPECT_EQ(2, d.get_modifier());

  creature->get_skills().set_value(SkillType::SKILL_MAGIC_CANTRIPS, 75);

  d = mdc.calculate_base_damage_with_bonuses_or_penalties(creature);

  EXPECT_EQ(static_cast<uint>(3), d.get_num_dice());
  EXPECT_EQ(static_cast<uint>(4), d.get_dice_sides());
  EXPECT_EQ(9, d.get_modifier());

  tear_down_spells();
}

TEST(Engine_Calculators_MagicalDamageCalculator, base_damage_stat_component)
{
  setup_spells();
  CreaturePtr creature = setup_creature();
  creature->set_intelligence(13);
  creature->set_willpower(18);

  MagicalDamageCalculator mdc(PhaseOfMoonType::PHASE_OF_MOON_NULL);
  Damage d = mdc.calculate_base_damage_with_bonuses_or_penalties(creature);

  EXPECT_EQ(static_cast<uint>(3), d.get_num_dice());
  EXPECT_EQ(static_cast<uint>(4), d.get_dice_sides());
  EXPECT_EQ(3, d.get_modifier());

  creature->set_intelligence(24);
  creature->set_willpower(31);

  d = mdc.calculate_base_damage_with_bonuses_or_penalties(creature);

  EXPECT_EQ(static_cast<uint>(3), d.get_num_dice());
  EXPECT_EQ(static_cast<uint>(4), d.get_dice_sides());
  EXPECT_EQ(5, d.get_modifier());

  tear_down_spells();
}

