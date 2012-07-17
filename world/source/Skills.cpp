#include <sstream>
#include <boost/foreach.hpp>
#include "Skills.hpp"
#include "SkillTypes.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"

using namespace std;

// Skill
Skill::Skill()
{
  initialize();
}

Skill::Skill(const SkillCategory new_category)
{
  initialize();
  category = new_category;
}

Skill& Skill::operator=(const Skill& skill)
{
  if (this != &skill)
  {
    this->category = skill.category;
    this->value = skill.value;
    this->marks = skill.marks;
    this->threshold = skill.threshold;
    this->skill_name_sid = skill.skill_name_sid;
  }

  return *this;
}

Skill::Skill(const Skill& skill)
{
  *this = skill;
}

void Skill::initialize()
{
  category = SKILL_CATEGORY_UNDEFINED;
  value = 0;
  marks = 0;
  threshold = 0;
}

void Skill::set_value(const int new_value)
{
  value = new_value;
}

int Skill::get_value() const
{
  return value;
}

void Skill::increment_value()
{
  value++;
}

void Skill::set_marks(const int new_marks)
{
  marks = new_marks;
}

int Skill::get_marks() const
{
  return marks;
}

void Skill::increment_marks()
{
  marks++;
}

void Skill::set_threshold(const int new_threshold)
{
  threshold = new_threshold;
}

int Skill::get_threshold() const
{
  return threshold;
}

SkillCategory Skill::get_category() const
{
  return category;
}

void Skill::set_skill_name_sid(const string& new_skill_name_sid)
{
  skill_name_sid = new_skill_name_sid;
}

string Skill::get_skill_name_sid() const
{
  return skill_name_sid;
}

// Shouldn't be used in-game - this is just a function for outputting the entire skill as a string.
string Skill::str() const
{
  ostringstream ss;

  ss << StringTable::get(skill_name_sid) << ": " << value;

  return ss.str();
}

// GeneralSkill
GeneralSkill::GeneralSkill() : Skill(SKILL_CATEGORY_GENERAL)
{
}

// WeaponSkill
WeaponSkill::WeaponSkill() : Skill(SKILL_CATEGORY_MELEE)
{
}

// RangedWeaponSkill
RangedWeaponSkill::RangedWeaponSkill() : Skill(SKILL_CATEGORY_RANGED)
{
}

// MagicSkill
MagicSkill::MagicSkill() : Skill(SKILL_CATEGORY_MAGIC)
{
}

// Individual Skills

// Archery
ArcherySkill::ArcherySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_ARCHERY;
}

// Awareness
AwarenessSkill::AwarenessSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_AWARENESS;
}

// Bargaining
BargainingSkill::BargainingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BARGAINING;
}

// Beastmastery
BeastmasterySkill::BeastmasterySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BEASTMASTERY;
}

// Blind Fighting
BlindFightingSkill::BlindFightingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BLIND_FIGHTING;
}

// Boating
BoatingSkill::BoatingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOATING;
}

// Bowyer
BowyerSkill::BowyerSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOWYER;
}

// Brewing
BrewingSkill::BrewingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BREWING;
}

// Cantrips
CantripsSkill::CantripsSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CANTRIPS;
}

// Carrying
CarryingSkill::CarryingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CARRYING;
}

// Combat
CombatSkill::CombatSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_COMBAT;
}

// Crafting
CraftingSkill::CraftingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CRAFTING;
}

// Desert Lore
DesertLoreSkill::DesertLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DESERT_LORE;
}

// Detection
DetectionSkill::DetectionSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DETECTION;
}

// Disarm Traps
DisarmTrapsSkill::DisarmTrapsSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DISARM_TRAPS;
}

// Dual Wield
DualWieldSkill::DualWieldSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUAL_WIELD;
}

// Dungeoneering
DungeoneeringSkill::DungeoneeringSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUNGEONEERING;
}

// Escape
EscapeSkill::EscapeSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_ESCAPE;
}

// Foraging
ForagingSkill::ForagingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FORAGING;
}

// Forest Lore
ForestLoreSkill::ForestLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FOREST_LORE;
}

// Fishing
FishingSkill::FishingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FISHING;
}

// Fletchery
FletcherySkill::FletcherySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FLETCHERY;
}

// Herbalism
HerbalismSkill::HerbalismSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HERBALISM;
}

// Hiding
HidingSkill::HidingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HIDING;
}

