#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

class Dice : public ISerializable
{
  public:
    Dice();
    Dice(const uint new_num_dice, const uint new_dice_sides, const int modifier);
    virtual ~Dice();
    virtual bool operator==(const Dice& dice) const;

    int max() const;
    
    void set_num_dice(const uint new_num_dice);
    uint get_num_dice() const;

    void set_dice_sides(const uint new_dice_sides);
    uint get_dice_sides() const;

    void set_modifier(const int new_modifier);
    int get_modifier() const;

    // Convert to a string (for UI use, etc)
    std::string str() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    uint num_dice;
    uint dice_sides;
    int modifier;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
