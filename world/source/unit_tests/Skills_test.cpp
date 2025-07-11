#include "gtest/gtest.h"
#include "SkillFactory.hpp"

// Can't instantiate Skill directly, so test the methods of a
// descendent.
TEST(SW_World_Skills_GeneralSkill, value)
{
  ArcherySkill gs;
  gs.set_value(5);

  EXPECT_EQ(5, gs.get_value());

  gs.increment_value();

  EXPECT_EQ(6, gs.get_value());
}

TEST(SW_World_Skills_GeneralSkill, marks)
{
  ArcherySkill gs;
  gs.set_marks(7);

  EXPECT_EQ(7, gs.get_marks().get_value());

  gs.get_marks_ref().incr();

  EXPECT_EQ(8, gs.get_marks().get_value());
}

TEST(SW_World_Skills_GeneralSkill, threshold)
{
  ArcherySkill gs;
  gs.set_threshold(100);

  EXPECT_EQ(100, gs.get_threshold());
}

TEST(SW_World_Skills_GeneralSkill, category)
{
  ArcherySkill archery;
  EXPECT_EQ(SkillCategory::SKILL_CATEGORY_GENERAL, archery.get_category());
}

TEST(SW_World_Skills_WeaponSkill, category)
{
  AxesSkill axes;
  EXPECT_EQ(SkillCategory::SKILL_CATEGORY_MELEE, axes.get_category());
}

TEST(SW_World_Skills_RangedWeaponSkill, category)
{
  BowsSkill bows;
  EXPECT_EQ(SkillCategory::SKILL_CATEGORY_RANGED, bows.get_category());
}

TEST(SW_World_Skills_MagicSkill, category)
{
  ArcaneMagicSkill arcane;
  EXPECT_EQ(SkillCategory::SKILL_CATEGORY_MAGIC, arcane.get_category());
}

TEST(SW_World_Skills, serialization_id)
{
  Skills skills;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILLS, skills.get_class_identifier());
}

TEST(SW_World_Skills, serialization_ids_general_skills)
{
  ArcherySkill archery;
  AwarenessSkill awareness;
  BargainingSkill bargaining;
  BeastmasterySkill beastmastery;
  BlindFightingSkill blind_fighting;
  BoatingSkill boating;
  BowyerSkill bowyer;
  BrewingSkill brewing;
  CantripsSkill cantrips;
  CarryingSkill carrying;
  CombatSkill combat;
  CraftingSkill crafting;
  DesertLoreSkill desert_lore;
  DetectionSkill detection;
  DisarmTrapsSkill disarm_traps;
  DualWieldSkill dual_wield;
  DungeoneeringSkill dungeoneering;
  EscapeSkill escape;
  FishingSkill fishing;
  FletcherySkill fletchery;
  ForagingSkill foraging;
  ForestLoreSkill forest_lore;
  HerbalismSkill herbalism;
  HidingSkill hiding;
  HuntingSkill hunting;
  IntimidationSkill intimidation;
  JewelerSkill jeweler;
  JumpingSkill jumping;
  LeadershipSkill leadership;
  LiteracySkill literacy;
  LoreSkill lore;
  MagicGeneralSkill magic;
  MarshLoreSkill marsh_lore;
  MedicineSkill medicine;
  MountainLoreSkill mountain_lore;
  MusicSkill music;
  NightSightSkill night_sight;
  OceanLoreSkill ocean_lore;
  PapercraftSkill papercraft;
  ReligionSkill religion;
  ScribingSkill scribing;
  SkinningSkill skinning;
  SmithingSkill smithing;
  SpelunkingSkill spelunking;
  StealthSkill stealth;
  SwimmingSkill swimming;
  TanningSkill tanning;
  ThieverySkill thievery;
  WandcraftSkill wandcraft;
  WeavingSkill weaving;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_ARCHERY, archery.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_AWARENESS, awareness.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BARGAINING, bargaining.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BEASTMASTERY, beastmastery.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BLINDFIGHTING, blind_fighting.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BOATING, boating.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BOWYER, bowyer.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BREWING, brewing.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_CANTRIPS, cantrips.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_CARRYING, carrying.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_COMBAT, combat.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_CRAFTING, crafting.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_DESERT_LORE, desert_lore.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_DETECTION, detection.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_DISARM_TRAPS, disarm_traps.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_DUAL_WIELD, dual_wield.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_DUNGEONEERING, dungeoneering.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_ESCAPE, escape.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_FISHING, fishing.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_FLETCHERY, fletchery.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_FORAGING, foraging.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_FOREST_LORE, forest_lore.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_HERBALISM, herbalism.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_HIDING, hiding.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_HUNTING, hunting.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_INTIMIDATION, intimidation.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_JEWELER, jeweler.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_JUMPING, jumping.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_LEADERSHIP, leadership.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_LITERACY, literacy.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_LORE, lore.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_MAGICGENERAL, magic.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_MARSH_LORE, marsh_lore.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_MEDICINE, medicine.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_MOUNTAIN_LORE, mountain_lore.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_MUSIC, music.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_NIGHT_SIGHT, night_sight.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_OCEAN_LORE, ocean_lore.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_PAPERCRAFT, papercraft.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_RELIGION, religion.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SCRIBING, scribing.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SKINNING, skinning.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SMITHING, smithing.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SPELUNKING, spelunking.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_STEALTH, stealth.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SWIMMING, swimming.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_TANNING, tanning.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_THIEVERY, thievery.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_WANDCRAFT, wandcraft.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_WEAVING, weaving.get_class_identifier());
}

