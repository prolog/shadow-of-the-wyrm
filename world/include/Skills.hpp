#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "ISerializable.hpp"
#include "SkillTypes.hpp"
#include "StringTable.hpp"

// Abstract class - subclasses GeneralSkill, WeaponSkill, MagicSkill
// implement it.
class Skill : public ISerializable
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

    bool is_learned() const;
    virtual bool can_train_from_unlearned() const;
    
    virtual void set_marks(const int new_marks);
    virtual int  get_marks() const;
    virtual void increment_marks();

    virtual void set_threshold(const int new_threshold);
    virtual void set_threshold_for_value(const int skill_value);
    virtual int  get_threshold() const;
    virtual float get_threshold_multiplier() const;

    virtual SkillCategory get_category() const;

    virtual void set_skill_name_sid(const std::string& new_skill_name_sid);
    virtual std::string get_skill_name_sid() const;
    
    virtual void set_skill_increment_message_sid(const std::string& new_skill_increment_message_sid);
    virtual std::string get_skill_increment_message_sid() const;

    std::string str() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

    virtual Skill* clone() = 0;

  protected:
    int value;
    int marks;
    int threshold;
    SkillCategory category;
    std::string skill_name_sid;
    std::string skill_increment_message_sid;

  private:
    ClassIdentifier internal_class_identifier() const = 0;
};

class GeneralSkill : public Skill
{
  public:
    GeneralSkill();
};

class WeaponSkill : public Skill
{
  public:
    WeaponSkill();

    float get_threshold_multiplier() const;
    bool can_train_from_unlearned() const;
};

class RangedWeaponSkill : public Skill
{
  public:
    RangedWeaponSkill();

    bool can_train_from_unlearned() const;
};

class MagicSkill : public Skill
{
  public:
    MagicSkill();
};

