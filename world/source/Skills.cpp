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
    this->skill_increment_message_sid = skill.skill_increment_message_sid;
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

// Set the value, and then also update the threshold for the new value.
void Skill::set_value(const int new_value)
{
  value = new_value;
  
  set_threshold_for_value(value);
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

// By default, the threshold for a skill is the skill's value.
// Certain classes of skills (weapon skills, etc) may override this.
void Skill::set_threshold_for_value(const int skill_value)
{
  threshold = skill_value;
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

void Skill::set_skill_increment_message_sid(const string& new_skill_increment_message_sid)
{
  skill_increment_message_sid = new_skill_increment_message_sid;
}

string Skill::get_skill_increment_message_sid() const
{
  return skill_increment_message_sid;
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

void WeaponSkill::set_threshold_for_value(const int skill_value)
{
  // As the majority of skill use in-game will be weapon skills,
  // these should be harder to train to max.  Ranged weapon skills
  // will be easier due to the scarcity of ammunition.
  threshold = (skill_value * 2);
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
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_ARCHERY_INCREMENT;
}

// Awareness
AwarenessSkill::AwarenessSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_AWARENESS;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_AWARENESS_INCREMENT;
}

// Bargaining
BargainingSkill::BargainingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BARGAINING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BARGAINING_INCREMENT;
}

// Beastmastery
BeastmasterySkill::BeastmasterySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BEASTMASTERY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BEASTMASTERY_INCREMENT;
}

// Blind Fighting
BlindFightingSkill::BlindFightingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BLIND_FIGHTING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BLIND_FIGHTING_INCREMENT;
}

// Boating
BoatingSkill::BoatingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOATING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BOATING_INCREMENT;
}

// Bowyer
BowyerSkill::BowyerSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOWYER;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BOWYER_INCREMENT;
}

// Brewing
BrewingSkill::BrewingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BREWING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BREWING_INCREMENT;
}

// Cantrips
CantripsSkill::CantripsSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CANTRIPS;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_CANTRIPS_INCREMENT;
}

// Carrying
CarryingSkill::CarryingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CARRYING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_CARRYING_INCREMENT;
}

// Combat
CombatSkill::CombatSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_COMBAT;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_COMBAT_INCREMENT;
}

// Combat is a much more difficult skill to increase.
void CombatSkill::set_threshold_for_value(const int skill_value)
{
  threshold = (skill_value * 2);
}


// Crafting
CraftingSkill::CraftingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CRAFTING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_CRAFTING_INCREMENT;
}

// Desert Lore
DesertLoreSkill::DesertLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DESERT_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DESERT_LORE_INCREMENT;
}

// Detection
DetectionSkill::DetectionSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DETECTION;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DETECTION_INCREMENT;
}

// Disarm Traps
DisarmTrapsSkill::DisarmTrapsSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DISARM_TRAPS;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DISARM_TRAPS_INCREMENT;
}

// Dual Wield
DualWieldSkill::DualWieldSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUAL_WIELD;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DUAL_WIELD_INCREMENT;
}

// Dungeoneering
DungeoneeringSkill::DungeoneeringSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUNGEONEERING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DUNGEONEERING_INCREMENT;
}

// Escape
EscapeSkill::EscapeSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_ESCAPE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_ESCAPE_INCREMENT;
}

// Foraging
ForagingSkill::ForagingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FORAGING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FORAGING_INCREMENT;
}

// Forest Lore
ForestLoreSkill::ForestLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FOREST_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FOREST_LORE_INCREMENT;
}

// Fishing
FishingSkill::FishingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FISHING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FISHING_INCREMENT;
}

// Fletchery
FletcherySkill::FletcherySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FLETCHERY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FLETCHERY_INCREMENT;
}

// Herbalism
HerbalismSkill::HerbalismSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HERBALISM;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_HERBALISM_INCREMENT;
}

// Hiding
HidingSkill::HidingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HIDING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_HIDING_INCREMENT;
}

// Hunting
HuntingSkill::HuntingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HUNTING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_HUNTING_INCREMENT;
}

// Intimidation
IntimidationSkill::IntimidationSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_INTIMIDATION;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_INTIMIDATION_INCREMENT;
}

// Jeweler
JewelerSkill::JewelerSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JEWELER;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_JEWELER_INCREMENT;
}

// Jumping
JumpingSkill::JumpingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JUMPING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_JUMPING_INCREMENT;
}

// Leadership
LeadershipSkill::LeadershipSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LEADERSHIP;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_LEADERSHIP_INCREMENT;
}

// Literacy
LiteracySkill::LiteracySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LITERACY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_LEADERSHIP_INCREMENT;
}

// Lore
LoreSkill::LoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_LORE_INCREMENT;
}

// Magic
MagicGeneralSkill::MagicGeneralSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MAGIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MAGIC_INCREMENT;
}

// Magic, like Combat, is a much more difficult skill to increase.
void MagicGeneralSkill::set_threshold_for_value(const int skill_value)
{
  threshold = skill_value * 2;
}

// Marsh Lore
MarshLoreSkill::MarshLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MARSH_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MARSH_LORE_INCREMENT;
}

