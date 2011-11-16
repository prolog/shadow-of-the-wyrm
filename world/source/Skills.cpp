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
Archery::Archery()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_ARCHERY;
}

// Awareness
Awareness::Awareness()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_AWARENESS;
}

// Bargaining
Bargaining::Bargaining()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BARGAINING;
}

// Beastmastery
Beastmastery::Beastmastery()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BEASTMASTERY;
}

// Blind Fighting
BlindFighting::BlindFighting()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BLIND_FIGHTING;
}

// Boating
Boating::Boating()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOATING;
}

// Bowyer
Bowyer::Bowyer()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOWYER;
}

// Brewing
Brewing::Brewing()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BREWING;
}

// Cantrips
Cantrips::Cantrips()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CANTRIPS;
}

// Carrying
Carrying::Carrying()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CARRYING;
}

// Combat
Combat::Combat()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_COMBAT;
}

// Crafting
Crafting::Crafting()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CRAFTING;
}

// Desert Lore
DesertLore::DesertLore()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DESERT_LORE;
}

// Detection
Detection::Detection()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DETECTION;
}

// Disarm Traps
DisarmTraps::DisarmTraps()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DISARM_TRAPS;
}

// Dual Wield
DualWield::DualWield()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUAL_WIELD;
}

// Dungeoneering
Dungeoneering::Dungeoneering()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUNGEONEERING;
}

// Escape
Escape::Escape()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_ESCAPE;
}

// Foraging
Foraging::Foraging()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FORAGING;
}

// Forest Lore
ForestLore::ForestLore()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FOREST_LORE;
}

// Fishing
Fishing::Fishing()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FISHING;
}

// Fletchery
Fletchery::Fletchery()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FLETCHERY;
}

// Herbalism
Herbalism::Herbalism()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HERBALISM;
}

// Hiding
Hiding::Hiding()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HIDING;
}

// Hunting
Hunting::Hunting()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HUNTING;
}

// Intimidation
Intimidation::Intimidation()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_INTIMIDATION;
}

// Jeweler
Jeweler::Jeweler()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JEWELER;
}

// Jumping
Jumping::Jumping()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JUMPING;
}

// Leadership
Leadership::Leadership()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LEADERSHIP;
}

// Literacy
Literacy::Literacy()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LITERACY;
}

// Lore
Lore::Lore()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LORE;
}

// Magic
Magic::Magic()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MAGIC;
}

// Marsh Lore
MarshLore::MarshLore()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MARSH_LORE;
}

// Medicine
Medicine::Medicine()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MEDICINE;
}

// Mountain Lore
MountainLore::MountainLore()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAIN_LORE;
}

// Mountaineering
Mountaineering::Mountaineering()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAINEERING;
}

// Music
Music::Music()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MUSIC;
}

// Night Sight
NightSight::NightSight()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_NIGHT_SIGHT;
}

// Oceanography
Oceanography::Oceanography()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_OCEANOGRAPHY;
}

// Papercraft
Papercraft::Papercraft()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_PAPERCRAFT;
}

// Religion
Religion::Religion()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_RELIGION;
}

// Scribing
Scribing::Scribing()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SCRIBING;
}

// Skinning
Skinning::Skinning()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SKINNING;
}

// Smithing
Smithing::Smithing()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SMITHING;
}

// Spelunking
Spelunking::Spelunking()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SPELUNKING;
}

// Stealth
Stealth::Stealth()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_STEALTH;
}

// Swimming
Swimming::Swimming()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SWIMMING;
}

// Tanning
Tanning::Tanning()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_TANNING;
}

// Thievery
Thievery::Thievery()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_THIEVERY;
}

// Weaving
Weaving::Weaving()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_WEAVING;
}

// MELEE WEAPON SKILLS

// Axes
Axes::Axes()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_AXES;
}

// Short Blades
ShortBlades::ShortBlades()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SHORT_BLADES;
}

// Long Blades
LongBlades::LongBlades()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_LONG_BLADES;
}

// Bludgeons
Bludgeons::Bludgeons()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_BLUDGEONS;
}

// Daggers
Daggers::Daggers()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_DAGGERS;
}

