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
    virtual void set_threshold_for_value(const int skill_value);
    virtual int  get_threshold() const;

    virtual SkillCategory get_category() const;

    virtual void set_skill_name_sid(const std::string& new_skill_name_sid);
    virtual std::string get_skill_name_sid() const;
    
    virtual void set_skill_increment_message_sid(const std::string& new_skill_increment_message_sid);
    virtual std::string get_skill_increment_message_sid() const;

    std::string str() const;

  protected:
    int value;
    int marks;
    int threshold;
    SkillCategory category;
    std::string skill_name_sid;
    std::string skill_increment_message_sid;
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

    virtual void set_threshold_for_value(const int skill_value);

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
class ArcherySkill : public GeneralSkill
{
  public:
    ArcherySkill();
};

class AwarenessSkill : public GeneralSkill
{
  public:
    AwarenessSkill();
};

class BargainingSkill : public GeneralSkill
{
  public:
    BargainingSkill();
};

class BeastmasterySkill : public GeneralSkill
{
  public:
    BeastmasterySkill();
};

class BlindFightingSkill : public GeneralSkill
{
  public:
    BlindFightingSkill();
};

class BoatingSkill : public GeneralSkill
{
  public:
    BoatingSkill();
};

class BowyerSkill : public GeneralSkill
{
  public:
    BowyerSkill();
};

class BrewingSkill : public GeneralSkill
{
  public:
    BrewingSkill();
};

class CantripsSkill : public GeneralSkill
{
  public:
    CantripsSkill();
};

class CarryingSkill : public GeneralSkill
{
  public:
    CarryingSkill();
};

class CombatSkill : public GeneralSkill
{
  public:
    CombatSkill();

    virtual void set_threshold_for_value(const int skill_value);
};

class CraftingSkill : public GeneralSkill
{
  public:
    CraftingSkill();
};

class DesertLoreSkill : public GeneralSkill
{
  public:
    DesertLoreSkill();
};

class DetectionSkill : public GeneralSkill
{
  public:
    DetectionSkill();
};

class DisarmTrapsSkill : public GeneralSkill
{
  public:
    DisarmTrapsSkill();
};

class DualWieldSkill : public GeneralSkill
{
  public:
    DualWieldSkill();
};

class DungeoneeringSkill : public GeneralSkill
{
  public:
    DungeoneeringSkill();
};

class EscapeSkill : public GeneralSkill
{
  public:
    EscapeSkill();
};

class FishingSkill : public GeneralSkill
{
  public:
    FishingSkill();
};

class FletcherySkill : public GeneralSkill
{
  public:
    FletcherySkill();
};

class ForagingSkill : public GeneralSkill
{
  public:
    ForagingSkill();
};

class ForestLoreSkill : public GeneralSkill
{
  public:
    ForestLoreSkill();
};

class HerbalismSkill : public GeneralSkill
{
  public:
    HerbalismSkill();
};

class HidingSkill : public GeneralSkill
{
  public:
    HidingSkill();
};

class HuntingSkill : public GeneralSkill
{
  public:
    HuntingSkill();
};

class IntimidationSkill : public GeneralSkill
{
  public:
    IntimidationSkill();
};

class JewelerSkill : public GeneralSkill
{
  public:
    JewelerSkill();
};

class JumpingSkill : public GeneralSkill
{
  public:
    JumpingSkill();
};

class LeadershipSkill : public GeneralSkill
{
  public:
    LeadershipSkill();
};

class LiteracySkill : public GeneralSkill
{
  public:
    LiteracySkill();
};

class LoreSkill : public GeneralSkill
{
  public:
    LoreSkill();
};

class MagicGeneralSkill : public GeneralSkill
{
  public:
    MagicGeneralSkill();

    virtual void set_threshold_for_value(const int skill_value);
};

class MarshLoreSkill : public GeneralSkill
{
  public:
    MarshLoreSkill();
};

class MedicineSkill : public GeneralSkill
{
  public:
    MedicineSkill();
};

class MountainLoreSkill : public GeneralSkill
{
  public:
    MountainLoreSkill();
};

class MountaineeringSkill : public GeneralSkill
{
  public:
    MountaineeringSkill();
};

