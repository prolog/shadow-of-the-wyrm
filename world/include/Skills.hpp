#pragma once
#include <string>
#include "SkillTypes.hpp"
#include "StringTable.hpp"

// Abstract class - subclasses GeneralSkill, WeaponSkill, MagicSkill
// implement it.
class Skill
{
  public:
    Skill();
    Skill(const SkillCategory skill_category);
    Skill(const Skill& skill);
    Skill& operator=(const Skill& skill);

    void initialize();

    virtual void set_value(const int new_value);
    virtual int  get_value() const;
    virtual void increment_value();

    virtual void set_marks(const int new_marks);
    virtual int  get_marks() const;
    virtual void increment_marks();

    virtual void set_threshold(const int new_threshold);
    virtual int  get_threshold() const;

    virtual SkillCategory get_category() const;

    virtual void set_skill_name_sid(const std::string& new_skill_name_sid);
    virtual std::string get_skill_name_sid() const;

    std::string str() const;

  protected:
    int value;
    int marks;
    int threshold;
    SkillCategory category;
    std::string skill_name_sid;
};

class GeneralSkill : public Skill
{
  public:
    GeneralSkill();

  protected:
};

class WeaponSkill : public Skill
{
  public:
    WeaponSkill();

  protected:
};

class RangedWeaponSkill : public Skill
{
  public:
    RangedWeaponSkill();

  protected:
};

class MagicSkill : public Skill
{
  public:
    MagicSkill();

  protected:
};

// Individual skills
class Archery : public GeneralSkill
{
  public:
    Archery();
};

class Awareness : public GeneralSkill
{
  public:
    Awareness();
};

class Bargaining : public GeneralSkill
{
  public:
    Bargaining();
};

class Beastmastery : public GeneralSkill
{
  public:
    Beastmastery();
};

class BlindFighting : public GeneralSkill
{
  public:
    BlindFighting();
};

class Boating : public GeneralSkill
{
  public:
    Boating();
};

class Bowyer : public GeneralSkill
{
  public:
    Bowyer();
};

class Brewing : public GeneralSkill
{
  public:
    Brewing();
};

class Cantrips : public GeneralSkill
{
  public:
    Cantrips();
};

class Carrying : public GeneralSkill
{
  public:
    Carrying();
};

class Combat : public GeneralSkill
{
  public:
    Combat();
};

class Crafting : public GeneralSkill
{
  public:
    Crafting();
};

class DesertLore : public GeneralSkill
{
  public:
    DesertLore();
};

class Detection : public GeneralSkill
{
  public:
    Detection();
};

class DisarmTraps : public GeneralSkill
{
  public:
    DisarmTraps();
};

class DualWield : public GeneralSkill
{
  public:
    DualWield();
};

class Dungeoneering : public GeneralSkill
{
  public:
    Dungeoneering();
};

class Escape : public GeneralSkill
{
  public:
    Escape();
};

class Fishing : public GeneralSkill
{
  public:
    Fishing();
};

class Fletchery : public GeneralSkill
{
  public:
    Fletchery();
};

class Foraging : public GeneralSkill
{
  public:
    Foraging();
};

class ForestLore : public GeneralSkill
{
  public:
    ForestLore();
};

class Herbalism : public GeneralSkill
{
  public:
    Herbalism();
};

class Hiding : public GeneralSkill
{
  public:
    Hiding();
};

class Hunting : public GeneralSkill
{
  public:
    Hunting();
};

class Intimidation : public GeneralSkill
{
  public:
    Intimidation();
};

class Jeweler : public GeneralSkill
{
  public:
    Jeweler();
};

class Jumping : public GeneralSkill
{
  public:
    Jumping();
};

class Leadership : public GeneralSkill
{
  public:
    Leadership();
};

class Literacy : public GeneralSkill
{
  public:
    Literacy();
};

class Lore : public GeneralSkill
{
  public:
    Lore();
};

class Magic : public GeneralSkill
{
  public:
    Magic();
};

class MarshLore : public GeneralSkill
{
  public:
    MarshLore();
};

class Medicine : public GeneralSkill
{
  public:
    Medicine();
};

class MountainLore : public GeneralSkill
{
  public:
    MountainLore();
};