// Individual, concrete skills
class ArcherySkill : public GeneralSkill
{
  public:
    ArcherySkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class AwarenessSkill : public GeneralSkill
{
  public:
    AwarenessSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BargainingSkill : public GeneralSkill
{
  public:
    BargainingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BeastmasterySkill : public GeneralSkill
{
  public:
    BeastmasterySkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BlindFightingSkill : public GeneralSkill
{
  public:
    BlindFightingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BoatingSkill : public GeneralSkill
{
  public:
    BoatingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BowyerSkill : public GeneralSkill
{
  public:
    BowyerSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BrewingSkill : public GeneralSkill
{
  public:
    BrewingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class CantripsSkill : public GeneralSkill
{
  public:
    CantripsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class CarryingSkill : public GeneralSkill
{
  public:
    CarryingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class CombatSkill : public GeneralSkill
{
  public:
    CombatSkill();
    
    float get_threshold_multiplier() const;

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class CraftingSkill : public GeneralSkill
{
  public:
    CraftingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class DesertLoreSkill : public GeneralSkill
{
  public:
    DesertLoreSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class DetectionSkill : public GeneralSkill
{
  public:
    DetectionSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class DisarmTrapsSkill : public GeneralSkill
{
  public:
    DisarmTrapsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class DualWieldSkill : public GeneralSkill
{
  public:
    DualWieldSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class DungeoneeringSkill : public GeneralSkill
{
  public:
    DungeoneeringSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class EscapeSkill : public GeneralSkill
{
  public:
    EscapeSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class FishingSkill : public GeneralSkill
{
  public:
    FishingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class FletcherySkill : public GeneralSkill
{
  public:
    FletcherySkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ForagingSkill : public GeneralSkill
{
  public:
    ForagingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ForestLoreSkill : public GeneralSkill
{
  public:
    ForestLoreSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class HerbalismSkill : public GeneralSkill
{
  public:
    HerbalismSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class HidingSkill : public GeneralSkill
{
  public:
    HidingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class HuntingSkill : public GeneralSkill
{
  public:
    HuntingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class IntimidationSkill : public GeneralSkill
{
  public:
    IntimidationSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class JewelerSkill : public GeneralSkill
{
  public:
    JewelerSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class JumpingSkill : public GeneralSkill
{
  public:
    JumpingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class LeadershipSkill : public GeneralSkill
{
  public:
    LeadershipSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class LiteracySkill : public GeneralSkill
{
  public:
    LiteracySkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class LoreSkill : public GeneralSkill
{
  public:
    LoreSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class MagicGeneralSkill : public GeneralSkill
{
  public:
    MagicGeneralSkill();
    
    float get_threshold_multiplier() const;

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class MarshLoreSkill : public GeneralSkill
{
  public:
    MarshLoreSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class MedicineSkill : public GeneralSkill
{
  public:
    MedicineSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class MountainLoreSkill : public GeneralSkill
{
  public:
    MountainLoreSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class MountaineeringSkill : public GeneralSkill
{
  public:
    MountaineeringSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class MusicSkill : public GeneralSkill
{
  public:
    MusicSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class NightSightSkill : public GeneralSkill
{
  public:
    NightSightSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class OceanographySkill : public GeneralSkill
{
  public:
    OceanographySkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class PapercraftSkill : public GeneralSkill
{
  public:
    PapercraftSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ReligionSkill : public GeneralSkill
{
  public:
    ReligionSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ScribingSkill : public GeneralSkill
{
  public:
    ScribingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class SkinningSkill : public GeneralSkill
{
  public:
    SkinningSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class SmithingSkill : public GeneralSkill
{
  public:
    SmithingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class SpelunkingSkill : public GeneralSkill
{
  public:
    SpelunkingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class StealthSkill : public GeneralSkill
{
  public:
    StealthSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class SwimmingSkill : public GeneralSkill
{
  public:
    SwimmingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class TanningSkill : public GeneralSkill
{
  public:
    TanningSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ThieverySkill : public GeneralSkill
{
  public:
    ThieverySkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class WeavingSkill : public GeneralSkill
{
  public:
    WeavingSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

// WEAPON SKILLS (MELEE)

class AxesSkill : public WeaponSkill
{
  public:
    AxesSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ShortBladesSkill : public WeaponSkill
{
  public:
    ShortBladesSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class LongBladesSkill : public WeaponSkill
{
  public:
    LongBladesSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BludgeonsSkill : public WeaponSkill
{
  public:
    BludgeonsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class DaggersSkill : public WeaponSkill
{
  public:
    DaggersSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class RodsAndStavesSkill : public WeaponSkill
{
  public:
    RodsAndStavesSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class SpearsSkill : public WeaponSkill
{
  public:
    SpearsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class UnarmedSkill : public WeaponSkill
{
  public:
    UnarmedSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class WhipsSkill : public WeaponSkill
{
  public:
    WhipsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ExoticMeleeSkill : public WeaponSkill
{
  public:
    ExoticMeleeSkill();

    float get_threshold_multiplier() const;

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

// WEAPON SKILLS (RANGED)

class ThrownAxesSkill : public RangedWeaponSkill
{
  public:
    ThrownAxesSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ThrownBladesSkill : public RangedWeaponSkill
{
  public:
    ThrownBladesSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ThrownBludgeonsSkill : public RangedWeaponSkill
{
  public:
    ThrownBludgeonsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class BowsSkill : public RangedWeaponSkill
{
  public:
    BowsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class CrossbowsSkill : public RangedWeaponSkill
{
  public:
    CrossbowsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ThrownDaggersSkill : public RangedWeaponSkill
{
  public:
    ThrownDaggersSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class RocksSkill : public RangedWeaponSkill
{
  public:
    RocksSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class SlingsSkill : public RangedWeaponSkill
{
  public:
    SlingsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ThrownSpearsSkill : public RangedWeaponSkill
{
  public:
    ThrownSpearsSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class ExoticRangedSkill : public RangedWeaponSkill
{
  public:
    ExoticRangedSkill();

    float get_threshold_multiplier() const;

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

// MAGICAL SKILLS

class ArcaneMagicSkill : public MagicSkill
{
  public:
    ArcaneMagicSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class DivineMagicSkill : public MagicSkill
{
  public:
    DivineMagicSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class MysticMagicSkill : public MagicSkill
{
  public:
    MysticMagicSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class PrimordialMagicSkill : public MagicSkill
{
  public:
    PrimordialMagicSkill();

    virtual Skill* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

// Classes aggregating skills

typedef boost::shared_ptr<Skill> SkillPtr;
typedef std::map<SkillType, SkillPtr> SkillMap;
typedef std::map<SkillType, SkillPtr>* SkillMapPtr;

typedef std::map<SkillType, SkillPtr> RawSkillMap;

class Skills : public ISerializable
{
  public:
    Skills();
    Skills(const Skills& skills);
    Skills& operator=(const Skills& skills);

    void set_value(const SkillType skill_name, const unsigned int new_value);
    void mark(const SkillType skill_name);

    int get_value(const SkillType& skill_name) const;
    
    void set_skill(const SkillType& skill_name, SkillPtr skill);
    SkillPtr get_skill(const SkillType& st) const;

    std::string str() const;
    
    RawSkillMap& get_raw_skills();

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    void initialize_skills();

    void initialize_general_skills();
    void initialize_melee_skills();
    void initialize_ranged_skills();
    void initialize_magic_skills();

    RawSkillMap skills;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