// Hunting
HuntingSkill::HuntingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HUNTING;
}

// Intimidation
IntimidationSkill::IntimidationSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_INTIMIDATION;
}

// Jeweler
JewelerSkill::JewelerSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JEWELER;
}

// Jumping
JumpingSkill::JumpingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JUMPING;
}

// Leadership
LeadershipSkill::LeadershipSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LEADERSHIP;
}

// Literacy
LiteracySkill::LiteracySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LITERACY;
}

// Lore
LoreSkill::LoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LORE;
}

// Magic
MagicGeneralSkill::MagicGeneralSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MAGIC;
}

// Marsh Lore
MarshLoreSkill::MarshLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MARSH_LORE;
}

// Medicine
MedicineSkill::MedicineSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MEDICINE;
}

// Mountain Lore
MountainLoreSkill::MountainLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAIN_LORE;
}

// Mountaineering
MountaineeringSkill::MountaineeringSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAINEERING;
}

// Music
MusicSkill::MusicSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MUSIC;
}

// Night Sight
NightSightSkill::NightSightSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_NIGHT_SIGHT;
}

// Oceanography
OceanographySkill::OceanographySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_OCEANOGRAPHY;
}

// Papercraft
PapercraftSkill::PapercraftSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_PAPERCRAFT;
}

// Religion
ReligionSkill::ReligionSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_RELIGION;
}

// Scribing
ScribingSkill::ScribingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SCRIBING;
}

// Skinning
SkinningSkill::SkinningSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SKINNING;
}

// Smithing
SmithingSkill::SmithingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SMITHING;
}

// Spelunking
SpelunkingSkill::SpelunkingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SPELUNKING;
}

// Stealth
StealthSkill::StealthSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_STEALTH;
}

// Swimming
SwimmingSkill::SwimmingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SWIMMING;
}

// Tanning
TanningSkill::TanningSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_TANNING;
}

// Thievery
ThieverySkill::ThieverySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_THIEVERY;
}

// Weaving
WeavingSkill::WeavingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_WEAVING;
}

// MELEE WEAPON SKILLS

// Axes
AxesSkill::AxesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_AXES;
}

// Short Blades
ShortBladesSkill::ShortBladesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SHORT_BLADES;
}

// Long Blades
LongBladesSkill::LongBladesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_LONG_BLADES;
}

// Bludgeons
BludgeonsSkill::BludgeonsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_BLUDGEONS;
}

// Daggers
DaggersSkill::DaggersSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_DAGGERS;
}

// Rods and Staves
RodsAndStavesSkill::RodsAndStavesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_RODS_AND_STAVES;
}

// Spears
SpearsSkill::SpearsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SPEARS;
}

// Unarmed
UnarmedSkill::UnarmedSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_UNARMED;
}

// Whips
WhipsSkill::WhipsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_WHIPS;
}

// RANGED WEAPON SKILLS

// Thrown Axes
ThrownAxesSkill::ThrownAxesSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_AXES;
}

// Thrown Blades
ThrownBladesSkill::ThrownBladesSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLADES;
}

// Thrown Bludgeons
ThrownBludgeonsSkill::ThrownBludgeonsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLUDGEONS;
}

// Bows
BowsSkill::BowsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BOWS;
}

// Crossbows
CrossbowsSkill::CrossbowsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_CROSSBOWS;
}

// Daggers
ThrownDaggersSkill::ThrownDaggersSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_DAGGERS;
}

// Rocks
RocksSkill::RocksSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_ROCKS;
}

// Slings
SlingsSkill::SlingsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SLINGS;
}

// Spears
ThrownSpearsSkill::ThrownSpearsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SPEARS;
}

// MAGIC SKILLS

// Arcane
ArcaneMagicSkill::ArcaneMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_ARCANE;
}

// Divine
DivineMagicSkill::DivineMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_DIVINE;
}

// Mystic
MysticMagicSkill::MysticMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_MYSTIC;
}

// Primordial
PrimordialMagicSkill::PrimordialMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_PRIMORDIAL;
}

// Skills
Skills::Skills()
{
  initialize_skills();
}

Skills::Skills(const Skills& copy_skills)
{
  *this = copy_skills;
}

Skills& Skills::operator=(const Skills& copy_skills)
{
  if (this != &copy_skills)
  {
    this->skills = copy_skills.skills;
  }

  return *this;
}

// Set the value of a skill
void Skills::set_value(const SkillType skill_name, const unsigned int value)
{
  Skill& skill_to_set = skills[skill_name];
  skill_to_set.set_value(value);
}

