#pragma once
#include "Damage.hpp"
#include "SkillTypes.hpp"
#include "WeaponTypes.hpp"
#include "Wearable.hpp"

class Weapon : public Wearable
{
  public:
    Weapon();
    
    virtual ItemType get_type() const;
    virtual WeaponStyle get_style() const = 0;
    
    virtual void set_difficulty(const int new_difficulty);
    virtual int get_difficulty() const;
    
    virtual void set_damage(const Damage& new_damage);
    virtual Damage get_damage() const;
    
    virtual void set_trained_skill(const SkillType new_trained_skill);
    SkillType get_trained_skill() const;
    
  protected:
    int difficulty;
    Damage damage;
    SkillType trained_skill;
};

class MeleeWeapon : public Weapon
{
  public:
    MeleeWeapon();
    ~MeleeWeapon();
    
    virtual WeaponStyle get_style() const;    
    virtual Item* clone();
    
  protected:
};

class RangedWeapon : public Weapon
{
  public:
    RangedWeapon();
    ~RangedWeapon();
    
    virtual WeaponStyle get_style() const;
    virtual Item* clone();
    
  protected:
};

typedef boost::shared_ptr<Weapon> WeaponPtr;
typedef boost::shared_ptr<MeleeWeapon> MeleeWeaponPtr;
typedef boost::shared_ptr<RangedWeapon> RangedWeaponPtr;
