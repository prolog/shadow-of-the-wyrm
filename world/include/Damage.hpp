#pragma once
#include <memory>
#include "DamageTypes.hpp"
#include "Dice.hpp"

class Damage;

class Damage : public Dice
{
  public:
    explicit Damage();
    explicit Damage(const uint dice, const uint sides, const int mod, const DamageType dtype, const bool chaos);
    Damage(const Damage& d);
    Damage&  operator= (const Damage& d);
    bool     operator==(const Damage& d) const;
    
    ~Damage();

    void set_damage_type(const DamageType new_damage_type);
    DamageType get_damage_type() const;

    void set_chaotic(const bool new_chaotic);
    bool get_chaotic() const;
    
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
    DamageType damage_type;
    std::shared_ptr<Damage> additional_damage;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Damage> DamagePtr;
