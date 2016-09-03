#pragma once
#include <memory>
#include <string>
#include <vector>
#include "DamageTypes.hpp"
#include "Dice.hpp"
#include "StatusAilments.hpp"

class Damage;

class Damage : public Dice
{
  public:
    explicit Damage();
    explicit Damage(const uint dice, const uint sides, const int mod, const DamageType dtype, const std::vector<std::string>& rslays, const bool chaos, const bool vorp, const bool piercing, const bool incorporeal, const int ebonus, const StatusAilments& sa);
    Damage(const Damage& d);
    Damage&  operator= (const Damage& d);
    bool     operator==(const Damage& d) const;
    
    ~Damage();

    void set_damage_type(const DamageType new_damage_type);
    DamageType get_damage_type() const;

    virtual void set_slays_races(const std::vector<std::string>& new_slay_races);
    std::vector<std::string> get_slays_races() const;

    void set_chaotic(const bool new_chaotic);
    bool get_chaotic() const;

    void set_vorpal(const bool new_vorpal);
    bool get_vorpal() const;

    void set_piercing(const bool new_piercing);
    bool get_piercing() const;

    void set_incorporeal(const bool new_incorporeal);
    bool get_incorporeal() const;

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
    bool vorpal; // chance to insta-kill
    bool piercing; // ignore soak
    bool incorporeal; // only a quarter of the soak is used
    DamageType damage_type;
    std::vector<std::string> slays_races;
    int effect_bonus;
    StatusAilments status_ailments;

    std::shared_ptr<Damage> additional_damage;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using DamagePtr = std::shared_ptr<Damage>;