// Rods and Staves
RodsAndStaves::RodsAndStaves()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_RODS_AND_STAVES;
}

// Spears
Spears::Spears()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SPEARS;
}

// Unarmed
Unarmed::Unarmed()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_UNARMED;
}

// Whips
Whips::Whips()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_WHIPS;
}

// RANGED WEAPON SKILLS

// Thrown Axes
ThrownAxes::ThrownAxes()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_AXES;
}

// Thrown Blades
ThrownBlades::ThrownBlades()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLADES;
}

// Thrown Bludgeons
ThrownBludgeons::ThrownBludgeons()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLUDGEONS;
}

// Bows
Bows::Bows()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BOWS;
}

// Crossbows
Crossbows::Crossbows()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_CROSSBOWS;
}

// Daggers
ThrownDaggers::ThrownDaggers()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_DAGGERS;
}

// Rocks
Rocks::Rocks()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_ROCKS;
}

// Slings
Slings::Slings()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SLINGS;
}

// Spears
ThrownSpears::ThrownSpears()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SPEARS;
}

// MAGIC SKILLS

// Arcane
ArcaneMagic::ArcaneMagic()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_ARCANE;
}

// Divine
DivineMagic::DivineMagic()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_DIVINE;
}

// Mystic
MysticMagic::MysticMagic()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_MYSTIC;
}

// Primordial
PrimordialMagic::PrimordialMagic()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_PRIMORDIAL;
}

// Skills
Skills::Skills()
{
  initialize_skills();
}

Skills::Skills(const Skills& skills)
{
  *this = skills;
}

Skills& Skills::operator=(const Skills& skills)
{
  if (this != &skills)
  {
    this->skills = skills.skills;
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
  Archery archery;
  Awareness awareness;
  Bargaining bargaining;
  Beastmastery beastmastery;
  BlindFighting blind_fighting;
  Boating boating;
  Bowyer bowyer;
  Brewing brewing;
  Cantrips cantrips;
  Carrying carrying;
  Combat combat;
  Crafting crafting;
  DesertLore desert_lore;
  Detection detection;
  DisarmTraps disarm_traps;
  DualWield dual_wield;
  Dungeoneering dungeoneering;
  Escape escape;
  Fishing fishing;
  Fletchery fletchery;
  Foraging foraging;
  ForestLore forest_lore;
  Herbalism herbalism;
  Hiding hiding;
  Hunting hunting;
  Intimidation intimidation;
  Jeweler jeweler;
  Jumping jumping;
  Leadership leadership;
  Literacy literacy;
  Lore lore;
  Magic magic;
  MarshLore marsh_lore;
  Medicine medicine;
  MountainLore mountain_lore;
  Mountaineering mountaineering;
  Music music;
  NightSight night_sight;
  Oceanography oceanography;
  Papercraft papercraft;
  Religion religion;
  Scribing scribing;
  Skinning skinning;
  Smithing smithing;
  Spelunking spelunking;
  Stealth stealth;
  Swimming swimming;
  Tanning tanning;
  Thievery thievery;
  Weaving weaving;

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
  Axes axes;
  ShortBlades short_blades;
  LongBlades long_blades;
  Bludgeons bludgeons;
  Daggers daggers;
  RodsAndStaves rods_and_staves;
  Spears spears;
  Unarmed unarmed;
  Whips whips;

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
  ThrownAxes axes;
  ThrownBlades blades;
  ThrownBludgeons bludgeons;
  Bows bows;
  Crossbows crossbows;
  ThrownDaggers daggers;
  Rocks rocks;
  Slings slings;
  ThrownSpears spears;

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
  ArcaneMagic arcane;
  DivineMagic divine;
  MysticMagic mystic;
  PrimordialMagic primordial;

  skills.insert(make_pair(SKILL_MAGIC_ARCANE, arcane));
  skills.insert(make_pair(SKILL_MAGIC_DIVINE, divine));
  skills.insert(make_pair(SKILL_MAGIC_MYSTIC, mystic));
  skills.insert(make_pair(SKILL_MAGIC_PRIMORDIAL, primordial));
}

#ifdef UNIT_TESTS
#include "unit_tests/Skills_test.cpp"
#endif
