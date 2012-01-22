#pragma once
#include <string>
#include "common.hpp"
#include "DamageTypes.hpp"

class Damage
{
  public:
    Damage();
    ~Damage();

    void set_num_dice(const uint new_num_dice);
    uint get_num_dice() const;

    void set_dice_sides(const uint new_dice_sides);
    uint get_dice_sides() const;

    void set_modifier(const int new_modifier);
    int get_modifier() const;

    void set_damage_type(const DamageType new_damage_type);
    DamageType get_damage_type() const;
    
    // Convert to a string (for UI use, etc)
    std::string str() const;

  protected:
    uint num_dice;
    uint dice_sides;
    int modifier;
    DamageType damage_type;
};
