#pragma once
#include <memory>
#include "DamageTypes.hpp"
#include "Dice.hpp"
#include "StatusAilments.hpp"

class Damage;

class Damage : public Dice
{
  public:
    explicit Damage();
    explicit Damage(const uint dice, const uint sides, const int mod, const DamageType dtype, const bool chaos, const bool piercing, const int ebonus, const StatusAilments& sa);
    Damage(const Damage& d);
    Damage&  operator= (const Damage& d);
    bool     operator==(const Damage& d) const;
    
    ~Damage();

    void set_damage_type(const DamageType new_damage_type);
    DamageType get_damage_type() const;

    void set_chaotic(const bool new_chaotic);
    bool get_chaotic() const;

    void set_piercing(const bool new_piercing);
    bool get_piercing() const;

    void set_effect_bonus(const int new_bonus);
    int get_effect_bonus() const;

    void set_status_ailments(const StatusAilments& new_ailments);
    StatusAilments get_status_ailments() const;

    // Does the damage or any of the additional damages contain
    // a particular damage type?
    bool contains(const DamageType dt) const;

    // Check to see if the damage is always zero - this is used for
    // effect spells with no damage component (blindness, etc).
    bool is_always_zero() const;
    
    // Additional damage is used for things like "1d6+2d4".  This is relatively rare,
    // and likely will only be used for ranged combat, where the damage is a fuction
    // of both the ranged weapon and the missile.
    void set_additional_damage(std::shared_ptr<Damage> new_additional_damage);
    bool has_additional_damage() const;
    std::shared_ptr<Damage> get_additional_damage() const;
    
    std::string str() const;
    
    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    bool chaotic;
    bool piercing;
    DamageType damage_type;
    int effect_bonus;
    StatusAilments status_ailments;

    std::shared_ptr<Damage> additional_damage;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using DamagePtr = std::shared_ptr<Damage>;
