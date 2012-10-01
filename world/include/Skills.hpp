#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include "SkillTypes.hpp"
#include "StringTable.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

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

  protected:
    int value;
    int marks;
    int threshold;
    SkillCategory category;
    std::string skill_name_sid;
    std::string skill_increment_message_sid;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & value & marks & threshold & category & skill_name_sid & skill_increment_message_sid;
    }
};

class GeneralSkill : public Skill
{
  public:
    GeneralSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class WeaponSkill : public Skill
{
  public:
    WeaponSkill();

    float get_threshold_multiplier() const;
    bool can_train_from_unlearned() const;

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class RangedWeaponSkill : public Skill
{
  public:
    RangedWeaponSkill();

    bool can_train_from_unlearned() const;

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MagicSkill : public Skill
{
  public:
    MagicSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

// Individual skills
class ArcherySkill : public GeneralSkill
{
  public:
    ArcherySkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class AwarenessSkill : public GeneralSkill
{
  public:
    AwarenessSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BargainingSkill : public GeneralSkill
{
  public:
    BargainingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BeastmasterySkill : public GeneralSkill
{
  public:
    BeastmasterySkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BlindFightingSkill : public GeneralSkill
{
  public:
    BlindFightingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BoatingSkill : public GeneralSkill
{
  public:
    BoatingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BowyerSkill : public GeneralSkill
{
  public:
    BowyerSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BrewingSkill : public GeneralSkill
{
  public:
    BrewingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class CantripsSkill : public GeneralSkill
{
  public:
    CantripsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class CarryingSkill : public GeneralSkill
{
  public:
    CarryingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class CombatSkill : public GeneralSkill
{
  public:
    CombatSkill();
    
    float get_threshold_multiplier() const;

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class CraftingSkill : public GeneralSkill
{
  public:
    CraftingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class DesertLoreSkill : public GeneralSkill
{
  public:
    DesertLoreSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class DetectionSkill : public GeneralSkill
{
  public:
    DetectionSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class DisarmTrapsSkill : public GeneralSkill
{
  public:
    DisarmTrapsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class DualWieldSkill : public GeneralSkill
{
  public:
    DualWieldSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class DungeoneeringSkill : public GeneralSkill
{
  public:
    DungeoneeringSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class EscapeSkill : public GeneralSkill
{
  public:
    EscapeSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class FishingSkill : public GeneralSkill
{
  public:
    FishingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class FletcherySkill : public GeneralSkill
{
  public:
    FletcherySkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ForagingSkill : public GeneralSkill
{
  public:
    ForagingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ForestLoreSkill : public GeneralSkill
{
  public:
    ForestLoreSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class HerbalismSkill : public GeneralSkill
{
  public:
    HerbalismSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class HidingSkill : public GeneralSkill
{
  public:
    HidingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class HuntingSkill : public GeneralSkill
{
  public:
    HuntingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class IntimidationSkill : public GeneralSkill
{
  public:
    IntimidationSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class JewelerSkill : public GeneralSkill
{
  public:
    JewelerSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class JumpingSkill : public GeneralSkill
{
  public:
    JumpingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class LeadershipSkill : public GeneralSkill
{
  public:
    LeadershipSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class LiteracySkill : public GeneralSkill
{
  public:
    LiteracySkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class LoreSkill : public GeneralSkill
{
  public:
    LoreSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MagicGeneralSkill : public GeneralSkill
{
  public:
    MagicGeneralSkill();
    
    float get_threshold_multiplier() const;

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MarshLoreSkill : public GeneralSkill
{
  public:
    MarshLoreSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MedicineSkill : public GeneralSkill
{
  public:
    MedicineSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MountainLoreSkill : public GeneralSkill
{
  public:
    MountainLoreSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MountaineeringSkill : public GeneralSkill
{
  public:
    MountaineeringSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MusicSkill : public GeneralSkill
{
  public:
    MusicSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class NightSightSkill : public GeneralSkill
{
  public:
    NightSightSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class OceanographySkill : public GeneralSkill
{
  public:
    OceanographySkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class PapercraftSkill : public GeneralSkill
{
  public:
    PapercraftSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ReligionSkill : public GeneralSkill
{
  public:
    ReligionSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ScribingSkill : public GeneralSkill
{
  public:
    ScribingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class SkinningSkill : public GeneralSkill
{
  public:
    SkinningSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class SmithingSkill : public GeneralSkill
{
  public:
    SmithingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class SpelunkingSkill : public GeneralSkill
{
  public:
    SpelunkingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class StealthSkill : public GeneralSkill
{
  public:
    StealthSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class SwimmingSkill : public GeneralSkill
{
  public:
    SwimmingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class TanningSkill : public GeneralSkill
{
  public:
    TanningSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ThieverySkill : public GeneralSkill
{
  public:
    ThieverySkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class WeavingSkill : public GeneralSkill
{
  public:
    WeavingSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

// WEAPON SKILLS (MELEE)

class AxesSkill : public WeaponSkill
{
  public:
    AxesSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ShortBladesSkill : public WeaponSkill
{
  public:
    ShortBladesSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class LongBladesSkill : public WeaponSkill
{
  public:
    LongBladesSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BludgeonsSkill : public WeaponSkill
{
  public:
    BludgeonsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class DaggersSkill : public WeaponSkill
{
  public:
    DaggersSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class RodsAndStavesSkill : public WeaponSkill
{
  public:
    RodsAndStavesSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class SpearsSkill : public WeaponSkill
{
  public:
    SpearsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class UnarmedSkill : public WeaponSkill
{
  public:
    UnarmedSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class WhipsSkill : public WeaponSkill
{
  public:
    WhipsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ExoticMeleeSkill : public WeaponSkill
{
  public:
    ExoticMeleeSkill();

    float get_threshold_multiplier() const;

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

// WEAPON SKILLS (RANGED)

class ThrownAxesSkill : public RangedWeaponSkill
{
  public:
    ThrownAxesSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ThrownBladesSkill : public RangedWeaponSkill
{
  public:
    ThrownBladesSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ThrownBludgeonsSkill : public RangedWeaponSkill
{
  public:
    ThrownBludgeonsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class BowsSkill : public RangedWeaponSkill
{
  public:
    BowsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class CrossbowsSkill : public RangedWeaponSkill
{
  public:
    CrossbowsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ThrownDaggersSkill : public RangedWeaponSkill
{
  public:
    ThrownDaggersSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class RocksSkill : public RangedWeaponSkill
{
  public:
    RocksSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class SlingsSkill : public RangedWeaponSkill
{
  public:
    SlingsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ThrownSpearsSkill : public RangedWeaponSkill
{
  public:
    ThrownSpearsSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class ExoticRangedSkill : public RangedWeaponSkill
{
  public:
    ExoticRangedSkill();

    float get_threshold_multiplier() const;

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

// MAGICAL SKILLS

class ArcaneMagicSkill : public MagicSkill
{
  public:
    ArcaneMagicSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class DivineMagicSkill : public MagicSkill
{
  public:
    DivineMagicSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class MysticMagicSkill : public MagicSkill
{
  public:
    MysticMagicSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

class PrimordialMagicSkill : public MagicSkill
{
  public:
    PrimordialMagicSkill();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Skill>(*this);
    }
};

// Classes aggregating skills

typedef boost::shared_ptr<Skill> SkillPtr;
typedef std::map<SkillType, SkillPtr> SkillMap;
typedef std::map<SkillType, SkillPtr>* SkillMapPtr;

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
    
    void set_skill(const SkillType& skill_name, SkillPtr skill);
    SkillPtr get_skill(const SkillType& st) const;

    std::string str() const;
    
    std::map<SkillType, SkillPtr>& get_raw_skills();

  protected:
    void initialize_skills();

    void initialize_general_skills();
    void initialize_melee_skills();
    void initialize_ranged_skills();
    void initialize_magic_skills();

    std::map<SkillType, SkillPtr> skills;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & skills;
    }
};

