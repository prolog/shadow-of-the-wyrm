#pragma once
#include <map>
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
    explicit Damage(const uint dice, const uint sides, const int mod, const DamageType dtype, const std::vector<std::string>& rslays, const bool chaos, const bool vorp, const bool drain, const bool ether, const bool piercing, const bool incorporeal, const bool scything, const bool explosive, const int ebonus, const StatusAilments& sa);
    Damage(const Damage& d);
    Damage&  operator= (const Damage& d);
    bool     operator==(const Damage& d) const;
    
    ~Damage();

    void set_damage_type(const DamageType new_damage_type);
    DamageType get_damage_type() const;
    DamageCategory get_damage_category() const;

    virtual void set_slays_races(const std::vector<std::string>& new_slay_races);
    std::vector<std::string> get_slays_races() const;

    void set_damage_flags(const std::map<DamageFlagType, bool>& dflags);
    void set_damage_flag(const DamageFlagType df, const bool value);
    bool get_damage_flag(const DamageFlagType df) const;
    std::vector<DamageFlagType> get_damage_flags_by_value(const bool val) const;

    void set_chaotic(const bool new_chaotic);
    bool get_chaotic() const;

    void set_vorpal(const bool new_vorpal);
    bool get_vorpal() const;

    void set_draining(const bool new_draining);
    bool get_draining() const;

    void set_ethereal(const bool new_ethereal);
    bool get_ethereal() const;

    void set_piercing(const bool new_piercing);
    bool get_piercing() const;

    void set_incorporeal(const bool new_incorporeal);
    bool get_incorporeal() const;

    void set_scything(const bool new_scything);
    bool get_scything() const;

    void set_explosive(const bool new_explosive);
    bool get_explosive() const;

    void set_effect_bonus(const int new_bonus);
    int get_effect_bonus() const;

    void set_status_ailments(const StatusAilments& new_ailments);
    StatusAilments get_status_ailments() const;

    // Check to see if the damage is always zero - this is used for
    // effect spells with no damage component (blindness, etc).
    bool is_always_zero() const;

    std::string str() const;
    
    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    bool chaotic;
    bool vorpal; // chance to insta-kill
    bool draining; // chance to increase damage dealer's HP
    bool ethereal; // Ditto, but AP.
    bool piercing; // ignore soak
    bool incorporeal; // only a quarter of the soak is used
    bool scything; // damage may affect other targets nearby the attacker
    bool explosive; // additional damage to the target and creatures adjacent to it

    DamageType damage_type;
    std::vector<std::string> slays_races;
    int effect_bonus;
    StatusAilments status_ailments;

    std::shared_ptr<Damage> additional_damage;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using DamagePtr = std::shared_ptr<Damage>;