class Mountaineering : public GeneralSkill
{
  public:
    Mountaineering();
};

class Music : public GeneralSkill
{
  public:
    Music();
};

class NightSight : public GeneralSkill
{
  public:
    NightSight();
};

class Oceanography : public GeneralSkill
{
  public:
    Oceanography();
};

class Papercraft : public GeneralSkill
{
  public:
    Papercraft();
};

// Calling this "ReligionSkill" to differentiate from a creature's actual Religion (religion/include/Religion.hpp)
class ReligionSkill : public GeneralSkill
{
  public:
    ReligionSkill();
};

class Scribing : public GeneralSkill
{
  public:
    Scribing();
};

class Skinning : public GeneralSkill
{
  public:
    Skinning();
};

class Smithing : public GeneralSkill
{
  public:
    Smithing();
};

class Spelunking : public GeneralSkill
{
  public:
    Spelunking();
};

class Stealth : public GeneralSkill
{
  public:
    Stealth();
};

class Swimming : public GeneralSkill
{
  public:
    Swimming();
};

class Tanning : public GeneralSkill
{
  public:
    Tanning();
};

class Thievery : public GeneralSkill
{
  public:
    Thievery();
};

class Weaving : public GeneralSkill
{
  public:
    Weaving();
};

// WEAPON SKILLS (MELEE)

class Axes : public WeaponSkill
{
  public:
    Axes();
};

class ShortBlades : public WeaponSkill
{
  public:
    ShortBlades();
};

class LongBlades : public WeaponSkill
{
  public:
    LongBlades();
};

class Bludgeons : public WeaponSkill
{
  public:
    Bludgeons();
};

class Daggers : public WeaponSkill
{
  public:
    Daggers();
};

class RodsAndStaves : public WeaponSkill
{
  public:
    RodsAndStaves();
};

class Spears : public WeaponSkill
{
  public:
    Spears();
};

class Unarmed : public WeaponSkill
{
  public:
    Unarmed();
};

class Whips : public WeaponSkill
{
  public:
    Whips();
};

// WEAPON SKILLS (RANGED)

class ThrownAxes : public RangedWeaponSkill
{
  public:
    ThrownAxes();
};

class ThrownBlades : public RangedWeaponSkill
{
  public:
    ThrownBlades();
};

class ThrownBludgeons : public RangedWeaponSkill
{
  public:
    ThrownBludgeons();
};

class Bows : public RangedWeaponSkill
{
  public:
    Bows();
};

class Crossbows : public RangedWeaponSkill
{
  public:
    Crossbows();
};

class ThrownDaggers : public RangedWeaponSkill
{
  public:
    ThrownDaggers();
};

class Rocks : public RangedWeaponSkill
{
  public:
    Rocks();
};

class Slings : public RangedWeaponSkill
{
  public:
    Slings();
};

class ThrownSpears : public RangedWeaponSkill
{
  public:
    ThrownSpears();
};

// MAGICAL SKILLS

class ArcaneMagic : public MagicSkill
{
  public:
    ArcaneMagic();
};

class DivineMagic : public MagicSkill
{
  public:
    DivineMagic();
};

class MysticMagic : public MagicSkill
{
  public:
    MysticMagic();
};

class PrimordialMagic : public MagicSkill
{
  public:
    PrimordialMagic();
};

// Classes aggregating skills

typedef std::map<SkillType, Skill> SkillMap;
typedef std::map<SkillType, Skill>* SkillMapPtr;

class Skills
{
  public:
    Skills();
    Skills(const Skills& skills);
    Skills& operator=(const Skills& skills);

    // JCD FIXME: An intermediary SkillManager can handle marking/threshold/reset
    // type logic.
    void set_value(const SkillType skill_name, const unsigned int new_value);
    void mark(const SkillType skill_name);

    int get_value(const SkillType& skill_name) const;

    Skill get_skill(const SkillType& st) const;

    std::string str() const;
    
    // This just provides a copy of the map - direct manipulation requires the various
    // methods above.
    std::map<SkillType, Skill> get_raw_skills() const;

  protected:
    void initialize_skills();

    void initialize_general_skills();
    void initialize_melee_skills();
    void initialize_ranged_skills();
    void initialize_magic_skills();

    std::map<SkillType, Skill> skills;
};

