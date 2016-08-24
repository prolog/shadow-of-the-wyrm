#pragma once
#include <map>
#include <string>
#include <memory>
#include "ISerializable.hpp"
#include "Marks.hpp"
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
    bool operator==(const Skill& skill) const;

    void initialize();

    virtual void set_value(const int new_value);
    virtual int  get_value() const;
    virtual void increment_value();

    bool is_learned() const;
    virtual bool can_train_from_unlearned() const;
    
    virtual void set_marks(const Marks& marks);
    virtual Marks get_marks() const;
    virtual Marks& get_marks_ref();

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

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Skill* clone() = 0;

  protected:
    Marks marks;
    int value;
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

    float get_threshold_multiplier() const override;
    bool can_train_from_unlearned() const override;
};

class RangedWeaponSkill : public Skill
{
  public:
    RangedWeaponSkill();

    bool can_train_from_unlearned() const override;
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

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class AwarenessSkill : public GeneralSkill
{
  public:
    AwarenessSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BargainingSkill : public GeneralSkill
{
  public:
    BargainingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BeastmasterySkill : public GeneralSkill
{
  public:
    BeastmasterySkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BlindFightingSkill : public GeneralSkill
{
  public:
    BlindFightingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BoatingSkill : public GeneralSkill
{
  public:
    BoatingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BowyerSkill : public GeneralSkill
{
  public:
    BowyerSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BrewingSkill : public GeneralSkill
{
  public:
    BrewingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class CantripsSkill : public GeneralSkill
{
  public:
    CantripsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class CarryingSkill : public GeneralSkill
{
  public:
    CarryingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class CombatSkill : public GeneralSkill
{
  public:
    CombatSkill();
    
    float get_threshold_multiplier() const override;

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class CraftingSkill : public GeneralSkill
{
  public:
    CraftingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class DesertLoreSkill : public GeneralSkill
{
  public:
    DesertLoreSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class DetectionSkill : public GeneralSkill
{
  public:
    DetectionSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class DisarmTrapsSkill : public GeneralSkill
{
  public:
    DisarmTrapsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class DualWieldSkill : public GeneralSkill
{
  public:
    DualWieldSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class DungeoneeringSkill : public GeneralSkill
{
  public:
    DungeoneeringSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class EscapeSkill : public GeneralSkill
{
  public:
    EscapeSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class FishingSkill : public GeneralSkill
{
  public:
    FishingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class FletcherySkill : public GeneralSkill
{
  public:
    FletcherySkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ForagingSkill : public GeneralSkill
{
  public:
    ForagingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ForestLoreSkill : public GeneralSkill
{
  public:
    ForestLoreSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HerbalismSkill : public GeneralSkill
{
  public:
    HerbalismSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HidingSkill : public GeneralSkill
{
  public:
    HidingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HuntingSkill : public GeneralSkill
{
  public:
    HuntingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class IntimidationSkill : public GeneralSkill
{
  public:
    IntimidationSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class JewelerSkill : public GeneralSkill
{
  public:
    JewelerSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class JumpingSkill : public GeneralSkill
{
  public:
    JumpingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class LeadershipSkill : public GeneralSkill
{
  public:
    LeadershipSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class LiteracySkill : public GeneralSkill
{
  public:
    LiteracySkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class LoreSkill : public GeneralSkill
{
  public:
    LoreSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class MagicGeneralSkill : public GeneralSkill
{
  public:
    MagicGeneralSkill();
    
    float get_threshold_multiplier() const override;

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class MarshLoreSkill : public GeneralSkill
{
  public:
    MarshLoreSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class MedicineSkill : public GeneralSkill
{
  public:
    MedicineSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class MountainLoreSkill : public GeneralSkill
{
  public:
    MountainLoreSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class MountaineeringSkill : public GeneralSkill
{
  public:
    MountaineeringSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class MusicSkill : public GeneralSkill
{
  public:
    MusicSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class NightSightSkill : public GeneralSkill
{
  public:
    NightSightSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class OceanographySkill : public GeneralSkill
{
  public:
    OceanographySkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PapercraftSkill : public GeneralSkill
{
  public:
    PapercraftSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ReligionSkill : public GeneralSkill
{
  public:
    ReligionSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ScribingSkill : public GeneralSkill
{
  public:
    ScribingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SkinningSkill : public GeneralSkill
{
  public:
    SkinningSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SmithingSkill : public GeneralSkill
{
  public:
    SmithingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SpelunkingSkill : public GeneralSkill
{
  public:
    SpelunkingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class StealthSkill : public GeneralSkill
{
  public:
    StealthSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SwimmingSkill : public GeneralSkill
{
  public:
    SwimmingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class TanningSkill : public GeneralSkill
{
  public:
    TanningSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ThieverySkill : public GeneralSkill
{
  public:
    ThieverySkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class WeavingSkill : public GeneralSkill
{
  public:
    WeavingSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// WEAPON SKILLS (MELEE)

class AxesSkill : public WeaponSkill
{
  public:
    AxesSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ShortBladesSkill : public WeaponSkill
{
  public:
    ShortBladesSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class LongBladesSkill : public WeaponSkill
{
  public:
    LongBladesSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BludgeonsSkill : public WeaponSkill
{
  public:
    BludgeonsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class DaggersSkill : public WeaponSkill
{
  public:
    DaggersSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class RodsAndStavesSkill : public WeaponSkill
{
  public:
    RodsAndStavesSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SpearsSkill : public WeaponSkill
{
  public:
    SpearsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class UnarmedSkill : public WeaponSkill
{
  public:
    UnarmedSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class WhipsSkill : public WeaponSkill
{
  public:
    WhipsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ExoticMeleeSkill : public WeaponSkill
{
  public:
    ExoticMeleeSkill();

    float get_threshold_multiplier() const override;

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// WEAPON SKILLS (RANGED)

class ThrownAxesSkill : public RangedWeaponSkill
{
  public:
    ThrownAxesSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ThrownBladesSkill : public RangedWeaponSkill
{
  public:
    ThrownBladesSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ThrownBludgeonsSkill : public RangedWeaponSkill
{
  public:
    ThrownBludgeonsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class BowsSkill : public RangedWeaponSkill
{
  public:
    BowsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class CrossbowsSkill : public RangedWeaponSkill
{
  public:
    CrossbowsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ThrownDaggersSkill : public RangedWeaponSkill
{
  public:
    ThrownDaggersSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class RocksSkill : public RangedWeaponSkill
{
  public:
    RocksSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SlingsSkill : public RangedWeaponSkill
{
  public:
    SlingsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ThrownSpearsSkill : public RangedWeaponSkill
{
  public:
    ThrownSpearsSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ExoticRangedSkill : public RangedWeaponSkill
{
  public:
    ExoticRangedSkill();

    float get_threshold_multiplier() const override;

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// MAGICAL SKILLS

class ArcaneMagicSkill : public MagicSkill
{
  public:
    ArcaneMagicSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class DivineMagicSkill : public MagicSkill
{
  public:
    DivineMagicSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class MysticMagicSkill : public MagicSkill
{
  public:
    MysticMagicSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PrimordialMagicSkill : public MagicSkill
{
  public:
    PrimordialMagicSkill();

    virtual Skill* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// Classes aggregating skills

using SkillPtr = std::shared_ptr<Skill>;
using SkillMap = std::map<SkillType, SkillPtr>;
using SkillMapPtr = std::map<SkillType, SkillPtr>*;

using RawSkillMap = std::map<SkillType, SkillPtr>;

class Skills : public ISerializable
{
  public:
    Skills();
    Skills(const Skills& skills);
    Skills& operator=(const Skills& skills);
    virtual bool operator==(const Skills& skills) const;

    // For each skill in skills_to_increment, update the values in the current
    // object by the appropriate amount.
    void increment_skills(const Skills& skills_to_increment);

    void set_value(const SkillType skill_name, const unsigned int new_value);
    void mark(const SkillType skill_name, const bool override_default = false /* whether to mark regardless of whether the skill indicates it can be trained from unlearned */);

    int get_value(const SkillType& skill_name) const;
    int get_value_incr_marks(const SkillType& skill_name);
    
    void set_skill(const SkillType& skill_name, SkillPtr skill);
    void set_all_to(const int val);
    SkillPtr get_skill(const SkillType& st) const;

    bool has_trainable_skill() const;
    std::string str() const;
    
    RawSkillMap& get_raw_skills_ref();
    RawSkillMap get_raw_skills() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    static const int MAX_SKILL_VALUE;

  protected:
    void initialize_skills();

    void initialize_general_skills();
    void initialize_melee_skills();
    void initialize_ranged_skills();
    void initialize_magic_skills();

    RawSkillMap skills;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

