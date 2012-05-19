#pragma once
#include "DamageTypes.hpp"
#include "Dice.hpp"

class Damage : public Dice
{
  public:
    Damage();
    Damage(const uint dice, const uint sides, const int mod, const DamageType dtype);
    ~Damage();

    void set_damage_type(const DamageType new_damage_type);
    DamageType get_damage_type() const;
    
  protected:
    DamageType damage_type;
};
