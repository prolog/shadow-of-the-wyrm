#include "gtest/gtest.h"
#include "Ammunition.hpp"
#include "Weapon.hpp"

TEST(SW_Engine_Creatures_NPCSkillDistributor, improve_skills)
{
  NPCSkillDistributor nsd;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills& skills = creature->get_skills();

  vector<SkillType> imp_skills = {SkillType::SKILL_MELEE_UNARMED, SkillType::SKILL_GENERAL_DUNGEONEERING, SkillType::SKILL_GENERAL_MAGIC, SkillType::SKILL_MAGIC_PRIMORDIAL};

  for (const SkillType sk : imp_skills)
  {
    skills.set_value(sk, 10);
  }

  creature->set_skill_points(imp_skills.size() * Skills::MAX_SKILL_VALUE);
  nsd.distribute_unused_skill_points(creature);

  for (const SkillType sk : imp_skills)
  {
    EXPECT_EQ(Skills::MAX_SKILL_VALUE, skills.get_value(sk));
  }
}

TEST(SW_Engine_Creatures_NPCSkillDistributor, get_skills_to_improve)
{
  NPCSkillDistributor nsd;
  vector<SkillType> to_improve;
  to_improve = nsd.get_skills_to_improve(nullptr);

  EXPECT_TRUE(to_improve.empty());

  CreaturePtr creature = std::make_shared<Creature>();

  to_improve = nsd.get_skills_to_improve(creature);

  EXPECT_TRUE(to_improve.size() == 1);
}

TEST(SW_Engine_Creatures_NPCSkillDistributor, get_skills_to_improve_magic)
{
  NPCSkillDistributor nsd;
  vector<SkillType> to_improve;
  vector<SkillType> pot_skills;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills& skills = creature->get_skills();

  skills.set_value(SkillType::SKILL_GENERAL_MAGIC, 15);
  skills.set_value(SkillType::SKILL_MAGIC_ARCANE, 20);

  to_improve = nsd.get_skills_to_improve(creature);
  pot_skills = {SkillType::SKILL_GENERAL_MAGIC, SkillType::SKILL_MAGIC_ARCANE};

  for (SkillType sk : pot_skills)
  {
    EXPECT_TRUE(std::find(to_improve.begin(), to_improve.end(), sk) != to_improve.end());
  }

  skills.set_all_to(10);

  pot_skills.push_back(SkillType::SKILL_MAGIC_DIVINE);
  pot_skills.push_back(SkillType::SKILL_MAGIC_CANTRIPS);
  pot_skills.push_back(SkillType::SKILL_MAGIC_MYSTIC);
  pot_skills.push_back(SkillType::SKILL_MAGIC_PRIMORDIAL);
  to_improve = nsd.get_skills_to_improve(creature);

  for (SkillType sk : pot_skills)
  {
    EXPECT_TRUE(std::find(to_improve.begin(), to_improve.end(), sk) != to_improve.end());
  }
}

TEST(SW_Engine_Creatures_NPCSkillDistributor, get_skills_to_improve_combat)
{
  NPCSkillDistributor nsd;
  vector<SkillType> to_improve;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills& skills = creature->get_skills();
  WeaponPtr ammo = std::make_shared<Ammunition>();
  WeaponPtr weapon = std::make_shared<MeleeWeapon>();
    
  to_improve = nsd.get_skills_to_improve(creature);
  EXPECT_TRUE(std::find(to_improve.begin(), to_improve.end(), SkillType::SKILL_MELEE_UNARMED) != to_improve.end());

  vector<SkillType> pot_skills = {SkillType::SKILL_RANGED_ROCKS, SkillType::SKILL_MELEE_SPEARS};
  ammo->set_trained_ranged_skill(SkillType::SKILL_RANGED_ROCKS);
  weapon->set_trained_skill(SkillType::SKILL_MELEE_SPEARS);
  creature->get_equipment().set_item(weapon, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
  creature->get_equipment().set_item(ammo, EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);

  to_improve = nsd.get_skills_to_improve(creature);
  for (SkillType sk : pot_skills)
  {
    EXPECT_TRUE(std::find(to_improve.begin(), to_improve.end(), sk) != to_improve.end());
  }
}

TEST(SW_Engine_Creatures_NPCSkillDistributor, get_skills_to_improve_misc)
{
  NPCSkillDistributor nsd;
  vector<SkillType> to_improve;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills& skills = creature->get_skills();
  WeaponPtr ammo = std::make_shared<Ammunition>();
  WeaponPtr weapon = std::make_shared<MeleeWeapon>();
  vector<SkillType> pot_skills = {SkillType::SKILL_GENERAL_COMBAT, SkillType::SKILL_GENERAL_DUNGEONEERING, SkillType::SKILL_GENERAL_ARCHERY, SkillType::SKILL_GENERAL_INTIMIDATION, SkillType::SKILL_GENERAL_AWARENESS};

  skills.set_all_to(50);
  to_improve = nsd.get_skills_to_improve(creature);

  for (SkillType ps : pot_skills)
  {
    EXPECT_TRUE(std::find(to_improve.begin(), to_improve.end(), ps) != to_improve.end());
  }
}