TEST(SW_World_Skills, serialization_ids_magic_skills)
{
  ArcaneMagicSkill ams;
  DivineMagicSkill dms;
  MysticMagicSkill mms;
  PrimordialMagicSkill pms;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_ARCANE, ams.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_DIVINE, dms.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_MYSTIC, mms.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_PRIMORDIAL, pms.get_class_identifier());
}

TEST(SW_World_Skills, serialization_ids_melee_skills)
{
  AxesSkill axes;
  ShortBladesSkill short_blades;
  LongBladesSkill long_blades;
  BludgeonsSkill bludgeons;
  DaggersSkill daggers;
  RodsAndStavesSkill rods_and_staves;
  SpearsSkill spears;
  UnarmedSkill unarmed;
  WhipsSkill whips;
  ExoticMeleeSkill exotic;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_AXES, axes.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SHORT_BLADES, short_blades.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_LONG_BLADES, long_blades.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BLUDGEONS, bludgeons.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_DAGGERS, daggers.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_RODS_AND_STAVES, rods_and_staves.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SPEARS, spears.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_UNARMED, unarmed.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_WHIPS, whips.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_EXOTIC, exotic.get_class_identifier());
}

TEST(SW_World_Skills, serialization_ids_ranged_skills)
{
  ThrownAxesSkill ta;
  ThrownBladesSkill tb;
  ThrownBludgeonsSkill tbdg;
  BowsSkill bows;
  CrossbowsSkill crossbows;
  ThrownDaggersSkill td;
  RocksSkill rocks;
  SlingsSkill slings;
  ThrownSpearsSkill ts;
  ExoticRangedSkill te;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_THROWN_AXES, ta.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_THROWN_BLADES, tb.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_THROWN_BLUDGEONS, tbdg.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_BOWS, bows.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_CROSSBOWS, crossbows.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_THROWN_DAGGERS, td.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_ROCKS, rocks.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_SLINGS, slings.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_THROWN_SPEARS, ts.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_SKILL_THROWN_EXOTIC, te.get_class_identifier());
}

