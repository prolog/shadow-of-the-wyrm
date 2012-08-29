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
    
    virtual void set_speed(const int new_speed);
    virtual int get_speed() const;
    
    virtual void set_damage(const Damage& new_damage);
    virtual Damage get_damage() const;
    
    virtual void set_trained_skill(const SkillType new_trained_skill);
    SkillType get_trained_skill() const;
    
    virtual void set_trained_ranged_skill(const SkillType new_trained_ranged_skill);
    SkillType get_trained_ranged_skill() const;
    
    virtual void set_requires_ranged_weapon(const bool new_requires_ranged_weapon);
    virtual bool get_requires_ranged_weapon() const;
    
    virtual bool additional_item_attributes_match(boost::shared_ptr<Item> i);
    
  protected:
  
    int difficulty;
    int speed;
    Damage damage;
    SkillType trained_skill;
    SkillType trained_ranged_skill;
    bool requires_ranged_weapon;
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