class MusicSkill : public GeneralSkill
{
  public:
    MusicSkill();
};

class NightSightSkill : public GeneralSkill
{
  public:
    NightSightSkill();
};

class OceanographySkill : public GeneralSkill
{
  public:
    OceanographySkill();
};

class PapercraftSkill : public GeneralSkill
{
  public:
    PapercraftSkill();
};

class ReligionSkill : public GeneralSkill
{
  public:
    ReligionSkill();
};

class ScribingSkill : public GeneralSkill
{
  public:
    ScribingSkill();
};

class SkinningSkill : public GeneralSkill
{
  public:
    SkinningSkill();
};

class SmithingSkill : public GeneralSkill
{
  public:
    SmithingSkill();
};

class SpelunkingSkill : public GeneralSkill
{
  public:
    SpelunkingSkill();
};

class StealthSkill : public GeneralSkill
{
  public:
    StealthSkill();
};

class SwimmingSkill : public GeneralSkill
{
  public:
    SwimmingSkill();
};

class TanningSkill : public GeneralSkill
{
  public:
    TanningSkill();
};

class ThieverySkill : public GeneralSkill
{
  public:
    ThieverySkill();
};

class WeavingSkill : public GeneralSkill
{
  public:
    WeavingSkill();
};

// WEAPON SKILLS (MELEE)

class AxesSkill : public WeaponSkill
{
  public:
    AxesSkill();
};

class ShortBladesSkill : public WeaponSkill
{
  public:
    ShortBladesSkill();
};

class LongBladesSkill : public WeaponSkill
{
  public:
    LongBladesSkill();
};

class BludgeonsSkill : public WeaponSkill
{
  public:
    BludgeonsSkill();
};

class DaggersSkill : public WeaponSkill
{
  public:
    DaggersSkill();
};

class RodsAndStavesSkill : public WeaponSkill
{
  public:
    RodsAndStavesSkill();
};

class SpearsSkill : public WeaponSkill
{
  public:
    SpearsSkill();
};

class UnarmedSkill : public WeaponSkill
{
  public:
    UnarmedSkill();
};

class WhipsSkill : public WeaponSkill
{
  public:
    WhipsSkill();
};

// WEAPON SKILLS (RANGED)

class ThrownAxesSkill : public RangedWeaponSkill
{
  public:
    ThrownAxesSkill();
};

class ThrownBladesSkill : public RangedWeaponSkill
{
  public:
    ThrownBladesSkill();
};

class ThrownBludgeonsSkill : public RangedWeaponSkill
{
  public:
    ThrownBludgeonsSkill();
};

class BowsSkill : public RangedWeaponSkill
{
  public:
    BowsSkill();
};

class CrossbowsSkill : public RangedWeaponSkill
{
  public:
    CrossbowsSkill();
};

class ThrownDaggersSkill : public RangedWeaponSkill
{
  public:
    ThrownDaggersSkill();
};

class RocksSkill : public RangedWeaponSkill
{
  public:
    RocksSkill();
};

class SlingsSkill : public RangedWeaponSkill
{
  public:
    SlingsSkill();
};

class ThrownSpearsSkill : public RangedWeaponSkill
{
  public:
    ThrownSpearsSkill();
};

// MAGICAL SKILLS

class ArcaneMagicSkill : public MagicSkill
{
  public:
    ArcaneMagicSkill();
};

class DivineMagicSkill : public MagicSkill
{
  public:
    DivineMagicSkill();
};

class MysticMagicSkill : public MagicSkill
{
  public:
    MysticMagicSkill();
};

class PrimordialMagicSkill : public MagicSkill
{
  public:
    PrimordialMagicSkill();
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

    void set_skill(const SkillType& skill_name, const Skill& skill);
    Skill get_skill(const SkillType& st) const;

    std::string str() const;
    
    std::map<SkillType, Skill>& get_raw_skills();

  protected:
    void initialize_skills();

    void initialize_general_skills();
    void initialize_melee_skills();
    void initialize_ranged_skills();
    void initialize_magic_skills();

    std::map<SkillType, Skill> skills;
};