// Medicine
MedicineSkill::MedicineSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MEDICINE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MEDICINE_INCREMENT;
}

// Mountain Lore
MountainLoreSkill::MountainLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAIN_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAIN_LORE_INCREMENT;
}

// Mountaineering
MountaineeringSkill::MountaineeringSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAINEERING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAINEERING_INCREMENT;
}

// Music
MusicSkill::MusicSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MUSIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MUSIC_INCREMENT;
}

// Night Sight
NightSightSkill::NightSightSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_NIGHT_SIGHT;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_NIGHT_SIGHT_INCREMENT;
}

// Oceanography
OceanographySkill::OceanographySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_OCEANOGRAPHY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_OCEANOGRAPHY_INCREMENT;
}

// Papercraft
PapercraftSkill::PapercraftSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_PAPERCRAFT;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_PAPERCRAFT_INCREMENT;
}

// Religion
ReligionSkill::ReligionSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_RELIGION;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_RELIGION_INCREMENT;
}

// Scribing
ScribingSkill::ScribingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SCRIBING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SCRIBING_INCREMENT;
}

// Skinning
SkinningSkill::SkinningSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SKINNING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SKINNING_INCREMENT;
}

// Smithing
SmithingSkill::SmithingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SMITHING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SMITHING_INCREMENT;
}

// Spelunking
SpelunkingSkill::SpelunkingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SPELUNKING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SPELUNKING_INCREMENT;
}

// Stealth
StealthSkill::StealthSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_STEALTH;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_STEALTH_INCREMENT;
}

// Swimming
SwimmingSkill::SwimmingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SWIMMING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SWIMMING_INCREMENT;
}

// Tanning
TanningSkill::TanningSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_TANNING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_TANNING_INCREMENT;
}

// Thievery
ThieverySkill::ThieverySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_THIEVERY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_THIEVERY_INCREMENT;
}

// Weaving
WeavingSkill::WeavingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_WEAVING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_WEAVING_INCREMENT;
}

// MELEE WEAPON SKILLS

// Axes
AxesSkill::AxesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_AXES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_AXES_INCREMENT;
}

// Short Blades
ShortBladesSkill::ShortBladesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SHORT_BLADES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_SHORT_BLADES_INCREMENT;
}

// Long Blades
LongBladesSkill::LongBladesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_LONG_BLADES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_LONG_BLADES_INCREMENT;
}

// Bludgeons
BludgeonsSkill::BludgeonsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_BLUDGEONS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_BLUDGEONS_INCREMENT;
}

// Daggers
DaggersSkill::DaggersSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_DAGGERS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_DAGGERS_INCREMENT;
}

// Rods and Staves
RodsAndStavesSkill::RodsAndStavesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_RODS_AND_STAVES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_RODS_AND_STAVES_INCREMENT;
}

// Spears
SpearsSkill::SpearsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SPEARS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_SPEARS_INCREMENT;
}

// Unarmed
UnarmedSkill::UnarmedSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_UNARMED;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_UNARMED_INCREMENT;
}

// Whips
WhipsSkill::WhipsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_WHIPS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_WHIPS_INCREMENT;
}

// RANGED WEAPON SKILLS

// Thrown Axes
ThrownAxesSkill::ThrownAxesSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_AXES;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_AXES_INCREMENT;
}

// Thrown Blades
ThrownBladesSkill::ThrownBladesSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLADES;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_BLADES_INCREMENT;
}

// Thrown Bludgeons
ThrownBludgeonsSkill::ThrownBludgeonsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLUDGEONS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_BLUDGEONS_INCREMENT;
}

// Bows
BowsSkill::BowsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BOWS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_BOWS_INCREMENT;
}

// Crossbows
CrossbowsSkill::CrossbowsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_CROSSBOWS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_CROSSBOWS_INCREMENT;
}

// Daggers
ThrownDaggersSkill::ThrownDaggersSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_DAGGERS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_DAGGERS_INCREMENT;
}

// Rocks
RocksSkill::RocksSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_ROCKS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_ROCKS_INCREMENT;
}

// Slings
SlingsSkill::SlingsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SLINGS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_SLINGS_INCREMENT;
}

// Spears
ThrownSpearsSkill::ThrownSpearsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SPEARS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_SPEARS_INCREMENT;
}

// MAGIC SKILLS

// Arcane
ArcaneMagicSkill::ArcaneMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_ARCANE;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_ARCANE_INCREMENT;
}

// Divine
DivineMagicSkill::DivineMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_DIVINE;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_DIVINE_INCREMENT;
}

// Mystic
MysticMagicSkill::MysticMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_MYSTIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_MYSTIC_INCREMENT;
}

// Primordial
PrimordialMagicSkill::PrimordialMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_PRIMORDIAL;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_PRIMORDIAL_INCREMENT;
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

void Skills::set_skill(const SkillType& st, const Skill& skill)
{
  // Always overwrite any previously existing skill.
  skills[st] = skill;
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

// Return a reference to the skills map
std::map<SkillType, Skill>& Skills::get_raw_skills()
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