// Mark a skill.  JCD FIXME: A skill manager should control this...
void Skills::mark(const SkillType skill_name)
{
  Skill& skill_to_mark = skills[skill_name];
  skill_to_mark.increment_marks();
}

int Skills::get_value(const SkillType& skill_name) const
{
  Skill skill = get_skill(skill_name);
  return skill.get_value();
}

Skill Skills::get_skill(const SkillType& st) const
{
  Skill result;

  map<SkillType, Skill>::const_iterator sk_it = skills.find(st);

  if (sk_it != skills.end())
  {
    result = sk_it->second;
  }

  return result;
}

string Skills::str() const
{
  string skills_str;

  for (SkillMap::const_iterator sk_it = skills.begin(); sk_it != skills.end(); sk_it++)
  {
    Skill skill = sk_it->second;
    skills_str = skills_str + skill.str() + " ";
  }

  return skills_str;
}

// Return a copy of the skills map
std::map<SkillType, Skill> Skills::get_raw_skills() const
{
  return skills;
}

// Initialize all the general, combat, and magical skills.
void Skills::initialize_skills()
{
  initialize_general_skills();
  initialize_melee_skills();
  initialize_ranged_skills();
  initialize_magic_skills();
}

// Initialize the list of general skills.
void Skills::initialize_general_skills()
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
  MountaineeringSkill mountaineering;
  MusicSkill music;
  NightSightSkill night_sight;
  OceanographySkill oceanography;
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
  WeavingSkill weaving;

  skills.insert(make_pair(SKILL_GENERAL_ARCHERY, archery));
  skills.insert(make_pair(SKILL_GENERAL_AWARENESS, awareness));
  skills.insert(make_pair(SKILL_GENERAL_BARGAINING, bargaining));
  skills.insert(make_pair(SKILL_GENERAL_BEASTMASTERY, beastmastery));
  skills.insert(make_pair(SKILL_GENERAL_BLIND_FIGHTING, blind_fighting));
  skills.insert(make_pair(SKILL_GENERAL_BOATING, boating));
  skills.insert(make_pair(SKILL_GENERAL_BOWYER, bowyer));
  skills.insert(make_pair(SKILL_GENERAL_BREWING, brewing));
  skills.insert(make_pair(SKILL_GENERAL_CANTRIPS, cantrips));
  skills.insert(make_pair(SKILL_GENERAL_CARRYING, carrying));
  skills.insert(make_pair(SKILL_GENERAL_COMBAT, combat));
  skills.insert(make_pair(SKILL_GENERAL_CRAFTING, crafting));
  skills.insert(make_pair(SKILL_GENERAL_DESERT_LORE, desert_lore));
  skills.insert(make_pair(SKILL_GENERAL_DETECTION, detection));
  skills.insert(make_pair(SKILL_GENERAL_DISARM_TRAPS, disarm_traps));
  skills.insert(make_pair(SKILL_GENERAL_DUAL_WIELD, dual_wield));
  skills.insert(make_pair(SKILL_GENERAL_DUNGEONEERING, dungeoneering));
  skills.insert(make_pair(SKILL_GENERAL_ESCAPE, escape));
  skills.insert(make_pair(SKILL_GENERAL_FISHING, fishing));
  skills.insert(make_pair(SKILL_GENERAL_FLETCHERY, fletchery));
  skills.insert(make_pair(SKILL_GENERAL_FORAGING, foraging));
  skills.insert(make_pair(SKILL_GENERAL_FOREST_LORE, forest_lore));
  skills.insert(make_pair(SKILL_GENERAL_HERBALISM, herbalism));
  skills.insert(make_pair(SKILL_GENERAL_HIDING, hiding));
  skills.insert(make_pair(SKILL_GENERAL_HUNTING, hunting));
  skills.insert(make_pair(SKILL_GENERAL_INTIMIDATION, intimidation));
  skills.insert(make_pair(SKILL_GENERAL_JEWELER, jeweler));
  skills.insert(make_pair(SKILL_GENERAL_JUMPING, jumping));
  skills.insert(make_pair(SKILL_GENERAL_LEADERSHIP, leadership));
  skills.insert(make_pair(SKILL_GENERAL_LITERACY, literacy));
  skills.insert(make_pair(SKILL_GENERAL_LORE, lore));
  skills.insert(make_pair(SKILL_GENERAL_MAGIC, magic));
  skills.insert(make_pair(SKILL_GENERAL_MARSH_LORE, marsh_lore));
  skills.insert(make_pair(SKILL_GENERAL_MEDICINE, medicine));
  skills.insert(make_pair(SKILL_GENERAL_MOUNTAIN_LORE, mountain_lore));
  skills.insert(make_pair(SKILL_GENERAL_MOUNTAINEERING, mountaineering));
  skills.insert(make_pair(SKILL_GENERAL_MUSIC, music));
  skills.insert(make_pair(SKILL_GENERAL_NIGHT_SIGHT, night_sight));
  skills.insert(make_pair(SKILL_GENERAL_OCEANOGRAPHY, oceanography));
  skills.insert(make_pair(SKILL_GENERAL_PAPERCRAFT, papercraft));
  skills.insert(make_pair(SKILL_GENERAL_RELIGION, religion));
  skills.insert(make_pair(SKILL_GENERAL_SCRIBING, scribing));
  skills.insert(make_pair(SKILL_GENERAL_SKINNING, skinning));
  skills.insert(make_pair(SKILL_GENERAL_SMITHING, smithing));
  skills.insert(make_pair(SKILL_GENERAL_SPELUNKING, spelunking));
  skills.insert(make_pair(SKILL_GENERAL_STEALTH, stealth));
  skills.insert(make_pair(SKILL_GENERAL_SWIMMING, swimming));
  skills.insert(make_pair(SKILL_GENERAL_TANNING, tanning));
  skills.insert(make_pair(SKILL_GENERAL_THIEVERY, thievery));
  skills.insert(make_pair(SKILL_GENERAL_WEAVING, weaving));
}