void serialize_test_skills(ClassIdentifier skill_ci)
{
  SkillPtr skill, skill2;
  skill = SkillFactory::create_skill(skill_ci);
  skill2 = SkillFactory::create_skill(skill_ci);

  if (skill != nullptr && skill2 != nullptr)
  {
    ostringstream ss;

    skill->serialize(ss);

    istringstream iss(ss.str());

    skill2->deserialize(iss);

    EXPECT_TRUE(*skill == *skill2);
  }
}

TEST(SW_World_Skills, saveload_general_skills)
{
  for(int i = static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_ARCHERY); i <= static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_WEAVING); i++)
  {
    ClassIdentifier skill_ci = static_cast<ClassIdentifier>(i);
  
    serialize_test_skills(skill_ci);
  }
}

TEST(SW_World_Skills, saveload_melee_skills)
{
  for(int i = static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_AXES); i <= static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_EXOTIC); i++)
  {
    ClassIdentifier skill_ci = static_cast<ClassIdentifier>(i);
  
    serialize_test_skills(skill_ci);
  }
}

TEST(SW_World_Skills, saveload_ranged_skills)
{
  for(int i = static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_THROWN_AXES); i <= static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_THROWN_EXOTIC); i++)
  {
    ClassIdentifier skill_ci = static_cast<ClassIdentifier>(i);
  
    serialize_test_skills(skill_ci);
  }
}

TEST(SW_World_Skills, saveload_magic_skills)
{
  for(int i = static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_ARCANE); i <= static_cast<int>(ClassIdentifier::CLASS_ID_SKILL_PRIMORDIAL); i++)
  {
    ClassIdentifier skill_ci = static_cast<ClassIdentifier>(i);
  
    serialize_test_skills(skill_ci);
  }
}

TEST(SW_World_Skills_Skills, has_trainable)
{
  Skills s1;

  EXPECT_TRUE(s1.has_trainable_skill());

  s1.set_all_to(100);

  EXPECT_FALSE(s1.has_trainable_skill());

  s1.set_value(SkillType::SKILL_GENERAL_ARCHERY, 30);

  EXPECT_TRUE(s1.has_trainable_skill());
}

TEST(SW_World_Skills, increment_skills)
{
  Skills s1;
  s1.set_value(SkillType::SKILL_GENERAL_ARCHERY, 30);
  s1.set_value(SkillType::SKILL_GENERAL_BOATING, 50);

  Skills s2;
  s2.set_value(SkillType::SKILL_GENERAL_ARCHERY, 22);
  s2.set_value(SkillType::SKILL_GENERAL_CARRYING, 10);

  s1.increment_skills(s2);

  EXPECT_EQ(52, s1.get_value(SkillType::SKILL_GENERAL_ARCHERY));
  EXPECT_EQ(50, s1.get_value(SkillType::SKILL_GENERAL_BOATING));
  EXPECT_EQ(10, s1.get_value(SkillType::SKILL_GENERAL_CARRYING));
}

TEST(SW_World_Skills, get_trained_magic_skills)
{
  Skills skills;

  EXPECT_TRUE(skills.get_trained_magic_skills().empty());

  vector<SkillType> to_train = {SkillType::SKILL_MAGIC_CANTRIPS, SkillType::SKILL_MAGIC_DIVINE};
  for (SkillType st : to_train)
  {
    skills.set_value(st, 5);
  }

  vector<SkillType> trained = skills.get_trained_magic_skills();

  EXPECT_EQ(static_cast<size_t>(2), trained.size());
  EXPECT_TRUE(trained == to_train);

  to_train = {SkillType::SKILL_MAGIC_CANTRIPS, SkillType::SKILL_MAGIC_ARCANE, SkillType::SKILL_MAGIC_DIVINE, SkillType::SKILL_MAGIC_MYSTIC, SkillType::SKILL_MAGIC_PRIMORDIAL};
  skills.set_all_to(10);
  trained = skills.get_trained_magic_skills();

  EXPECT_TRUE(trained == to_train);
}
