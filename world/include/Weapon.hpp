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
    
    virtual void set_base_to_hit(const int new_base_to_hit);
    virtual int get_base_to_hit() const;
    
    virtual void set_damage(const Damage& new_damage);
    virtual Damage get_damage() const;
    
    virtual void set_trained_skill(const SkillType new_trained_skill);
    SkillType get_trained_skill() const;

  protected:
    int base_to_hit;
    Damage damage;
    SkillType trained_skill;
};

class MeleeWeapon : public Weapon
{
  public:
    MeleeWeapon();
    ~MeleeWeapon();
    
    virtual WeaponStyle get_style() const;
    
  protected:
};

class RangedWeapon : public Weapon
{
  public:
    RangedWeapon();
    ~RangedWeapon();
    
    virtual WeaponStyle get_style() const;
    
  protected:
};

typedef boost::shared_ptr<Weapon> WeaponPtr;
typedef boost::shared_ptr<MeleeWeapon> MeleeWeaponPtr;
typedef boost::shared_ptr<RangedWeapon> RangedWeaponPtr;