// Initialize all the melee skills.
void Skills::initialize_melee_skills()
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

  skills.insert(make_pair(SKILL_MELEE_AXES, axes));
  skills.insert(make_pair(SKILL_MELEE_SHORT_BLADES, short_blades));
  skills.insert(make_pair(SKILL_MELEE_LONG_BLADES, long_blades));
  skills.insert(make_pair(SKILL_MELEE_BLUDGEONS, bludgeons));
  skills.insert(make_pair(SKILL_MELEE_DAGGERS, daggers));
  skills.insert(make_pair(SKILL_MELEE_RODS_AND_STAVES, rods_and_staves));
  skills.insert(make_pair(SKILL_MELEE_SPEARS, spears));
  skills.insert(make_pair(SKILL_MELEE_UNARMED, unarmed));
  skills.insert(make_pair(SKILL_MELEE_WHIPS, whips));
}

// Initialize all the ranged weapon skills.
void Skills::initialize_ranged_skills()
{
  ThrownAxesSkill axes;
  ThrownBladesSkill blades;
  ThrownBludgeonsSkill bludgeons;
  BowsSkill bows;
  CrossbowsSkill crossbows;
  ThrownDaggersSkill daggers;
  RocksSkill rocks;
  SlingsSkill slings;
  ThrownSpearsSkill spears;

  skills.insert(make_pair(SKILL_RANGED_AXES, axes));
  skills.insert(make_pair(SKILL_RANGED_BLADES, blades));
  skills.insert(make_pair(SKILL_RANGED_BLUDGEONS, bludgeons));
  skills.insert(make_pair(SKILL_RANGED_BOWS, bows));
  skills.insert(make_pair(SKILL_RANGED_CROSSBOWS, crossbows));
  skills.insert(make_pair(SKILL_RANGED_DAGGERS, daggers));
  skills.insert(make_pair(SKILL_RANGED_ROCKS, rocks));
  skills.insert(make_pair(SKILL_RANGED_SLINGS, slings));
  skills.insert(make_pair(SKILL_RANGED_SPEARS, spears));
}

// Initialize all the magic skills.
void Skills::initialize_magic_skills()
{
  ArcaneMagicSkill arcane;
  DivineMagicSkill divine;
  MysticMagicSkill mystic;
  PrimordialMagicSkill primordial;

  skills.insert(make_pair(SKILL_MAGIC_ARCANE, arcane));
  skills.insert(make_pair(SKILL_MAGIC_DIVINE, divine));
  skills.insert(make_pair(SKILL_MAGIC_MYSTIC, mystic));
  skills.insert(make_pair(SKILL_MAGIC_PRIMORDIAL, primordial));
}

#ifdef UNIT_TESTS
#include "unit_tests/Skills_test.cpp"
#endif
