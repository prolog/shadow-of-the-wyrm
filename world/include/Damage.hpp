#pragma once
#include "DamageTypes.hpp"

class Damage
{
  public:
    Damage();
    ~Damage();

    void set_num_dice(const int new_num_dice);
    int get_num_dice() const;

    void set_dice_sides(const int new_dice_sides);
    int get_dice_sides() const;

    void set_modifier(const int new_modifier);
    int get_modifier() const;

    void set_damage_type(const DamageType new_damage_type);
    DamageType get_damage_type() const;
    
    // Convert to a string (for UI use, etc)
    std::string str() const;

  protected:
    int num_dice;
    int dice_sides;
    int modifier;
    DamageType damage_type;
};
